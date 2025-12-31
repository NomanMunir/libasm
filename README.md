# libasm

A collection of standard C library functions reimplemented in x86-64 assembly language (NASM syntax).

## Overview

This project implements common C standard library functions in pure assembly, providing a low-level understanding of how these functions work at the CPU instruction level.

## Implemented Functions

| Function | Prototype | Description |
|----------|-----------|-------------|
| `ft_strlen` | `size_t ft_strlen(const char *s)` | Calculate string length |
| `ft_strcpy` | `char *ft_strcpy(char *dst, const char *src)` | Copy string |
| `ft_strcmp` | `int ft_strcmp(const char *s1, const char *s2)` | Compare two strings |
| `ft_write` | `ssize_t ft_write(int fd, const void *buf, size_t count)` | Write to file descriptor |
| `ft_read` | `ssize_t ft_read(int fd, void *buf, size_t count)` | Read from file descriptor |
| `ft_strdup` | `char *ft_strdup(const char *s)` | Duplicate string (with malloc) |

## Requirements

- **NASM** (Netwide Assembler) - version 2.14+
- **GCC** - for compiling test suite
- **Linux** x86-64 architecture

## Installation

```bash
# Install NASM
sudo apt install nasm

# Clone repository
git clone https://github.com/NomanMunir/libasm.git
cd libasm

# Build library
make
```

## Usage

### Build the library

```bash
make              # Compile all .s files to libasm.a
```

### Run tests

```bash
make test         # Compile and run test suite
```

### Clean build artifacts

```bash
make clean        # Remove object files
make fclean       # Remove object files and library
make re           # Rebuild from scratch
```

### Use in your project

```c
#include "libasm.h"

int main(void) {
    char *str = "Hello, Assembly!";
    size_t len = ft_strlen(str);
    ft_write(1, str, len);
    return 0;
}
```

Compile with:
```bash
gcc your_program.c -L. -lasm -o your_program
```

## Project Structure

```
.
├── ft_strlen.s       # String length
├── ft_strcpy.s       # String copy
├── ft_strcmp.s       # String compare
├── ft_write.s        # Write syscall wrapper
├── ft_read.s         # Read syscall wrapper
├── ft_strdup.s       # String duplication
├── libasm.h          # Header file
├── main.c            # Test suite
├── Makefile          # Build configuration
└── README.md         # This file
```

## Technical Details

- **Architecture:** x86-64 (64-bit)
- **Syntax:** Intel syntax (NASM)
- **Calling Convention:** System V AMD64 ABI
- **File Format:** ELF64

### Register Usage

| Register | Purpose |
|----------|---------|
| `rdi` | 1st argument |
| `rsi` | 2nd argument |
| `rdx` | 3rd argument |
| `rcx` | 4th argument |
| `rax` | Return value |

## Learning Resources

- [NASM Documentation](https://www.nasm.us/doc/)
- [x86-64 Instruction Reference](https://www.felixcloutier.com/x86/)
- [System V ABI](https://refspecs.linuxbase.org/elf/x86_64-abi-0.99.pdf)

## License

MIT License - see [LICENSE](LICENSE) file for details.

## Author

NomanMunir
