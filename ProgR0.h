#pragma once

/*

	author: Ivan Blaskic
	date:	01/24/2019
	use:	Jay's CC Class
	at:		UML

	1) + data types for R0 program ASTs 
	2) + pretty-printer for R0 program
	3) + test suite of dozen R0 programs
	4) + interpreter for R0 programs
	5) + function generating an R0 program computing 2^^n for a given N
		- ExpR0* onNth (int m) {
			if (m == 0) return I(1);
			if (m > 0) return A(onNth(m-1),onNth(m-1));
			if (m < 0) cout << "error calling function onNth: m < 0\n";
		  } 
	6) + function generating a random R0 program of depth N
		- ExpR0* randP (int n) {
			if (n == 0) {
				srand(time(NULL));
				n = rand() % 2;
				if (n == 0) 
					mode = Interactive;
				else if (n == 1) 
					mode = Automated;
				return R();
			}
			else {
				srand(time(NULL));
				if ((rand() % 2) == 0)
					return N(randP(n-1));
				else 
					return A(randP(n-1),randP(n-1));
			}
		  }
	7) + extend your test suite to generate a large number of random programs
		- nodes either do all of the returns in automated or interactive mode
	8) ? optimizer tests
		- ...
	9) ? an optimizer for R0
		- opt(I[x])						= I(x)
		- opt(R[])						= R()
		- opt(A [I(x)] [I(y)])			= I(x+y)
		- opt(N [N (I[x])])				= I(x)
		- opt(A [I(x)] [A (R[]) (I[y])])= A [A (I [x]) (I[y])] [R()]
		- opt(A []
	10) ? extending test suite to use the optimizer
		- ...

	11) extand data types from R0 to R1
		- e = ... | var | let (|var e|) e)
		- var = variable-not-otherwise-mentioned

		class VarR0 : public ExpR0 {
public:
	VarR0(string _name) {
		this->name = name;
		// put it into the list of variables
	}
	int eval() {
		return ;
	}
	string toString() {
		return to_string(this->value);
	}
	ExpR0* opt() {
		// gotta figure out
	}
private:
	string name;
	int value;
};

		
	12) extend your pretty printer from R0 to R1
		- use syntax that looks nice
	13) write a dozen test R1 programs
	14) extend your interpreter from R0 to R1
	15) extend your random generation function from R0 to R1
		- have the env that records which variables are bound by prior lets 
		  and allow these variables to be used in depth-0 expressions
	16) write some R1-specific optimizer test
	17) extend your optimizer from R0 to R1
		- you should inline variables that have been reduced to values or other variables
	18) define data types for X0 program ASTs
		- var = var-not-otherwise-mentioned
		- label = string
		- register = ...
		- arg = ...
		- instr = ...
		- blk = ...
		- p = ...
	19) write an emitter for X0 programs
		- should emit in the syntax of the assembler you will use 
		- takes a parameter whether variables should be allowed in the output
		- only makes sense for debugging
	20) build a test suite of a dozen X0 programs
		- intrp should ony ret value of rax on retq rather than entire state of machine
		- ideally these programs are manually compiled versions of your R1 test programs
	21) write an interpreter for X0 programs
		- register file is simple fixed vector where registers are indices and the stack is stack
		- have to have special case for when you callq to system function like read or print
	22) connect your X0 test suite to system assembler 
		- create intermediate file containing the assembly on disk - you can look at assembly 
		  you producing during compilation in the future 
		- automatically compare results of assembled program and your interpreter
	23) define data types for C0 program ASTs
		- var = ...
		- label = ...
		- arg = ...
		- exp = ...
		- stmt = ...
		- tail = ...
		- p = ...
	24) write a pretty printer for C0 programs
		- purely debugging tool
	25) build a test suite of a dozen C0 programs
		- manually compiled versions of R1 test programs
	26) write an interpreter for C0 programs
		- should use global environment for variables values and should error 
		  when undefined variables are referenced
*/

#pragma once

#ifndef ProgR0_H
#define ProgR0_H

#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include <list>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum Mode {Interactive,Automated};
static Mode mode = Interactive;

enum Operation {Add, Neg, Read, Num};

class ExpR0 {
public:
	int virtual eval() = 0;
	virtual string toString() = 0;
	virtual ExpR0* opt() = 0;
};

class NumR0 : public ExpR0 {
public:
	NumR0(int _value) {
		this->value = _value;
	}
	int eval() {
		return this->value;
	}
	string toString() {
		return to_string(this->value);
	}
	ExpR0* opt() {
		return this;
	}
private:
	int value;
};

class ReadR0 : public ExpR0 {
public:
	ReadR0() {
	}
	int eval() {
		if (mode == Interactive) {
			cout << "Input the value for read: ";
			cin >> this->value;
			return this->value;
		}
		if (mode == Automated) {
			this->value = ((rand() % 2049) - 1024);
			return this->value;
		}
	}
	string toString() {
		if (mode == Interactive) {
			return "(print)";
		}
		if (mode == Automated) {
			return to_string(this->value);
		}
	}
	ExpR0* opt() {
		return this;
	}
private:
	int value;
};

class NegR0 : public ExpR0 {
public:
	NegR0(ExpR0 *_exp) {
		this->exp = _exp;
	}
	int eval() {
		return -(this->exp->eval());
	}
	string toString() {
		return "(- " + this->exp->toString() + ")";
	}
	// gotta check if the next expression is negation 
	//		if so then both of these could be removed 
	//		only N(N(ExpR0))) --> ExpR0 object could be returned
	ExpR0* opt() {
		ExpR0 *temp = exp->opt();
	}
private:
	ExpR0 *exp;
};

class AddR0 : public ExpR0 {
public:
	AddR0(ExpR0 *_lexp, ExpR0 *_rexp) {
		this->lexp = _lexp;
		this->rexp = _rexp;
	}
	int eval() {
		return (this->lexp->eval() + this->rexp->eval());
	}
	string toString() {
		return "(+ " + this->lexp->toString() + " " + this->rexp->toString() + ")";
	}
	ExpR0* opt() {
		ExpR0 *tempr = rexp->opt();
		ExpR0 *templ = lexp->opt();
		// if both numbers then add them
		// if one is put it left
		// add number from left one and from right one if exist and put as left one
		// remainder of expression leave on right
	}
private:
	ExpR0 *lexp, *rexp;
};

ExpR0* A(ExpR0* l, ExpR0* r) {
	return new AddR0(l, r);
}

ExpR0* N(ExpR0* e) {
	return new NegR0(e);
}

ExpR0* R() {
	return new ReadR0();
}

ExpR0* I(int _value) {
	return new NumR0(_value);
}

class ProgR0 {
public:
	ProgR0(list<pair<string, int>> *_info, ExpR0 *_code) {
		srand(time(NULL));
		code = _code;
		info = _info;
	}
	int intrp() {
		return code->eval();
	}
	string prnt() {
		return code->toString();
	}
	ExpR0* optmz() {
		return code->opt();
	}
private:
	list<pair<string, int>> *info;
	ExpR0 *code;
};

ExpR0* onNth(int m) {
	if (m == 0) return I(1);
	if (m > 0) return A(onNth(m - 1), onNth(m - 1));
	if (m < 0) cout << "Error calling function onNth: m < 0\n";
}

ExpR0* randP(int n) {
	if (n == 0) {
		int temp = rand();
		cout << "\n\t VALUE: " << temp << "\n\n";
		if ((temp % 2) == 0) {
			mode = Interactive;
			return R();
		}
		else {
			mode = Automated;
			return R();
		}
	}
	else {
		if ((rand() % 2) == 0)
			return N(randP(n - 1));
		else
			return A(randP(n - 1), randP(n - 1));
	}
}


#endif