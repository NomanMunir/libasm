#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "libasm.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

void	test_strlen(void)
{
	printf("\n=== Testing ft_strlen ===\n");
	
	const char *tests[] = {"", "Hello", "Hello, World!", "a", NULL};
	
	for (int i = 0; tests[i]; i++)
	{
		size_t expected = strlen(tests[i]);
		size_t result = ft_strlen(tests[i]);
		
		if (expected == result)
			printf(GREEN "[OK] " RESET);
		else
			printf(RED "[KO] " RESET);
		printf("strlen(\"%s\"): expected %zu, got %zu\n", tests[i], expected, result);
	}
}

void	test_strcpy(void)
{
	printf("\n=== Testing ft_strcpy ===\n");
	
	const char *tests[] = {"", "Hello", "Hello, World!", "a", NULL};
	
	for (int i = 0; tests[i]; i++)
	{
		char buf1[100];
		char buf2[100];
		
		strcpy(buf1, tests[i]);
		char *result = ft_strcpy(buf2, tests[i]);
		
		if (strcmp(buf1, buf2) == 0 && result == buf2)
			printf(GREEN "[OK] " RESET);
		else
			printf(RED "[KO] " RESET);
		printf("strcpy(\"%s\"): expected \"%s\", got \"%s\"\n", tests[i], buf1, buf2);
	}
}

void	test_strcmp(void)
{
	printf("\n=== Testing ft_strcmp ===\n");
	
	struct {
		const char *s1;
		const char *s2;
	} tests[] = {
		{"", ""},
		{"Hello", "Hello"},
		{"Hello", "World"},
		{"World", "Hello"},
		{"Hello", "Hello!"},
		{"Hello!", "Hello"},
		{"abc", "abd"},
		{NULL, NULL}
	};
	
	for (int i = 0; tests[i].s1; i++)
	{
		int expected = strcmp(tests[i].s1, tests[i].s2);
		int result = ft_strcmp(tests[i].s1, tests[i].s2);
		
		// Normalize for comparison (signs should match)
		int exp_sign = (expected > 0) - (expected < 0);
		int res_sign = (result > 0) - (result < 0);
		
		if (exp_sign == res_sign)
			printf(GREEN "[OK] " RESET);
		else
			printf(RED "[KO] " RESET);
		printf("strcmp(\"%s\", \"%s\"): expected %d, got %d\n", 
			tests[i].s1, tests[i].s2, expected, result);
	}
}

void	test_write(void)
{
	printf("\n=== Testing ft_write ===\n");
	
	const char *msg = "Hello from ft_write!\n";
	ssize_t result;
	
	// Test valid write
	printf("Writing to stdout: ");
	result = ft_write(1, msg, strlen(msg));
	if (result == (ssize_t)strlen(msg))
		printf(GREEN "[OK] " RESET "Returned %zd bytes\n", result);
	else
		printf(RED "[KO] " RESET "Expected %zu, got %zd\n", strlen(msg), result);
	
	// Test invalid fd
	errno = 0;
	result = ft_write(-1, msg, strlen(msg));
	if (result == -1 && errno == EBADF)
		printf(GREEN "[OK] " RESET "Invalid fd: returned -1, errno = EBADF (%d)\n", errno);
	else
		printf(RED "[KO] " RESET "Invalid fd: returned %zd, errno = %d\n", result, errno);
}

void	test_read(void)
{
	printf("\n=== Testing ft_read ===\n");
	
	char buf[100];
	ssize_t result;
	
	// Create a test file
	int fd = open("/tmp/libasm_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd >= 0)
	{
		write(fd, "Test content", 12);
		close(fd);
	}
	
	// Test valid read
	fd = open("/tmp/libasm_test.txt", O_RDONLY);
	if (fd >= 0)
	{
		memset(buf, 0, sizeof(buf));
		result = ft_read(fd, buf, sizeof(buf) - 1);
		if (result == 12 && strcmp(buf, "Test content") == 0)
			printf(GREEN "[OK] " RESET "Read %zd bytes: \"%s\"\n", result, buf);
		else
			printf(RED "[KO] " RESET "Read %zd bytes: \"%s\"\n", result, buf);
		close(fd);
	}
	
	// Test invalid fd
	errno = 0;
	result = ft_read(-1, buf, sizeof(buf));
	if (result == -1 && errno == EBADF)
		printf(GREEN "[OK] " RESET "Invalid fd: returned -1, errno = EBADF (%d)\n", errno);
	else
		printf(RED "[KO] " RESET "Invalid fd: returned %zd, errno = %d\n", result, errno);
	
	// Cleanup
	unlink("/tmp/libasm_test.txt");
}

void	test_strdup(void)
{
	printf("\n=== Testing ft_strdup ===\n");
	
	const char *tests[] = {"", "Hello", "Hello, World!", "a", NULL};
	
	for (int i = 0; tests[i]; i++)
	{
		char *expected = strdup(tests[i]);
		char *result = ft_strdup(tests[i]);
		
		if (result && expected && strcmp(expected, result) == 0)
			printf(GREEN "[OK] " RESET);
		else
			printf(RED "[KO] " RESET);
		printf("strdup(\"%s\"): expected \"%s\", got \"%s\"\n", 
			tests[i], expected ? expected : "(null)", result ? result : "(null)");
		
		free(expected);
		free(result);
	}
}

void	test_write_big_data(void)
{
	printf("\n=== Testing ft_write with Big Data ===\n");
	
	// Create a large buffer (1MB)
	size_t big_size = 1024 * 1024; // 1MB
	char *big_data = malloc(big_size);
	if (!big_data)
	{
		printf(RED "[KO] " RESET "Failed to allocate memory\n");
		return;
	}
	
	// Fill with pattern
	for (size_t i = 0; i < big_size; i++)
		big_data[i] = 'A' + (i % 26);
	
	// Write to temp file
	int fd = open("/tmp/libasm_write_big.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd >= 0)
	{
		ssize_t written = ft_write(fd, big_data, big_size);
		if (written == (ssize_t)big_size)
			printf(GREEN "[OK] " RESET "Wrote %zd bytes (1MB) successfully\n", written);
		else
			printf(RED "[KO] " RESET "Expected %zu bytes, wrote %zd\n", big_size, written);
		close(fd);
	}
	
	// Verify written data
	fd = open("/tmp/libasm_write_big.txt", O_RDONLY);
	if (fd >= 0)
	{
		char *verify = malloc(big_size);
		ssize_t read_bytes = read(fd, verify, big_size);
		if (read_bytes == (ssize_t)big_size && memcmp(big_data, verify, big_size) == 0)
			printf(GREEN "[OK] " RESET "Data integrity verified\n");
		else
			printf(RED "[KO] " RESET "Data mismatch after write/read\n");
		free(verify);
		close(fd);
	}
	
	unlink("/tmp/libasm_write_big.txt");
	free(big_data);
}

void	test_read_big_data(void)
{
	printf("\n=== Testing ft_read with Big Data ===\n");
	
	// Create test file with 1MB data
	size_t big_size = 1024 * 1024;
	char *big_data = malloc(big_size);
	if (!big_data)
	{
		printf(RED "[KO] " RESET "Failed to allocate memory\n");
		return;
	}
	
	// Fill with pattern
	for (size_t i = 0; i < big_size; i++)
		big_data[i] = 'X' + (i % 26);
	
	// Write test file
	int fd = open("/tmp/libasm_read_big.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd >= 0)
	{
		write(fd, big_data, big_size);
		close(fd);
	}
	
	// Read back with ft_read
	fd = open("/tmp/libasm_read_big.txt", O_RDONLY);
	if (fd >= 0)
	{
		char *read_data = malloc(big_size);
		ssize_t bytes_read = ft_read(fd, read_data, big_size);
		
		if (bytes_read == (ssize_t)big_size)
			printf(GREEN "[OK] " RESET "Read %zd bytes (1MB) successfully\n", bytes_read);
		else
			printf(RED "[KO] " RESET "Expected %zu bytes, read %zd\n", big_size, bytes_read);
		
		if (memcmp(big_data, read_data, big_size) == 0)
			printf(GREEN "[OK] " RESET "Data integrity verified\n");
		else
			printf(RED "[KO] " RESET "Data mismatch after write/read\n");
		
		free(read_data);
		close(fd);
	}
	
	unlink("/tmp/libasm_read_big.txt");
	free(big_data);
}

void	test_strcpy_big_data(void)
{
	printf("\n=== Testing ft_strcpy with Big Data ===\n");
	
	// Create a large string (512KB)
	size_t big_size = 512 * 1024;
	char *src = malloc(big_size + 1);
	char *dst = malloc(big_size + 1);
	if (!src || !dst)
	{
		printf(RED "[KO] " RESET "Failed to allocate memory\n");
		free(src);
		free(dst);
		return;
	}
	
	// Fill source with pattern
	for (size_t i = 0; i < big_size; i++)
		src[i] = 'B' + (i % 26);
	src[big_size] = '\0';
	
	// Test ft_strcpy
	char *result = ft_strcpy(dst, src);
	
	if (result == dst)
		printf(GREEN "[OK] " RESET "ft_strcpy returned destination pointer\n");
	else
		printf(RED "[KO] " RESET "ft_strcpy did not return destination pointer\n");
	
	if (memcmp(src, dst, big_size) == 0 && dst[big_size] == '\0')
		printf(GREEN "[OK] " RESET "Copied %zu bytes (512KB) with null terminator\n", big_size);
	else
		printf(RED "[KO] " RESET "Data mismatch or missing null terminator\n");
	
	free(src);
	free(dst);
}

void	test_read_write_copy_cycle(void)
{
	printf("\n=== Testing Read/Write/Copy Cycle with Big Data ===\n");
	
	size_t big_size = 512 * 1024;
	char *original = malloc(big_size);
	char *intermediate = malloc(big_size);
	char *final = malloc(big_size);
	
	if (!original || !intermediate || !final)
	{
		printf(RED "[KO] " RESET "Failed to allocate memory\n");
		free(original);
		free(intermediate);
		free(final);
		return;
	}
	
	// Fill original with pattern
	for (size_t i = 0; i < big_size; i++)
		original[i] = 'C' + (i % 26);
	
	// Step 1: Write original to file
	int fd = open("/tmp/libasm_cycle_1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ssize_t written = 0;
	if (fd >= 0)
	{
		written = ft_write(fd, original, big_size);
		close(fd);
	}
	
	// Step 2: Read from file into intermediate
	fd = open("/tmp/libasm_cycle_1.txt", O_RDONLY);
	ssize_t read1 = 0;
	if (fd >= 0)
	{
		read1 = ft_read(fd, intermediate, big_size);
		close(fd);
	}
	
	// Step 3: Copy intermediate to final
	memcpy(final, intermediate, big_size);
	
	// Step 4: Write final to another file
	fd = open("/tmp/libasm_cycle_2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ssize_t written2 = 0;
	if (fd >= 0)
	{
		written2 = ft_write(fd, final, big_size);
		close(fd);
	}
	
	// Step 5: Read back and compare
	fd = open("/tmp/libasm_cycle_2.txt", O_RDONLY);
	char *verify = malloc(big_size);
	ssize_t read2 = 0;
	if (fd >= 0)
	{
		read2 = ft_read(fd, verify, big_size);
		close(fd);
	}
	
	// Verify all steps
	if (written == (ssize_t)big_size && read1 == (ssize_t)big_size && 
	    written2 == (ssize_t)big_size && read2 == (ssize_t)big_size)
		printf(GREEN "[OK] " RESET "All read/write operations completed successfully\n");
	else
		printf(RED "[KO] " RESET "Some read/write operations failed\n");
	
	if (memcmp(original, intermediate, big_size) == 0 &&
	    memcmp(intermediate, final, big_size) == 0 &&
	    memcmp(final, verify, big_size) == 0)
		printf(GREEN "[OK] " RESET "Data integrity maintained through full cycle\n");
	else
		printf(RED "[KO] " RESET "Data mismatch in read/write/copy cycle\n");
	
	unlink("/tmp/libasm_cycle_1.txt");
	unlink("/tmp/libasm_cycle_2.txt");
	free(original);
	free(intermediate);
	free(final);
	free(verify);
}

int	main(void)
{
	printf("====================================\n");
	printf("       LIBASM TEST SUITE\n");
	printf("====================================\n");
	
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
	test_read();
	test_strdup();
	
	printf("\n====================================\n");
	printf("    BIG DATA TESTS\n");
	printf("====================================\n");
	
	test_write_big_data();
	test_read_big_data();
	test_strcpy_big_data();
	test_read_write_copy_cycle();
	
	printf("\n====================================\n");
	printf("       TESTS COMPLETE\n");
	printf("====================================\n");
	
	return 0;
}

// The x86-64 General-Purpose Registers
// In 64-bit mode, you have these main registers (each holds 64 bits = 8 bytes):
// ┌────────────────────────────────────────────────────────────────┐
// │ 64-bit register │  Purpose / Convention                        │
// ├─────────────────┼──────────────────────────────────────────────┤
// │ rax             │  Return value from functions                 │
// │ rbx             │  Callee-saved (preserved across calls)       │
// │ rcx             │  4th argument to functions                   │
// │ rdx             │  3rd argument to functions                   │
// │ rsi             │  2nd argument to functions                   │
// │ rdi             │  1st argument to functions                   │
// │ rbp             │  Base pointer (stack frame)                  │
// │ rsp             │  Stack pointer (top of stack)                │
// │ r8              │  5th argument                                │
// │ r9              │  6th argument                                │
// │ r10-r15         │  General purpose                             │
// └─────────────────┴──────────────────────────────────────────────┘

// section .text and global ft_strlen
// section .text
// An executable file has different sections (areas):

// ┌─────────────────────────────────────────────────────────┐
// │  .text section                                          │
// │  • Contains executable CODE (your functions)            │
// │  • Read-only, executable                                │
// │  • This is where ft_strlen lives                        │
// ├─────────────────────────────────────────────────────────┤
// │  .data section                                          │
// │  • Initialized global variables                         │
// │  • Example: int x = 42;                                 │
// ├─────────────────────────────────────────────────────────┤
// │  .bss section                                           │
// │  • Uninitialized global variables                       │
// │  • Example: int arr[100];                               │
// ├─────────────────────────────────────────────────────────┤
// │  .rodata section                                        │
// │  • Read-only data (string literals)                     │
// │  • Example: "Hello, World!"                             │
// └─────────────────────────────────────────────────────────┘