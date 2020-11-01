# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/29 16:31:42 by nsena             #+#    #+#              #
#    Updated: 2020/10/31 13:44:47 by vneelix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_NONE = \e[0m
COLOR_WHITE = \e[1;37m
COLOR_BLUE = \e[1;34m
COLOR_GREEN = \e[1;32m
COLOR_PURPLE = \e[1;35m

SRC_DIR = ./src
INC_DIR = .
OBJ_DIR = ./obj

SRCS = $(SRC_DIR)/func.c $(SRC_DIR)/geometry_init.c $(SRC_DIR)/intersection2.c						\
	$(SRC_DIR)/intersection.c $(SRC_DIR)/io_init.c $(SRC_DIR)/main.c $(SRC_DIR)/material_init.c		\
	$(SRC_DIR)/quit.c $(SRC_DIR)/renderer.c $(SRC_DIR)/renderer_func.c								\
	$(SRC_DIR)/vec_op.c

INCS = $(INC_DIR)/wolf3d.h
OBJ = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRCS:.c=.o))

LIBFT_DIR = minilibft
LIBFT_SRC = $(LIBFT_DIR)/src/ft_assert.c				$(LIBFT_DIR)/src/ft_find_str.c	$(LIBFT_DIR)/src/ft_putstr.c	$(LIBFT_DIR)/src/ft_strlen.c	\
			$(LIBFT_DIR)/src/ft_atoi.c					$(LIBFT_DIR)/src/ft_getfile.c	$(LIBFT_DIR)/src/ft_strchr.c	$(LIBFT_DIR)/src/ft_strncmp.c	\
			$(LIBFT_DIR)/src/ft_bzero.c					$(LIBFT_DIR)/src/ft_isdigit.c	$(LIBFT_DIR)/src/ft_strcmp.c	$(LIBFT_DIR)/src/ft_strncpy.c 	\
			$(LIBFT_DIR)/src/ft_directory.c				$(LIBFT_DIR)/src/ft_memalloc.c	$(LIBFT_DIR)/src/ft_strdup.c	$(LIBFT_DIR)/src/hex_to_uint.c	\
			$(LIBFT_DIR)/src/ft_double_ptr_release.c	$(LIBFT_DIR)/src/ft_memcpy.c	$(LIBFT_DIR)/src/ft_strjoin.c
LIBFT_INCS = $(LIBFT_DIR)/minilibft.h
LIBFT_OBJS = $(patsubst $(LIBFT_DIR)/src/%,$(OBJ_DIR)/%,$(LIBFT_SRC:.c=.o))

PARSER_DIR = parser
PARSER_SRC = 	$(PARSER_DIR)/instruments.c		\
				$(PARSER_DIR)/line_checkers.c	\
				$(PARSER_DIR)/line_checkers1.c	\
				$(PARSER_DIR)/parser.c			\
				$(PARSER_DIR)/parser1.c			\
				$(PARSER_DIR)/parser2.c

PARSER_INCS = 	$(PARSER_DIR)/instruments.h		\
				$(PARSER_DIR)/line_checkers.h	\
				$(PARSER_DIR)/parser.h

PARSER_OBJS = $(patsubst $(PARSER_DIR)/%,$(OBJ_DIR)/%,$(PARSER_SRC:.c=.o))

INCL = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(PARSER_DIR)

NAME = wolf3d

CC = clang
LIBS = -lm -lSDL2 -lSDL2_image
CCFL = -Wall -Werror -Wextra -O2

.PHONY: all clean fclean re

all: $(SDL2_DIR) $(NAME)

$(NAME): $(OBJ) $(PARSER_OBJS) $(LIBFT_OBJS)
	@printf "$(COLOR_GREEN)Compiled successfully$(COLOR_NONE)\n"
	@printf "$(COLOR_GREEN)Linking...$(COLOR_NONE)\n"
	@$(CC) $(CCFL) $(OBJ) $(LIBFT_OBJS) $(PARSER_OBJS) $(LIBS) -o $(NAME)
	@printf "$(COLOR_GREEN)Built successfully$(COLOR_NONE)\n"

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c $(INCS)
	@printf "$(COLOR_GREEN)Compiling $(COLOR_PURPLE)$<$(COLOR_GREEN) to $(COLOR_PURPLE)$@$(COLOR_GREEN)...$(COLOR_NONE)\n"
	@$(CC) $(CCFL) $(INCL) $< -c -o $@

$(OBJ_DIR)/%.o:$(PARSER_DIR)/%.c $(PARSER_INCS)
	@printf "$(COLOR_GREEN)Compiling $(COLOR_PURPLE)$<$(COLOR_GREEN) to $(COLOR_PURPLE)$@$(COLOR_GREEN)...$(COLOR_NONE)\n"
	@$(CC) $(CCFL) $(INCL) $< -c -o $@

$(OBJ_DIR)/%.o:$(LIBFT_DIR)/src/%.c $(LIBFT_INCS)
	@printf "$(COLOR_GREEN)Compiling $(COLOR_PURPLE)$<$(COLOR_GREEN) to $(COLOR_PURPLE)$@$(COLOR_GREEN)...$(COLOR_NONE)\n"
	@$(CC) $(CCFL) $(INCL) $< -c -o $@

clean:
	@printf "$(COLOR_GREEN)Cleaning object files...$(COLOR_NONE)\n"
	@/bin/rm -rf $(LIBFT_OBJS) $(PARSER_OBJS) $(OBJ) 
	@printf "$(COLOR_GREEN)Cleaned successfully$(COLOR_NONE)\n"

fclean: clean
	@printf "$(COLOR_GREEN)Cleaning executable...$(COLOR_NONE)\n"
	@/bin/rm -f $(NAME)

re: fclean all
