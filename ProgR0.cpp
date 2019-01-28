#include "ProgR0.h"

int main() {

	// optimization test
	mode = Interactive;

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

	/*
	// function onNth test 
	mode = Interactive;
	int m_test = 5;
	ProgR0 *test_program_onNth = new ProgR0(NULL, onNth(m_test));
	cout << "is it 32?\n";
	cout << test_program_onNth->prnt() << " = " << test_program_onNth->intrp();
	cout << "\n\n";
	system("Pause");

	// function randP test
	int n_test = 4;
	for (int i = 1; i < 100; ++i) {
		ProgR0 *test_program_randP = new ProgR0(NULL, randP(n_test));
		cout << test_program_randP->prnt() << " = " << test_program_randP->intrp();
		cout << "\n\n";
		system("Pause");
	}

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

}