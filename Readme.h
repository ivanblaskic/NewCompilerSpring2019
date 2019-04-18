#pragma once

/*

	... figure out how to test complicated programs so something gets spilled at the stack ...

*/

// Steps taken and to be taken while building compilers
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
	42) + write a few tests for assign-homes that predict its output
		- you’ll want to make sure that the output program contains no variables
		  and that variables are assigned homes consistently
	43) + implement the assign-homes pass for X0 programs
		- this pass takes X0 programs and returns new X0 programs which do not mention variables
		- for now, it should just assign everything to consistent stack locations in an arbitrary way
		  based on the set of variables used in the program
	44) + connect assign-homes to your test suite
		- ensure that every test program behaves the same before and after assign-homes by using the X0 interpreter
		- you may want to also include a check that guarantees the result contains no variable references
	45) 1/6 write a half-dozen tests for patch-instructions that predict its output
		- you’ll want to make sure memory references are legal
	46) + implement the patch-instructions pass for X0 programs
		- this pass takes X0 programs and returns new X0 programs which mention memory
		  either zero or one times per instruction
	47) + connect patch-instructions to your test suite
		- ensure that every test program behaves the same before and after patch-instructions
		  by using the X0 interpreter
		- remember, this pass assumes that assign-homes has run

		  TOUCHDOWN(:
	48) ? implement your language runtime
		- initially, this is just two functions: read_int and print_int
		- the first corresponds to the read call and the second is automatically used at the end of programs
	49) ? implement the main-generation pass for X0 programs
		- this pass should extend your final X0 programs with the prelude and postlude operations
		  that set up the stack pointer appropriately for your code
	50) ? connect your test suite to your system assembler and language runtime
		- close the final knot and get an actual compiler by having your final X0 programs
		  (that come out of main-generation) sent to the system assembler and linked with your language runtime
		- you finally have a working compiler! Aren’t you proud?

	SKIPPED 48-50 with 48 & 49 being partially done and commented out in the .cpp and .asm file that has the program stored in it is named ASMFunction.asm

		  UNCOVER-LIVE()
	51) + write a dozen tests for uncover-live that predict its output
		- I don’t remember using examples from real programs, because they are likely to be too complicated
		- instead, use simple ones that you come up with by hand
	52) + implement the uncover-live pass for X0 programs
		- this pass takes X0 programs and returns new X0 programs
		  where the block’s auxiliary field contains a list of live-after sets corresponds to each instruction
		- make sure that you add registers to the live sets, not just variables

		  BUILD-INTERFERENCES()
	53) + Write a dozen tests for build-interferences that predict its output
		- these should be the same programs you tested uncover-live with
	54) + implement the build-interferences pass for X0 programs
		- don’t go overboard with finding and using a graph library for your language
		- these are really simple graphs, relax

		  COLOR-GRAPH()
	55) + write a dozen tests for color-graph that predict its output
		- in addition to tests that use your build-interferences results
		- you should also make some examples that correspond to Sudoku boards
	56) + implement the color-graph function on arbitrary graphs
		- using the greedy saturation algorithm described in the book

		  ASSIGN-REGISTERS()
	57) + replace assign-homes with a new pass named assign-registers
		  and implement the stupid-allocate-registers pass for X0 programs
		- assign-registers pass should expect an assignment of variables to registers
		  or stack locations in the auxiliary field and remove variables
		  from the program by using the given mapping. stupid-allocate-registers
		  will generate this mapping from the set of variables by assigning them
		  all to stack locations
		- this is a trivial generalization of assign-homes!
	58) + write a dozen tests for the assign-registers that predict its output and check their behavior
		- you should manually come up with register assignments for some sample programs,
		  verify that assign-registers (when given those assignments) does it job,
		  and check that the programs behave the same as they did before assignment

		  ALLOCATE-REGISTERS()
	59) + write a dozen tests for allocate-registers that predict its output
		- these should be the same programs you tested color-graph with
		- make sure there are tests that actually spill to the stack
	60) + replace stupid-allocate-registers with a new allocate-registers pass on X0 programs
		- this pass will assume uncover-live and build-interferences have been run
		  and use color-graph to construct a register assignment for assign-registers

		  MAIN-GENERATION()
	61) + update the main-generation pass to save and restore callee-saved registers
		- start off by saving and restoring all callee-saved registers,
		  then make it sensitive to what you actually use
	62) + connect your test suite to the new main-generation and allocate-registers passes
		- you now have a better compiler

		  MOVE-GRAPH()
	63) + write a few test programs that have opportunities for move-biasing to be effective
		- the book contain some examples
		- you should come up with at least one R1 program that has the property;
		- in addition to X0 program
	64) + extend your build-interferences pass to construct a move-graph
		- update your build-interference tests to check that the move-graph is constructed correctly

		  MOVE-BIASING()
	65) + extend your color-graph function to incorporate move-biasing with an optional input argument
		- translate your move-biasing tests to color-graph problems and expected outputs
	66) + update your allocate-registers pass to make use of the move-biasing feature of color-graph
		- this should be a trivial step of connecting the dots

		>> C- <<

		Completed "Task #N - Description"

*/