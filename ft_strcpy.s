; ft_strcpy.s - Copy a string to another
; char *ft_strcpy(char *dest, const char *src);
; Input: rdi = dest, rsi = src
; Output: rax = dest

section .text
	global ft_strcpy

ft_strcpy:
	mov		rax, rdi			; Save dest pointer for return value
	xor		rcx, rcx			; Initialize index to 0

.loop:
	mov		dl, [rsi + rcx]		; Load byte from src
	mov		[rdi + rcx], dl		; Store byte to dest
	test	dl, dl				; Check if null terminator
	jz		.done				; If null, we're done
	inc		rcx					; Increment index
	jmp		.loop				; Continue loop

.done:
	ret							; Return dest in rax
