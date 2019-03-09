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
	16) + write some R1-specific optimizer test
	17) + extend your optimizer from R0 to R1
		- you should inline variables that have been reduced to values or other variables
	18) + define data types for X0 program ASTs
		- var = var-not-otherwise-mentioned
		- label = string
		- register = ...
		- arg = ...
		- instr = ...
		- blk = ...
		- p = ...
	19) + write an emitter for X0 programs
		- should emit in the syntax of the assembler you will use 
		- takes a parameter whether variables should be allowed in the output
		- only makes sense for debugging
	20) 1/12 build a test suite of a dozen X0 programs
		- intrp should ony ret value of rax on retq rather than entire state of machine
		- ideally these programs are manually compiled versions of your R1 test programs
	21) + write an interpreter for X0 programs
		- register file is simple fixed vector where registers are indices and the stack is stack
		- have to have special case for when you callq to system function like read or print
	22) + connect your X0 test suite to system assembler 
		- create intermediate file containing the assembly on disk - you can look at assembly 
		  you producing during compilation in the future 
		- automatically compare results of assembled program and your interpreter
	23) + define data types for C0 program ASTs
		- var = ...
		- label = ...
		- arg = ...
		- exp = ...
		- stmt = ...
		- tail = ...
		- p = ...
	24) + write a pretty printer for C0 programs
		- purely debugging tool
	25) 1/12 build a test suite of a dozen C0 programs
		- manually compiled versions of R1 test programs
	26) + write an interpreter for C0 programs
		- should use global environment for variables values and should error 
		  when undefined variables are referenced
	27) + write a few tests for uniquify that predict its output
		- this is only possible if your unique names are predictable
		- these tests should be explicitly designed to have multiple occurrences of the same variable in the input 
		  that mean different things
	28) + implement the uniquify pass for R1 programs
		- this accepts R1 programs and returns new R1 programs that are guaranteed 
		  to use unique variables in each let expression 
		- I recommend doing something to make the unique names deterministic, so it is possible to write tests
	29) 1/12 connect uniquify to your test suite
		- ensure that every test program behaves the same before and after the uniquify pass by using the R1 interpreter
	30) 1/6 write a half-dozen tests for resolve-complex that predict its output
		- write a half-dozen tests for resolve-complex that predict its output
		- work through the complicated examples and especially ensure that you don’t introduce aliases unnecessarily
	31)	+ implement the resolve-complex pass for R1 programs
		- this accepts R1 programs and returns new R1 programs that do not use complex expressions in argument positions 
		- we can express this as a new language
	32) + connect resolve-complex to your test suite
		- ensure that every test program behaves the same before and after resolve-complex by using the R1 interpreter 
		- you could also write a function that checks to see if your result is in the correct form 
		- remember, this pass requires uniquify to have already run
	33) 1/6 write a half-dozen tests for explicate-control that predict its output
		- work through the complicated examples and especially ensure that the order of operations (especially read calls) 
		  is preserved
	34) + implement the explicate-control pass for R1 programs
		- this accepts R1 programs and returns new C0 programs by lifting variables definitions 
		  outside of the bound expression position of let forms 
		- remember to use the mutually recursive functions explicate-control-tail and explicate-control-assign
	35) + connect explicate-control to your test suite
		- ensure that every test program behaves the same before and after explicate-control by using the C0 interpreter 
		- remember, this pass requires resolve-complex to have already run
	36) + write a few tests for uncover-locals that predict its output
		- this should be very easy to do!
	37) + implement the uncover-locals pass for C0 programs
		- this pass collects the set of variables used in the program 
		  and stores them for later passes in the auxiliary field of C0 programs
	38)	+ connect uncover-locals to your test suite
		- ensure that every test program behaves the same before and after uncover-locals by using the C0 interpter 
		- this is trivial because uncover-locals shouldn’t effect the behavior of programs 
		- you’re just doing this to make sure you call it and to make you didn’t accidentally change anything important 
		  during this pass
	39) 1/6 write a half-dozen tests for select-instr that predict its output
		- you’ll want to make sure that you maintain the correct order and select the write assembly instructions
	40) + implement the select-instr pass for C0 programs
		- this pass takes C0 programs and returns X0 programs 
		- it should preserve the set of variables used in the program
		- remember to use helper functions for each kind of C0 AST
	41) + connect select-instr to your test suite
		- ensure that every test program behaves the same before and after select-instr by using the X0 interpreter

		  ASSIGN()
	42) ! write a few tests for assign-homes that predict its output
		- you’ll want to make sure that the output program contains no variables 
		  and that variables are assigned homes consistently
	43) ! implement the assign-homes pass for X0 programs
		- this pass takes X0 programs and returns new X0 programs which do not mention variables
		- for now, it should just assign everything to consistent stack locations in an arbitrary way 
		  based on the set of variables used in the program
	44) ! connect assign-homes to your test suite
		- ensure that every test program behaves the same before and after assign-homes by using the X0 interpreter 
		- you may want to also include a check that guarantees the result contains no variable references

		  PATCH()
	45) 0/6 write a half-dozen tests for patch-instructions that predict its output
		- you’ll want to make sure memory references are legal
	46) ! implement the patch-instructions pass for X0 programs
		- this pass takes X0 programs and returns new X0 programs which mention memory 
		  either zero or one times per instruction
	47) ! connect patch-instructions to your test suite
		- ensure that every test program behaves the same before and after patch-instructions 
		  by using the X0 interpreter
		- remember, this pass assumes that assign-homes has run

		  TOUCHDOWN(:
	48) ! implement your language runtime
		- initially, this is just two functions: read_int and print_int 
		- the first corresponds to the read call and the second is automatically used at the end of programs
	49) ! implement the main-generation pass for X0 programs
		- this pass should extend your final X0 programs with the prelude and postlude operations 
		  that set up the stack pointer appropriately for your code
	50) ! connect your test suite to your system assembler and language runtime
		- close the final knot and get an actual compiler by having your final X0 programs 
		  (that come out of main-generation) sent to the system assembler and linked with your language runtime 
		- you finally have a working compiler! Aren’t you proud? 

		  UNCOVER-LIVE()
	51) ! write a dozen tests for uncover-live that predict its output
		- I don’t remember using examples from real programs, because they are likely to be too complicated
		- instead, use simple ones that you come up with by hand
	52) ! implement the uncover-live pass for X0 programs
		- this pass takes X0 programs and returns new X0 programs 
		  where the block’s auxiliary field contains a list of live-after sets corresponds to each instruction 
		- make sure that you add registers to the live sets, not just variables

		D-

*/

/*
	RC0	:=		p	=	(program	info	e)
				e	=	(arg)	|	(let	x	c	e)
				c	=	(read)	|	(-	arg)	|	(+	arg	arg)
				arg	=	(number)|	(var)

	RCO	:		e	x	(x	-->	 e)		-->		list (x * e) x e

	Program has expression where arguments are further expressions as input.
	Program has list of variables refering to expressions and argument being returned.

*/

/*
	OPTIMIZER's JOB example:

		(+ [+ (+ [5] [read]) (+ [10] [12])] [+(+ [read] [read]) (+ [12] [read])])
		opt (+ [+ (+ [5] [read]) (+ [10] [12])] [+(+ [read] [read]) (+ [12] [read])])
		= opt (+ [+ (27) (read)] [+ (12) (+ [+ (read) (read)] [read])])
		= (+ [39] [+ (+ [+ (read) (read)] [read]) (read)]
		opt [+ (+ [5] [read]) (+ [10] [12])] = opt [+ (+ [5] [read]) (22)] = [+ (27) (read)]
		opt (+ [5] [read]) = (+ [5] [read])
		opt (+ [10] [12]) = (22)
		opt [+ (+ [read][read])(+ [12] [read])] = (+ [(12)] [+ (+ [read] [read]) (read)])
		opt [+ (read) (read)] = (+ [read] [read])
		opt [+ (12) (read)] = (+ [12] [read])
*/

/*
	30) ! write a half-dozen tests for resolve-complex that predict its output
		- write a half-dozen tests for resolve-complex that predict its output
		- work through the complicated examples and especially ensure that you don’t introduce aliases unnecessarily
	31)	! implement the resolve-complex pass for R1 programs
		- this accepts R1 programs and returns new R1 programs that do not use complex expressions in argument positions
		- we can express this as a new language
	32) ! connect resolve-complex to your test suite
		- ensure that every test program behaves the same before and after resolve-complex by using the R1 interpreter
		- you could also write a function that checks to see if your result is in the correct form
		- remember, this pass requires uniquify to have already run

	in:		(+ [+ 2 3] [let x = read in (+ x x)])

	out:	let y	=	(+ 2  3 )	in
			let x'	=	(read)		in
			let z	=	(+ x' x')	in
			let x	=	(+ y  z )	in
				x

	in:		let x	8	(+ x x)
	out:	let z	=	(+ 8 8)		in
				z
*/

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

// -----------------------------------------------------------------------------------------------------------
//				-	-	-----			-------	----- -   - -----
//				 - -	-	-			   ---	-	- --  - -
//				  -		-	-	-----	  ---	-	- - - - ----
//				 - -	-	-			 ---	-	- -  -- -
//				-	-   -----			-------	----- -   - -----
// -----------------------------------------------------------------------------------------------------------

// X0: steps 18-22 --> compiling C0 into X0
//	   steps 42-44 --> assign-homes for putting vars in place --> from X0 w vars in2 X0 w/o vars

/*
	18) + define data types for X0 program ASTs
	19) + write an emitter for X0 programs - obicni toString jel...
		- should emit in the syntax of the assembler you will use
		- takes a parameter whether variables should be allowed in the output
		- only makes sense for debugging
	20) 1/12 build a test suite of a dozen X0 programs - jasno trivijalno
		- intrp should ony ret value of rax on retq rather than entire state of machine
		- ideally these programs are manually compiled versions of your R1 test programs
	21) + write an interpreter for X0 programs - interpretator jasno
		- register file is simple fixed vector where registers are indices and the stack is stack
		- have to have special case for when you callq to system function like read or print
	22) ? connect your X0 test suite to system assembler --> google the shit out of it
		- create intermediate file containing the assembly on disk - you can look at assembly
		  you producing during compilation in the future
		- automatically compare results of assembled program and your interpreter

	ASSIGN() - 1st step of "Register Allocation" problem
	42) ! write a few tests for assign-homes that predict its output
		- you’ll want to make sure that the output program contains no variables
		  and that variables are assigned homes consistently
	43) ! implement the assign-homes pass for X0 programs
		- this pass takes X0 programs and returns new X0 programs which do not mention variables
		- for now, it should just assign everything to consistent stack locations in an arbitrary way
		  based on the set of variables used in the program
	44) ! connect assign-homes to your test suite
		- ensure that every test program behaves the same before and after assign-homes by using the X0 interpreter
		- you may want to also include a check that guarantees the result contains no variable references

input:	assign (program info_for_the_program [BODY -> (block info_for_the_block) Instruction_Set])
			--> in info_for_the_program we have local variables = set of variables --> need spots
			--> local-vars = (x1, ..., xN)
			--> stack will be increased by N spots
			--> find all of the variables and replace them with corresponding stack location

output:	program (ip w/o local-vars) [
			BEGIN -> (block 0 [pushq RBP;	movq RSP, RBP;	subq VC, RSP;	jmp BODY;])
			END	  -> (block 0 [addq VC,RSP;	popq RBP;		retq])
			BODY  -> (block ib (assign o Instruction_Set))
		])
		
		o[rou] = [x1 --> %RSP(8x1), ..., xN --> %RSP(8xN)]
			--> you go through instruction set and look at the arguments 
			--> if argument is a variable then replace it with the given mapping

		VC = 8 x (N or N+1) --> must be divisible by 16 --> e.g. if N=5 then N+1=6 * 8 
			--> floating point vector registers want to be pushed on stack
			--> 256b --> you cannot look at the individual pieces of it
			--> at the bottom of the address those numbers are garantied to be 0s
			--> if we push FP values on top of stack --> has to be div by 16 bc we have to count on those 0s being there
			--> check if N is even and if not then add 1 to it o.w. it's all good

		RBP --> pointer to the top of the last function_call's frame --> Callee's save register
			--> add something to it and then subtract it later
		
		Caller Frame is calling function frame
		Callee Frame is being called frame

		assignIS o[rou] [empty_list]	=	[empty_list]
						(i: is)			=	(assign o[rou] i): (assign o[rou] is) --> assign on 1 intruction and then the rest

		assignI o[rou]	(addq aL,aR) = addq (assign o[rou] aL) (assign o[rou] aR)
						(negq aR)	 = negq (assign o[rou] aR)
						(movq aS,aD) = movq (assign o[rou] aS) (assign o[rou] aD)
						(jmp LAB)	 = jmp LAB
						(callq LAB)	 = callq LAB

		assignA o[rou] (num n) = (num n)
		assignA o[rou] (var x) = o[rou](x)
		
*/

/*
	main:	movq $10, %rax
			addq $32, %rax
			movq %rax, %rdi
			callq print_int
			movq $0, %rax retq

	+ p		::=		program		info	[label->block]	...
	+ blk	::=		block		info	instr			...
	+ instr	::=		  (addq arg arg)					{[q = quad = 4*normal size of number = 4*16b]}
					| (subq arg arg)
					| (movq arg arg)
					| (retq)			{[escape & say what's rax]}
					| (negq arg)
					| (callq label)		{[callq _read_int]}
					| (pushq arg)		{[(%rsp)->ms(%rsp)-8] [%rsp(0)->ms(src)]}
					| (popq arg)		{[(%rsp)->ms(dst)] [%rsp->ms(%rsp)+8]}
					| (jmp label)		{[xbi ms label]}
	+ arg	::=		  $int					-> number
					| %reg					-> registar
					| %reg(offset)			-> memory
					| var(x)				-> variable
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
	+ label	::=		string
	+ var	::=		not_otherwise_mentioned_variable
	+ X860	::=		(instr+)
*/

class LabelX0;
class BlockX0;
class InstrX0;

// label --> block	LIST
static list<pair<std::shared_ptr<LabelX0>,std::shared_ptr<BlockX0>>> label_block_list;
static list<pair<std::string, int>> init_variables_list;
static list<std::shared_ptr<InstrX0>> blk_body_list;
static list<std::shared_ptr<InstrX0>> blk_end_list;

// stack implementation for registers: rsp | rbp
static struct Node {
	int data;
	Node *link;
};

static int *StackX0 = new int[100];

//static Node *rbp = new Node();
//static Node *rsp = new Node();
static Node *top = NULL;

// register ::= rax | rbx | rcx | rdx | rsi | rdi | r8 | r9 | r10 | r11 | r12 | r13 | r14 | r15
static list<pair<std::string, int>> *RegistersX0 = new list<pair<std::string,int>> {
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

// program counter
static int pcnt;

// arg ::= $int | %reg | int(%reg) + var(x)
class ArgX0 {
public:
	int virtual eval() = 0;
	void virtual setValue(int _value) = 0;
	string virtual getName(void) = 0;
	string virtual toString(void) = 0;
	int virtual get_offset(void) = 0;
private:
};

// $int <-- arg - BRAVO
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
	int eval() {
		return this->value;
	}
	string toString() {
		return "$" + to_string(this->value);
	}
	int get_offset() {
		cout << "\n\tINT has no offset.\n";
		return 0;
	}
private:
	int value;
};
IntX0* IX(int _value) {
	return new IntX0(_value);
}

// %reg <-- arg
class RegX0 : public ArgX0 {
public:
	RegX0(string _name) {
		this->name = _name;
	}
	int eval() {
		// variables_list = _variables_list;
		for (std::list<pair<std::string, int>>::iterator it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == this->name) {
				this->setValue((*it).second);
				return this->value;
			}
		}
		return 1;
	}
	// set value is just setting local variable of that instance of class
	// is that what's expected?
	void setValue(int _value) {
		this->value = _value;
		std::list<pair<std::string, int>>::iterator it;
		for (it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == this->getName()) {
				((*it).second = this->value);
				return;
			}
		}
		cout << "\n\tError setting value for: " << this->getName() << "\n\n";
		return;
	}
	string getName() {
		return this->name;
	}
	string toString() {
		return "%" + this->name;
	}
	int get_offset() {
		return 0;
	}
private:
	int value;
	string name;
};
RegX0* RX(string _name) {
	return new RegX0(_name);
}

// %reg (offset) <-- arg
class IntRegX0 : public ArgX0 {
public:
	IntRegX0(int _offset, RegX0 *_reg) {
		this->reg = _reg;
		this->offset = _offset;
		// this->value = getVal(lookupList(this->name));
	}
	int eval() {
		// this->variables_list = _variables_list;
		if (this->reg->getName() == "rsp") {
			std::list<pair<std::string, int>>::iterator it;
			for (it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
				if ((*it).first == "rsp") {
					if (this->offset < 0) {
						if ((*it).second >= (this->offset*(-1))) {
							return StackX0[(*it).second + this->offset];
						}
						else {
							cout << "\n\tTried reaching the space that is below stack's range.\n";
						}
					}
					else {
						if ((this->offset + (*it).second) <= 99) {
							return StackX0[(*it).second + this->offset];
						}
						else {
							cout << "\n\tTried reaching the space that is above stack's range.\n";
						}
					}
				}
				else {
					cout << "\n\tCannot add offset to the integer type register. Tried doing so with: " << this->reg->getName() << ".\n";
				}
			}
		}
		return (this->offset + this->reg->eval());
	}
	void setValue(int _value) {
		this->value = _value;
	}
	string toString() {
		return this->reg->toString() + "(" + to_string(this->offset) + ")";
	}
	string getName() {
		return this->reg->getName();
	}
	int get_offset() {
		return this->offset;
	}
private:
	RegX0 *reg;
	int value, offset;
};
IntRegX0* IRX(int _offset, RegX0 *_reg) {
	return new IntRegX0(_offset, _reg);
}

// var (x) <-- arg
class VarX0 : public ArgX0 {
public:
	VarX0(string _name) {
		this->name = _name;
	}
	int eval() {
		std::list<pair<std::string, int>>::iterator it;
		for (it = init_variables_list.begin(); it != init_variables_list.end(); ++it) {
			if ((*it).first == this->name) {
				return (*it).second;
			}
		}
		cout << "Uninitialized Variable is Being Used Under Following name: " + this->name + "!\n";
		return this->value;
	}
	void setValue(int _value) {
		this->value = _value;
		std::list<pair<std::string, int>>::iterator it;
		for (it = init_variables_list.begin(); it != init_variables_list.end(); ++it) {
			if ((*it).first == this->getName()) {
				((*it).second = this->value);
				return;
			}
		}
		cout << "\n\tError setting value for: " << this->getName() << "\n\n";
		return;
	}
	string getName() {
		return this->name;
	}
	string toString() {
		return this->name;
	}
	int get_offset() {
		cout << "\n\tINT has no offset.\n";
		return 0;
	}
private:
	string name;
	int value;
};
VarX0* VX(string _name) {
	return new VarX0(_name);
}

//instruction ::= (addq arg arg) | (subq arg arg) | (movq arg arg) | (retq) | (negq arg) | (callq label) | (pushq arg) | (popq arg) | (jump label)
class InstrX0 {
public:
	//virtual ~InstrX0() { std::cout << "__PRETTY_FUNCTION__INSTR" << std::endl; }
	virtual int eval() = 0;
	virtual string toString() = 0;
	virtual bool isEnd() = 0;
	virtual bool isJump() = 0;
private:
};

// (popq arg) <-- instruction
class PopqX0 : public InstrX0 {
public:
	//~PopqX0() override { std::cout << "__PRETTY_FUNCTION__" << std::endl; }
	PopqX0(ArgX0* _dest) {
		this->dest = _dest;
	}
	bool isEmpty() {
		for (std::list<pair<std::string, int>>::iterator it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == "rsp") {
				if ((*it).second == 0) {
					return true;
				}
				else
					return false;
			}
		}
		/*
			if (top == NULL)
				return true;
			return false;
		*/
	}
	int pop(void) {
		for (std::list<pair<std::string, int>>::iterator it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == "rsp") {
				(*it).second -= 1;
				int temp = StackX0[(*it).second];
				StackX0[(*it).second] = 0;
				return temp;
			}
		}
		/*
			Node *tmp = top;
			int value = top->data;
			top = top->link;
			delete (tmp);
			return value;
		*/
	}
	int eval() {
		for (std::list<pair<std::string, int>>::iterator it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == this->dest->getName()) {
				if (!isEmpty()) {
					((*it).second = pop());
				}
				else {
					cout << "\n\tStack is empty, there is nothing there to pop.\n";
					return 8;
				}
				return 0;
			}
		}
		cout << "\n\tError register name for arg in pop command:" << this->dest->getName() << "\n";
		return 8;
	}
	string toString() {
		return "\tpopq\t\t" + this->dest->toString() + "\n";
	}
	bool isEnd() {
		return false;
	}
	bool isJump() {
		return false;
	}
private:
	ArgX0 *dest;
};
PopqX0* PopX(ArgX0 *_arg) {
	return new PopqX0(_arg);
}

// (pushq arg) <-- instruction
class PushqX0 : public InstrX0 {
public:
	//~PushqX0() override { std::cout << "__PRETTY_FUNCTION__PUSH" << std::endl; }
	PushqX0(ArgX0* _src) {
		this->src = _src;
	}
	void push(int _value) {
		for (std::list<pair<std::string, int>>::iterator it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == "rsp") {
				if ((*it).second < 99) {
					(*it).second += 1;
					StackX0[(*it).second-1] = _value;
					return;
				}
				else {
					cout << "\n\tTried doing push() when Stack was full.\n";
					return;
				}
			}
		}
		/*
			Node *rsp = new Node();
			rsp->data = _value;
			rsp->link = top;
			top = rsp;
		*/
	}
	int eval() {
		for (std::list<pair<std::string, int>>::iterator it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == this->src->getName()) {
				push((*it).second);
				cout << "\n\tPUSHING: " << (*it).second << "\n";
				return 0;
			}
		}
		cout << "\tError register name for arg in push command:" << this->src->getName() << "\n";
		return 7;
	}
	string toString() {
		return "\tpushq\t\t" + this->src->toString() + "\n";
	}
	bool isEnd() {
		return false;
	}
	bool isJump() {
		return false;
	}
private:
	ArgX0 *src;
};
PushqX0* PshX(ArgX0 *_arg) {
	return new PushqX0(_arg);
}

// (retq) <-- instruction (function marking success with storing 0 in %rax)
class RetqX0 : public InstrX0 {
public:
	//~RetqX0() override { std::cout << "__PRETTY_FUNCTION__RETQ" << std::endl; }
	RetqX0() {}
	int eval() {
		for (std::list<pair<std::string, int>>::iterator it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == "rax") {
				// (*it).second = 0;
				cout << "\tValue at %rax is : " << (*it).second << "\n\n";
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
	bool isEnd() {
		return true;
	}
	bool isJump() {
		return false;
	}
private:
	bool success = false;
};
RetqX0* RtX() {
	return new RetqX0();
};

// (callq read_int) <-- instruction (function printing out %rdi)
class CallqX0 : public InstrX0 {
public:
	//~CallqX0() override { std::cout << "__PRETTY_FUNCTION__CALLQ" << std::endl; }
	CallqX0() {
	}
	int eval() {
		cout << "\nType the input value -> ";
		cin >> this->value;
		for (std::list<pair<std::string, int>>::iterator it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == "rax") {
				(*it).second = this->value;
				cout << "\nInfo:\n\tValue at %rax is now: " << this->value << "\n\n";
				return 0;
			}
		}
		return 5;
	}
	string toString() {
		return "\tcallq\t\tread_int\n";
	}
	bool isEnd() {
		return false;
	}
	bool isJump() {
		return false;
	}
private:
	int value;
};
CallqX0* CllX() {
	return new CallqX0();
}

// (negq arg) <-- instruction
class NegqX0 : public InstrX0 {
public:
	//~NegqX0() override { std::cout << "__PRETTY_FUNCTION__NEGQ" << std::endl; }
	NegqX0(ArgX0* _dest) {
		this->dest = _dest;
	}
	int eval() {
		std::list<pair<std::string, int>>::iterator it;
		for (it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == this->dest->getName()) {
				((*it).second = -this->dest->eval());
				return 0;
			}
		}
		for (it = init_variables_list.begin(); it != init_variables_list.end(); ++it) {
			if ((*it).first == this->dest->getName()) {
				((*it).second = -this->dest->eval());
				return 0;
			}
		}
		return 4;
	}
	string toString() {
		return "\tnegq\t\t" + this->dest->toString() + "\n";
	}
	bool isEnd() {
		return false;
	}
	bool isJump() {
		return false;
	}
private:
	ArgX0 *dest;
};
NegqX0* NgX(ArgX0* _dest) {
	return new NegqX0(_dest);
}

// (subq arg, arg) <-- instruction
class SubqX0 : public InstrX0 {
public:
	//~SubqX0() override { std::cout << "__PRETTY_FUNCTION__SUBQ" << std::endl; }
	SubqX0(ArgX0* _src, ArgX0* _dest) {
		this->src = _src;
		this->dest = _dest;
	}
	int eval() {
		if (readValue(&rd_dst, this->dest->getName()) == 1)
			cout << "\n\tError Reading Values: " << this->src->getName() << " & " << this->dest->getName() << "\n\n";
		writeValue(this->rd_dst - this->rd_src);
		return 0;
	}
	string toString() {
		return "\tsubq\t\t" + this->src->toString() + ",\t" + this->dest->toString() + "\n";
	}
	bool isEnd() {
		return false;
	}
	int readValue(int *_val, string _name) {
		std::list<pair<std::string, int>>::iterator it;
		for (it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == _name) {
				*_val = (*it).second;
				src_rd++;
				if (src_rd == 1) {
					readValue(&this->rd_src, this->src->getName());
					return 0;
				}
				else {
					src_rd = 0;
					return 0;
				}
			}
		}
		for (it = init_variables_list.begin(); it != init_variables_list.end(); ++it) {
			if ((*it).first == _name) {
				*_val = (*it).second;
				src_rd++;
				if (src_rd == 1) {
					readValue(&this->rd_src, this->src->getName());
					return 0;
				}
				else {
					src_rd = 0;
					return 0;
				}
			}
		}
		return 1;
	}
	void writeValue(int _value) {
		this->dest->setValue(_value);
	}
	bool isJump() {
		return false;
	}
private:
	int src_rd = 0;
	int rd_src, rd_dst;
	ArgX0 *src, *dest;
};
SubqX0* SbX(ArgX0* _src, ArgX0* _dest) {
	return new SubqX0(_src, _dest);
}

// (addq arg, arg) <-- instruction
class AddqX0 : public InstrX0 {
public:
	//~AddqX0() override { std::cout << "__PRETTY_FUNCTION__ADDQ" << std::endl; }
	AddqX0(ArgX0* _src, ArgX0* _dest) {
		this->src = _src;
		this->dest = _dest;
	}
	int eval() {
		if (readValue(&rd_dst, this->dest->getName()) == 1)
			cout << "\n\tError Reading Values: " << this->src->getName() << " & " << this->dest->getName() << "\n\n";
		writeValue(this->rd_dst + this->rd_src);
		return 0;
	}
	int readValue(int *_val, string _name) {
		std::list<pair<std::string, int>>::iterator it;
		for (it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == _name) {
				*_val = (*it).second;
				src_rd++;
				if (src_rd == 1) {
					readValue(&this->rd_src, this->src->getName());
					return 0;
				}
				else {
					src_rd = 0;
					return 0;
				}
			}
		}
		for (it = init_variables_list.begin(); it != init_variables_list.end(); ++it) {
			if ((*it).first == _name) {
				*_val = (*it).second;
				src_rd++;
				if (src_rd == 1) {
					readValue(&this->rd_src, this->src->getName());
					return 0;
				}
				else {
					src_rd = 0;
					return 0;
				}
			}
		}
		return 1;
	}
	void writeValue(int _value) {
		this->dest->setValue(_value);
	}
	string toString() {
		return "\taddq\t\t" + this->src->toString() + ",\t" + this->dest->toString() + "\n";
	}
	bool isEnd() {
		return false;
	}
	bool isJump() {
		return false;
	}
private:
	int src_rd = 0;
	ArgX0 *src, *dest;
	int rd_src, rd_dst;
};
AddqX0* AdX(ArgX0* _src, ArgX0* _dest) {
	return new AddqX0(_src, _dest);
}

// (movq arg arg) <-- instruction
class MovqX0 : public InstrX0 {
public:
	//~MovqX0() override { std::cout << "__PRETTY_FUNCTION__MOVQ" << std::endl; }
	MovqX0(ArgX0* _src, ArgX0* _dest) {
		this->src = _src;
		this->dest = _dest;
	}
	int eval() {
		std::list<pair<std::string, int>>::iterator it;
		if (this->dest->getName() == "rsp") {
			for (it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
				if ((*it).first == this->dest->getName()) {
					if (this->dest->get_offset() < 0) {
						if ((*it).second >= (this->dest->get_offset()*(-1))) {
							StackX0[(*it).second + this->dest->get_offset()] = this->src->eval();
							return 0;
						}
						else {
							cout << "\n\tTried reaching the space that is below stack's range.\n";
							return 1;
						}
					}
					else {
						if ((this->dest->get_offset() + (*it).second) <= 99) {
							StackX0[(*it).second + this->dest->get_offset()] = this->src->eval();
							return 0;
						}
						else {
							cout << "\n\tTried reaching the space that is above stack's range.\n";
							return 1;
						}
					}
				}
			}
		}
		else {
			for (it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
				if ((*it).first == this->dest->getName()) {
					((*it).second = this->src->eval());
					return 0;
				}
			}
			for (it = init_variables_list.begin(); it != init_variables_list.end(); ++it) {
				if ((*it).first == this->dest->getName()) {
					((*it).second = this->src->eval());
					return 0;
				}
			}
		}
		return 1;
	}
	string toString() {
		return "\tmovq\t\t" + this->src->toString() + ",\t" + this->dest->toString() + "\n";
	}
	bool isEnd() {
		return false;
	}
	bool isJump() {
		return false;
	}
private:
	ArgX0 *src;
	ArgX0 *dest;
};
MovqX0* MvX(ArgX0* _src, ArgX0* _dest) {
	return new MovqX0(_src, _dest);
}

// block info instructions
class BlockX0 {
public:
	BlockX0 (list<std::shared_ptr<InstrX0>> *_instructions_list) {
		this->instructions_list = _instructions_list;
	}
	int instructions_cnt() {
		list<std::shared_ptr<InstrX0>>::iterator it;
		instr_cnt = 0;
		for (it = this->instructions_list->begin(); it != this->instructions_list->end(); ++it) {
			instr_cnt++;
		}
		return instr_cnt;
	}
	int eval() {
		list<std::shared_ptr<InstrX0>>::iterator it;
		instr_cnt = 0;
		for (it = this->instructions_list->begin(); it != this->instructions_list->end(); ++it) {
			instr_cnt++;
			(*it)->eval();
			if ((*it)->isEnd()) {
				end = true;
				return 0;
			}
			if ((*it)->isJump() == true) {
				jump = true;
				return 0;
			}
		}
		return 0;
	}
	// output to terminal for now
	void emit() {
		list<std::shared_ptr<InstrX0>>::iterator it;
		for (it = this->instructions_list->begin(); it != this->instructions_list->end(); ++it) {
			cout << (*it)->toString() << "\t";
		}
	}
	bool isEnd() {
		return end;
	}
	bool isJump() {
		return jump;
	}
private:
	bool end = false;
	bool jump = false;
	list<std::shared_ptr<InstrX0>> *instructions_list;
	int instr_cnt;
	LabelX0 *label;
};

// label instruction
class LabelX0 {
public:
	LabelX0(string _name) {
		this->name = _name;
	}
	void emit() {
		cout << name << "\t";
	}
	string getName() {
		return this->name;
	}
private:
	string name;
};
LabelX0* LbX(string _name) {
	return new LabelX0(_name);
}

// (jmp label) <-- instruction
class JumpX0 : public InstrX0 {
public:
	~JumpX0() { std::cout << "__PRETTY_FUNCTION__JUMP" << std::endl; }
	JumpX0(LabelX0 *_label) {
		this->label = _label;
	}
	int eval() {
		std::list<pair<std::shared_ptr<LabelX0>, std::shared_ptr<BlockX0>>>::iterator it;
		for (it = label_block_list.begin(); it != label_block_list.end(); ++it) {
			if ((it->first->getName()) == (this->label->getName())) {
				it->second->eval();
				if ((it->second)->isEnd()) {
					end_label = true;
					return 0;
				}
				end_label = false;
				if ((it->second)->isJump() == true) {
					return 0;
				}
			}
		}
	}
	string toString() {
		return "\tjmp\t\t" + label->getName() + "\n";
	};
	bool isEnd() {
		return end_label;
	};
	bool isJump() {
		return true;
	};
private:
	LabelX0 *label;
	bool end_label;
};

// program info [label->block]
class ProgramX0 {
public:
	ProgramX0() {
		pcnt = 0;
	}
	void execute() {
		std::list<pair<std::shared_ptr<LabelX0>, std::shared_ptr<BlockX0>>>::iterator it;
		for (it = label_block_list.begin(); it != label_block_list.end(); ++it) {
			if (it->second->eval() == 0) {
				if ((it->second)->isEnd()) {
					cout << "\tSuccessful Run\n\n";
					return;
				}
			}
		}
	}
	void emit() {
		std::list<pair<std::shared_ptr<LabelX0>, std::shared_ptr<BlockX0>>>::iterator it;
		for (it = label_block_list.begin(); it != label_block_list.end(); ++it) {
			it->first->emit();
			it->second->emit();
			cout << "\n";
		}
	}
private:
};
ProgramX0* PX(){
	return new ProgramX0();
}

// -----------------------------------------------------------------------------------------------------------
//				 ----	-----			-------	----- -   - -----
//				-	 -	-	-			   ---	-	- --  - -
//				-		-	-	-----	  ---	-	- - - - ----
//				-	 -	-	-			 ---	-	- -  -- -
//				 ----   -----			-------	----- -   - -----
// -----------------------------------------------------------------------------------------------------------

// C0: steps 23-26 --> compiled R0 into C0

/*


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

	tail	::= (return arg) | (seq stmt tail)

	C0   ::= (program info + [label->tail]) <-- {label->tail refers to instruction set}

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

class LabelC0;
class TailC0;
class VarC0;

static list<pair<string, int>> Variables;
static list<pair<std::shared_ptr<LabelC0>, std::shared_ptr<TailC0>>> label_tail_list;

// (exp)
class ExpC0 {
public:
	virtual int eval() = 0;
	string virtual toString() = 0;
	virtual ArgX0* select(VarC0* _dst) = 0;
	bool virtual isAdd() = 0;
	bool virtual isRead() = 0;
	bool virtual isNeg() = 0;
private:
};

// (argument) <-- exp
class ArgC0 : public ExpC0 {
public:
	virtual int eval() = 0;
	string virtual toString() = 0;
	virtual ArgX0* select(VarC0* _dst) = 0;
	bool virtual isAdd() = 0;
	bool virtual isRead() = 0;
	bool virtual isNeg() = 0;
private:
};

// (int) <-- argument
class IntC0 : public ArgC0 {
public:
	IntC0(int _value) {
		this->value = _value;
	}
	int eval() {
		return this->value;
	}
	string toString() {
		return "\t(" + to_string(this->value) + ")";
	}
	ArgX0* select(VarC0* _dst) {
		return IX(this->value);
	}
	bool isAdd() {
		return false;
	}
	bool isRead() {
		return false;
	}
	bool isNeg() {
		return false;
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
	int setVal(int _value) {
		for (list<pair<string, int>>::iterator it = Variables.begin(); it != Variables.end(); it++) {
			if ((*it).first == this->name) {
				(*it).second = _value;
				return 0;
			}
		}
		cout << "\tError: Variable: " << this->name << " is not found.\n";
		return 1;
	}
	int eval() {
		for (list<pair<string, int>>::iterator it = Variables.begin(); it != Variables.end(); it++) {
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
	ArgX0* select(VarC0* _dst) {
		return VX(this->name);
	}
	bool isAdd() {
		return false;
	}
	bool isRead() {
		return false;
	}
	bool isNeg() {
		return false;
	}
	string getName() {
		return this->name;
	}
private:
	string name;
};

// (read) <-- exp
class ReadC0 : public ExpC0 {
public:
	ReadC0() {}
	int eval() {
		cout << "Enter the integer value for (read): ";
		cin >> this->value;
		cout << "\n";
		return this->value;
	}
	string toString() {
		return "\t(read)";
	}
	bool isAdd() {
		return false;
	}
	bool isRead() {
		return true;
	}
	bool isNeg() {
		return false;
	}
	ArgX0* select(VarC0* _dst) {
		blk_body_list.push_back(std::make_shared<CallqX0>());
		blk_body_list.push_back(std::make_shared<MovqX0>(RX("rax"), VX(_dst->getName())));
		return NULL;
	}
private:
	int value;
};

// (- arg) <-- exp
class NegC0 : public ExpC0 {
public:
	NegC0(ArgC0 *_arg) {
		this->arg = _arg;
	}
	int eval() {
		return (-this->arg->eval());
	}
	string toString() {
		return "\t(- " + this->arg->toString() + ")";
	}
	bool isAdd() {
		return false;
	}
	bool isRead() {
		return false;
	}
	bool isNeg() {
		return true;
	}
	ArgX0* select(VarC0* _dst) {
		blk_body_list.push_back(std::make_shared<MovqX0>(this->arg->select(NULL), VX(_dst->getName())));
		blk_body_list.push_back(std::make_shared<NegqX0>(VX(_dst->getName())));
		return NULL;
	}
private:
	ArgC0 *arg;
};

// (+ arg arg) <-- exp
class AddC0 : public ExpC0 {
public:
	AddC0(ArgC0 *_left, ArgC0 *_right) {
		this->left = _left;
		this->right = _right;
	}
	int eval() {
		return (this->left->eval() + this->right->eval());
	}
	string toString() {
		return "\t(+ " + this->left->toString() + " " + this->right->toString() + ")";
	}
	bool isAdd() {
		return true;
	}
	bool isRead() {
		return false;
	}
	bool isNeg() {
		return false;
	}
	ArgX0* select(VarC0* _dst) {
		blk_body_list.push_back(std::make_shared<MovqX0>(this->right->select(NULL), VX(_dst->getName())));
		blk_body_list.push_back(std::make_shared<AddqX0>(this->left->select(NULL), VX(_dst->getName())));
		return NULL;
	}
private:
	ArgC0 *left, *right;
};

// (stmt)
class StmtC0 {
public:
	virtual int eval() = 0;
	virtual string toString() = 0;
	void virtual select() = 0;
private:
};

// (assign var exp) <-- stmt
class AssignC0 : public StmtC0 {
public:
	AssignC0(VarC0 *_var, ExpC0 *_exp) {
		this->var = _var;
		this->exp = _exp;
	}
	int eval() {
		if (this->var->setVal(this->exp->eval()) == 0) {
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
	void select() {
		// selectE (selectA x) e 
		//		for exp = arg:		selectE dst (a)			=	[movq (selectA a) dst;]
		//		for exp = read:		selectE dst (read)		=	[callq		_read_int;]
		//														[movq RAX		  dst;]
		//		for exp = neg:		selectE dst (-a)		=	[movq (selectA a) dst;]
		//														[negq			  dst;]
		//		for exp = add:		selectE dst (+ aL aR)	=	[movq (selectA aR)dst;]
		//														[addq (selectA aL)dst;]
		if (this->exp->isAdd()) {
			this->exp->select(var);
			return;
		}
		else if (this->exp->isNeg()) {
			this->exp->select(var);
			return;
		}
		else if (this->exp->isRead()) {
			this->exp->select(var);
		}
		else {
			blk_body_list.push_back(std::make_shared<MovqX0>(this->exp->select(NULL), VX(this->var->getName())));
			return;
		}
	}
private:
	VarC0 *var;
	ExpC0 *exp;
};

// (return arg)
class RetC0 : public StmtC0 {
public:
	RetC0(ArgC0 *_arg) {
		this->arg = _arg;
	}
	int eval() {
		cout << "\t\t>> Return Value is " << this->arg->eval() << " for following return statement <<\n";
		return 0;
	}
	string toString() {
		return "\t(return " + this->arg->toString() + ")\n";
	}
	ArgC0* get_arg() {
		return this->arg;
	}
	void select() {
		// [(movq (selectA a) RAX)	(jmp END)] 
		blk_body_list.push_back(std::make_shared<MovqX0>(this->arg->select(NULL), RX("rax")));
		// blk_body_list.push_back(std::make_shared<MovqX0>(RX("rax"), IRX(5, RX("rsp"))));
		blk_body_list.push_back(std::make_shared<JumpX0>(LbX("end:")));
	}
private:
	ArgC0 *arg;
};

// (label->tail)
class LabelC0 {
public:
	LabelC0(string _name) {
		this->name = _name;
	}
	void emit() {
		cout << this->name << "\n";
	}
private:
	string name;
};

// (return arg) | (sequence stmt tail) <-- tail
class TailC0 {
public:
	TailC0(list<std::shared_ptr<StmtC0>> *_stmts) {
		this->stmts = _stmts;
	}
	TailC0(RetC0 *_ret) {
		this->ret = _ret;
		is_end = true;
	}
	int eval() {
		if (isEnd() == true) {
			if (this->ret->eval() == 0) {
				cout << "\t" << this->ret->toString();
				return 0;
			}
			else {
				cout << "\n\tError executing return.\n";
				return 1;
			}
		}
		for (std::list<std::shared_ptr<StmtC0>>::iterator it = this->stmts->begin(); it != this->stmts->end(); ++it) {
			if ((*it)->eval() != 0) {
				// cout << "\t" << (*it)->toString();
				cout << "\n\tError executing program.\n\tCheck statement: " << (*it)->toString() << "\n";
				return 1;
			}
		}
		cout << "\n\tExecution is done.\n\n" << "\nMemory:\n\n" << "\tVariable\tValue\n";
		for (std::list<pair<std::string, int>>::iterator it = Variables.begin(); it != Variables.end(); ++it) {
			cout << "\t" << (*it).first << "\t\t" << (*it).second << "\n";
		}
		cout << "\n";
		return 0;
	}
	bool isEnd() {
		return this->is_end;
	}
	void emit() {
		if (isEnd() == true) {
			cout << "\t" << this->ret->toString() << "\n";
			return;
		}
		for (std::list<std::shared_ptr<StmtC0>>::iterator it = this->stmts->begin(); it != this->stmts->end(); ++it) {
			cout << "\t" << (*it)->toString();

		}
		return;
	}
	void select() {
		for (std::list<std::shared_ptr<StmtC0>>::iterator it = this->stmts->begin(); it != this->stmts->end(); ++it) {
			(*it)->select();
		}
		return;
	}
private:
	bool is_end = false;
	list<std::shared_ptr<StmtC0>> *stmts;
	RetC0 *ret;
};

// (program info {variables} [label->tail] {list_label_tail}
class ProgC0 {
public:
	ProgC0() {
	}
	void execute() {
		cout << "\nProgram:\n\n";
		std::list<pair<std::shared_ptr<LabelC0>, std::shared_ptr<TailC0>>>::iterator it;
		for (it = label_tail_list.begin(); it != label_tail_list.end(); ++it) {
			if (it->second->eval() != 0)
				cout << "\nError\n";
			cout << "\n";
			if ((it->second)->isEnd()) {
				return;
			}
		}
	}
	void emit() {
		std::list<pair<std::shared_ptr<LabelC0>, std::shared_ptr<TailC0>>>::iterator it;
		for (it = label_tail_list.begin(); it != label_tail_list.end(); ++it) {
			it->first->emit();
			it->second->emit();
		}
	}
	void select() {
		std::list<pair<std::shared_ptr<LabelC0>, std::shared_ptr<TailC0>>>::iterator it;
		for (it = label_tail_list.begin(); it != label_tail_list.end(); ++it) {
			(it->second->select());
		}
		std::shared_ptr<LabelX0> lbl_body(new LabelX0("body:"));
		std::shared_ptr<LabelX0> lbl_end(new LabelX0("end:"));
		blk_end_list.push_back(std::make_shared<RetqX0>());
		BlockX0 *temp_blk_body = new BlockX0(&blk_body_list);
		BlockX0 *temp_blk_end = new BlockX0(&blk_end_list);
		auto blk_body = std::make_shared<BlockX0>(*temp_blk_body);
		auto blk_end = std::make_shared<BlockX0>(*temp_blk_end);
		pcnt = 0;
		label_block_list.emplace_back(make_pair(lbl_body, blk_body));
		label_block_list.emplace_back(make_pair(lbl_end, blk_end));
		init_variables_list.push_back(std::make_pair("x_0", 0));
		init_variables_list.push_back(std::make_pair("x_1", 0));
		init_variables_list.push_back(std::make_pair("L_x_4", 0));
		init_variables_list.push_back(std::make_pair("A_x_3", 0));
		init_variables_list.push_back(std::make_pair("L_x_2", 0));
		return;
	}

private:
};


// -----------------------------------------------------------------------------------------------------------
//				-----	-----			-------	----- -   - -----
//				-	 -	-	-			   ---	-	- --  - -
//				-----	-	-	-----	  ---	-	- - - - ----
//				-	-	-	-			 ---	-	- -  -- -
//				-	 -  -----			-------	----- -   - -----
// -----------------------------------------------------------------------------------------------------------

/*
	R0 on paper
	R1 about to go on paper
	R0 + let + var + 
*/

/*

	RC0:	p	=	(program	info	e)
			e	=	arg		|	(let	x	=	c	in	e)
			c	=	read	|	(- arg)	|	(+	arg	arg)
			arg =	number	|	var

	RC0 --> C0

	econ (programR	info  exp)	=	(programC  info  [Label("BODY")-->t]
				t	=	econE	exp

	econE: expRc0 --> Ct
	econA: argRc0 --> argC0
	econC: complexRc0 --> expC0

	- for (arg) | (let x = c in e)
	econE arg = return (econA arg)
	econE (let x = ex in eb) = seq (set! x (econC ex)) (econE eb)

	- for (read) | (- arg) | (+ arg arg)
	econC (readR) = (readC)
	econC (-a) = (-(econA a))
	econC (+ l r) = (+ (econA l) (econA r))

	- for (number) | (var) 
	econA (numR n) = (numC n)
	econA (varR x) = (varC x)

*/

// R0-R1: steps 1-17 + 27-35 --> compiled R0 into C0

enum Mode {Interactive,Automated};
static Mode mode = Interactive;

class VarR0;
class ExpR0;

static int variable_counter_R1 = 0;
static list<pair<shared_ptr<VarR0>, shared_ptr<ExpR0>>> var_exp_mapp;

enum Operation {Add, Neg, Read, Num};

// Interface class ExpR0
class ExpR0 {
public:
	// interpreter of the tree-like program
	int virtual eval(list<pair<string, int>> *_info) = 0;

	// print the tree in the linear form
	virtual string toString() = 0;

	// is the expression var or int - opt - let specifically
	bool virtual simpleExp() = 0;

	// simplifying the code - doing all of the possible calculations ahead of interpretation
	virtual ExpR0* opt(list<pair<std::string, ExpR0*>> *_info) = 0;

	// optimizer helpers - is number, addition of number and read, or neg expression
	bool virtual isNum() = 0;
	bool virtual isNumRead() = 0;
	bool virtual isNegExp() = 0;

	// R1 maker functions
	// making the program variable set global
	virtual ExpR0* uniquify(list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>> *_mapp) = 0;
	// making a tree-like code linear
	virtual ExpR0* resolve_complex() = 0;

	// identity maker 
	virtual ExpR0* get_me() = 0;
	// copy maker
	virtual ExpR0* create_copy() = 0;

	// Rc0 --> C0 compiler
	virtual void econ(list<shared_ptr<StmtC0>> *_tail_tester,std::shared_ptr<LabelC0> _lbl_tester, string _name, bool _is_end) = 0;

};

ExpR0* A(ExpR0* l, ExpR0* r);
ExpR0* N(ExpR0* e);
ExpR0* R();
ExpR0* I(int _value);
ExpR0* I();
VarR0* V(string x);
VarR0* V(VarR0 *x);
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
	ExpR0* opt(list<pair<std::string, ExpR0*>> *_info) {
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
	ExpR0* uniquify(list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>> *_mapp) {
		return this;
	}
	ExpR0* resolve_complex() {
		return this;
	}
	ExpR0* get_me() {
		return this;
	}
	ExpR0* create_copy() {
		return new NumR0(this->value);
	}
	void econ(list<shared_ptr<StmtC0>> *_tail_tester, std::shared_ptr<LabelC0> _lbl_tester, string _name, bool _is_end) {
		_tail_tester->push_back(std::make_shared<AssignC0>(new VarC0(_name), new IntC0(this->value)));
		return;
	}
private:
	int value;
};

class VarR0 : public ExpR0 {
public:
	VarR0(string _name) {
		this->name = _name;
	}
	VarR0(VarR0 *old_variable) {
		this->name = old_variable->name + "_" + to_string(variable_counter_R1++);
	}
	// given the information on value assigned to the variables return the one assigned to this name
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
	ExpR0* opt(list<pair<std::string, ExpR0*>> *_info) {
		std::list<pair<std::string, ExpR0*>>::iterator it;
		for (it = (*_info).begin(); it != (*_info).end(); ++it) {
			if ((*it).first == this->name) {
				return (*it).second;
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
	void setString(string _name) {
		this->name = _name;
	}
	ExpR0* uniquify(list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>> *_mapp) {
		mapp = _mapp;
		std::list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>>::iterator it;
		for (it = (*mapp).begin(); it != (*mapp).end(); ++it) {
			if ((*it).first->toString() == this->toString()) {
				this->setString((*it).second->toString());
				return this;
			}
		}
		cout << "\n\tNo mapping - error occured.\n";
		return this;
	}
	ExpR0* resolve_complex() {
		for (std::list<pair<shared_ptr<VarR0>, shared_ptr<ExpR0>>>::iterator it = var_exp_mapp.begin(); it != var_exp_mapp.end(); ++it) {
			if (it->first->name == this->name) {
				return it->second->get_me();
			}
		}
		cout << "\n\tERROR: No mapping for variable: " << this->name << "\n";
		return this;
	}
	int getValue() {
		return this->value;
	}
	void setValue(int _value) {
		this->value = _value;
	}
	ExpR0* get_me() {
		return this;
	}
	ExpR0* create_copy() {
		return new VarR0(this->name);
	}
	void econ(list<shared_ptr<StmtC0>> *_tail_tester, std::shared_ptr<LabelC0> _lbl_tester, string _name, bool _is_end) {
		if (_is_end) {
			ArgC0 *new_arg = new VarC0(this->name);
			_tail_tester->push_back(std::make_shared<RetC0>(new_arg));
			TailC0 *temp_tail = new TailC0(_tail_tester);
			auto tail_body = std::make_shared<TailC0>(*temp_tail);
			label_tail_list.emplace_back(std::make_pair(_lbl_tester, tail_body));
			return;
		}
		else {
			_tail_tester->push_back(std::make_shared<AssignC0>(new VarC0(_name), new VarC0(this->name)));
			return;
		}
	}
private:
	int value;
	string name;
	list<pair<string, int>> *info;
	list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>> *mapp;
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
	ExpR0* opt(list<pair<std::string, ExpR0*>> *_info) {
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
	ExpR0* uniquify(list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>> *_mapp) {
		this->mapp = _mapp;
		return new AddR0(this->lexp->uniquify(this->mapp), this->rexp->uniquify(this->mapp));
	}
	ExpR0* resolve_complex() {
		VarR0 *new_var = V(V("A_x"));
		auto new_variable = std::make_shared<VarR0>(*new_var);
		auto new_expression = std::shared_ptr<ExpR0>(A(lexp->resolve_complex(), rexp->resolve_complex()));
		var_exp_mapp.emplace_back(make_pair(new_variable,new_expression));
		return V(new_var->toString());
	}
	ExpR0* get_me() {
		return this;
	}
	ExpR0* create_copy() {
		return new AddR0(this->lexp->create_copy(), this->rexp->create_copy());
	}
	void econ(list<shared_ptr<StmtC0>> *_tail_tester, std::shared_ptr<LabelC0> _lbl_tester, string _name, bool _is_end) {
		if (this->lexp->isNum()) {
			NumR0 *new_num_l = dynamic_cast<NumR0*>(this->lexp);
			IntC0 *new_arg_l_c = new IntC0(new_num_l->retVal());
			if (this->rexp->isNum()) {
				NumR0 *new_num_r = dynamic_cast<NumR0*>(this->rexp);
				IntC0 *new_arg_r_c = new IntC0(new_num_r->retVal());
				AddC0 *new_add = new AddC0(new_arg_l_c, new_arg_r_c);
				_tail_tester->push_back(std::make_shared<AssignC0>(new VarC0(_name), new_add));
				return;
			}
			else {
				VarR0 *new_var_r = dynamic_cast<VarR0*>(this->rexp);
				VarC0 *new_arg_r_c = new VarC0(new_var_r->toString());
				AddC0 *new_add = new AddC0(new_arg_l_c, new_arg_r_c);
				_tail_tester->push_back(std::make_shared<AssignC0>(new VarC0(_name), new_add));
				return;
			}
		}
		else {
			VarR0 *new_var_l = dynamic_cast<VarR0*>(this->lexp);
			VarC0 *new_arg_l_c = new VarC0(new_var_l->toString());
			if (this->rexp->isNum()) {
				NumR0 *new_num_r = dynamic_cast<NumR0*>(this->rexp);
				IntC0 *new_arg_r_c = new IntC0(new_num_r->retVal());
				AddC0 *new_add = new AddC0(new_arg_l_c, new_arg_r_c);
				_tail_tester->push_back(std::make_shared<AssignC0>(new VarC0(_name), new_add));
				return;
			}
			else {
				VarR0 *new_var_r = dynamic_cast<VarR0*>(this->rexp);
				VarC0 *new_arg_r_c = new VarC0(new_var_r->toString());
				AddC0 *new_add = new AddC0(new_arg_l_c, new_arg_r_c);
				_tail_tester->push_back(std::make_shared<AssignC0>(new VarC0(_name), new_add));
				return;
			}
		}
		cout << "Error in econ for addition for: " << _name << "\n\n";
		return;
	}
private:
	ExpR0 *lexp, *rexp;
	list<pair<string, int>> *info;
	list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>> *mapp;
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
	ExpR0* opt(list<pair<std::string, ExpR0*>> *_info) {
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
	// helpers in checking if -(-x) = x is possible
	bool isNegExp() {
		if (exp->isNegExp())
			return false;
		else
			return true;
	}
	ExpR0* getExp() {
		return exp;
	}
	ExpR0* uniquify(list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>> *_mapp) {
		this->mapp = _mapp;
		return new NegR0(this->exp->uniquify(mapp));
	}
	// da li let ljepimo u mapping ili ga vracamo ili pak vracamo samo variablu
	ExpR0* resolve_complex() {
		VarR0 *new_var = V(V("N_x"));
		auto new_variable = std::make_shared<VarR0>(*new_var);
		auto new_expression = std::shared_ptr<ExpR0>(exp->resolve_complex());
		var_exp_mapp.emplace_back(make_pair(new_variable, new_expression));
		return V(new_var->toString());
	}
	ExpR0* get_me() {
		return this;
	}
	ExpR0* create_copy() {
		return new NegR0(this->exp->create_copy());
	}
	void econ(list<shared_ptr<StmtC0>> *_tail_tester, std::shared_ptr<LabelC0> _lbl_tester, string _name, bool _is_end) {
		ArgC0 *new_arg_c;
		if (this->exp->isNum()) {
			NumR0 *new_num = dynamic_cast<NumR0*>(this->exp);
			IntC0 *new_arg_c = new IntC0(new_num->retVal());
			NegC0 *new_neg = new NegC0(new_arg_c);
			_tail_tester->push_back(std::make_shared<AssignC0>(new VarC0(_name), new_neg));
			return;
		}
		else {
			VarR0 *new_var = dynamic_cast<VarR0*>(this->exp);
			VarC0 *new_arg_c = new VarC0(new_var->toString());
			NegC0 *new_neg = new NegC0(new_arg_c);
			_tail_tester->push_back(std::make_shared<AssignC0>(new VarC0(_name), new_neg));
			return;
		}
		cout << "Error in econ for negation for: " << _name << "\n\n";
		return;
	}
private:
	ExpR0 *exp;
	list<pair<string, int>> *info;
	int value;
	list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>> *mapp;
};

// kad je variabla ista koristena tada brises u novom environmentu staru vrijednost
// testiraj kad je variabla x_exp
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
				(*it).second = var_value;
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
	ExpR0* opt(list<pair<std::string, ExpR0*>> *_info) {
		ExpR0 *x_expO = this->x_exp->opt(_info);
		list<pair<string, ExpR0*>> *new_info = new list<pair<string, ExpR0*>>();
		*new_info = *_info;
		std::list<pair<std::string, ExpR0*>>::iterator it;
		if (x_expO->simpleExp()) {
			// NumR0* tmp_num = dynamic_cast<NumR0*>(x_expO);
			for (it = (*new_info).begin(); it != (*new_info).end(); ++it) {
				if ((*it).first == variable->toString()) {
					(*it).second = x_expO;
					return this->b_exp->opt(new_info);
				}
			}
			(*new_info).push_back(std::make_pair(this->variable->toString(), x_expO));
			return this->b_exp->opt(new_info);
		}
		else {
			for (it = (*new_info).begin(); it != (*new_info).end(); ++it) {
				if ((*it).first == this->variable->toString()) {
					(*it).second = V(this->variable->toString());
					return L(dynamic_cast<VarR0*>(V(this->variable->toString())), x_expO, b_exp->opt(new_info));
				}
			}
			(*new_info).push_back(std::make_pair(this->variable->toString(), V(this->variable->toString())));
			return L(dynamic_cast<VarR0*>(V(this->variable->toString())), x_expO, b_exp->opt(new_info));
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
	ExpR0* uniquify(list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>> *_mapp) {
		this->mapp = _mapp;
		VarR0 *new_variable = new VarR0(this->variable);
		std::list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>>::iterator it;
		for (it = (*mapp).begin(); it != (*mapp).end(); ++it) {
			// if this variable already has been mapped we skratch that 
			// and put new mapping in 
			if ((*it).first->toString() == this->variable->toString()) {
				this->new_mapp = new list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>>();
				new_mapp = mapp;
				std::list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>>::iterator it1;
				for (it1 = (*new_mapp).begin(); it1 != (*new_mapp).end(); ++it1) {
					if ((*it1).first->toString() == this->variable->toString()) {
						(*it1).second = unique_ptr<VarR0>(new_variable);
					}
				}
				return new LetR0(new VarR0(new_variable->toString()), this->x_exp->uniquify(new_mapp), this->b_exp->uniquify(new_mapp));
			}
		}
		(*mapp).emplace_back(std::make_pair(unique_ptr<VarR0>(new VarR0(this->variable->toString())), unique_ptr<VarR0>(new_variable)));
		return new LetR0(new VarR0(new_variable->toString()), this->x_exp->uniquify(mapp), this->b_exp->uniquify(mapp));
	}
	ExpR0* resolve_complex() {
		VarR0 *new_var = V(V("L_x"));
		auto temp_var = std::make_shared<VarR0>(*variable);
		auto new_temp_var = std::shared_ptr<ExpR0>(x_exp->resolve_complex());
		var_exp_mapp.emplace_back(make_pair(temp_var, new_temp_var));
		auto new_variable = std::make_shared<VarR0>(*new_var);
		auto new_expression = std::shared_ptr<ExpR0>(b_exp->resolve_complex());
		var_exp_mapp.emplace_back(make_pair(new_variable, new_expression));
		return V(new_var->toString());
	}
	ExpR0* get_me() {
		return this;
	}
	ExpR0* create_copy() {
		return new LetR0(V(this->variable->toString()), x_exp->create_copy(), b_exp->create_copy());
	}
	void econ(list<shared_ptr<StmtC0>> *_tail_tester, std::shared_ptr<LabelC0> _lbl_tester, string _name, bool _is_end) {
		Variables.push_back(std::make_pair(this->variable->toString(), 0));
		x_exp->econ(_tail_tester, NULL, this->variable->toString(), false);
		b_exp->econ(_tail_tester, _lbl_tester, " ", true);
		return;
	}
private:
	VarR0 *variable;
	ExpR0 *x_exp, *b_exp;
	list<pair<string, int>> *info;
	list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>> *mapp,*new_mapp;
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
	ExpR0* opt(list<pair<std::string, ExpR0*>> *_info) {
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
	ExpR0* uniquify(list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>> *_mapp) {
		return this;
	}
	ExpR0* resolve_complex() {
		VarR0 *new_var = V(V("read_x"));
		auto new_variable = std::make_shared<VarR0>(*new_var);
		auto new_expression = std::shared_ptr<ExpR0>(R());
		var_exp_mapp.emplace_back(make_pair(new_variable, new_expression));
		return V(new_var->toString());
	}
	ExpR0* get_me() {
		return this;
	}
	ExpR0* create_copy() {
		return R();
	}
	void econ(list<shared_ptr<StmtC0>> *_tail_tester, std::shared_ptr<LabelC0> _lbl_tester, string _name, bool _is_end) {
		_tail_tester->push_back(std::make_shared<AssignC0>(new VarC0(_name), new ReadC0()));
		return;
	}
private:
	int value;
};

ExpR0* L(VarR0* v, ExpR0* ve, ExpR0* be) {
	return new LetR0(v, ve, be);
}
VarR0* V(string x) {
	return new VarR0(x);
}
VarR0* V(VarR0 *x) {
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
//		srand(time(NULL));
		code = _code;
		info = _info;
	}
	int intrp() {
		return code->eval(this->info);
	}
	string prnt() {
		return code->toString();
	}
	ExpR0* optmz(list<pair<std::string, ExpR0*>> *_info) {
		return code->opt(_info);
	}
	ExpR0* uniq(list<pair<unique_ptr<VarR0>, unique_ptr<VarR0>>> *_mapp) {
		return this->code->uniquify(_mapp);
	}
	ExpR0* resolv() {
		result_holder = this->code->resolve_complex();
		for (std::list<pair<shared_ptr<VarR0>, shared_ptr<ExpR0>>>::iterator it = var_exp_mapp.begin(); it != var_exp_mapp.end(); ++it) {
			cout << "\n\tLet (" << it->first->toString() << ")";
			cout << "= \t(" << it->second->toString() << ")";
			if (it->second->simpleExp())
				cout << "\t";
			cout << "\tin ";
			// result_holder = V(it->first->toString());
		}
		cout << "\n\t    (" << result_holder->toString() << ")";
		result_holder = NULL;
		for (std::list<pair<shared_ptr<VarR0>, shared_ptr<ExpR0>>>::reverse_iterator it = var_exp_mapp.rbegin(); it != var_exp_mapp.rend(); ++it) {
			if (!init) {
				init = true;
				result_holder = it->first->create_copy();
			}
			result_holder = L(V(it->first->toString()), it->second->create_copy(), result_holder);
		}
		cout << "\n\n\t" << "Result is: " << result_holder->eval(new list<pair<string, int>>());
		return result_holder;
	}
	void econ() {
		
		// label tester
		std::shared_ptr<LabelC0> lbl_tester(new LabelC0("body:"));
		// initializing program
		list<std::shared_ptr<StmtC0>> tail_tester;

		/*
		tail_tester.push_back(std::make_shared<AssignC0>(new VarC0("x"), new ReadC0()));
		tail_tester.push_back(std::make_shared<AssignC0>(new VarC0("y"), new IntC0(5)));
		tail_tester.push_back(std::make_shared<AssignC0>(new VarC0("z"), new VarC0("x")));
		tail_tester.push_back(std::make_shared<AssignC0>(new VarC0("a"), new NegC0(new VarC0("x"))));
		tail_tester.push_back(std::make_shared<AssignC0>(new VarC0("b"), new NegC0(new IntC0(5))));
		tail_tester.push_back(std::make_shared<AssignC0>(new VarC0("c"), new AddC0(new IntC0(5), new VarC0("x"))));

		Variables.push_back(std::make_pair("a", 0));
		Variables.push_back(std::make_pair("b", 0));
		Variables.push_back(std::make_pair("c", 0));
		Variables.push_back(std::make_pair("x", 0));
		Variables.push_back(std::make_pair("y", 0));
		Variables.push_back(std::make_pair("z", 0));
		*/

		this->code->econ(new list<shared_ptr<StmtC0>>(), lbl_tester, " ", true);

}
private:
	list<pair<string, int>> *info;
	ExpR0 *code;
	ExpR0 *result_holder;
	bool init = false;
};

/*
ExpR0* onNth(int m) {
	if (m == 0) return I(1);
	if (m > 0) return A(onNth(m - 1), onNth(m - 1));
	if (m < 0) cout << "Error calling function onNth: m < 0\n";
}

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
			return L(dynamic_cast<VarR0*>(V("x")), randP(new_info, n - 1), randP(new_info, n - 1));
		}
	}
}
*/

// -----------------------------------------------------------------------------------------------------------
//				-	-	-----			-------	----- -   - -----
//				 - -	-	-			   ---	-	- --  - -
//				  -		-	-	-----	  ---	-	- - - - ----
//				 - -	-	-			 ---	-	- -  -- -
//				-	-   -----			-------	----- -   - -----
// -----------------------------------------------------------------------------------------------------------

// X0: steps 18-22 --> compiling C0 into X0

/*
	18) + define data types for X0 program ASTs
	19) + write an emitter for X0 programs - obicni toString jel...
		- should emit in the syntax of the assembler you will use
		- takes a parameter whether variables should be allowed in the output
		- only makes sense for debugging
	20) 1/12 build a test suite of a dozen X0 programs - jasno trivijalno
		- intrp should ony ret value of rax on retq rather than entire state of machine
		- ideally these programs are manually compiled versions of your R1 test programs
	21) + write an interpreter for X0 programs - interpretator jasno
		- register file is simple fixed vector where registers are indices and the stack is stack
		- have to have special case for when you callq to system function like read or print
	22) ? connect your X0 test suite to system assembler --> google the shit out of it
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

	- p		::=		program		info	[label->block]	... 
	- blk	::=		block		info	instr			... 
	+ instr	::=		  (addq arg arg)					{[q = quad = 4*normal size of number = 4*16b]}
					| (subq arg arg)
					| (movq arg arg)
					| (retq)			{[escape & say what's rax]}
					| (negq arg)
					| (callq label)		{[callq _read_int]}
					| (pushq arg)		{[(%rsp)->ms(%rsp)-8] [%rsp(0)->ms(src)]}
					| (popq arg)		{[(%rsp)->ms(dst)] [%rsp->ms(%rsp)+8]}
					| (jmp label)		{[xbi ms label]} 
	+ arg	::=		  $int					-> number
					| %reg					-> registar
					| %reg(offset)			-> memory
					| var(x)				-> variable
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

class LabelX0;
class BlockX0;

// label --> block	LIST
static list<pair<std::shared_ptr<LabelX0>,std::shared_ptr<BlockX0>>> label_block_list;
static list<pair<std::string, int>> init_variables_list;

// stack implementation for registers: rsp | rbp
static struct Node {
	int data;
	Node *link;
};

//static Node *rbp = new Node();
//static Node *rsp = new Node();
static Node *top = NULL;

// register ::= rax | rbx | rcx | rdx | rsi | rdi | r8 | r9 | r10 | r11 | r12 | r13 | r14 | r15
static list<pair<std::string, int>> *RegistersX0 = new list<pair<std::string,int>> {
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

// program counter
static int pcnt;

// arg ::= $int | %reg | int(%reg) + var(x)
class ArgX0 {
public:
	int virtual eval() = 0;
	void virtual setValue(int _value) = 0;
	string virtual getName(void) = 0;
	string virtual toString(void) = 0;
private:
};

// $int <-- arg - BRAVO
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
	int eval() {
		return this->value;
	}
	string toString() {
		return "$" + to_string(this->value);
	}
private:
	int value;
};
IntX0* IX(int _value) {
	return new IntX0(_value);
}

// %reg <-- arg
class RegX0 : public ArgX0 {
public:
	RegX0(string _name) {
		this->name = _name;
	}
	int eval() {
		// variables_list = _variables_list;
		for (std::list<pair<std::string, int>>::iterator it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == this->name) {
				this->setValue((*it).second);
				return this->value;
			}
		}
		return 1;
	}
	// set value is just setting local variable of that instance of class
	// is that what's expected?
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
};
RegX0* RX(string _name) {
	return new RegX0(_name);
}

// %reg (offset) <-- arg
class IntRegX0 : public ArgX0 {
public:
	IntRegX0(int _offset, RegX0 *_reg) {
		this->reg = _reg;
		this->offset = _offset;
		// this->value = getVal(lookupList(this->name));
	}
	int eval() {
		// this->variables_list = _variables_list;
		return (this->offset + this->reg->eval());
	}
	void setValue(int _value) {
		this->value = _value;
	}
	string toString() {
		return "%" + this->reg->toString() + "(" + to_string(this->offset) + ")";
	}
	string getName() {
		return "Register type has no name.";
	}
private:
	RegX0 *reg;
	int value, offset;
};
IntRegX0* IRX(int _offset,RegX0 *_reg) {
	return new IntRegX0(_offset, _reg);
}

// var (x) <-- arg
class VarX0 : public ArgX0 {
public:
	VarX0(string _name) {
		this->name = _name;
	}
	int eval() {
		std::list<pair<std::string, int>>::iterator it;
		for (it = init_variables_list.begin(); it != init_variables_list.end(); ++it) {
			if ((*it).first == this->name) {
				return (*it).second;
			}
		}
		cout << "Uninitialized Variable is Being Used Under Following name: " + this->name + "!\n";
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
};
VarX0* VX(string _name) {
	return new VarX0(_name);
}

//instruction ::= (addq arg arg) | (subq arg arg) | (movq arg arg) | (retq) | (negq arg) | (callq label) | (pushq arg) | (popq arg) | (jump label)
class InstrX0 {
public:
	virtual ~InstrX0() { std::cout << "__PRETTY_FUNCTION__" << std::endl; }
	virtual int eval() = 0;
	virtual string toString() = 0;
	virtual bool isEnd() = 0;
	virtual bool isJump() = 0;
private:
};

// (popq arg) <-- instruction
class PopqX0 : public InstrX0 {
public:
	~PopqX0() override { std::cout << "__PRETTY_FUNCTION__" << std::endl; }
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
	int eval() {
		for (std::list<pair<std::string, int>>::iterator it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
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
	bool isEnd() {
		return false;
	}
	bool isJump() {
		return false;
	}
private:
	ArgX0 *dest;
};
PopqX0* PopX(ArgX0 *_arg) {
	return new PopqX0(_arg);
}

// (pushq arg) <-- instruction
class PushqX0 : public InstrX0 {
public:
	~PushqX0() override { std::cout << "__PRETTY_FUNCTION__" << std::endl; }
	PushqX0(ArgX0* _src) {
		this->src = _src;
	}
	void push(int _value) {
		Node *rsp = new Node();
		rsp->data = _value;
		rsp->link = top;
		top = rsp;
	}
	int eval() {
		for (std::list<pair<std::string, int>>::iterator it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
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
	bool isEnd() {
		return false;
	}
	bool isJump() {
		return false;
	}
private:
	ArgX0 *src;
};
PushqX0* PshX(ArgX0 *_arg) {
	return new PushqX0(_arg);
}

// (retq) <-- instruction (function marking success with storing 0 in %rax)
class RetqX0 : public InstrX0 {
public:
	~RetqX0() override { std::cout << "__PRETTY_FUNCTION__" << std::endl; }
	RetqX0() {}
	int eval() {
		for (std::list<pair<std::string, int>>::iterator it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == "rax") {
				// (*it).second = 0;
				cout << "\tValue at %rax is : " << (*it).second << "\n\n";
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
	bool isEnd() {
		return true;
	}
	bool isJump() {
		return false;
	}
private:
	bool success = false;
};
RetqX0* RtX() {
	return new RetqX0();
};

// (callq read_int) <-- instruction (function printing out %rdi)
class CallqX0 : public InstrX0 {
public:
	~CallqX0() override { std::cout << "__PRETTY_FUNCTION__" << std::endl; }
	CallqX0() {
	}
	int eval() {
		cout << "\nType the input value -> ";
		cin >> this->value;
		for (std::list<pair<std::string, int>>::iterator it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == "rax") {
				(*it).second = this->value;
				cout << "\nInfo:\n\tValue at %rax is now: " << this->value << "\n\n";
				return 0;
			}
		}
		return 5;
	}
	string toString() {
		return "\tcallq\t\tread_int\n";
	}
	bool isEnd() {
		return false;
	}
	bool isJump() {
		return false;
	}
private:
	int value;
};
CallqX0* CllX() {
	return new CallqX0();
}

// (negq arg) <-- instruction
class NegqX0 : public InstrX0 {
public:
	~NegqX0() override { std::cout << "__PRETTY_FUNCTION__" << std::endl; }
	NegqX0(ArgX0* _dest) {
		this->dest = _dest;
	}
	int eval() {
		std::list<pair<std::string, int>>::iterator it;
		for (it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == this->dest->getName()) {
				((*it).second = -this->dest->eval());
				return 0;
			}
		}
		for (it = init_variables_list.begin(); it != init_variables_list.end(); ++it) {
			if ((*it).first == this->dest->getName()) {
				((*it).second = -this->dest->eval());
				return 0;
			}
		}
		return 4;
	}
	string toString() {
		return "\tnegq\t\t" + this->dest->toString() + "\n";
	}
	bool isEnd() {
		return false;
	}
	bool isJump() {
		return false;
	}
private:
	ArgX0 *dest;
};
NegqX0* NgX(ArgX0* _dest) {
	return new NegqX0(_dest);
}

// (subq arg, arg) <-- instruction
class SubqX0 : public InstrX0 {
public:
	~SubqX0() override { std::cout << "__PRETTY_FUNCTION__" << std::endl; }
	SubqX0(ArgX0* _src, ArgX0* _dest) {
		this->src = _src;
		this->dest = _dest;
	}
	int eval() {
		if (readValue(&rd_dst, this->dest->getName()) == 1)
			cout << "\n\tError Reading Values: " << this->src->getName() << " & " << this->dest->getName() << "\n\n";
		writeValue(this->rd_dst - this->rd_src);
		return 0;
	}
	string toString() {
		return "\tsubq\t\t" + this->src->toString() + ",\t" + this->dest->toString() + "\n";
	}
	bool isEnd() {
		return false;
	}
	int readValue(int *_val, string _name) {
		std::list<pair<std::string, int>>::iterator it;
		for (it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == _name) {
				*_val = (*it).second;
				src_rd++;
				if (src_rd == 1) {
					readValue(&this->rd_src, this->src->getName());
					return 0;
				}
				else {
					src_rd = 0;
					return 0;
				}
			}
		}
		for (it = init_variables_list.begin(); it != init_variables_list.end(); ++it) {
			if ((*it).first == _name) {
				*_val = (*it).second;
				src_rd++;
				if (src_rd == 1) {
					readValue(&this->rd_src, this->src->getName());
					return 0;
				}
				else {
					src_rd = 0;
					return 0;
				}
			}
		}
		return 1;
	}
	void writeValue(int _value) {
		this->dest->setValue(_value);
	}
	bool isJump() {
		return false;
	}
private:
	int src_rd = 0;
	int rd_src, rd_dst;
	ArgX0 *src, *dest;
};
SubqX0* SbX(ArgX0* _src, ArgX0* _dest) {
	return new SubqX0(_src, _dest);
}

// (addq arg, arg) <-- instruction
class AddqX0 : public InstrX0 {
public:
	~AddqX0() override { std::cout << "__PRETTY_FUNCTION__" << std::endl; }
	AddqX0(ArgX0* _src, ArgX0* _dest) {
		this->src = _src;
		this->dest = _dest;
	}
	int eval() {
		if (readValue(&rd_dst, this->dest->getName()) == 1)
			cout << "\n\tError Reading Values: " << this->src->getName() << " & " << this->dest->getName() << "\n\n";
writeValue(this->rd_dst + this->rd_src);
return 0;
	}
	int readValue(int *_val, string _name) {
		std::list<pair<std::string, int>>::iterator it;
		for (it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == _name) {
				*_val = (*it).second;
				src_rd++;
				if (src_rd == 1) {
					readValue(&this->rd_src, this->src->getName());
					return 0;
				}
				else {
					src_rd = 0;
					return 0;
				}
			}
		}
		for (it = init_variables_list.begin(); it != init_variables_list.end(); ++it) {
			if ((*it).first == _name) {
				*_val = (*it).second;
				src_rd++;
				if (src_rd == 1) {
					readValue(&this->rd_src, this->src->getName());
					return 0;
				}
				else {
					src_rd = 0;
					return 0;
				}
			}
		}
		return 1;
	}
	void writeValue(int _value) {
		this->dest->setValue(_value);
	}
	string toString() {
		return "\taddq\t\t" + this->src->toString() + ",\t" + this->dest->toString() + "\n";
	}
	bool isEnd() {
		return false;
	}
	bool isJump() {
		return false;
	}
private:
	int src_rd = 0;
	ArgX0 *src, *dest;
	int rd_src, rd_dst;
};
AddqX0* AdX(ArgX0* _src, ArgX0* _dest) {
	return new AddqX0(_src, _dest);
}

// (movq arg arg) <-- instruction
class MovqX0 : public InstrX0 {
public:
	~MovqX0() override { std::cout << "__PRETTY_FUNCTION__" << std::endl; }
	MovqX0(ArgX0* _src, ArgX0* _dest) {
		this->src = _src;
		this->dest = _dest;
	}
	int eval() {
		std::list<pair<std::string, int>>::iterator it;
		for (it = RegistersX0->begin(); it != RegistersX0->end(); ++it) {
			if ((*it).first == this->dest->getName()) {
				((*it).second = this->src->eval());
				return 0;
			}
		}
		for (it = init_variables_list.begin(); it != init_variables_list.end(); ++it) {
			if ((*it).first == this->dest->getName()) {
				((*it).second = this->src->eval());
				return 0;
			}
		}
		return 1;
	}
	string toString() {
		return "\tmovq\t\t" + this->src->toString() + ",\t" + this->dest->toString() + "\n";
	}
	bool isEnd() {
		return false;
	}
	bool isJump() {
		return false;
	}
private:
	ArgX0 *src;
	ArgX0 *dest;
};
MovqX0* MvX(ArgX0* _src, ArgX0* _dest) {
	return new MovqX0(_src, _dest);
}

// block info instructions
class BlockX0 {
public:
	BlockX0 (list<std::shared_ptr<InstrX0>> *_instructions_list) {
		this->instructions_list = _instructions_list;
	}
	int instructions_cnt() {
		list<std::shared_ptr<InstrX0>>::iterator it;
		instr_cnt = 0;
		for (it = this->instructions_list->begin(); it != this->instructions_list->end(); ++it) {
			instr_cnt++;
		}
		return instr_cnt;
	}
	int eval() {
		list<std::shared_ptr<InstrX0>>::iterator it;
		instr_cnt = 0;
		for (it = this->instructions_list->begin(); it != this->instructions_list->end(); ++it) {
			instr_cnt++;
			(*it)->eval();
			if ((*it)->isEnd()) {
				end = true;
				return 0;
			}
			if ((*it)->isJump() == true) {
				jump = true;
				return 0;
			}
		}
		return 0;
	}
	// output to terminal for now
	void emit() {
		list<std::shared_ptr<InstrX0>>::iterator it;
		for (it = this->instructions_list->begin(); it != this->instructions_list->end(); ++it) {
			cout << (*it)->toString() << "\t";
		}
	}
	bool isEnd() {
		return end;
	}
	bool isJump() {
		return jump;
	}
private:
	bool end = false;
	bool jump = false;
	list<std::shared_ptr<InstrX0>> *instructions_list;
	int instr_cnt;
	LabelX0 *label;
};

// label instruction
class LabelX0 {
public:
	LabelX0(string _name) {
		this->name = _name; 
	}
	void emit() {
		cout << name << "\t";
	}
	string getName() {
		return this->name;
	}
private:
	string name;
};
LabelX0* LbX(string _name) {
	return new LabelX0(_name);
}

// (jmp label) <-- instruction
class JumpX0 : public InstrX0 {
public:
	~JumpX0() { std::cout << "__PRETTY_FUNCTION__" << std::endl; }
	JumpX0(LabelX0 *_label) {
		this->label = _label;
	}
	int eval() {
		std::list<pair<std::shared_ptr<LabelX0>, std::shared_ptr<BlockX0>>>::iterator it;
		for (it = label_block_list.begin(); it != label_block_list.end(); ++it) {
			if ((it->first->getName()) == (this->label->getName())) {
				it->second->eval();
				if ((it->second)->isEnd()) {
					return 0;
				}
				if ((it->second)->isJump() == true) {
					return 0;
				}
			}
		}
	}
	string toString() {
		return "\tjmp\t\t" + label->getName() + "\n";
	};
	bool isEnd() {
		return false;
	};
	bool isJump() {
		return true;
	};
private:
	LabelX0 *label;
};

// program info [label->block]
class ProgramX0 {
public:
	ProgramX0() {
		pcnt = 0;
	}
	void execute() {
		std::list<pair<std::shared_ptr<LabelX0>, std::shared_ptr<BlockX0>>>::iterator it;
		for (it = label_block_list.begin(); it != label_block_list.end(); ++it) {
			if(it->second->eval()==0) 
				cout << "\tSuccessful Run\n\n";
			if ((it->second)->isEnd()) {
				return;
			}
		}
	}
	void emit() {
		std::list<pair<std::shared_ptr<LabelX0>, std::shared_ptr<BlockX0>>>::iterator it;
		for (it = label_block_list.begin(); it != label_block_list.end(); ++it) {
			it->first->emit();
			it->second->emit();
		}
	}
private:
};
ProgramX0* PX(){
	return new ProgramX0();
}

*/

#endif