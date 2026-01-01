; ft_read.s - Read from a file descriptor
; ssize_t ft_read(int fd, void *buf, size_t count);
; Input: rdi = fd, rsi = buf, rdx = count
; Output: rax = bytes read or -1 on error (errno set)

section .text
	global ft_read
	extern __errno_location

ft_read:
	xor		rax, rax
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
