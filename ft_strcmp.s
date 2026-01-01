; ft_strcmp.s - Compare two strings
; int ft_strcmp(const char *s1, const char *s2);
; Input: rdi = s1, rsi = s2
; Output: rax = difference (s1[i] - s2[i]) at first differing position

section .text
	global ft_strcmp

ft_strcmp:
	xor		rcx, rcx

.loop:
	movzx	eax, byte [rdi + rcx]
	movzx	edx, byte [rsi + rcx]
	cmp		al, dl
	jne		.diff
	test	al, al
	jz		.equal
	inc		rcx
	jmp		.loop

.diff:
	sub		eax, edx
	ret

.equal:
	xor		eax, eax
	ret
