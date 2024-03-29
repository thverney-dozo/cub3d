CFLAGS = -Wall -Werror -Wextra
NAME = Cub3D

HEADERS = -I include -I gnl -I libft

SRC_PATH = srcs/
SRC_FILE = cub3d.c \
parsing.c \
distance.c \
events.c \
display.c \
texture.c \
ft_utils.c \
parsing_utils.c \
parsing_utils_2.c \
display_sprite.c \
ft_screenshot.c \
ft_error.c \
ft_stock_sprites.c \
ft_free.c \
ft_utils_2.c \
display_sprite_2.c \

GNL_PATH = gnl/
GNL_FILE = get_next_line.c get_next_line_utils.c

LIB_PATH = libft/
LIB_FILE = ft_split.c \
ft_substr.c \
ft_calloc.c \
ft_bzero.c \
ft_strjoin.c \
ft_atoi.c \
ft_putstr_fd.c \
ft_putchar_fd.c \
ft_strchr.c \
ft_sdupfr.c \
ft_isdigit.c \
ft_strlen.c \
ft_sjoin_free.c \

INC= srcs/cub3d.h
SRC = ${addprefix ${SRC_PATH}, $(SRC_FILE)} ${addprefix ${GNL_PATH}, $(GNL_FILE)} ${addprefix ${LIB_PATH}, $(LIB_FILE)}
OBJS = ${SRC:%.c=%.o}
FRAMEWORK = -framework OpenGL -framework AppKit

all: ${NAME}

$(NAME): ${OBJS} ${INC}
	@gcc ${CFLAGS} ${HEADERS} -g3 -l mlx ${FRAMEWORK} ${OBJS} -o ${NAME}
	@echo 
	@echo "\n\033[03m			A raycasting shooter Wolfenstein-type\033[00m\033[0;32m"
	@echo "──────────────────────────────────────────────────────────────────────────────"
	@echo "─██████████████─██████──██████─██████████████───██████████████─████████████───"
	@echo "─██░░░░░░░░░░██─██░░██──██░░██─██░░░░░░░░░░██───██░░░░░░░░░░██─██░░░░░░░░████─"
	@echo "─██░░██████████─██░░██──██░░██─██░░██████░░██───██████████░░██─██░░████░░░░██─"
	@echo "─██░░██─────────██░░██──██░░██─██░░██──██░░██───────────██░░██─██░░██──██░░██─"
	@echo "─██░░██─────────██░░██──██░░██─██░░██████░░████─██████████░░██─██░░██──██░░██─"
	@echo "─██░░██─────────██░░██──██░░██─██░░░░░░░░░░░░██─██░░░░░░░░░░██─██░░██──██░░██─"
	@echo "─██░░██─────────██░░██──██░░██─██░░████████░░██─██████████░░██─██░░██──██░░██─"
	@echo "─██░░██─────────██░░██──██░░██─██░░██────██░░██─────────██░░██─██░░██──██░░██─"
	@echo "─██░░██████████─██░░██████░░██─██░░████████░░██─██████████░░██─██░░████░░░░██─"
	@echo "─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░████─"
	@echo "─██████████████─██████████████─████████████████─██████████████─████████████───"
	@echo "──────────────────────────────────────────────────────────────────────────────\033[00m"
	@echo "                                \033[03mHas been created!\n\033[00m"

%.o : %.c
	@/bin/echo -n [+]
	@gcc $(CFLAGS) -c ${HEADERS} $< -o $@

clean:
	@rm -f ${OBJS} ${BONUS}

fclean: clean
	@rm -f ${NAME}

bonus :

re: clean all

