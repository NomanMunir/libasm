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