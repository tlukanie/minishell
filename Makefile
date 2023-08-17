# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/04 15:40:17 by okraus            #+#    #+#              #
#    Updated: 2023/08/17 15:00:07 by okraus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef ECHO
HIT_TOTAL	!=	${MAKE} ${MAKECMDGOALS} --dry-run ECHO="HIT_MARK" | grep -c "HIT_MARK"
HIT_COUNT1	=	$(eval HIT_N != expr ${HIT_N} + 1)${HIT_N}
HIT_COUNT2	=	$(eval HIT_M != expr ${HIT_M} + 1)${HIT_M}
HIT_COUNT3	=	$(eval HIT_O != expr ${HIT_O} + $(BAR_LENGTH))${HIT_O}
PERC		=	$(shell expr $(HIT_COUNT3) / $(HIT_TOTAL) | bc)
ECHO		=	echo "[`expr ${HIT_COUNT1} '*' 100 / ${HIT_TOTAL}`%]"
endif

NAME		=	minishell
LIBFT_F		=	libft/
LIBFT		=	libft.a
INCS		=	includes/minishell.h
CC 			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
OBJ_DIR		=	objects/
SLEEP		=	#sleep 0.5

# SOURCES

SRC			=	$(addprefix $(SRC_MS_DIR), $(addsuffix .c, $(SRC_MS))) \
				$(addprefix $(SRC_BI_DIR), $(addsuffix .c, $(SRC_BI))) \
				$(addprefix $(SRC_UT_DIR), $(addsuffix .c, $(SRC_UT)))

# Source directories

SRC_BI_DIR		=	srcs/builtins/
SRC_MS_DIR		=	srcs/minishell/
SRC_UT_DIR		=	srcs/utils/

# Minishell builtin functions

SRC_BI			=	ft_cd \
					ft_echo \
					ft_env \
					ft_exit \
					ft_export \
					ft_pwd \
					ft_unset
					
# Minishell main functions

SRC_MS			=	ft_bonus_exe \
					ft_bonus_exe2 \
					ft_executor \
					ft_executor2 \
					ft_executor3 \
					ft_executor4 \
					ft_executor5 \
					ft_executor6 \
					ft_expansion \
					ft_lexer \
					ft_lexer2 \
					ft_lexer3 \
					ft_minishell \
					ft_parser \
					ft_parser2 \
					ft_parser3 \
					ft_parsetext \
					ft_parsetext2 \
					ft_signal \
					ft_tokenchecker \
					ft_tokenchecker2 \
					ft_wildcard \
					ft_wildcard2 \
					ft_wildcard3

# Minishell utility functions

SRC_UT			=	ft_envvar \
					ft_free \
					ft_free2 \
					ft_init \
					ft_wait

# Formating

NRM_FORMAT	=	\033[0m

GREEN		=	\033[1;32m
YELLOW		=	\033[1;93m
RED			=	\033[1;31m
REVERSE		=	\033[7m
RETURN		=	\033[1F\r\033[2K

# Printing

BAR_LENGTH	:=	50
PRINT1		=	printf "[$(HIT_COUNT2)/$(HIT_TOTAL)]" ;
PRINT2		=	for num in `seq 1 $(BAR_LENGTH)` ; do \
					if [ $$num -le $(PERC) ] ; then \
						printf "$(REVERSE) $(NRM_FORMAT)" ; \
					else \
						printf " " ; \
        			fi \
    			done

# Objects

OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_BI))) \
				$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_MS))) \
				$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_UT)))

# Dependencies

DEP			=	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_BI))) \
				$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_MS))) \
				$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_UT)))

# RULES

all:			announce $(LIBFT) $(NAME)
				@$(PRINT2)
				@$(PRINT1)
				@$(ECHO)
				@echo "$(GREEN)Amazing <<$(REVERSE)Minishell$(NRM_FORMAT)$(GREEN)>> compiled!$(NRM_FORMAT)"
				

bonus:			all

# MESSAGES 

announce: 
				@echo "$(RED)Magic in progress...\n$(NRM_FORMAT)"

# COMPILATION

$(OBJ_DIR)%.o:	$(SRC_BI_DIR)%.c
				@mkdir -p $(OBJ_DIR)
				@$(SLEEP)
				@echo "$(RETURN)$(RETURN)$(YELLOW)Compiling Minishell: $< $(NRM_FORMAT)"
				@$(PRINT2)
				@$(PRINT1)
				@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
				@$(ECHO)

$(OBJ_DIR)%.o:	$(SRC_MS_DIR)%.c
				@mkdir -p $(OBJ_DIR)
				@$(SLEEP)
				@echo "$(RETURN)$(RETURN)$(YELLOW)Compiling Minishell: $< $(NRM_FORMAT)"
				@$(PRINT2)
				@$(PRINT1)
				@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
				@$(ECHO)

$(OBJ_DIR)%.o:	$(SRC_UT_DIR)%.c
				@mkdir -p $(OBJ_DIR)
				@$(SLEEP)
				@echo "$(RETURN)$(RETURN)$(YELLOW)Compiling Minishell: $< $(NRM_FORMAT)"
				@$(PRINT2)
				@$(PRINT1)
				@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
				@$(ECHO)

$(NAME): 		$(OBJ)
				@echo "$(RETURN)$(RETURN)$(GREEN)Libft compilation complete!$(NRM_FORMAT)"
				@$(CC) $(CFLAGS) $(SRC) libft.a -o $(NAME) -lreadline
				@$(PRINT2)
				@$(PRINT1)
				@$(ECHO)
				@echo "$(RETURN)$(RETURN)$(GREEN)Minishell compiled!$(NRM_FORMAT)"

# add dependencies for headers and stuff somehow

-include $(DEP)

$(LIBFT):
				@echo "$(RETURN)$(RETURN)$(YELLOW)Compiling LIBFT: $< $(NRM_FORMAT)"
				@make -s -C $(LIBFT_F)
				@cp libft/libft.a .
				@echo "$(YELLOW)Compiling Minishell: $< $(NRM_FORMAT)"
				@$(PRINT2)
				@$(PRINT1)
				@$(ECHO)

# clean library

clean:
				@rm -rf $(OBJ_DIR)
				@rm -f $(LIBFT)
				@make fclean -s -C $(LIBFT_F)
				@echo "$(RED)Library and objects removed!$(NRM_FORMAT)"
				@$(PRINT2)
				@$(PRINT1)
				@$(ECHO)

# Remove the program after running clean

fclean:			clean
				@rm $(NAME)
				@echo "$(RETURN)$(RED)Minishell deleted!$(NRM_FORMAT)"
				@$(PRINT2)
				@$(PRINT1)
				@$(ECHO)

# Remove stuff and make it all again

re: 			fclean all
				@$(PRINT2)
				@$(PRINT1)
				@$(ECHO)

# Phony stuff for rules

.PHONY: all announce clean fclean re bonus
