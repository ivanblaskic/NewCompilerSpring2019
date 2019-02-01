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
	8) + optimizer tests
	9) + an optimizer for R0
		- opt(I[x])						= I(x)
		- opt(R[])						= R()
		- opt(A [I(x)] [I(y)])			= I(x+y)
		- opt(N [N (I[x])])				= I(x)
		- opt(A [I(x)] [A (R[]) (I[y])])= A [A (I [x]) (I[y])] [R()]
		- opt(A []
	10) + extending test suite to use the optimizer
	11) + extand data types from R0 to R1
		- e = ... | var | let (|var e|) e)
		- var = variable-not-otherwise-mentioned
	12) + extend your pretty printer from R0 to R1
		- use syntax that looks nice
	13) + write a dozen test R1 programs
	14) + extend your interpreter from R0 to R1
	15) + extend your random generation function from R0 to R1
		- have the env that records which variables are bound by prior lets 
		  and allow these variables to be used in depth-0 expressions
		- if none are yet defined --> 2 options: have one initial x w value or do read or random #

	16) 1/... write some R1-specific optimizer test

	17) + extend your optimizer from R0 to R1
		- you should inline variables that have been reduced to values or other variables

	18) ! define data types for X0 program ASTs
		- var = var-not-otherwise-mentioned
		- label = string
		- register = ...
		- arg = ...
		- instr = ...
		- blk = ...
		- p = ...
	19) ? write an emitter for X0 programs
		- should emit in the syntax of the assembler you will use 
		- takes a parameter whether variables should be allowed in the output
		- only makes sense for debugging
	20) 1/12 build a test suite of a dozen X0 programs
		- intrp should ony ret value of rax on retq rather than entire state of machine
		- ideally these programs are manually compiled versions of your R1 test programs
	21) ! write an interpreter for X0 programs
		- register file is simple fixed vector where registers are indices and the stack is stack
		- have to have special case for when you callq to system function like read or print
	22) ? connect your X0 test suite to system assembler 
		- create intermediate file containing the assembly on disk - you can look at assembly 
		  you producing during compilation in the future 
		- automatically compare results of assembled program and your interpreter

	23) ! define data types for C0 program ASTs
		- var = ...
		- label = ...
		- arg = ...
		- exp = ...
		- stmt = ...
		- tail = ...
		- p = ...
	24) ! write a pretty printer for C0 programs
		- purely debugging tool
	25) 1/12 build a test suite of a dozen C0 programs
		- manually compiled versions of R1 test programs
	26) ! write an interpreter for C0 programs
		- should use global environment for variables values and should error 
		  when undefined variables are referenced

	// OPTIMIZER's JOB

	// (+ [+ (+ [5] [read]) (+ [10] [12])] [+(+ [read] [read]) (+ [12] [read])])
	// opt (+ [+ (+ [5] [read]) (+ [10] [12])] [+(+ [read] [read]) (+ [12] [read])])
	// = opt (+ [+ (27) (read)] [+ (12) (+ [+ (read) (read)] [read])])
	// = (+ [39] [+ (+ [+ (read) (read)] [read]) (read)]
	// opt [+ (+ [5] [read]) (+ [10] [12])] = opt [+ (+ [5] [read]) (22)] = [+ (27) (read)]
	// opt (+ [5] [read]) = (+ [5] [read])
	// opt (+ [10] [12]) = (22)
	// opt [+ (+ [read][read])(+ [12] [read])] = (+ [(12)] [+ (+ [read] [read]) (read)])
	// opt [+ (read) (read)] = (+ [read] [read])
	// opt [+ (12) (read)] = (+ [12] [read])

*/

// -----------------------------------------------------------------------------------------------------------
//				-----	-----			-------	----- -   - -----
//				-	 -	-	-			   ---	-	- --  - -
//				-----	-	-	-----	  ---	-	- - - - ----
//				-	-	-	-			 ---	-	- -  -- -
//				-	 -  -----			-------	----- -   - -----
// -----------------------------------------------------------------------------------------------------------

#pragma once

#ifndef Compiler_H
#define Compiler_H

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

class VarR0;

class ExpR0 {
public:
	int virtual eval(list<pair<string, int>> *_info) = 0;
	virtual string toString() = 0;
	bool virtual simpleExp() = 0;
	virtual ExpR0* opt(list<pair<std::string, int>> *_info) = 0;
	bool virtual isNum() = 0;
	bool virtual isNumRead() = 0;
	bool virtual isNegExp() = 0;
};

ExpR0* A(ExpR0* l, ExpR0* r);

ExpR0* N(ExpR0* e);

ExpR0* R();

ExpR0* I(int _value);

ExpR0* I();

VarR0* V(string x);

ExpR0* L(VarR0* v, ExpR0* ve, ExpR0* be);

static int number_counter;

class NumR0 : public ExpR0 {
public:
	NumR0(int _value) {
		this->value = _value;
	}
	NumR0() {
		this->value = number_counter;
		number_counter++;
	}
	int eval(list<pair<std::string, int>> *_info) {
		return this->value;
	}
	string toString() {
		return to_string(this->value);
	}
	bool simpleExp() {
		return true;
	} 
	ExpR0* opt(list<pair<std::string, int>> *_info) {
		return this;
	}
	int retVal() {
		return this->value;
	}
	bool isNum() {
		return true;
	}
	bool isNumRead() {
		return false;
	}
	bool isNegExp() {
		return false;
	}
private:
	int value;
};

class ReadR0 : public ExpR0 {
public:
	ReadR0() {
	}
	int eval(list<pair<std::string, int>> *_info) {
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
			return "(read)";
		}
		if (mode == Automated) {
			return to_string(this->value);
		}
	}
	bool simpleExp() {
		return false;
	}
	ExpR0* opt(list<pair<std::string, int>> *_info) {
		return this;
	}
	bool isNum() {
		return false;
	}
	bool isNumRead() {
		return false;
	}
	bool isNegExp() {
		return false;
	}
private:
	int value;
};

class AddR0 : public ExpR0 {
public:
	AddR0(ExpR0 *_lexp, ExpR0 *_rexp) {
		this->lexp = _lexp;
		this->rexp = _rexp;
	}
	int eval(list<pair<std::string, int>> *_info) {
		this->info = _info;
		return (this->lexp->eval(this->info) + this->rexp->eval(this->info));
	}
	string toString() {
		return "(+ " + this->lexp->toString() + " " + this->rexp->toString() + ")";
	}
	bool simpleExp() {
		return false;
	}
	ExpR0* opt(list<pair<std::string, int>> *_info) {
		lexp = lexp->opt(_info);
		rexp = rexp->opt(_info);
		if (lexp->isNum() && rexp->isNum()) {
			NumR0* lnum = dynamic_cast<NumR0*>(lexp);
			NumR0* rnum = dynamic_cast<NumR0*>(rexp);
			return I(lnum->retVal() + rnum->retVal());
		}
		else if (lexp->isNum() && rexp->isNumRead()) {
			NumR0* lnum = dynamic_cast<NumR0*>(lexp);
			AddR0* radd = dynamic_cast<AddR0*>(rexp);
			NumR0* rnum = dynamic_cast<NumR0*>(radd->lexp);
			return A(I(lnum->retVal() + rnum->retVal()), radd->rexp);
		}
		else if (lexp->isNumRead() && rexp->isNum()) {
			NumR0* rnum = dynamic_cast<NumR0*>(rexp);
			AddR0* ladd = dynamic_cast<AddR0*>(lexp);
			NumR0* lnum = dynamic_cast<NumR0*>(ladd->lexp);
			return A(I(lnum->retVal() + rnum->retVal()), ladd->rexp);
		}
		else if (lexp->isNumRead() && rexp->isNumRead()) {
			AddR0* ladd = dynamic_cast<AddR0*>(lexp);
			AddR0* radd = dynamic_cast<AddR0*>(rexp);
			NumR0* lnum = dynamic_cast<NumR0*>(ladd->lexp);
			NumR0* rnum = dynamic_cast<NumR0*>(radd->lexp);
			return A(I(lnum->retVal() + rnum->retVal()), A(ladd->rexp, radd->rexp));
		}
		else if (rexp->isNumRead()) {
			AddR0* radd = dynamic_cast<AddR0*>(rexp);
			NumR0* rnum = dynamic_cast<NumR0*>(radd->getL());
			return A(I(rnum->retVal()), A(lexp, radd->rexp));
		}
		else if (lexp->isNumRead()) {
			AddR0* ladd = dynamic_cast<AddR0*>(lexp);
			NumR0* lnum = dynamic_cast<NumR0*>(ladd->getL());
			return A(I(lnum->retVal()), A(ladd->getR(), rexp));
		}
		else return this;
	}
	bool isNum() {
		if ((lexp->isNum()) && (rexp->isNum()))
			return true;
		return false;
	}
	bool isNumRead() {
		if(rexp->isNum()){
			ExpR0 *temp = lexp;
			lexp = rexp;
			rexp = temp;
			return true;
		}
		else if (lexp->isNum())
			return true;
		else
			return false;
	}
	bool isNegExp() {
		return false;
	}
	ExpR0* getR() {
		return rexp;
	}
	ExpR0* getL() {
		return lexp;
	}
private:
	ExpR0 *lexp, *rexp;
	list<pair<string, int>> *info;
};

class NegR0 : public ExpR0 {
public:
	NegR0(ExpR0 *_exp) {
		this->exp = _exp;
	}
	int eval(list<pair<std::string, int>> *_info) {
		this->info = _info;
		return -(this->exp->eval(this->info));
	}
	string toString() {
		return "(- " + this->exp->toString() + ")";
	}
	bool simpleExp() {
		return false;
	}
	ExpR0* opt(list<pair<std::string, int>> *_info) {
		exp = exp->opt(_info);
		if (exp->isNum()) {
			NumR0* num = dynamic_cast<NumR0*>(exp);
			return (I(-1 * num->retVal()));
		}
		else if (exp->isNumRead()) {
			AddR0* aexp = dynamic_cast<AddR0*>(exp);
			NumR0* laexp = dynamic_cast<NumR0*>(aexp->getL());
			if (aexp->getR()->isNegExp()) {
				NegR0* nexp = dynamic_cast<NegR0*>(aexp->getR());
				return A(I(-1*laexp->retVal()), nexp->getExp());
			}
			return A(I(-1*laexp->retVal()), N(aexp->getR()));
		}
		else if (exp->isNegExp()) {
			NegR0* nexp = dynamic_cast<NegR0*>(exp);
			return nexp->getExp();
		}
		return this;
	}
	bool isNum() {
		if (exp->isNum()) {
			return true;
		}
		return false;
	}
	bool isNumRead() {
		if (exp->isNumRead())
			return true;
		return false;
	}
	bool isNegExp() {
		if (exp->isNegExp())
			return false;
		else
			return true;
	}
	ExpR0* getExp() {
		return exp;
	}
private:
	ExpR0 *exp;
	list<pair<string, int>> *info;
	int value;
};

// gotta figure out all 4 optimization functions for let and var
class VarR0 : public ExpR0 {
public:
	VarR0(string _name) {
		this->name = _name;
		// put it into the list of variables 
	}
	int eval(list<pair<std::string, int>> *_info) {
		this->info = _info;
		std::list<pair<std::string, int>>::iterator it;
		for (it = (*this->info).begin(); it != (*this->info).end(); ++it) {
			if ((*it).first == this->name) {
				return (*it).second;
			}
		}
		cout << "\n- error_1: Variable " + this->name + " is not initialized yet - \n";
		return 0;
	}
	string toString() {
		return name;
	}
	bool simpleExp() {
		return true;
	}
	ExpR0* opt(list<pair<std::string, int>> *_info) {
		std::list<pair<std::string, int>>::iterator it;
		for (it = (*_info).begin(); it != (*_info).end(); ++it) {
			if ((*it).first == this->name) {
				return I((*it).second);
			}
		}
		cout << "Uninitialized Variable Used: " << this->name << "\n\n";
		return this;
	}
	bool isNum() {
		return false;
	}
	bool isNumRead() {
		return false;
	}
	bool isNegExp() {
		return false;
	}
private:
	string name;
	list<pair<string, int>> *info;
};

// gotta figure out all 4 optimization functions for let and var
class LetR0 : public ExpR0 {
public:
	LetR0(VarR0 *_variable, ExpR0 *_x_exp, ExpR0 *_b_exp) {
		this->variable = _variable;
		this->x_exp = _x_exp;
		this->b_exp = _b_exp;
	}
	int eval(list<pair<std::string, int>> *_info) {
		this->info = _info;
		int var_value = this->x_exp->eval(this->info);
		list<pair<string, int>> *new_info = new list<pair<string, int>>();
		*new_info = *info;
		// in case variable with same name exists it's overwritten
		std::list<pair<std::string, int>>::iterator it;
		for (it = (*new_info).begin(); it != (*new_info).end(); ++it) {
			if ((*it).first == this->variable->toString()) {
				((*it).second = var_value);
				return b_exp->eval(new_info);
			}
		}
		// o.w. new variable is stored and same list is used furthermore
		(*this->info).push_back(std::make_pair(this->variable->toString(), var_value));
		return b_exp->eval(info);
	}
	string toString() {
		return "Let[(" + this->variable->toString() + " " + this->x_exp->toString() + ") " + this->b_exp->toString() + "]";
	}
	bool simpleExp() {
		return false;
	}
	ExpR0* opt(list<pair<std::string, int>> *_info) {
		ExpR0 *x_expO = this->x_exp->opt(_info);
		if (x_expO->simpleExp()) {
			std::list<pair<std::string, int>>::iterator it;
			NumR0* tmp_num = dynamic_cast<NumR0*>(x_expO);
			for (it = (*_info).begin(); it != (*_info).end(); ++it) {
				if ((*it).first == variable->toString()) {
					(*it).second = tmp_num->retVal();
				}
			}
			(*_info).push_back(std::make_pair(this->variable->toString(), tmp_num->retVal()));
			return this->b_exp->opt(_info);
		}
		else {
			return L(V(this->variable->toString()), x_expO, b_exp->opt(_info));
		}
	}
	bool isNum() {
		return false;
	}
	bool isNumRead() {
		return false;
	}
	bool isNegExp() {
		return false;
	}
private:
	VarR0 *variable;
	ExpR0 *x_exp, *b_exp;
	list<pair<string, int>> *info;
};

ExpR0* L(VarR0* v, ExpR0* ve, ExpR0* be) {
	return new LetR0(v, ve, be);
}

VarR0* V(string x) {
	return new VarR0(x);
}

ExpR0* A(ExpR0* l, ExpR0* r) {
	return new AddR0(l, r);
}

ExpR0* N(ExpR0* e) {
	return new NegR0(e);
}

ExpR0* I() {
	return new NumR0();
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
		return code->eval(this->info);
	}
	string prnt() {
		return code->toString();
	}
	ExpR0* optmz(list<pair<std::string, int>> *_info) {
		return code->opt(_info);
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

/* 15) ? extend your random generation function from R0 to R1
- have the env that records which variables are bound by prior lets
and allow these variables to be used in depth - 0 expressions
- if none are yet defined-- > 2 options: have one initial x w value
or do read or random #
*/
// 
ExpR0* randP(list<pair<string, int>> *_info, int n) {
	(*_info).push_back(std::make_pair("x", 10));
	if (n == 0) {
		int temp_1 = rand();
		if ((temp_1 % 3) == 0) {
			mode = Interactive;
			return R();
		}
		else if((temp_1 % 3) == 1) {
			return I();
		}
		else {
			pair<std::string, int> *temp_pair = new pair<std::string, int>();
			*temp_pair = (_info)->back();
			return V(temp_pair->first);
		}
	}
	else {
		int temp_2 = rand() % 3;
		if ((temp_2) == 0)
			return N(randP(_info,n - 1));
		else if ((temp_2) == 1) 
			return A(randP(_info,n - 1), randP(_info,n - 1));
		else {
			list<pair<string, int>> *new_info = new list<pair<string, int>>();
			*new_info = *_info;
			return L(V("x"), randP(new_info, n - 1), randP(new_info, n - 1));
		}
	}
}

// -----------------------------------------------------------------------------------------------------------
//				-	-	-----			-------	----- -   - -----
//				 - -	-	-			   ---	-	- --  - -
//				  -		-	-	-----	  ---	-	- - - - ----
//				 - -	-	-			 ---	-	- -  -- -
//				-	-   -----			-------	----- -   - -----
// -----------------------------------------------------------------------------------------------------------

/*
	18) +/- define data types for X0 program ASTs
		- var = var-not-otherwise-mentioned
		- - label = string
		- register = ...
		- arg = ...
		- instr = ...
		- - blk = ... --> dodaj - sadrzi informacije o machine stateu/ovima i instrukciju
		- - p = ... --> sadrzi - informacije o machine stateu/ovima i label s odgovarajucim blockom
	19) ? write an emitter for X0 programs
		- should emit in the syntax of the assembler you will use
		- takes a parameter whether variables should be allowed in the output
		- only makes sense for debugging
	20) 1/12 build a test suite of a dozen X0 programs
		- intrp should ony ret value of rax on retq rather than entire state of machine
		- ideally these programs are manually compiled versions of your R1 test programs
	21) +/- write an interpreter for X0 programs
		- register file is simple fixed vector where registers are indices and the stack is stack
		- have to have special case for when you callq to system function like read or print
	22) ? connect your X0 test suite to system assembler
		- create intermediate file containing the assembly on disk - you can look at assembly
		  you producing during compilation in the future
		- automatically compare results of assembled program and your interpreter
*/

/*
	main:	movq $10, %rax
			addq $32, %rax
			movq %rax, %rdi
			callq print_int
			movq $0, %rax retq

	- p		::=		program		info	[label->block]	... sve labele po programu
	- blk	::=		block		info	instr			... sve instrukcije po bloku
	+ instr	::=		  (addq arg arg)
					| (subq arg arg)
					| (movq arg arg)
					| (retq)
					| (negq arg)
					| (callq label)
					| (pushq arg)
					| (popq arg)
	+ arg	::=		  $int		-> number
					| %reg		-> registar
					- | int(%reg) -> memory
					- | var(x)
	+ reg	::=		  rsp
					| rbp
					| rax
					| rbx
					| rcx
					| rdx
					| rsi
					| rdi
					| r8
					| r9
					| r10
					| r11
					| r12
					| r13
					| r14
					| r15
	- label	::=		string			
	- var	::=		not_otherwise_mentioned_variable
	+ X860	::=		(instr+)
*/

/*
// stack implementation for registers: rsp | rbp
struct Node {
	int data;
	Node *link;
};

//static Node *rbp = new Node();
//static Node *rsp = new Node();
static Node *top = NULL;

// register ::= rax | rbx | rcx | rdx | rsi | rdi | r8 | r9 | r10 | r11 | r12 | r13 | r14 | r15
static list<pair<std::string, int>> RegistersX0 = {
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
	//std::make_pair("rsp", 0),
	//std::make_pair("rbp", 0)
};

// program counter
static int pcnt;

// arg ::= $int | %reg | int(%reg)
class ArgX0 {
public:
	int virtual eval(list<pair<std::string, int>> *_regs) = 0;
	void virtual setValue(int _value) = 0;
	string virtual getName(void) = 0;
	string virtual toString(void) = 0;
private:
};

// $int <-- arg
class IntX0 : public ArgX0 {
public:
	void setValue(int _value) {
		this->value = _value;
	}
	string getName(void) {
		return "Integer type has no name.";
	};
	IntX0(int _value) {
		this->value = _value;
	}
	int eval(list<pair<std::string, int>> *_regs) {
		return this->value;
	}
	string toString() {
		return "$" + to_string(this->value);
	}
private:
	int value;
};

// %reg <-- arg
class RegX0 : public ArgX0 {
public:
	RegX0(string _name) {
		this->name = _name;
	}
	int eval(list<pair<std::string, int>> *_regs) {
		this->regs = _regs;
		for (std::list<pair<std::string, int>>::iterator it = this->regs->begin(); it != this->regs->end(); ++it) {
			if ((*it).first == this->name) {
				this->setValue((*it).second);
				return this->value;
			}
		}
		return 1;
	}
	void setValue(int _value) {
		this->value = _value;
	}
	string getName() {
		return this->name;
	}
	string toString() {
		return "%" + this->name;
	}
private:
	int value;
	string name;
	list<pair<std::string, int>> *regs;
};
*/

/*
// int (%reg) <-- arg
class IntRegX0 : public ArgX0 {
public:
	IntRegX0(int _offset, string _name) {
		this->name = _name;
		this->offset = _offset;
		// this->value = getVal(lookupList(this->name));
	}
	int eval(list<pair<std::string, int>> *_regs) {
		this->regs = _regs;
	}
	void setValue(int _value) {
		this->value = _value;
	}
	string getName() {
		return this->name;
		// setVal(this-> name, this->value);
	}
	string toString() {
		return to_string(this->offset) + "(%" + this->name + ")";
	}
private:
	int value, offset;
	string name;
	list<pair<std::string, int>> *regs;
};

// var (x) <-- var
class VarX0 : public ArgX0 {
public:
	VarX0(string _name) {
		this->name = _name;
	}
	int eval(list<pair<std::string, int>> *_regs) {
		return this->value;
	}
	void setValue(int _value) {
		// imagining this would be updated
		this->value = _value;
	}
	string getName() {
		return this->name;
	}
	string toString() {
		return "var(" + this->name + ")";
	}
private:
	string name;
	int value;
	list<pair<std::string, int>> *regs;
};
*/

/*
//instruction ::= (addq arg arg) | (subq arg arg) | (movq arg arg) | (retq) | (negq arg) | (callq label) | (pushq arg) | (popq arg)
class InstrX0 {
public:
	virtual int eval(list<pair<std::string, int>> *_regs) {
		return 10;
	}
	virtual string toString() {
		return "Error InstrX0 class had to do print.\n";
	}
private:
};

// (popq arg) <-- instruction
class PopqX0 : public InstrX0 {
public:
	PopqX0(ArgX0* _dest) {
		this->dest = _dest;
	}
	bool isEmpty() {
		if (top == NULL)
			return true;
		return false;
	}
	int pop(void) {
		Node *tmp = top;
		int value = top->data;
		top = top->link;
		delete (tmp);
		return value;
	}
	int eval(list<pair<std::string, int>> *_regs) {
		this->regs = _regs;
		for (std::list<pair<std::string, int>>::iterator it = this->regs->begin(); it != this->regs->end(); ++it) {
			if ((*it).first == this->dest->getName()) {
				if (!isEmpty()) {
					((*it).second = pop());
				}
				else {
					cout << "\tStack is empty, there is nothing there to pop.\n";
					return 8;
				}
				return 0;
			}
		}
		cout << "\tError register name for arg in pop command:" << this->dest->getName() << "\n";
		return 8;
	}
	string toString() {
		return "\tpopq\t\t" + this->dest->toString() + "\n";
	}
private:
	ArgX0 *dest;
	list<pair<std::string, int>> *regs;
};

// (pushq arg) <-- instruction
class PushqX0 : public InstrX0 {
public:
	PushqX0(ArgX0* _src) {
		this->src = _src;
	}
	void push(int _value) {
		Node *rsp = new Node();
		rsp->data = _value;
		rsp->link = top;
		top = rsp;
	}
	int eval(list<pair<std::string, int>> *_regs) {
		this->regs = _regs;
		for (std::list<pair<std::string, int>>::iterator it = this->regs->begin(); it != this->regs->end(); ++it) {
			if ((*it).first == this->src->getName()) {
				(push((*it).second));
				return 0;
			}
		}
		cout << "\tError register name for arg in push command:" << this->src->getName() << "\n";
		return 7;
	}
	string toString() {
		return "\tpushq\t\t" + this->src->toString() + "\n";
	}
private:
	ArgX0 *src;
	list<pair<std::string, int>> *regs;
};

// (retq) <-- instruction (function marking success with storing 0 in %rax)
class RetqX0 : public InstrX0 {
public:
	RetqX0() {}
	int eval(list<pair<std::string, int>> *_regs) {
		this->regs = _regs;
		for (std::list<pair<std::string, int>>::iterator it = this->regs->begin(); it != this->regs->end(); ++it) {
			if ((*it).first == "rax") {
				(*it).second = 0;
				success = true;
				return 0;
			}
		}
		success = false;
		return 6;
	}
	string toString() {
		if (success) {
			return "\tretq\n\n\t\t('The code was executed successfully')\n\n";
		}
		else {
			return "\tretq\n";
		}
	}
private:
	bool success = false;
	list<pair<std::string, int>> *regs;
};

// (callq print_int) <-- instruction (function printing out %rdi)
class CallqX0 : public InstrX0 {
public:
	CallqX0() {
	}
	int eval(list<pair<std::string, int>> *_regs) {
		this->regs = _regs;
		for (std::list<pair<std::string, int>>::iterator it = this->regs->begin(); it != this->regs->end(); ++it) {
			if ((*it).first == "rdi") {
				value = (*it).second;
				return 0;
			}
		}
		return 5;
	}
	string toString() {
		return ("\tcallq\t\tprint_int\n\n\t\t('Value at %rdi: " + to_string(this->value) + "')\n\n");
	}
private:
	int value;
	list<pair<std::string, int>> *regs;
};

// (negq arg) <-- instruction
class NegqX0 : public InstrX0 {
public:
	NegqX0(ArgX0* _dest) {
		this->dest = _dest;
	}
	int eval(list<pair<std::string, int>> *_regs) {
		this->regs = _regs;
		for (std::list<pair<std::string, int>>::iterator it = this->regs->begin(); it != this->regs->end(); ++it) {
			if ((*it).first == this->dest->getName()) {
				((*it).second = -this->dest->eval(this->regs));
				return 0;
			}
		}
		return 4;
	}
	string toString() {
		return "\tnegq\t\t" + this->dest->toString() + "\n";
	}
private:
	ArgX0 *dest;
	list<pair<std::string, int>> *regs;
};

// (subq arg, arg) <-- instruction
class SubqX0 : public InstrX0 {
public:
	SubqX0(ArgX0* _src, ArgX0* _dest) {
		this->src = _src;
		this->dest = _dest;
	}
	int eval(list<pair<std::string, int>> *_regs) {
		this->regs = _regs;
		for (std::list<pair<std::string, int>>::iterator it = this->regs->begin(); it != this->regs->end(); ++it) {
			if ((*it).first == this->dest->getName()) {
				((*it).second = this->src->eval(this->regs) - this->dest->eval(this->regs));
				return 0;
			}
		}
		return 3;
	}
	string toString() {
		return "\tsubq\t\t" + this->src->toString() + ",\t" + this->dest->toString() + "\n";
	}
private:
	ArgX0 *src, *dest;
	list<pair<std::string, int>> *regs;
};

// (addq arg, arg) <-- instruction
class AddqX0 : public InstrX0 {
public:
	AddqX0(ArgX0* _src, ArgX0* _dest) {
		this->src = _src;
		this->dest = _dest;
	}
	int eval(list<pair<std::string, int>> *_regs) {
		this->regs = _regs;
		for (std::list<pair<std::string, int>>::iterator it = this->regs->begin(); it != this->regs->end(); ++it) {
			if ((*it).first == this->dest->getName()) {
				((*it).second = this->src->eval(this->regs) + this->dest->eval(this->regs));
				return 0;
			}
		}
		return 2;
	}
	string toString() {
		return "\taddq\t\t" + this->src->toString() + ",\t" + this->dest->toString() + "\n";
	}
private:
	ArgX0 *src, *dest;
	list<pair<std::string, int>> *regs;
};

// (movq arg arg) <-- instruction
class MovqX0 : public InstrX0 {
public:
	MovqX0(ArgX0* _src, ArgX0* _dest) {
		this->src = _src;
		this->dest = _dest;
	}
	int eval(list<pair<std::string, int>> *_regs) {
		this->regs = _regs;
		for (std::list<pair<std::string, int>>::iterator it = this->regs->begin(); it != this->regs->end(); ++it) {
			if ((*it).first == this->dest->getName()) {
				((*it).second = this->src->eval(this->regs));
				return 0;
			}
		}
		return 1;
	}
	string toString() {
		return "\tmovq\t\t" + this->src->toString() + ",\t" + this->dest->toString() + "\n";
	}
private:
	list<pair<std::string, int>> *regs;
	ArgX0 *src;
	ArgX0 *dest;
};

//X860  ::= (instr+)
class ProgramX0 {
public:
	ProgramX0(list<std::unique_ptr<InstrX0>> *_instructions) {
		pcnt = 0;
		this->instructions = _instructions;
	}
	void execute(list<pair<std::string, int>> *_regs) {
		this->regs = _regs;
		cout << "\nProgram:\n\n";
		for (list<std::unique_ptr<InstrX0>>::iterator it = this->instructions->begin(); it != this->instructions->end(); ++it) {
			if ((*it)->eval(this->regs) == 0) {
				cout << pcnt << "\t" << (*it)->toString();
				pcnt += 8;
			}
			else {
				cout << "\n\tError executing program.\n\tCheck Address: " << pcnt << ".\n\n";
				cout << (*it)->toString();
			}
		}
		pcnt = 0;
		cout << "\n\tExecution is done.\n\n" << "\nMemory:\n\n" << "\tRegister\tValue\n";
		for (list<pair<std::string, int>>::iterator it = this->regs->begin(); it != this->regs->end(); ++it) {
			cout << "\t" << (*it).first << "\t\t" << to_string((*it).second) << "\n";
		}
		cout << "\n";
	}
private:
	list<pair<std::string, int>> *regs;
	list<std::unique_ptr<InstrX0>> *instructions;
};
*/

// -----------------------------------------------------------------------------------------------------------
//				 ----	-----			-------	----- -   - -----
//				-	 -	-	-			   ---	-	- --  - -
//				-		-	-	-----	  ---	-	- - - - ----
//				-	 -	-	-			 ---	-	- -  -- -
//				 ----   -----			-------	----- -   - -----
// -----------------------------------------------------------------------------------------------------------

/*
	23) ! define data types for C0 program ASTs
		- var = ...
		- label = ...
		- arg = ...
		- exp = ...
		- stmt = ...
		- tail = ...
		- p = ...
	24) ! write a pretty printer for C0 programs
		- purely debugging tool
	25) 1/12 build a test suite of a dozen C0 programs
		- manually compiled versions of R1 test programs
	26) ! write an interpreter for C0 programs
		- should use global environment for variables values and should error
		  when undefined variables are referenced
*/

/*
	Ivan Blaskic [ @UML 4Jay's-CC-class ]
	C0Language.hpp

	arg		::= int
			  | var

	exp		::= arg
			  | (read)
			  | (- arg)
			  | (+ arg arg)

	stmt	::= (assign var exp)
			  | (return arg)

	C0   ::= (program (var*) stmt+)

	C Code: progC0
		- receives list of stmts initialized in main
		- executes in a way that it receives all variables necessary for execution
			- goes statement by statement
				- evaluates sharing list of variables

	R --> C:	flatten in the deepest node
					--> creates new list of statements and variables when returning
				flatten in operation node
					--> adds new statement to existing set of statements received from arguments
*/

/*

static list<pair<string, int>> variables;

// (exp)
class ExpC0 {
public:
	virtual int eval(list<pair<string, int>> *_vars) = 0;
	string virtual toString() = 0;
private:
};

// (argument)
class ArgC0 : public ExpC0 {
public:
	virtual int eval(list<pair<string, int>> *_vars) = 0;
	string virtual toString() = 0;
private:
};

// (int) <-- argument
class IntC0 : public ArgC0 {
public:
	IntC0(int _value) {
		this->value = _value;
	}
	int eval(list<pair<string, int>> *_vars) {
		return this->value;
	}
	string toString() {
		return "\t(" + to_string(this->value) + ")";
	}
private:
	int value;
};

// (var) <-- argument
class VarC0 : public ArgC0 {
public:
	VarC0(string _name) {
		this->name = _name;
	}
	int setVal(int _value, list<pair<string, int>> *_vars) {
		this->vars = _vars;
		for (list<pair<string, int>>::iterator it = this->vars->begin(); it != this->vars->end(); it++) {
			if ((*it).first == this->name) {
				(*it).second = _value;
				return 0;
			}
		}
		cout << "\tVariable: " << this->name << " is not found.\n";
		return 1;
	}
	int eval(list<pair<string, int>> *_vars) {
		this->vars = _vars;
		for (list<pair<string, int>>::iterator it = this->vars->begin(); it != this->vars->end(); it++) {
			if ((*it).first == this->name) {
				return (*it).second;
			}
		}
		cout << "\tVariable: " << this->name << " is not found.\n";
		return 1;
	}
	string toString() {
		return "\t(" + this->name + ")";
	}
private:
	list<pair<string, int>> *vars;
	string name;
};

// (read) <-- exp
class ReadC0 : public ExpC0 {
public:
	ReadC0() {}
	int eval(list<pair<string, int>> *_vars) {
		cout << "Enter the integer value for (read): ";
		cin >> this->value;
		cout << "\n";
		return this->value;
	}
	string toString() {
		return "\t(read)";
	}
private:
	int value;
	list<pair<string, int>> *vars;
};

// (- arg) <-- exp
class NegC0 : public ExpC0 {
public:
	NegC0(ArgC0 *_arg) {
		this->arg = _arg;
	}
	int eval(list<pair<string, int>> *_vars) {
		this->vars = _vars;
		return (-this->arg->eval(this->vars));
	}
	string toString() {
		return "\t(- " + this->arg->toString() + ")";
	}
private:
	list<pair<string, int>> *vars;
	ArgC0 *arg;
};

// (+ arg arg) <-- exp
class AddC0 : public ExpC0 {
public:
	AddC0(ArgC0 *_left, ArgC0 *_right) {
		this->left = _left;
		this->right = _right;
	}
	int eval(list<pair<string, int>> *_vars) {
		this->vars = _vars;
		return (this->left->eval(this->vars) + this->right->eval(this->vars));
	}
	string toString() {
		return "\t(+ " + this->left->toString() + " " + this->right->toString() + ")";
	}
private:
	ArgC0 *left, *right;
	list<pair<string, int>> *vars;
};

// (stmt)
class StmtC0 {
public:
	virtual int eval(list<pair<string, int>> *_vars) = 0;
	virtual string toString() = 0;
private:
};

// (assign var exp) <-- stmt
class AssignC0 : public StmtC0 {
public:
	AssignC0(VarC0 *_var, ExpC0 *_exp) {
		this->var = _var;
		this->exp = _exp;
	}
	int eval(list<pair<string, int>> *_vars) {
		this->vars = _vars;
		if (this->var->setVal(this->exp->eval(this->vars), this->vars) == 0) {
			return 0;
		}
		else {
			cout << "\tError setting value for: " << this->var->toString() << "\n";
			return 1;
		}
	}
	string toString() {
		return "\t(assign\t" + this->var->toString() + this->exp->toString() + ")\n";
	}
private:
	list<pair<string, int>> *vars;
	VarC0 *var;
	ExpC0 *exp;
};

// (return arg) <-- stmt
class RetC0 : public StmtC0 {
public:
	RetC0(ArgC0 *_arg) {
		this->arg = _arg;
	}
	int eval(list<pair<string, int>> *_vars) {
		this->vars = _vars;
		cout << "\t\t>> Return Value is " << this->arg->eval(this->vars) << " for following return statement <<\n";
		return 0;
	}
	string toString() {
		return "\t(return " + this->arg->toString() + ")\n";
	}
private:
	ArgC0 *arg;
	list<pair<string, int>> *vars;
};

// C0
class C0 {
public:
	virtual void execute(list<pair<string, int>> *vars_) = 0;
private:
};

// (program (var*) stmt+) <-- C0
class ProgC0 : public C0 {
public:
	ProgC0(list<std::unique_ptr<StmtC0>> *_stmts) {
		this->stmts = _stmts;
	}
	// called from deepest node returns newly initialized program C0 with return variable
	ProgC0(VarC0 *_var) {
		this->stmts = new list<std::unique_ptr<StmtC0>>();
		this->vars = new list<pair<string, int>>{ (make_pair(_var->toString(), 0)) };
		this->ret_arg = _var;
	}
	ProgC0() {
		this->stmts = new list<std::unique_ptr<StmtC0>>();
		this->vars = new list<pair<string, int>>();
	}
	// called from deepest node returns newly initialized program C0 with return value of int
	ProgC0(IntC0 *_int) {
		this->stmts = new list<std::unique_ptr<StmtC0>>();
		this->vars = new list<pair<string, int>>();
		this->ret_arg = _int;
	}
	ProgC0(ArgC0 *ass_arg, VarC0 *_var, ProgC0 *_prog) {
		this->stmts = _prog->stmts;
		this->vars = _prog->vars;
		this->stmts->emplace_back(new AssignC0(_var, ass_arg));
		this->ret_arg = _var;
	}
	// called after flattening arguments in operations so we have program with assignment statements that happened in them
	ProgC0(ExpC0 *_exp, VarC0 *_var, ProgC0 *_merging_one, ProgC0 *_merging_two) {
		this->stmts = _merging_one->stmts;
		this->stmts->emplace_back(_merging_two->stmts);
		this->vars = _merging_one->vars;
		this->vars->emplace_back(_merging_two->vars);
		this->stmts->emplace_back(new AssignC0(_var, _exp));
		this->ret_arg = _var;
	}
	void execute() {
		cout << "\nProgram:\n\n";
		for (std::list<std::unique_ptr<StmtC0>>::iterator it = this->stmts->begin(); it != this->stmts->end(); ++it) {
			if ((*it)->eval(this->vars) == 0) {
				cout << "\t" << (*it)->toString();
			}
			else {
				cout << "\n\tError executing program.\n\tCheck statement: " << (*it)->toString() << "\n";
			}
		}
		StmtC0 *ret_var = new RetC0(this->ret_argument());
		cout << "\t" << ret_var->toString();
		cout << "\n\tExecution is done.\n\n" << "\nMemory:\n\n" << "\tVariable\tValue\n";
		for (std::list<pair<std::string, int>>::iterator it = this->vars->begin(); it != this->vars->end(); ++it) {
			cout << "\t" << (*it).first << "\t\t" << (*it).second << "\n";
		}
		cout << "\n";
	}
	void execute(list<pair<string, int>> *_vars) {
		this->vars = _vars;
		cout << "\nProgram:\n\n";
		for (std::list<std::unique_ptr<StmtC0>>::iterator it = this->stmts->begin(); it != this->stmts->end(); ++it) {
			if ((*it)->eval(vars) == 0) {
				cout << "\t" << (*it)->toString();
			}
			else {
				cout << "\n\tError executing program.\n\tCheck statement: " << (*it)->toString() << "\n";
			}
		}
		StmtC0 *ret_var = new RetC0(this->ret_argument());
		cout << "\t" << ret_var->toString();
		cout << "\n\tExecution is done.\n\n" << "\nMemory:\n\n" << "\tVariable\tValue\n";
		for (std::list<pair<std::string, int>>::iterator it = vars->begin(); it != vars->end(); ++it) {
			cout << "\t" << (*it).first << "\t\t" << (*it).second << "\n";
		}
		cout << "\n";
	}
	ArgC0* ret_argument(void) {
		return this->ret_arg;
	}
private:
	list<pair<string, int>> *vars;
	list<std::unique_ptr<StmtC0>> *stmts;
	ArgC0 *ret_arg;
};

*/

#endif