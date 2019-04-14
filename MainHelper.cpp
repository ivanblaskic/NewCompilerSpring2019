#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

static list<pair<std::string, int>> init_variables_list;

// which variables are active at the same time
static list<list<std::string>> interference_variables_list;

// information on: how many interferences this var has {use isVar to separate regs from vars} and what are those
	// e.g.		add_0	x_0		x_1		add_1	let_0	add_2
static list<list<std::string>> detailed_interference_list;

// information on: what are the vars interfering with along with its colors
	// e.g.		add_0		x_0	N		x_1	0		add_1 N		let_0 N		add_2 1
	// add_0	--> add_0 2 into vars_assignment_colors_list
	// N		--> not yet assigned
static list<list<std::string>> interfering_colors_list;

// information on: how many colors were used and by which vars
	// 0	x_1		x_5
	// 1	add_2	let_3
	// 2	add_0	let_2
	// 3	x_0
	// 4	let_0
	// 5	add_1
static list<list<std::string>> vars_assignment_colors_list;

// information on how many vars is even used in coloring
static int colors_used;

// assigning registers to colors - have to be initialized
//	e.g.	[0]	"rax"	[1] "rbx"	[2] "rcx"	[3] "rdx"	... which ones we cannot use?
static vector<list<string>> colors_assigned;

// saturation priority queue
	// e.g.		"add_0"		"2"		-->		there is 2 colors that add_0 cannot be (0,1)
static list<pair<string, int>> priority_queue;

// what is moved into what
static list<pair<string, string>> move_list;

static list<pair<std::string, int>> *RegistersX0 = new list<pair<std::string, int>>{
	std::make_pair("rax", 0),
	std::make_pair("rbx", 0),
	std::make_pair("rcx", 0),
	std::make_pair("rdx", 0),
	std::make_pair("rsi", 0),
	std::make_pair("rdi", 0),
	std::make_pair("r8", 0),
	std::make_pair("r9", 0),
	std::make_pair("r10", 0),
	std::make_pair("r11", 0),
	std::make_pair("r12", 0),
	std::make_pair("r13", 0),
	std::make_pair("r14", 0),
	std::make_pair("r15", 0),
	std::make_pair("rsp", 0),
	std::make_pair("rbp", 0)
};

static list<pair<string, int>> colors =	   {(make_pair("rax", 0)),
											(make_pair("rbx", 1)),
											(make_pair("rcx", 2)),
											(make_pair("rdx", 3)),
											(make_pair("r8", 4)),
											(make_pair("r9", 5)),
											(make_pair("r10", 6)),
											(make_pair("r11", 7)),
											(make_pair("r12", 8)),
											(make_pair("r13", 9)),
											(make_pair("r14", 10)),
											(make_pair("r15", 11)),
											(make_pair("rsi", 12)),
											(make_pair("rdi", 13))};



void print_color_graph_x0(list<list<string>> *ptr_printable) {
	bool first = true;
	cout << "\n" << "Printing Detailed Interference List: " << "\n";
	for (list<list<string>>::iterator it2 = ptr_printable->begin(); it2 != ptr_printable->end(); it2++) {
		for (list<string>::iterator it3 = (*it2).begin(); it3 != (*it2).end(); ++it3) {
			if (first) {
				cout << "\n\t" << *it3 << "\t\t";
				first = false;
			}
			else {
				cout << *it3 << "\t";
			}
		}
		first = true;
	}
	cout << "\n\n";
}

void refresh_queue(string name, int color) {
	bool first = true;
	bool erase = false;
	list<list<string>> new_list;
	for (list<list<string>>::iterator it = interfering_colors_list.begin(); it != interfering_colors_list.end(); ++it) {
		for (list<string>::iterator it1 = (*it).begin(); it1 != (*it).end(); ++it1) {
			if (first) {
				if ((*it1) == name) {
					erase = true;
				}
			}
			else if (!(erase)) {
				if ((*it1) == name) {
					*it1 = to_string(color);
				}
			}
			first = false;
		}
		first = true;
		if (!erase) {
			new_list.emplace_back(*it);
		}
		erase = false;
	}
	interfering_colors_list.clear();
	interfering_colors_list = new_list;
}

int main(void) {
	list<string> temp1 ({"add_x_0", "rax" });
	interference_variables_list.emplace_back(temp1);
	list<string> temp2 ({ "add_x_0", "add_x_1" });
	interference_variables_list.emplace_back(temp2);
	list<string> temp3 ({"add_x_0", "rbx", "rax"});
	interference_variables_list.emplace_back(temp3);
	list<string> temp4 ({"rbx", "rcx"});
	interference_variables_list.emplace_back(temp4);

	bool found = false;
	bool first = true;
	int var_cnt = 0;

	// figure out how to sort them into have-colors and don't have-colors if you need - trying w/o
	// compare your idea to Jay's - let's do main
	// see where will you and how write the functions
	// use the patch as an example

	for (list<list<std::string>>::iterator it = interference_variables_list.begin(); it != interference_variables_list.end(); ++it) {
		// emptying the interference list and filling the detailed interference list up 
		// initialization - var_1 0 ...		var_2 0 ...		var_3 0 ...		...
		list<string> temp_list = *it;
		for (list<string>::iterator it1 = temp_list.begin(); it1 != temp_list.end(); it1++) {
			string temp_string = *it1;
			for (list<list<string>>::iterator it2 = detailed_interference_list.begin(); it2 != detailed_interference_list.end(); it2++) {
				for (list<string>::iterator it3 = (*it2).begin(); it3 != (*it2).end(); ++it3) {
					if (((*it3) == (temp_string)) && (first)) {
						found = true;
					}
					first = false;
				}
				first = true;
			}
			if (!(found)) {
				list<string> new_list({ temp_string});
				detailed_interference_list.emplace_back(new_list);
				var_cnt++;
			}
			found = false;
		}
	}

	found = false;
	first = true;
	string curr;

	list<list<string>> temp_result;

	for (list<list<string>>::iterator it = detailed_interference_list.begin(); it != detailed_interference_list.end(); it++) {
		list<string> per_var_list;
		for (list<string>::iterator it1 = (*it).begin(); it1 != (*it).end(); ++it1) {
			if (first) {
				curr = *it1;
				first = false;
				per_var_list.emplace_back(curr);
			}
			for (list<list<std::string>>::iterator it2 = interference_variables_list.begin(); it2 != interference_variables_list.end(); ++it2) {
				list<string> temp_list = *it2;
				for (list<string>::iterator it3 = temp_list.begin(); it3 != temp_list.end(); it3++) {
					if (curr == *it3) {
						found = true;
					}
				}
				if (found) {
					for (list<string>::iterator it4 = temp_list.begin(); it4 != temp_list.end(); it4++) {
						if (curr != *it4) {
							per_var_list.emplace_back(*it4);
						}
					}
					found = false;
				}
			}
		}
		temp_result.emplace_back(per_var_list);
		per_var_list.clear();
		first = true;
	}

	detailed_interference_list.clear();
	detailed_interference_list = temp_result; 

	// information on: what are the vars interfering with along with its colors
	// e.g.		add_0		x_0	N		x_1	0		add_1 N		let_0 N		add_2 1
	// add_0	--> add_0 2 into vars_assignment_colors_list
	// N		--> not yet assigned

	first = true;
	list<string> temp_iteration;
	list<string> temp_input_list;
	list<string> sorted_list;
	bool assigned = false;

	for (list<list<string>>::iterator it = detailed_interference_list.begin(); it != detailed_interference_list.end(); it++) {
		temp_iteration = *it;
		string curr_str;
		string first_str;
		string curr_val = "none";
		for (list<string>::iterator it1 = temp_iteration.begin(); it1 != temp_iteration.end(); ++it1) {
			if (first) {
				temp_input_list.emplace_back(*it1);
				first_str = *it1;
				for (list<pair<string, int>>::iterator it2 = colors.begin(); it2 != colors.end(); it2++) {
					if (first_str == (*it2).first) {
						assigned = true;
					}
				}
			}
			else {
				if (!assigned) {
					curr_str = *it1;
					for (list<pair<string, int>>::iterator it2 = colors.begin(); it2 != colors.end(); it2++) {
						if (curr_str == (*it2).first) {
							curr_val = to_string((*it2).second);
						}
					}
					//temp_input_list.emplace_back(curr_str);
					if (curr_val == "none") {
						sorted_list.emplace_back(curr_str);
					}
					else {
						sorted_list.emplace_back(curr_val);
					}
				}
			}
			first = false;
			curr_val = "none";
		}
		first = true;
		if (!assigned) {
			sorted_list.sort();
			sorted_list.unique();
			for (list<string>::iterator it2 = sorted_list.begin(); it2 != sorted_list.end(); ++it2) {
				temp_input_list.emplace_back(*it2);
			}
			interfering_colors_list.emplace_back(temp_input_list);
		}
		assigned = false;
		temp_input_list.clear();
	}

	print_color_graph_x0(&detailed_interference_list);
	system("Pause");

	print_color_graph_x0(&interfering_colors_list);
	system("Pause");

	refresh_queue("add_x_0", 3);

	print_color_graph_x0(&interfering_colors_list);
	system("Pause");
	
	// going through detailed interference list and initializing coloring list
	// adding registers that need to be interfering with variables in body
	// this is done by adding "rax" together with "0" or "rbx" with "1" in coloring list

	// following initialize priority queue list with var_name and its saturation
	// take the first var, check its neigbours and what it cannot be
	// extra step will be looking at the move graph 
	// then checking if there is var that this one moves into 
	// then seeing what their color is for each
	// now we subtract what we cannot be colors from those 
	// we assign the color if there is any left after subtracting saturation
	// assign the lowest color that it can be to it if move-graph set doesn't work
	// removing this var from priority queue 
	// after this move to don't have colors neighboors jay says - or just to priority queue I say?
	return 0;

}