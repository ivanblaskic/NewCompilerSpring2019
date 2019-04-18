#include "Compiler.h"


void print_variables_x0() {
	cout << "\nVariables:\n";
	cout << "\tName\tValue\n";
	for (std::list<pair<std::string, int>>::iterator it = init_variables_list.begin(); it != init_variables_list.end(); ++it) {
		cout << "\t" << (*it).first << "\t\t" << (*it).second << "\n";
	}
}
void print_registers_x0() {
	cout << "\nMemory:\n";
	cout << "\tRegister\tValue\n";
	for (std::list<pair<std::string, int>>::iterator it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
		cout << "\t" << (*it).first << "\t\t" << (*it).second << "\n";
	}
}
void print_stack_x0() {
	cout << "\nStack Values:\n";
	cout << "\tAddress\t\tValue\n";
	int temp;
	for (std::list<pair<std::string, int>>::iterator it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
		if ((*it).first == "rsp") {
			temp = (*it).second;
		}
	}
	temp = print_stack_var + 1;
	for (int i = 0; i < temp; i++) {
		cout << "\t" << &StackX0[i] << "\t" << StackX0[i] << "\n";
	}
	/*
		Node *temp = NULL;
		temp = top;
		while (temp != NULL) {
			cout << "\t" << temp << "\t" << temp->data << "\n";
			temp = temp->link;
		}
	*/
}
void print_liveness_before_x0() {
	cout << "\nLiveness Before Analysis:\n";
	cout << "\tLine Number\tWhat's Live Before\n";
	for (std::list<list<string>>::iterator it = live_before.begin(); it != live_before.end(); ++it) {
		list<string> temp = *it;
		for (std::list<string>::iterator it1 = temp.begin(); it1 != temp.end(); ++it1) {
			if (it1 == temp.begin()) {
				cout << "\t" << *it1 << "\t\t";
			}
			else {
				cout << *it1 << ", ";
			}
		}
		cout << "\n";
	}
}
void print_liveness_after_x0() {
	cout << "\nLiveness After Analysis:\n";
	cout << "\tLine Number\tWhat's Live After\n";
	for (std::list<list<string>>::iterator it = live_after.begin(); it != live_after.end(); ++it) {
		list<string> temp = *it;
		for (std::list<string>::iterator it1 = temp.begin(); it1 != temp.end(); ++it1) {
			if (it1 == temp.begin()) {
				cout << "\t" << *it1 << "\t\t";
			}
			else {
				cout << *it1 << ", ";
			}
		}
		cout << "\n";
	}
}
void print_interference_x0() {
	cout << "\nInterference Analysis:\n";
	cout << "\tLine Number\tWhat's Iterfering?\n";
	for (std::list<list<string>>::iterator it = interference_variables_list.begin(); it != interference_variables_list.end(); ++it) {
		list<string> temp = *it;
		for (std::list<string>::iterator it1 = temp.begin(); it1 != temp.end(); ++it1) {
			if (it1 == temp.begin()) {
				cout << "\t" << *it1 << "\t\t";
			}
			else {
				cout << *it1 << ", ";
			}
		}
		cout << "\n";
	}
}

int main() {

	// -----------------------------------------------------------------------------------------------------------
	//				-----	-----			-------	----- -   - -----
	//				-	 -	-	-			   ---	-	- --  - -
	//				-----	-	-	-----	  ---	-	- - - - ----
	//				-	-	-	-			 ---	-	- -  -- -
	//				-	 -  -----			-------	----- -   - -----
	// -----------------------------------------------------------------------------------------------------------

		cout << "\nMy program has a weird requirement where I am not letting you use my register names as your variable names.\nI demand creativity from you mate!\n\n";
		system("Pause");
		system("Cls");

		mode = Interactive;
		
		// R1 uniquify & resolve_complex test_suite
		// R1 uniquify function test_suite
		list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>> *variables_mapping = new list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>>();
		// let ([x 5] [+(L [(x 6) x]) (x)]) --> add(let ([x 5] [+(L [(x 6) x]) (x)]), let([x 2] [+ (read) (x)]))
		//ExpR0 *te = L(dynamic_cast<VarR0*>(V("x")), I(5), A(L(dynamic_cast<VarR0*>(V("x")), I(6), V("x")), V("x")));
		ExpR0 *te = A(L(dynamic_cast<VarR0*>(V("x")), I(5), A(L(dynamic_cast<VarR0*>(V("x")), I(6), V("x")), V("x"))),L(V("x"),I(2),A(V("x"),I(2))));
		// let ([x 5] [+ (x) (2)]) 
		//ExpR0 *te = L((dynamic_cast<VarR0*>(V("x"))), I(5), A((V("x")), I(2)));
		// (+ (5) (6))
		//ExpR0 *te = A(I(5), I(2));
		// let ([x (read)][+ (x) (5)])
		//ExpR0 *te = L(V("x"), R(), A(V("x"), I(5)));

		cout << "\n\nPROGRAM EXECUTION IN R0 LANGUAGE: \n\n";
			
		ProgR0 *tp = new ProgR0(new list<pair<string, int>>(), te);
		cout << tp->prnt() << " = " << tp->intrp();
		//cout << result;
		cout << "\n\n";
		system("Pause");
		system("Cls");

		cout << "\n\nPROGRAM EXECUTION IN R0 LANGUAGE WITH UNIQUE VARIABLE NAMES: \n\n";
	
		ProgR0 *tp_uniq = new ProgR0(new list<pair<string, int>>(), te->uniquify(variables_mapping));
		int result_uniq = tp_uniq->intrp();
		cout << tp_uniq->prnt() << " = " << result_uniq;
		cout << "\n\n";
		system("Pause");
		system("Cls");

		/* 
		// comment these 5 out 
		if (result == result_uniq)
			cout << "Compiler works! Bravo :) \n\n";
		else
			cout << "Fix compiler! :( \n\n";
		system("Pause");
		*/
	
		// R1 resolve_complex function test_suite
	
		cout << "\n\nPROGRAM EXECUTION IN R0 LANGUAGE WITH UNIQUE VARIABLE NAMES AND SIMPLIFIED FOR COMPILATION: \n\n";
	
		ProgR0 *tp_res_comp = new ProgR0(new list<pair<string,int>>(), tp_uniq->resolv());
		cout << "\n\n";
		system("Pause");
		system("Cls");

		cout << "\n\nPROGRAM EXECUTION IN C0 LANGUAGE: \n\n";
	
		tp_res_comp->econ();
	
		/* 
		// R1 optimization test_suite
		// success * 5
		// Let([X 5] Let([Y 95] X+Y)) = 100
		ExpR0 *te_1 = L(V("x"), I(5), L(V("y"), I(95), A(V("x"), V("y"))));
		cout << "is it 100?" << "\n";
		cout << te_1->toString() << " = " << te_1->eval(new list<pair<string, int>>());
		cout << "\n\n";
		ExpR0 *test_suite1_opt = te_1->opt(new list<pair<string, ExpR0*>>());
		cout << test_suite1_opt->toString() << " = " << test_suite1_opt->eval(new list<pair<string, int>>());
		cout << "\n\n";
		system("Pause");

		// Add([Neg(Let ([X 10] X+100))] [Add(Let([X 5] Let([Y 6] Let([Z X+Y] Z))), 100)]) = -110 + 100 + 11 = 1 
		ExpR0 *te_2 = A(N(L(V("x"), I(10), A(V("x"), I(100)))), A(L(V("x"), I(5), L(V("y"), I(6), L(V("z"), A(V("x"), V("y")), V("z")))), I(100)));
		cout << "is it 1?" << "\n";
		cout << te_2->toString() << " = " << te_2->eval(new list<pair<string, int>>());
		cout << "\n\n";
		ExpR0 *test_suite2_opt = te_2->opt(new list<pair<string, ExpR0*>>());
		cout << test_suite2_opt->toString() << " = " << test_suite2_opt->eval(new list<pair<string, int>>());
		cout << "\n\n";
		system("Pause");

		// (-[+ (let [(x [+ 21 14]) (+ x 14)]) (-[let ([y 10] [+ (y) -(100)])])]) = -139
		ExpR0 *te_3 = N(A(L(V("x"), A(I(21), I(14)), A(V("x"), (I(14)))), (N(L(V("y"), I(10), A(V("y"), N(I(100))))))));
		cout << "is it -139?" << "\n";
		cout << te_3->toString() << " = " << te_3->eval(new list<pair<string, int>>());
		cout << "\n\n";
		ExpR0 *test_suite3_opt = te_3->opt(new list<pair<string, ExpR0*>>());
		cout << test_suite3_opt->toString() << " = " << test_suite3_opt->eval(new list<pair<string, int>>());
		cout << "\n\n";
		system("Pause");
	
		//  let([x 5][(let [(x [read]) (x+5)]]) = (read) + 10
		ExpR0 *te_4 = L(V("x"),I(5),L(V("x"), R(), A(V("x"), I(5))));
		cout << "is it read + 5?" << "\n";
		cout << te_4->toString() << " = " << te_4->eval(new list<pair<string, int>>());
		cout << "\n\n";
		ExpR0 *test_suite4_opt = te_4->opt(new list<pair<string, ExpR0*>>());
		cout << test_suite4_opt->toString() << " = " << test_suite4_opt->eval(new list<pair<string, int>>());
		cout << "\n\n";
		system("Pause");
			
		//  let([x 5][(let [(y x) (y+5)]]) = 10
		ExpR0 *te_5 = L(V("x"), I(5), L(V("y"), V("x"), A(V("y"), I(5))));
		cout << "is it 10?" << "\n";
		cout << te_5->toString() << " = " << te_5->eval(new list<pair<string, int>>());
		cout << "\n\n";
		ExpR0 *test_suite5_opt = te_5->opt(new list<pair<string, ExpR0*>>());
		cout << test_suite5_opt->toString() << " = " << test_suite5_opt->eval(new list<pair<string, int>>());
		cout << "\n\n";
		system("Pause");
		*/
		
		/*
		// R1 test_suite
		// success * 12
		// Let([x 4+5] Let([x 3+4] -x) + x) = 2
		ExpR0 *te_1 = L(V("x"), A(I(4), I(5)), A(L(V("x"), A(I(3), I(4)), N(V("x"))), V("x")));
		// Let([X 5] Let([Y 95] X+Y)) = 100
		ExpR0 *te_2 = L(V("x"), I(5), L(V("y"), I(95), A(V("x"), V("y"))));
		// Add([Neg(Let ([X 10] X+100))] [Add(Let([X 5] Let([Y 6] Let([Z X+Y] Z))), 100)]) = -110 + 100 + 11 = 1 
		ExpR0 *te_3 = A(N(L(V("x"), I(10), A(V("x"), I(100)))), A(L(V("x"), I(5), L(V("y"), I(6), L(V("z"), A(V("x"), V("y")), V("z")))), I(100)));
		// (-[+ (let [(x [+ 21 14]) (+ x 14)]) (-[let ([y 10] [+ (y) -(100)])])]) = -139
		ExpR0 *te_4 = N(A(L(V("x"), A(I(21), I(14)), A(V("x"), (I(14)))), (N(L(V("y"), I(10), A(V("y"), N(I(100))))))));
		// (let [(x [+ 10 -(5)]) (N[+ x 10])]) = -15
		ExpR0 *te_5 = L(V("x"),A(I(10),N(I(5))),N(A(V("x"),I(10))));
		// (let [(x 5) (let [(y 10) (let [(z 15) (let [(x 10)(+ [+ (x) (y)] [+ (x) (z)])])])])] = 2*x + y + z = 45 
		ExpR0 *te_6 = L(V("x"), I(5), L(V("y"), I(10), L(V("z"), I(15), L(V("x"), I(10), A(A(V("x"), V("y")), A(V("x"), V("z")))))));
		// (+ [-(let[(x 10) (+ [x] [x])])] [+ (-10) (-10)]) = -40
		ExpR0 *te_7 = A(N(L(V("x"), I(10), A(V("x"), V("x")))), A(N(I(10)), N(I(10))));
		// (+ [- (let [(x 10) (x)])] [let ([x -(10)][x])]) = -20 
		ExpR0 *te_8 = A(N(L(V("x"), I(10), V("x"))), L(V("x"), N(I(10)), V("x")));
		// Let ([x 20] [let ([y 20] [x+y])]) = 40
		ExpR0 *te_9 = L(V("x"), I(20), L(V("y"), I(20), A(V("x"), V("y"))));
		// - (let [(x [+ (10) (10)]) (+ [10] [+ (x) (x)])]) = 50
		ExpR0 *te_10 = L(V("x"), A(I(10), I(10)), A(I(10), A(V("x"), V("x"))));
		// Let ([x 10] [100]) = 100
		ExpR0 *te_11 = L(V("x"), I(10), I(100));
		// (+ [let ([x 10] [x])] [(-[let([y 10] [y])])]) = 0
		ExpR0 *te_12 = A(L(V("x"), I(10), V("x")), N(L(V("y"), I(10), V("y"))));
		
		ProgR0 *tp = new ProgR0(new list<pair<string, int>>(), te_12);
		cout << "\nis it -15?\n";
		cout << tp->prnt() << " = " << tp->intrp();
		cout << "\n\n";
		system("Pause");
		*/
	
		/*
		// optimization test
		mode = Interactive;

		// success * 3+
		// program 4 definition
		// (+ [read] [+ (+ [10] [-(7)]) (+ [14] [read])]) = (+ read [+ 3 (+ 14 read)]) = (+ 17 (+ read read)) 
		ExpR0 *test_suite4 = A(R(), A(A(I(10), N(I(7))), A(I(14), R())));
		cout << "is it (17+x+y)?" << "\n";
		cout << test_suite4->toString() << " = " << test_suite4->eval(NULL);
		cout << "\n\n";
		ExpR0 *test_suite4_opt = test_suite4->opt();
		cout << test_suite4_opt->toString() << " = " << test_suite4_opt->eval(NULL);
		cout << "\n\n";
		system("Pause");
			
		// program 5 definition
		// (+ [+ (+ [-(+ [123] [243])] [43]) (- [read])] [24]) = (+ (+ (+ -366 43) -read) 24) = -323 - read + 24 = - 299 - read
		ExpR0 *test_suite5 = A(A(A(N(A(I(123), I(243))), I(43)), N(R())), I(24));
		cout << "is it -(299 + read)?" << "\n";
		cout << test_suite5->toString() << " = " << test_suite5->eval(NULL);
		cout << "\n\n";
		ExpR0 *test_suite5_opt = test_suite5->opt();
		cout << test_suite5_opt->toString() << " = " << test_suite5_opt->eval(NULL);
		cout << "\n\n";
		system("Pause");
	
		// program 6 definition
		// - (+ [+ (+ [read] [-(10)]) (+ [+ (-[2]) (23)] [read])] [+ (+ [read] [100] ) (read)]) = (+ [111] [+ (+ [read] [read]) (+ [read] [read])])
		// opt (+ [+ (+ [read] [-(10)]) (+ [+ (-[2]) (23)] [read])] [+ (+ [read] [100] ) (read)] = (+ [+ (11) (+ [read] [read])] [+ (100) (+ [read] [read])])
		// opt [+ (+ [read] [-(10)]) (+ [+ (-[2]) (23)] [read])] = [+ (+ [-10] [read]) (+ (21) (read))] = [+ (11) (+ [read] [read])]
		// opt (+ [read] [-(10)]) = (+ [read] [-10])
		// opt (read) = (read)
		// opt [-(10)] = (-10)
		// opt (+ [+ (-[2]) (23)] [read]) = (+ (21) (read)) 
		// opt (+ (-2) (23)) = 21
		// opt (+ [+ (read) (100)] [read]) = [+ (100) (+ [read] [read])]
		ExpR0 *test_suite6 = N(A(A(A(R(), N(I(10))), (A(A(N(I(2)), (I(23))), R()))), A(A(R(), I(100)), R())));
		cout << "is it -(x + y + z + w + 111)?" << "\n";
		cout << test_suite6->toString() << " = " << test_suite6->eval(NULL);
		cout << "\n\n";
		ExpR0 *test_suite6_opt = test_suite6->opt();
		cout << test_suite6_opt->toString() << " = " << test_suite6_opt->eval(NULL);
		cout << "\n\n";
		system("Pause");
		*/
		
		/*
		// function onNth test 
		mode = Interactive;
		int m_test = 5;
		ProgR0 *test_program_onNth = new ProgR0(NULL, onNth(m_test));
		cout << "is it 32?\n";
		cout << test_program_onNth->prnt() << " = " << test_program_onNth->intrp();
		cout << "\n\n";
		system("Pause");
		*/
	
		/* 
		// randP function for R1 successfully tested
		// L ( [x (L[(x L[(x (+ x (read))) (-[read])]) (+ [-(read)] [Let([x read] [read])])])] 
		//		[Let([x (+ [+ (read) (read)] [Let ([x x] [x])])] [+ (-[read]) (+ [read] [x])])]) = 20
		// 
		// function randP test
		mode = Interactive;
		list<pair<std::string, int>> *info = new list<pair<std::string, int>>();
	
		int n_test = 4;
		for (int i = 1; i < 2; ++i) {
			ProgR0 *test_program_randP = new ProgR0(info, randP(info,n_test));
			cout << test_program_randP->prnt() << " = " << test_program_randP->intrp();
			cout << "\n\n";
			system("Pause");
		}
		*/
	
		/*
		// program 1 definition
		// (+ [-(5) (+ [read] 10)]) = (-5) + (10 + read) = 5 + read
		mode = Interactive;
		ExpR0 *test_suite1 = new AddR0(	new NegR0(	new NumR0(5)),
										new AddR0(	new ReadR0(),
													new NumR0(10)));
		ProgR0 *test_program1 = new ProgR0(NULL, test_suite1);
		cout << "is it (5+x)?\n";
		cout << test_program1->prnt() << " = " << test_program1->intrp();
		//cout << test_suite1->toString() << " = " << test_suite1->eval();
		cout << "\n\n";
		system("Pause");
		*/
		
		/*
		// program 2 definition
		// (- [+ (+ [- 2] [+ 14 (-2)]) -(23)]) = - [((14-2) - 2) - 23] = -12 + 2 + 23 = 13
		ExpR0 *test_suite2 = new NegR0(	new AddR0(	new AddR0(	new NegR0(	new NumR0(2)),
																new AddR0(	new NumR0(14),
																			new NegR0(new NumR0(2)))),
													new NegR0(new NumR0(23))));
		cout << "is it 13?\n";
		cout << test_suite2->toString() << " = " << test_suite2->eval();
		cout << "\n\n";
		system("Pause");
	
		// program 3 definition
		// (- [+ (read) (read)])
		ExpR0 *test_suite3 = N(A(R(), R()));
		cout << "is it -(x+y)?\n";
		cout << test_suite3->toString() << " = " << test_suite3->eval();
		cout << "\n\n";
		system("Pause");
		*/
		
		/*
		// program 4 definition
		// (+ [read] [+ (+ [10] [-(7)]) (+ [14] [read])]) = (+ read [+ 3 (+ 14 read)]) = (+ 17 (+ read read)) 
		ExpR0 *test_suite4 = A(R(), A(A(I(10), N(I(7))), A(I(14), R())));	
		cout << "is it (17+x+y)?" << "\n";
		cout << test_suite4->toString() << " = " << test_suite4->eval();
		cout << "\n\n";
		system("Pause");
	
		// program 5 definition
		// (+ [+ (+ [-(+ [123] [243])] [43]) (- [read])] [24]) = (+ (+ (+ -366 43) -read) 24) = -323 - read + 24 = - 299 - read
		ExpR0 *test_suite5 = A(A(A(N(A(I(123), I(243))), I(43)), N(R())), I(24));
		cout << "is it -(299 + read)?" << "\n";
		cout << test_suite5->toString() << " = " << test_suite5->eval();
		cout << "\n\n";
		system("Pause");
	
		// program 6 definition
		// - (+ [+ (+ [read] [-(10)]) (+ [+ (-[2]) (23)] [read])] [+ (+ [read] [100] ) (read)]) = 
		// read + read + 11 + 100 + read + read = 111 + 4 * read
		ExpR0 *test_suite6 = N(A(A(A(R(), N(I(10))), (A(A(N(I(2)), (I(23))), R()))), A(A(R(), I(100)), R())));
		cout << "is it -(x + y + z + w + 111)?" << "\n";
		cout << test_suite6->toString() << " = " << test_suite6->eval();	
		cout << "\n\n";
		system("Pause");
		*/
	
		/*
		// program 7 definition
		// (+ (14) (-291)) = -277
		ExpR0 *test_suite7 = A(I(14), N(I(291)));
		cout << "is it -277?\n";
		cout << test_suite7->toString() << " = " << test_suite7->eval();
		cout << "\n\n";
		system("Pause");
			
		// program 8 definition
		// (- [+ (+ [100] [-(100)]) (+ [-(100)] [100])])
		cout << "is it 0?\n";
		ExpR0 * test_suite8 = N(A(A(I(100), N(I(100))), A(N(I(100)), I(100))));
		cout << test_suite8->toString() << " = " << test_suite8->eval();
		cout << "\n\n";
		system("Pause");
			
		// program 9 definition
		// (read)
		ExpR0 *test_suite9 = R();
		cout << "is it x?\n";
		cout << test_suite9->toString() << " = " << test_suite9->eval();
		cout << "\n\n";
		system("Pause");
	
		// program 10 definition
		// (+ [- (+ [- (15)] [+ (30) (15)])] [+ (45) (- [30])])
		// (-((30 + 15) - 15)) + (45 - 30) = -30 + 15 = -15
		ExpR0 *test_suite10 = A(N(A(N(I(15)), A(I(30), I(15)))), A(I(45), N(I(30))));
		cout << "is it -15?\n";
		cout << test_suite10->toString() << " = " << test_suite10->eval();
		cout << "\n\n";
		system("Pause");
	
		// program 11 definition
		// (+ [- (5)] [+ (+ [+ (5) (- [14])] [+ (25) (-[29])]) (15)]) 
		// ((((5-14)-4)+15)-5) = -28
		ExpR0 *test_suite11 = A(N(I(5)), A(A(A(I(5), N(I(14))), A(I(25), N(I(29)))), I(15)));
		cout << "is it - 3?\n";	
		cout << test_suite11->toString() << " = " << test_suite11->eval();
		cout << "\n\n";
		system("Pause");

		// program 12 definition
		// (+ [+ (read) (+ [12] [12])] [+ (- [12]) (- [12])]) = 0 + read 
		ExpR0 *test_suite12 = A(A(R(), A(I(12), I(12))), A(N(I(12)), N(I(12))));
		cout << "is it x?\n";
		cout << test_suite12->toString() << " = " << test_suite12->eval();
		cout << "\n\n";
		cout << ">> 12 Programs have been executed! <<\n";
		system("Pause");
		*/

	// -----------------------------------------------------------------------------------------------------------
	//				 ----	-----			-------	----- -   - -----
	//				-	 -	-	-			   ---	-	- --  - -
	//				-		-	-	-----	  ---	-	- - - - ----
	//				-	 -	-	-			 ---	-	- -  -- -
	//				 ----   -----			-------	----- -   - -----
	// -----------------------------------------------------------------------------------------------------------

		/*
		// label tester
		std::shared_ptr<LabelC0> lbl1_tester(new LabelC0("main:"));
		std::shared_ptr<LabelC0> lbl2_tester(new LabelC0("end:"));

		// initializing program
		list<std::shared_ptr<StmtC0>> tail1_tester;

		tail1_tester.push_back(std::make_shared<AssignC0>(new VarC0("x"), new ReadC0()));
		tail1_tester.push_back(std::make_shared<AssignC0>(new VarC0("y"), new IntC0(5)));
		tail1_tester.push_back(std::make_shared<AssignC0>(new VarC0("z"), new VarC0("x")));
		tail1_tester.push_back(std::make_shared<AssignC0>(new VarC0("a"), new NegC0(new VarC0("x"))));
		tail1_tester.push_back(std::make_shared<AssignC0>(new VarC0("b"), new NegC0(new IntC0(5))));
		tail1_tester.push_back(std::make_shared<AssignC0>(new VarC0("c"), new AddC0(new IntC0(5), new VarC0("x"))));

		Variables.push_back(std::make_pair("a", 0));
		Variables.push_back(std::make_pair("b", 0));
		Variables.push_back(std::make_pair("c", 0));
		Variables.push_back(std::make_pair("x", 0));
		Variables.push_back(std::make_pair("y", 0));
		Variables.push_back(std::make_pair("z", 0));

		TailC0 *temp_tail1 = new TailC0(&tail1_tester);
		auto tail_main = std::make_shared<TailC0>(*temp_tail1);
		auto tail_end = std::make_shared<TailC0>(new RetC0(new VarC0("x")));

		label_tail_list.emplace_back(std::make_pair(lbl1_tester, tail_main));
		label_tail_list.emplace_back(std::make_pair(lbl2_tester, tail_end));
		*/

		ProgC0 *program = new ProgC0();
		program->execute();
		program->emit();
		cout << "\n\n";
		system("Pause");
		system("Cls");

	// -----------------------------------------------------------------------------------------------------------
	//				-	-	-----			-------	----- -   - -----
	//				 - -	-	-			   ---	-	- --  - -
	//				  -		-	-	-----	  ---	-	- - - - ----
	//				 - -	-	-			 ---	-	- -  -- -
	//				-	-   -----			-------	----- -   - -----
	// -----------------------------------------------------------------------------------------------------------

		cout << "\n\nPROGRAM EXECUTION IN X0 LANGUAGE: \n\n";

		program->select();

		ProgramX0 *program_test_select = PX();
		program_test_select->emit();
		program_test_select->execute();
		program_test_select->liveness();
		program_test_select->interference();
		cout << "\n\n";
		system("Pause");
		system("Cls");

		program_test_select->moveGraph();
		program_test_select->colorGraph();
		cout << "\n\n";
		system("Pause");
		system("Cls");

		print_variables_x0();
		print_registers_x0();
		//print_stack_x0();

		cout << "\n\nPROGRAM EXECUTION IN X0 LANGUAGE THAT IS NOT USING VARIABLES: \n\n";
		

		program_test_select->assign();
		ProgramX0 *program_test_assign = PX();
		program_test_assign->emit();
		program_test_assign->execute();
		cout << "\n\n";
		system("Pause");
		system("Cls");
		
		print_variables_x0();
		cout << "\n\n";
		system("Pause");
		system("Cls");
		print_registers_x0();
		cout << "\n\n";
		system("Pause");
		system("Cls");
		print_stack_x0();
		cout << "\n\n";
		system("Pause");
		system("Cls");

		cout << "\n\nPROGRAM EXECUTION IN X0 LANGUAGE THAT IS USING ONLY ONE MEMORY REFERENCE PER INSTRUCTION: \n\n";

		program_test_assign->patch();
		ProgramX0 *program_test_patch = PX();
		program_test_patch->emit();
		program_test_patch->execute();
		cout << "\n\n";
		system("Pause");
		system("Cls");

		/*
		std::list<pair<std::shared_ptr<LabelX0>, std::shared_ptr<BlockX0>>>::iterator it;
		string temp;
		for (it = label_block_list.begin(); it != label_block_list.end(); ++it) {
			temp += it->first->getName() + ":" + "\t" + it->second->masm() + "\n";
		}
		ofstream myfile;
		myfile.open("ASMFunction.asm");
		myfile << ".code\n" << "getValueFromASM proc\n" << temp << "getValueFromASM endp\n" << "end";
		myfile.close();
		*/

		print_variables_x0();
		cout << "\n\n";
		system("Pause");
		system("Cls");
		print_registers_x0();
		cout << "\n\n";
		system("Pause");
		system("Cls");
		print_stack_x0();
		cout << "\n\n";
		system("Pause");
		system("Cls");

		print_liveness_before_x0();
		cout << "\n\n";
		system("Pause");
		system("Cls");
		print_liveness_after_x0();
		cout << "\n\n";
		system("Pause");
		system("Cls");
		print_interference_x0();
		cout << "\n\n";
		system("Pause");
		system("Cls");

		cout << "\n\nHOPE YOU ENJOYED!\n\n";
		delete te;
		delete tp;
		delete tp_uniq;
		delete tp_res_comp;
		delete program_test_select;
		delete program_test_assign;
		delete program;
		//delete program_test_patch;
		system("Pause");
		system("Cls");

		/*

		// label-block init
		std::shared_ptr<LabelX0> lbl_main(new LabelX0("main:"));
	
		list<std::shared_ptr<InstrX0>> blk_main_list;
		blk_main_list.push_back(std::make_shared<MovqX0>(IX(10),RX("rax")));		// movq		intX0, regx0
		blk_main_list.push_back(std::make_shared<MovqX0>(RX("rax"), RX("rbx")));	// movq		regX0, regx0
		blk_main_list.push_back(std::make_shared<AddqX0>(IX(15), RX("rax")));		// addq		intx0, regX0
		blk_main_list.push_back(std::make_shared<CallqX0>());						// callq
		blk_main_list.push_back(std::make_shared<AddqX0>(RX("rbx"), RX("rax")));	// addq		regX0, regX0
		blk_main_list.push_back(std::make_shared<SubqX0>(IX(10),RX("rax")));		// subq		intX0, regX0
		blk_main_list.push_back(std::make_shared<SubqX0>(RX("rax"),RX("rdi")));		// subq		regX0, regX0
		blk_main_list.push_back(std::make_shared<NegqX0>(RX("rbx")));				// negq		regX0
		blk_main_list.push_back(std::make_shared<PushqX0>(RX("rax")));				// pushq	regX0
		blk_main_list.push_back(std::make_shared<PushqX0>(RX("rax")));				// pushq	regX0
		blk_main_list.push_back(std::make_shared<PushqX0>(RX("rax")));				// pushq	regX0
		blk_main_list.push_back(std::make_shared<PopqX0>(RX("rcx")));				// popq		regX0
		blk_main_list.push_back(std::make_shared<MovqX0>(VX("x"), RX("rdx")));		// movq		varX0, regx0
		blk_main_list.push_back(std::make_shared<MovqX0>(RX("rax"), VX("x")));		// movq		regX0, varX0
		// works perfect, creates loop if used here
		// blk_main_list.push_back(std::make_shared<JumpX0>(LbX("main:")));			// jmp		labelX0			
		blk_main_list.push_back(std::make_shared<RetqX0>());						// retq
		BlockX0 *temp_blk = new BlockX0(&blk_main_list);
		auto blk_main = std::make_shared<BlockX0>(*temp_blk);
	
		pcnt = 0;
		label_block_list.emplace_back(make_pair(lbl_main, blk_main));
	
		// program call
		init_variables_list.push_back(std::make_pair("x", 36));
		ProgramX0 *program_test = PX();
		program_test->emit();
		program_test->execute();
		system("Pause");
		
		// variables print
		print_variables_x0();
	
		// registers print
		print_registers_x0();
	
		// stack print
		print_stack_x0();
	
		*/

}
