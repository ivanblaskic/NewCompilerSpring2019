.code
getValueFromASM proc
begin:	push rbp
mov rbp, rsp
push r12
push r13
push r14
push r15
add rsp, 0
jmp body
pop r15
pop r14
pop r13
pop r12

body:	mov rax, 2
mov rax, 2
add rax, 2
mov rax, rax
mov rbx, 5
mov rbx, 6
mov rbx, 6
mov rcx, 5
add rcx, rbx
mov rcx, rcx
mov rax, rax
add rax, rcx
mov rax, rax
jmp end

end:	sub rsp, 0
pop rbp
ret

getValueFromASM endp
end