.PHONY: libft.a all clean fclean re log bonus

CC = cc
INCLUDES = libmlx_mac
NAME = fdf
LIBFT = ./lib/libft.a
LIBFT_DIR = ./libft
CFLAGS = -Wall -Wextra -Werror

SOURCES = fdf.c

OBJS = $(SOURCES:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	clang $(CFLAGS) -o $@ -lmlx -lft -framework OpenGL -framework AppKit -L lib $(OBJS)

$(LIBFT):
	make bonus -C $(LIBFT_DIR)
	cp -fp libft/libft.a lib/

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