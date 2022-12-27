.PHONY: all clean fclean re log bonus libft

CC = clang
INCLUDES = libmlx_mac
NAME = fdf
LIBFT = ./lib/libft.a
LIBFT_DIR = ./libft
CFLAGS = -Wall -Wextra -Werror
UNAME := $(shell uname)
LIBS := -lmlx -lXext -lX11 -lft -lm

ifeq ($(UNAME), Darwin)
	CFLAGS = -Wall -Wextra -Werror -arch x86_64
	LIBS = -lmlx -lft -framework OpenGL -framework AppKit
endif

SOURCES = main.c utils.c calc.c parse.c bresenham.c draw.c hooks.c pixel.c utils2.c

OBJS = $(SOURCES:.c=.o)

all: $(NAME)

%.o: %.c fdf.h
	$(CC) $(CFLAGS) -c $< -o $@ -I libft/include

$(NAME): $(OBJS) | libft
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS) -L $(LIBFT_DIR)

libft:
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(LIBFT)
	make fclean -C $(LIBFT_DIR)

re: fclean all

git_libft:
	git clone https://github.com/taandreo/42-libft.git libft

libmlx_mac:
	wget https://projects.intra.42.fr/uploads/document/document/9394/minilibx_macos_sierra_20161017.tgz
	tar -xf minilibx_macos_sierra_20161017.tgz && rm -f minilibx_macos_sierra_20161017.tgz

libmlx_linux:
	wget https://projects.intra.42.fr/uploads/document/document/9393/minilibx-linux.tgz
	tar -xf minilibx-linux.tgz && rm -f minilibx-linux.tgz
	sudo apt-get install gcc make xorg libxext-dev libbsd-dev

maps:
	wget https://projects.intra.42.fr/uploads/document/document/9390/maps.zip
	unzip maps.zip
	rm -f maps.zip
