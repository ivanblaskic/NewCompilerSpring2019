#pragma once

/*

		LEFT TO DO
		----------

		  ASSIGN-REGISTERS() -- patch
	57) - replace assign-homes with a new pass named assign-registers
		  and implement the stupid-allocate-registers pass for X0 programs
		- assign-registers pass should expect an assignment of variables to registers
		  or stack locations in the auxiliary field and remove variables
		  from the program by using the given mapping. stupid-allocate-registers
		  will generate this mapping from the set of variables by assigning them
		  all to stack locations
		- this is a trivial generalization of assign-homes!

			Adding a Mapping from Color to Registers or Stack Locations (Color --> X arg)
					
			Sigma		-->		(for i = 0 to 13) && (for r = rbx ... r15)
									Sigma[i] = r
								(for i = 14 to biggest number in C - assignment)
									Sigma[i] = Stack var (i-13)		{%rsp(8 x (i-13))}

			* don't forget to record how many stack variables there are --> equals to biggest # in C-13
			* same as it used to be with old no-variables pass, but now we use registers for better performance
			* modifying the already existing function or modification
			* SIGMA(V) = sigma[c(V)] --> should be easy to stack this code on top of everything you have

	58) - write a dozen tests for the assign-registers that predict its output and check their behavior
		- you should manually come up with register assignments for some sample programs,
		  verify that assign-registers (when given those assignments) does it job,
		  and check that the programs behave the same as they did before assignment

		  ALLOCATE-REGISTERS()
	59) ! write a dozen tests for allocate-registers that predict its output
		- these should be the same programs you tested color-graph with
		- make sure there are tests that actually spill to the stack

	60) ! replace stupid-allocate-registers with a new allocate-registers pass on X0 programs
		- this pass will assume uncover-live and build-interferences have been run
		  and use color-graph to construct a register assignment for assign-registers

			Write new programs to test the code rather than doing the entire compilation.
			Maybe just make up your interference graph and test how it assigns registers for it.

		  MAIN-GENERATION()
	61) ! update the main-generation pass to save and restore callee-saved registers
		- start off by saving and restoring all callee-saved registers,
		  then make it sensitive to what you actually use

			** any register that you use that is callee save registers you have to actually save it
			** used to be:		main-pass		BEGIN	-->		pushq		rbp			// saving rbp
			**													movq		rsp, rbp	// saving rbp
			**													save		callee-saves regs
			**													subq		FC {free var cnt}, rsp
			**																			// saving rsp
			**													jmp			BODY		

			** now: FC = how many stack-vars rather than how many vars
			** used to be:		main-pass		END		-->		addq		FC, rsp
			**													restore		callee-saves regs
			**													popq		rbp

			callee-saves = rsp, rbp, r12-r15 --> have to be saved by callee
			- if we are going to use them we have to save them

			** saving-regs: rsp & rbp already pushed
			** add: pushq r12, pushq r13, ..., pushq r15
			** you can either always push them or just those which you use

			** restoring-regs: always in the opposite order
			** add: popq r15, popq r14, ..., popq r12
	
			Caller Frame is calling-function-frame.
			Callee Frame is function-being-called-frame.

	62) ! connect your test suite to the new main-generation and allocate-registers passes
		- you now have a better compiler

			Test on your running example. Add some others too.

*/