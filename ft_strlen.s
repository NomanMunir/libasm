; ft_strlen.s - Returns the length of a string
; size_t ft_strlen(const char *s);
; Input: rdi = pointer to string
; Output: rax = length of string

section .text
	global ft_strlen

ft_strlen:
	xor		rax, rax

.loop:
	cmp		byte [rdi + rax], 0
	je		.done
	inc		rax
	jmp		.loop

.done:
	ret
