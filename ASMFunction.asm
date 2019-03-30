.code
getValueFromASM proc
begin:	push rbp
mov rbp, rsp
add rsp, 4
jmp body

body:	call function_name
mov [rbp+3], rax
mov rax, [rbp+3]
mov [rbp+2], rax
mov [rbp+1], 5
mov rax, [rbp+3]
add [rbp+1], rax
mov rax, [rbp+1]
mov [rbp+0], rax
mov rax, [rbp+0]
jmp end

end:	sub rsp, 4
pop rbp
ret

getValueFromASM endp
end