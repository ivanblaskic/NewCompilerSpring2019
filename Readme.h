#pragma once

// Steps to be taken while building compilers
/*

	author: Ivan Blaskic
	date:	01/24/2019
	use:	Jay's CC Class
	at:		UML

	<<< R1 --> R2 >>>

		>>> WATCH LECTURE <<<

	73) ! extend your random generation function from R1 to R2
		- you should have two helper functions. The first should generate an R2 program 
		  that returns a number and the other should generate one that returns a boolean 
		- you’ll need to extend your environment to record the type of let-bound variables

	74) ! write some R2-specific optimizer tests
		- again, to verify that you are actually optimizing the programs
	75) ! extend your optimizer from R1 to R2
		- you should expand the partial evaluation of boolean operations and by removing ifs with known values 
		- another thing is to remove nots by flipping the branches of ifs 
		- if you substitute variables are bound to (not var), then you can do this more completely too

	76) ! extend the uniquify pass from R1 to R2 programs, with a few test cases to check its output
		- the new features don’t meaningfully change this pass

	<<< C0 --> C1 >>>

	77) ! extend your data types from C0 to C1
	78) ! extend your pretty-printer from C0 to C1 programs
		- the gotos everywhere will be a little ugly
	79) ! write a half-dozen C1 test programs
		- obviously, use the new features
	80) ! extend your interpreter from C0 to C1 programs
		- you’ll want to hold an environment mapping labels to tails for use with gotos

	<<< X0 --> X1 >>>

	81) ! extend your data types from X0 to X1
	82) ! extend your emitter from X0 to X1 programs
		- the only annoying part is keeping track of the byte version of the registers
	83) ! write a half-dozen X1 test programs
		- obviously, use the new features
	84) ! extend your interpreter from X0 to X1 programs
		- use bitmasking to pull out the appropriate byte from registers

	<<< Compiling R2-->C1-->X1 >>>

	85) ! extend the resolve-complex pass from R1 to R2 programs, with a few test cases to check its output
		- the new features don’t meaningfully change this pass 
		- comparisons are complex, while ifs can be complex or expressions, 
		- depending on whether they are in tail position 
		- the test expression of an if should be a comparison
	86) ! extend the explicate-control pass from R1 to R2 programs, w a half-dozen tests that predict its output
		- this will be much more complicated than before, because you’ll be outputing multiple labels 
		  when there are ifs in the code 
		- you’ll want to have a new helper for predicate positions
	87) ! extend the uncover-locals pass for C1 programs
	88) ! extend the select-instr pass for C1 programs, with a few test cases to check its output
		- this should actually quite easy because the new C1 features map directly to new X1 features
	89) ! write a half-dozen tests for the uncover-live pass
		- in particular, you need to make sure you are handling multiple blocks correctly
	90) ! extend your uncover-live pass for X1 programs
		- you’ll need to produce the blocks in topological order so you can identify appropriate after blocks
	91) ! extend your build-interference pass for X1 programs, with a few test cases to check its output
		- this should be easy
		- you should update alloc-registers as well
	92) ! extend the patch-instructions pass for X1 programs, with a few test cases to check its output
		- cmpq and movzbq cannot have a constant in the second position
	93) ! update your runtime to support printing out booleans, in addition to integers
		- use a convenient syntax, but don’t expose that booleans are really numbers
	94) ! update your main-generation pass for boolean-outputting programs
		- you’ll want to keep track the whole time what the final type of the program is 
		  so you can print the right kind of thing

	<<< Support for Conditional Moves in Compiler >>>

	95) ! extend your compiler to support conditional moves
		- this requires a change to the C and X languages
		- the most interesting change is to the explicate-control pass
		- you would use these when the RHS of a let is a simple if

	<<< R2 --> R3 >>>

	96) ! extend your data types from R2 to R3
		- it is important to understand that vectors are not arrays: the field referenced 
		  or mutated is statically known 
		- they are more like C structures
	97) ! extend your pretty printer from R2 to R3
		- again, use whichever syntax you think looks nice
	98) ! write a dozen test R3 programs
		- make sure you create different sized vectors and verify that shallow copying works
	99) ! extend your interpreter from R2 to R3
		- there’s nothing very special about this
	100) ! write type-checker tests for R3
		- these should be programs that fail to type-check
	101) ! extend your type-checker from R2 to R3
		- this is not very interesting
	102) ! extend your random generation function from R2 to R3
		- you’ll need to have a new helper that generates a random vector of a certain length 
		  with a certain type at a particular index
	103) ! write a function that generates R3 program that uses N bytes of memory and makes it unreachable M times 
		- you’ll use this for testing garbage collection

		Completed "Task #N - Description"

*/

// Class notes --> Adding Control Flow {Changes Everything} + Need of Type Checker {2 types}
/*

	R1 := 
		p	:=  program info e
		e	:=  (+ e e) | (- e) | number | var | read | (let x = xe in be) {where x --> var} 

	R2 :=
		e	:=	.... | true | false | (and e e) | (or e e) | (not e) | (cmp e e) | (if e e e) | (sub e e)
		cmp	:=	== | < | <= | >= | >
		ty	:=	S64 {signed integer} | Bool

	Cijeli program se koristi rekurzivnim pozivima - 
		potreban je type-checker kao komponenta expressiona koji ce ici kroz svaki poziv 
			te provjeravati je li vrijednost koja se vraca ona koja se ocekuje.

	Od (+, -, number, var, read, let, sub, var) ocekuje se broj/number.
	Od (cmp, not, and, or, true, false) ocekuje se bool/true-false.
	Od (if) ocekuje se bilo sta ja mislim - provjeri u notes.

	Zanimljivo je kako onda implementirati interpreter/eval() sada kada se ne ocekuje vise int 
		pretpostavljam da mi znamo je za svaku funkciju sto se vraca i za svaku sto se ocekuje kao ulaz
			ali sto sa if-om? sto on vraca? ili moze samo vratiti broj?

	

	let x = 5 in 
		let y = 4 in 
			if (> x y) (x) (y)
	
	let x = 5 in
		let y = 4 in
			if (true) (if (cmp x y) (x) (y))

	class BoolR2 : public ExpR0, TypeR2 {
	public:
		BoolR2(BoolR2* _bool_type) {
			this->bool_type = _bool_type; 
		}
	private:
		BoolR2* bool_type;
	};

	class TrueR2 : public BoolR2 {
	public:
		TrueR2() {}
	private:
		bool is_true = true;
	};

	class TypeR2 {
	public:
		virtual TypeR2* type_checker(ExpR0* check_exp) = 0;
	};

	class NumR0 : public ExpR0, TypeR2 {

	};

	interp	sigma	true		=		true
					false		=		false
					and (eL eR)	= if (eL eR false)
					or (eL eR)	= if (eL true eR)
					not (eA)	= if (interp sigma ea) (false) else (true)

					if (eCond eT eF) = if (interp{I} sigma eCond) (I sigma eT) else (I sigma eF)
					comp (eL eR)	 = (I sigma eL) cmp (I sigma eR) {depending on cmp sign given}
									   * (1 <= true) --> undefined behavior {UB}
											* implement type-checker 
												* identifies {UB} and refuses to compile program										

	* macros: compiler API - allows you to modify things in compiler

	* different if then C: there you are true if you are != 0 and false if == 0
		x = y || z --> x can be 42 or any number doesn't have to be true
		No type systems in C but just rules for manipulating bits




	Type-Checker {typec}:	e	-->	error - detect it and notify properly

	Gamma: mapping from variables to their types
	
	--> Gamma proves that expression e has type t

	Gamma-t	e	:	t 
	Gamma-t x	:	Gamma(x)	--> look inside our type environment what the variable is

	if you call type-checker and you give it type environment it will return that type

	Gamma-t n	:	S64
	Gamma-t t/f	:	Bool

	Gamma proves that an addition of eL and eR has type S64 
		if gamma proves that eL has type 64 and gamma proves that eR has type 64
			--> recursive call to the type checker with the same gamma and eL 
				--> then look at the code

	** longer version
	translated to code --> typec gamma (+ eL eR) =
								tyL = typec gamma (eL)
								tyR	= typec gamma (eR)
								if tyL != S64	error
								if tyr != S64	error
							S64

	*** shorter version
	{Gamma-t	(+ eL eR)			: S64}		if {Gamma-t		(eL) : S64  &&  Gamma-t		(eR) : S64}	
	{Gamma-t	(- eL)				: S64}		if {Gamma-t		(eL) : S64}
	{Gamma-t	(cmp eL eR)			: Bool}		if {Gamma-t		(eL) : S64	&&	Gamma-t		(eR) : S64}
	{Gamma-t	(not eA)			: Bool}		if {Gamma-t		(eA) : Bool}
	{Gamma-t	(if eC eT eF)		: tyR}		if {Gamma-t		(eC) : Bool	&&  Gamma-t (eT,eF) : tyR}
	{Gamma-t	(let x = xe in be)	: tyB}		if {Gamma-t		(xe) : tyX	&&  Gamma[x-->tyX] <-- be : tyB}

	-->	notice that {<--} stands for gamma extended with the mapping x-->tyX then be has to be typed tyB

	Continue: 
		- next class link --> https://echo360.org/lesson/G_79ff9958-bdaf-488c-ad67-efc8c8df744d_048d767f-297d-4866-b7b5-56943761d03a_2019-02-12T11:00:00.000_2019-02-12T12:20:00.000/classroom#sortDirection=desc
		- 7.pdf in CC file on Desktop

*/

// Class Notes --> Data Structures
/*

	...

*/

// Class Notes --> Functions
/*

	...

*/

// Class Notes --> Closures
/*

	...

*/