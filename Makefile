NAME		= libasm.a

ASM			= nasm
ASMFLAGS	= -f elf64

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

SRCS		= ft_strlen.s \
			  ft_strcpy.s \
			  ft_strcmp.s \
			  ft_write.s \
			  ft_read.s \
			  ft_strdup.s

OBJS		= $(SRCS:.s=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f main

re: fclean all

test: $(NAME)
	$(CC) $(CFLAGS) main.c -L. -lasm -o main
	./main

.PHONY: all clean fclean re test
