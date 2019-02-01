#include "Compiler.h"

int main() {

	// -----------------------------------------------------------------------------------------------------------
	//				-----	-----			-------	----- -   - -----
	//				-	 -	-	-			   ---	-	- --  - -
	//				-----	-	-	-----	  ---	-	- - - - ----
	//				-	-	-	-			 ---	-	- -  -- -
	//				-	 -  -----			-------	----- -   - -----
	// -----------------------------------------------------------------------------------------------------------

	mode = Interactive;

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
	//				-	-	-----			-------	----- -   - -----
	//				 - -	-	-			   ---	-	- --  - -
	//				  -		-	-	-----	  ---	-	- - - - ----
	//				 - -	-	-			 ---	-	- -  -- -
	//				-	-   -----			-------	----- -   - -----
	// -----------------------------------------------------------------------------------------------------------

	/*
	// instructions tester
	instrX0 *movq_tester1		= new MovqX0	(new IntX0(10),		new RegX0("rax"));		// movq		int -> reg
	instrX0 *movq_tester2		= new MovqX0	(new RegX0("rax"),	new RegX0("rbx"));		// movq		reg -> reg
	instrX0 *addq_tester1		= new AddqX0	(new IntX0(15),		new RegX0("rax"));		// addq		int -> reg
	instrX0 *addq_tester2		= new AddqX0	(new RegX0("rbx"),	new RegX0("rax"));		// addq		reg -> reg
	instrX0 *subq_tester1		= new SubqX0	(new IntX0(100),	new RegX0("rax"));		// subq		int -> reg
	instrX0 *subq_tester2		= new SubqX0	(new RegX0("rax"),	new RegX0("rbx"));		// subq		reg -> reg
	instrX0 *retq_tester		= new RetqX0	();											// retq
	instrX0 *negq_tester		= new NegqX0	(new RegX0("rbx"));							// negq		reg
	instrX0 *callq_tester		= new CallqX0	();											// callq	print_int -> calling function that prints %rdi
	//instrX0 *pushq_tester1	= new PushqX0	(new IntX0(10));							// pushq	int
	//instrX0 *pushq_tester2	= new PushqX0	(new RegX0("rax"));							// pushq	reg
	//instrX0 *popq_tester		= new PopqX0	(new RegX0("rcx"));							// popq		reg
	*/

	/*
	// program tester initialization
	list<std::unique_ptr<InstrX0>> prog_tester;
	pcnt = 0;

	prog_tester.emplace_back(new MovqX0(new IntX0(10),		new RegX0("rax")));
	prog_tester.emplace_back(new MovqX0(new RegX0("rax"),	new RegX0("rbx")));
	prog_tester.emplace_back(new AddqX0(new IntX0(15),		new RegX0("rax")));
	prog_tester.emplace_back(new AddqX0(new RegX0("rbx"),	new RegX0("rax")));
	prog_tester.emplace_back(new SubqX0(new IntX0(100),		new RegX0("rax")));
	prog_tester.emplace_back(new SubqX0(new RegX0("rax"),	new RegX0("rbx")));
	//prog_tester.emplace_back(new RetqX0());
	prog_tester.emplace_back(new NegqX0(new RegX0("rbx")));
	prog_tester.emplace_back(new CallqX0());
	prog_tester.emplace_back(new PushqX0(new RegX0("rax")));
	prog_tester.emplace_back(new PopqX0(new RegX0("rbx")));

	ProgramX0 *x0_tester = new ProgramX0(&prog_tester);

	// program tester execution
	x0_tester->execute(&RegistersX0);
	
	system("Pause");
	*/

	/*
	// instructions execution test
	movq_tester1->eval(&regs);
	movq_tester2->eval(&regs);
	addq_tester1->eval(&regs);
	addq_tester2->eval(&regs);
	subq_tester1->eval(&regs);
	subq_tester2->eval(&regs);
	negq_tester->eval(&regs);
	callq_tester->eval(&regs);
	retq_tester->eval(&regs);

	// instructions print
	cout << "\nProgram:\n";
	cout << movq_tester1->toString();
	cout << movq_tester2->toString();
	cout << addq_tester1->toString();
	cout << addq_tester2->toString();
	cout << subq_tester1->toString();
	cout << subq_tester2->toString();
	cout << negq_tester->toString();
	cout << callq_tester->toString();
	cout << retq_tester->toString();
	*/
	
	/*
	// registers print
	cout << "\nMemory:\n";
	cout << "\tRegister\tValue\n";
	for (std::list<pair<std::string,int>>::iterator it = ptr_register_list->begin(); it != ptr_register_list->end(); ++it) {
		cout << "\t" << (*it).first << "\t\t" << (*it).second << "\n";
	}
	cout << "\n";
	*/

	// -----------------------------------------------------------------------------------------------------------
	//				 ----	-----			-------	----- -   - -----
	//				-	 -	-	-			   ---	-	- --  - -
	//				-		-	-	-----	  ---	-	- - - - ----
	//				-	 -	-	-			 ---	-	- -  -- -
	//				 ----   -----			-------	----- -   - -----
	// -----------------------------------------------------------------------------------------------------------

	/*
	// assignment tester
	stmtC0 *assign_read2var = new assignC0(new varC0("x"), new readC0());								// read2arg
	stmtC0 *assign_int2var = new assignC0(new varC0("y"), new intC0(5));								// arg2arg
	stmtC0 *assign_var2var = new assignC0(new varC0("z"), new varC0("x"));								// arg2arg
	stmtC0 *assign_negvar2var = new assignC0(new varC0("a"), new negC0(new varC0("x")));				// neg(var)2arg
	stmtC0 *assign_negint2var = new assignC0(new varC0("b"), new negC0(new intC0(5)));					// neg(int)2arg
	stmtC0 *assign_plus2var = new assignC0(new varC0("c"), new addC0(new intC0(5), new varC0("x")));	// plus(int,var)2arg

	// return tester
	stmtC0 *ret_var = new retC0(new varC0("x"));
	stmtC0 *ret_int = new retC0(new intC0(5));
	
	// list of statements tester
	list<std::unique_ptr<stmtC0>> prog_tester;
	list<pair<std::string, int>> vars;

	prog_tester.emplace_back(assign_read2var);
	prog_tester.emplace_back(assign_int2var);
	prog_tester.emplace_back(assign_var2var);
	prog_tester.emplace_back(assign_negvar2var);
	prog_tester.emplace_back(assign_negint2var);
	prog_tester.emplace_back(assign_plus2var);
	prog_tester.emplace_back(ret_var);
	prog_tester.emplace_back(ret_int);
	
	vars.push_back(std::make_pair("a", 0));
	vars.push_back(std::make_pair("b", 0));
	vars.push_back(std::make_pair("c", 0));
	vars.push_back(std::make_pair("x", 0));
	vars.push_back(std::make_pair("y", 0));
	vars.push_back(std::make_pair("z", 0));

	progC0 *program = new progC0(&prog_tester);

	program->execute(&vars);

	system("pause");
	*/

}