; ft_strdup.s - Duplicate a string
; char *ft_strdup(const char *s);
; Input: rdi = pointer to string
; Output: rax = pointer to duplicated string or NULL on error

section .text
	global ft_strdup
	extern malloc
	extern ft_strlen
	extern ft_strcpy

ft_strdup:
	push	rbx
	push	r12
	mov		r12, rdi

	call	ft_strlen wrt ..plt
	inc		rax

	mov		rdi, rax
	call	malloc wrt ..plt
	test	rax, rax
	jz		.done

	mov		rbx, rax
	mov		rdi, rax
	mov		rsi, r12
	call	ft_strcpy wrt ..plt
	mov		rax, rbx

.done:
	pop		r12
	pop		rbx
	ret
