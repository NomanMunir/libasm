; ft_write.s - Write to a file descriptor
; ssize_t ft_write(int fd, const void *buf, size_t count);
; Input: rdi = fd, rsi = buf, rdx = count
; Output: rax = bytes written or -1 on error (errno set)

section .text
	global ft_write
	extern __errno_location

ft_write:
	mov		rax, 1
	syscall
	cmp		rax, 0
	jl		.error
	ret

.error:
	neg		rax
	mov		rdi, rax
	push	rdi
	call	__errno_location wrt ..plt
	pop		rdi
	mov		[rax], edi
	mov		rax, -1
	ret
