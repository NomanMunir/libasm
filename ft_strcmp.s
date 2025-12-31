; ft_strcmp.s - Compare two strings
; int ft_strcmp(const char *s1, const char *s2);
; Input: rdi = s1, rsi = s2
; Output: rax = difference (s1[i] - s2[i]) at first differing position

section .text
	global ft_strcmp

ft_strcmp:
	xor		rcx, rcx			; Initialize index to 0

.loop:
	movzx	eax, byte [rdi + rcx]	; Load byte from s1 (zero-extend to eax)
	movzx	edx, byte [rsi + rcx]	; Load byte from s2 (zero-extend to edx)
	cmp		al, dl				; Compare bytes
	jne		.diff				; If different, calculate difference
	test	al, al				; Check if null terminator
	jz		.equal				; If null, strings are equal
	inc		rcx					; Increment index
	jmp		.loop				; Continue loop

.diff:
	sub		eax, edx			; Calculate difference
	ret

.equal:
	xor		eax, eax			; Return 0 for equal strings
	ret
