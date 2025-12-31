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
	push	rbx					; Save callee-saved register
	push	r12					; Save callee-saved register
	mov		r12, rdi			; Save original string pointer

	; Get string length
	call	ft_strlen wrt ..plt	; Call ft_strlen (result in rax)
	inc		rax					; Add 1 for null terminator

	; Allocate memory
	mov		rdi, rax			; Set size argument for malloc
	call	malloc wrt ..plt	; Call malloc
	test	rax, rax			; Check if malloc returned NULL
	jz		.done				; If NULL, return NULL (errno already set by malloc)

	; Copy string
	mov		rbx, rax			; Save allocated pointer
	mov		rdi, rax			; dest = allocated memory
	mov		rsi, r12			; src = original string
	call	ft_strcpy wrt ..plt	; Copy string
	mov		rax, rbx			; Return allocated pointer

.done:
	pop		r12					; Restore callee-saved register
	pop		rbx					; Restore callee-saved register
	ret
