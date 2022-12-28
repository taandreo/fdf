.PHONY: all clean fclean re log bonus libft

CC = cc
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

SRCS_MANDATORY = mandatory/main.c mandatory/utils.c mandatory/calc.c mandatory/parse.c \
	mandatory/bresenham.c mandatory/draw.c mandatory/hooks.c mandatory/pixel.c mandatory/utils2.c

SRCS_BONUS = bonus/main_bonus.c bonus/utils_bonus.c bonus/calc_bonus.c bonus/parse_bonus.c \
	bonus/bresenham_bonus.c bonus/draw_bonus.c bonus/hooks_bonus.c bonus/pixel_bonus.c bonus/utils2_bonus.c

OBJS_MANDATORY = $(SRCS_MANDATORY:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

OBJS_ALL = $(OBJS_MANDATORY) $(OBJS_BONUS)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I libft/include -I include -c $< -o $@ 

$(NAME): $(OBJS_MANDATORY) | libft
	$(CC) $(CFLAGS) $(OBJS_MANDATORY) -o $(NAME) $(LIBS) -L $(LIBFT_DIR)

bonus: $(OBJS_BONUS) | libft
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME) $(LIBS) -L $(LIBFT_DIR)

libft:
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS_ALL)
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

log:
	@echo $(SRCS_MANDATORY)
	@echo $(SRCS_BONUS)
	@echo $(OBJS_MANDATORY)
	@echo $(OBJS_BONUS)
	@echo $(OBJS_ALL)
