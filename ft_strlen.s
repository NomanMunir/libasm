; ft_strlen.s - Returns the length of a string
; size_t ft_strlen(const char *s);
; Input: rdi = pointer to string
; Output: rax = length of string

section .text
	global ft_strlen

ft_strlen:
	xor		rax, rax			; Initialize counter to 0

.loop:
	cmp		byte [rdi + rax], 0	; Compare current char with null terminator
	je		.done				; If null, we're done
	inc		rax					; Increment counter
	jmp		.loop				; Continue loop

.done:
	ret							; Return length in rax
