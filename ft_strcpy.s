; ft_strcpy.s - Copy a string to another
; char *ft_strcpy(char *dest, const char *src);
; Input: rdi = dest, rsi = src
; Output: rax = dest

section .text
	global ft_strcpy

ft_strcpy:
	mov		rax, rdi
	xor		rcx, rcx

.loop:
	mov		dl, [rsi + rcx]
	mov		[rdi + rcx], dl
	test	dl, dl
	jz		.done
	inc		rcx
	jmp		.loop

.done:
	ret
