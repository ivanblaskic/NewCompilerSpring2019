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

// Class notes --> ...
/*

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

*/

// Class Notes --> Data Structures
// Random Generation Function
/*

	TESTING TYPE CHECKER

	before:
		randp : Number {depth} + setVars --> Exp

		randp varsSet 0 = number
					variable-reference (if vars)
					bool (50% true / 50% false)

		(+ 1 true) --> generating programs that fails type-check pass

		randExp : (Type -> setVars that have that type - gimme var with int/bool type) 
			  x (Type that you want to generate)
			  x (Number for depth)
			  -> retrun expression of type T

		randp N = randExp (empty mapping, pick a random type (int or bool)) N {passing a depth}

		FUNCT.	ENV.  T.T. DEPTH   = DEFINITION
		-------|-----|----|------- = --------------------------------------------------------------------------------------------------------------------------------
		randExp SIGMA Bool 0	   = true/false/vars(SIGMA(bool))
					  Num  0	   = num/vars(SIGMA(int))
					  Bool (1+N)   = (cmp (rande SIGMA Num N) (rande SIGMA Num N)) 
									 * generating random bool with generating random numbers inside of it
									 * option one for generating random bool -> specific thing
					  Bool (1+N)   = let x := xe in b 
											where xe := randExp SIGMA T N --> any random var w random Type [where T := random_ty]
												   b := randExp SIGMA(T)->extended[add x with type T] Bool N
									 * pick a random type = T --> that's type we will try to generate and that T is the one we will extend to
									 * SIGMA' = SIGMA [T --> VS'] --> VS' = SIGMA [T] U {x} --> where "x" is the new var that has that type we have choosen --> T
									 * now also you have to go to all the other type->var mappings and remove instances of "x" because it's shadowed now
									 * SIGMA'' = remove "x" from the other primes {now only Bool and S64}
									 * second option -> general thing
					  Bool (1+N)   = if (randExp SIGMA Bool N)
										(randExp SIGMA Ty-you got in) (randExp SIGMA Ty-you got in)

	**sigma => environment for the variables
	** T.T. => target type

	Everything that your randp takes the type kind you want it to generate 
		so whenever you generate something it is guaranteed to pass the type check.

	Whole bunch of test cases for the type check
		because I know that everything that my randp creates should pass the type check
			so this way I know that if it fails the type checking 
				then either type checker is wrong or randp function.

	2 separate functions for INT and BOOL - maybe easier to have one function taking in as an argument the target type			

*/

// Class Notes --> Data Structures
// Optimizing and Uniquifying R2 Programs
/*

	What optimizations apply to R2?

	R0 + IFs + CMPs + Booleans

	OBVIOUS
	1) Bools are "simple" --> allowed to be substituted --> getting rid off the variable.
	2) (CMP N1 N2) --> reducing that to a variable --> similar to finding out if addition is being done btw to actual numbers and actually doing it.
	3) (if B1 eT eF) --> reducable to eT or eF depending on B1.
	
	COMPLICATED 
	1) (not (not e)) -> e --> (not x) = (if (x) (f) (t)) --> (if (if (e f t) f t) -> e; proven
	2) (if (not c) t f) -> (if c f t)
	3) (== e1 e1) = true? not if e1s are (read) or better have the (read) in them
	*  has_read is an extremily useful thing to think about --> rather than opt returns new exp
																	it return: new exp + bool {has_read}
	*  old opt: (V-->Exp) x Exp ==> Exp
	   new opt:					==> Exp x Bool {there is no read} --> purtiy: if it has no effects - read is an effect bc it changes the world in some way
	*  nst opt:					==> Exp x Bool {pure} x setVars {used by program}
	*  useful in let case --> if initializing var that is not being used we can replace it with the sequnece of the expression --> look at 6th optimization 
	4) (< e1 (+ N e1)) --> True ==> + 1,000,000 more useful thingys don't go too crazy -> no worries brotha
	*  N has to be positive obviously
	*  some thingys could be very valuable if we know we will be using them a lot in our database
	5) (if (cond) e1 e1) --> only if it's pure {cond}; in that case --> (seq (c e1))
	*  sequence: Exp {after this effect}	x	Exp {returns this var}		-->		Exp	
	*  sequence: (+ N read) 12 = (let some_var := read in 12) --> have to return number 12 --> if there is effect(s) add it (them in order) 
	*  sequence: (true)		12 = 12 --> if there is no effect then return the body only
	*  removing things that are not useful --> extremely valuable
	6) opt SIGMA (let v := xc in b) = let (xe', xe_pure?, xe_vars) = opt SIGMA xe
									  let (SIGMA') = SIGMA [mapping from x-->xe' if pure and simple o.w. x]
									  then (b', b_pure?, b_vars) = opt SIGMA' b
									  * WHAT DO WE WANT TO RETURN?
									  - if x is not inside of b_var --> no need to generate the let
											instead generate (seq of xe' and b')=Exp, (and xe and b purity)=purity, (union of xe and b vars)=vars
									  * in future no need for having variable for it; doing register allocation; etc.
									  - if x is inside of b_var then (let x := xe' in b'), purity as above, xe_vars U (b_vars - {x}) --> don't want to include shadowed var
	7) if x {var_reference although optimized} eT eF := 
			if c'=x then opt SIGMA [x->true] eT
						 opt SIGMA [x->false] eF 
	* where c'=x, eT'=eT and eF'=eF --> learning about the variables by the control flow of the program
	* related to 5) --> helps in a lot of cases to benefit from 5) as well

	*  PURE --> var, num, boolean --> has no computation in it

	Jay's code for all If-based optimization - 39:00

	UNIQUIFY PASS --> no different really --> just including more expressions --> ExpR2 rather than ExpR0

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

*/

// Class Notes --> Data Structures
// Getting C and X language ready so they can be targets for the other passes
/*

	40:00 --> February 2nd

*/

// Class Notes --> Functions
/*

	...

*/

// Class Notes --> Closures
/*

	...

*/