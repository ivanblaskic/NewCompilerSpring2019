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

// information on how many colors is even available in coloring
static int colors_used = 13;

// assigning registers to colors - have to be initialized
//	e.g.	[0]	"rax"	[1] "rbx"	[2] "rcx"	[3] "rdx"	... which ones we cannot use?
static vector<list<string>> colors_assigned;

// saturation priority queue
	// e.g.		"add_0"		"2"		-->		there is 2 colors that add_0 cannot be (0,1)
static list<pair<string, int>> saturation_queue;

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

int color(string var_name) {
	bool found = false;
	bool first;
	bool nope = false;
	list<string> cannot_be;
	list<string> temp_list;
	for (list<list<string>>::iterator it1 = interfering_colors_list.begin(); it1 != interfering_colors_list.end(); ++it1) {
		first = true;
		for (list<string>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
			if ((first) && (*it2 == var_name)) {
				cannot_be = *it1;
				found = true;
			}
			first = false;
		}
	}
	if (found) {
		for (int i = 0; i < 14; ++i) {
			nope = false;
			for (list<string>::iterator it1 = cannot_be.begin(); it1 != cannot_be.end(); it1++) {
				if (to_string(i) == (*it1)) {
					nope = true;
				}
			}
			if (!(nope)) {
				return i;
			}
		}
	}
	else {
		colors_assigned[0].push_back(var_name);
		return 0;
	}
}

bool isQueueEmpty() {
	int queue_elements = 0;
	for (list<pair<string, int>>::iterator it = saturation_queue.begin(); it != saturation_queue.end(); ++it) {
		queue_elements++;
	}
	if (queue_elements > 0) {
		return false;
	}
	else {
		return true;
	}
}

string get_sat_max() {
	string return_string;
	int temp_max = -1;
	for (list<pair<string, int>>::iterator it = saturation_queue.begin(); it != saturation_queue.end(); it++) {
		if ((*it).second > temp_max) {
			return_string = (*it).first;
		}
	}
	return return_string;
}

void print_queue() {
	cout << "\n" << "Printing Saturation Priority Queue: " << "\n\n";
	for (list<pair<string, int>>::iterator it = saturation_queue.begin(); it != saturation_queue.end(); it++) {
		cout << "\t" << (*it).first << "\t" << (*it).second;
	}
	cout << "\n\n";
}

void print_colors_assigned() {
	cout << "\n" << "Printing Colors Assignment: " << "\n\n";
	for (int i = 0; i < 14; ++i) {
		cout << "\t" << i;
		for (list<string>::iterator it = colors_assigned[i].begin(); it != colors_assigned[i].end(); ++it) {
			cout << "\t" << *it;
		}
		cout << "\n";
	}
	cout << "\n\n";
}

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
	bool erased = false;
	list<list<string>> new_list;
	list<pair<string, int>> temp_queue;
	for (list<list<string>>::iterator it = interfering_colors_list.begin(); it != interfering_colors_list.end(); ++it) {
		for (list<string>::iterator it1 = (*it).begin(); it1 != (*it).end(); ++it1) {
			if (first) {
				if ((*it1) == name) {
					erase = true;
					for (list<pair<string, int>>::iterator it2 = saturation_queue.begin(); it2 != saturation_queue.end(); ++it2) {
						if (!((*it2).first == name)) {
							temp_queue.emplace_back(*it2);
							erased = true;
						}
					}
				}
			}
			else if (!(erase) && (erased)) {
				if ((*it1) == name) {
					*it1 = to_string(color);
					for (list<pair<string, int>>::iterator it3 = temp_queue.begin(); it3 != temp_queue.end(); ++it3) {
						if ((*it1) == (*it3).first) {
							--(*it3).second;
						}
					}
				}
			}
			else if (!(erase) && !(erased)) {
				if ((*it1) == name) {
					*it1 = to_string(color);
					for (list<pair<string, int>>::iterator it3 = saturation_queue.begin(); it3 != saturation_queue.end(); ++it3) {
						if ((*it1) == (*it3).first) {
							--(*it3).second;
						}
					}
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
	saturation_queue.clear();
	saturation_queue = temp_queue;
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

	// initialize variables and registers used
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

	// given all the registers and variables the stuff they will be interfering with
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

	first = true;
	list<string> temp_iteration;
	list<string> temp_input_list;
	list<string> sorted_list;
	bool assigned = false;

	// replacing registers with the colors they are initially assigned to make the task easier 
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

	// filling up saturation queue
	for (list<list<string>>::iterator it = interfering_colors_list.begin(); it != interfering_colors_list.end(); it++) {
		temp_iteration = *it;
		first = true;
		string input_string;
		int input_saturation_value = 0;
		bool try_it = true;
		for (list<string>::iterator it1 = temp_iteration.begin(); it1 != temp_iteration.end(); ++it1) {
			if (first) {
				input_string = *it1;
			}
			else {
				try {
					stoi(*it1);
				}
				catch (std::invalid_argument& e) {
					try_it = false;
				}
				if (try_it) {
					if ((stoi(*it1) >= 0) && (stoi(*it1) <= 13)) {
						++input_saturation_value;
					}
				}
				try_it = true;
			}
			first = false;
		}
		saturation_queue.emplace_back(make_pair(input_string, input_saturation_value));
	}

	// filling the colors assigned vector with appropriate stuff that gets assigned to them
	for (list<pair<string, int>>::iterator it = colors.begin(); it != colors.end(); ++it) {
		temp_input_list.clear();
		temp_input_list.push_back((*it).first);
		colors_assigned.push_back(temp_input_list);
	}

	print_color_graph_x0(&detailed_interference_list);
	system("Pause");

	print_color_graph_x0(&interfering_colors_list);
	system("Pause");

	//refresh_queue("add_x_0", 3);
	//print_color_graph_x0(&interfering_colors_list);
	//system("Pause");

	print_queue();

	string temp_var;
	int temp_color;

	while (!(isQueueEmpty())) {
		temp_var = get_sat_max();
		temp_color = color(temp_var);
		refresh_queue(temp_var,temp_color);		
		print_color_graph_x0(&interfering_colors_list);
		system("Pause");
		print_queue();
		system("Pause");
	}

	// not printing what it's supposed to missing assigned vars
	print_colors_assigned();
	system("Pause");

	//fill the move list
	//print the move list

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