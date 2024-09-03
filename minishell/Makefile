# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpajuelo <jpajuelo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 13:58:48 by jpajuelo          #+#    #+#              #
#    Updated: 2024/09/03 14:46:03 by jpajuelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SHELL=/bin/bash
CDEBUG = #-fsanitize=address
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror -MD -g3
RM = rm -f
CC = gcc
PRINTF = printf
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
UTILS_DIR = minishell_utils
LIBFT = libft/libft.a
BIN = minishell
NAME = $(BIN_DIR)/$(BIN)
LIBFT_DIR = libft
#verificacion del directorio exista y luego procedemos a tomar los .c
LIBFT_SRC = $(shell [ -d libft ] && ls libft/*.c)

SRC = builtins.c custom_cmd.c  env.c error.c exec.c expand.c fill_node.c ft_cmd_subsplit.c\
		ft_cmd_trim.c ft_str_trim_all.c get_cmd.c get_next_line_utils.c get_next_line.c \
		get_params.c heredoc.c minishell.c parseo.c prompt.c signal.c  ft_between_chars.c ft_chartostr.c ft_countchar.c ft_dup_matrix.c\
		ft_extend_matrix.c ft_free_matrix.c ft_isspce.c ft_lsttomatrix.c ft_putendl_fd_2.c ft_putstr_fd_2.c ft_putchar_fd_2.c\
		ft_matrix_replace_in.c ft_matrixlen.c ft_matrixtolst.c ft_nbrlen.c \
		ft_putmatrix_fd.c ft_putnbr_base_fd.c ft_putnchar_fd.c ft_putstrn_ds.c ft_recursive_power.c\
		ft_sqrt.c ft_strchars_i.c ft_strchr_i.c ft_strenlarge.c ft_strrncmp.c ft_subsplit.c ft_uitoa.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
SRC_COUNT_TOT := $(shell expr $(shell echo -n $(SRC) | wc -w) - $(shell ls -l $(OBJ_DIR) 2>&1 | grep ".o" | wc -l) + 1)
ifeq ($(shell test $(SRC_COUNT_TOT) -le 0; echo $$?),0)
	SRC_COUNT_TOT:= $(shell echo -n $(SRC) | wc -w)
endif
SRC_COUNT := 0
SRC_PCT = $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) | $(BIN_DIR)
	@$(CC) -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include $(CFLAGS) $(CDEBUG) $(OBJ) $(LIBFT) -lreadline -o $@
	@$(PRINTF) "\r%100s\r$(GREEN)$(BIN) is finish o.o!$(DEFAULT)\n"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $(BLUE)$<$(DEFAULT)..." "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)
	@$(CC) -c $< -o $@

$(LIBFT): $(LIBFT_SRC) | $(LIBFT_DIR) $(BIN_DIR)
	@make all -C libft
	@$(AR) $(NAME) $(LIBFT)

clean: | $(LIBFT_DIR)
	@$(PRINTF) "$(CYAN)Cleaning up object files in $(NAME)...$(DEFAULT)\n"
	@make clean -C libft
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) -r $(BIN_DIR)
	$(RM) $(LIBFT)
	@$(PRINTF) "$(CYAN)Removed $(LIBFT)$(DEFAULT)\n"
	@$(PRINTF) "$(CYAN)Removed $(NAME)$(DEFAULT)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

re:	fclean
	@make all

-include $(OBJ_DIR)/*.d