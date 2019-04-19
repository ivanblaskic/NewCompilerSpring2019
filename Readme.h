#pragma once

// Steps taken and to be taken while building compilers
// Watch class - tonight
/*
	author: Ivan Blaskic
	date:	01/24/2019
	use:	Jay's CC Class
	at:		UML


	67) ! extend your data types from R1 to R2
		- recall the definition of R2:
		- I recommend not making explicit constructors for 
		  binary subtraction, and, or or, but have those be pseudo-ASTs that expand to other forms 
		- for example, in Racket, (define (make-and-ast x y) (make-if-ast x y (make-false-ast))) 
		- this is not required, but will simplify the rest of your compiler
		- you could do this with not as well and turn some of the comparisons into not’d versions of others, 
		  but I don’t recommend that, because X86-64 supports all of these operations nicely
		- and and or are specifically useful because their short-circuiting behavior is annoying to implement ow
	68) ! extend your pretty printer from R1 to R2
		- again, use whichever syntax you think looks nice
	69) ! write a dozen test R2 programs
		- obviously, these should incorporate the new features
	70) ! extend your interpreter from R1 to R2
		- there’s nothing very special about this
	71) ! write type-checker tests for R2
		- these should be programs that fail to type-check
	72) ! write a type-checker for R2
		- you’ll need an environment mapping variables to their types 
		- integrate this into your R2 tests so that every program you’ve written is type-checked before being used
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
	77) ! extend your data types from C0 to C1
	78) ! extend your pretty-printer from C0 to C1 programs
		- the gotos everywhere will be a little ugly
	79) ! write a half-dozen C1 test programs
		- obviously, use the new features
	80) ! extend your interpreter from C0 to C1 programs
		- you’ll want to hold an environment mapping labels to tails for use with gotos
	81) ! extend your data types from X0 to X1
	82) ! extend your emitter from X0 to X1 programs
		- the only annoying part is keeping track of the byte version of the registers
	83) ! write a half-dozen X1 test programs
		- obviously, use the new features
	84) ! extend your interpreter from X0 to X1 programs
		- use bitmasking to pull out the appropriate byte from registers
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
	95) ! extend your compiler to support conditional moves
		- this requires a change to the C and X languages
		- the most interesting change is to the explicate-control pass
		- you would use these when the RHS of a let is a simple if
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