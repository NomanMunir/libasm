; ft_write.s - Write to a file descriptor
; ssize_t ft_write(int fd, const void *buf, size_t count);
; Input: rdi = fd, rsi = buf, rdx = count
; Output: rax = bytes written or -1 on error (errno set)

section .text
	global ft_write
	extern __errno_location

ft_write:
	mov		rax, 1				; syscall number for write
	syscall						; Perform syscall
	cmp		rax, 0				; Check for error (negative return)
	jl		.error				; If negative, handle error
	ret							; Return bytes written

.error:
	neg		rax					; Convert negative error code to positive errno
	mov		rdi, rax			; Save errno value
	push	rdi					; Preserve errno value on stack
	call	__errno_location wrt ..plt	; Get pointer to errno
	pop		rdi					; Restore errno value
	mov		[rax], edi			; Set errno
	mov		rax, -1				; Return -1
	ret
