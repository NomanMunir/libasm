; ft_read.s - Read from a file descriptor
; ssize_t ft_read(int fd, void *buf, size_t count);
; Input: rdi = fd, rsi = buf, rdx = count
; Output: rax = bytes read or -1 on error (errno set)

section .text
	global ft_read
	extern __errno_location

ft_read:
	mov		rax, 0				; syscall number for read
	syscall						; Perform syscall
	cmp		rax, 0				; Check for error (negative return)
	jl		.error				; If negative, handle error
	ret							; Return bytes read

.error:
	neg		rax					; Convert negative error code to positive errno
	mov		rdi, rax			; Save errno value
	push	rdi					; Preserve errno value on stack
	call	__errno_location wrt ..plt	; Get pointer to errno
	pop		rdi					; Restore errno value
	mov		[rax], edi			; Set errno
	mov		rax, -1				; Return -1
	ret
