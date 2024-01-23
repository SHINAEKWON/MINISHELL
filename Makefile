# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shikwon <shikwon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 13:49:06 by anouri            #+#    #+#              #
#    Updated: 2023/12/03 19:42:51 by shikwon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME= minishell

INCS_DIR	= ./includes/
MAIN_INC	= -I $(INCS_DIR)

LIB_DIR		= ./libft/
LIB_INC		= -I$(LIB_DIR)includes/
LIB_NAME	= $(LIB_DIR)libft.a

SRCS= env.c \
	main.c \
	path.c \
	format_exec.c \
	in_files.c \
	out_files.c \
	signal.c \
	safe_exit.c \
	parser/varenv.c \
	parser/varenv2-join.c \
	parser/varenv3-trans1.c \
	parser/varenv3-trans2.c \
	parser/varenv4-find_put_envvar_value1.c \
	parser/varenv4-find_put_envvar_value2.c \
	parser/varenv5-put_this_text.c \
	safe_exit1.c \
	parser/parser.c \
	parser/cmd_pos_to_token.c \
	parser/cmd_tokenizer1.c \
	parser/cmd_tokenizer2.c \
	parser/cmd_tokenizer3.c \
	parser/ft_lexer.c \
	parser/ft_lexer2.c \
	parser/free_parsed_cmd.c \
	parser/parser_pre_exec1.c \
	parser/parser_pre_exec2.c \
	parser/malloc_position.c \
	parser/quote_management.c \
	parser/parser_error1.c \
	parser/parser_error2.c \
	builtins/builtins.c \
	builtins/builtin_cd.c \
	builtins/builtin_pwd.c \
	builtins/builtin_env.c \
	builtins/builtin_echo.c \
	builtins/builtin_exit.c \
	builtins/builtin_export.c \
	builtins/simple_export.c \
	builtins/builtin_unset.c \
	child.c \
	minishell.c \
	exec.c \
	exec_builtins.c \
	exit_status.c \
	heredocument.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	redirection.c \
	error.c \
	env_restricted.c \
	env_utils.c \
	ft_exit.c \
	pipes.c \
	
# SRCS_BONUS=


OBJS= ${SRCS:.c=.o}$(INCS)

# OBJS_BONUS= ${SRCS_BONUS:.c=.o}

CC= cc

FLAGS= -g3 -lreadline -Wall -Werror -Wextra #-fsanitize=address #dont use fsanitize flag with valgrind

CFLAGS= -g3 -Wall -Werror -Wextra
RM= rm -f

all: ${NAME}
	
${NAME}: ${OBJS} 
	@make --silent -C $(LIB_DIR)
	${CC} ${FLAGS} ${OBJS} $(LIB_NAME) -L$(LIB_DIR) $(LIB_INC) $(MAIN_INC) -o ${NAME}

# libft:
	# @make --silent -C $(LIB_DIR)

# bonus: ${OBJS_BONUS}
# 	@make --silent -C $(LIB_DIR)
# 	${CC} ${FLAGS} ${OBJS_BONUS} $(LIB_NAME) -L$(LIB_DIR) $(LIB_INC) $(MAIN_INC) -o ${NAME}

clean:
	@$(MAKE) clean --silent -C $(LIB_DIR)
	@$(RM) $(OBJS) #$(OBJS_BONUS)

fclean: clean
	@$(MAKE) fclean --silent -C $(LIB_DIR)
	@$(RM) $(NAME) $(LIB_NAME)


re: fclean all

.PHONY: all clean fclean re
