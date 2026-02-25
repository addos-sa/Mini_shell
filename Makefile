

NAME	:= minishell
CFLAGS	:= -Wextra -Wall -Werror
LDFLAGS := -lreadline
CC		:= cc
LIBFT	:= libft/libft.a
SRCS	:= src/main.c src/token_ls.c src/env_ls_0.c src/env_ls_1.c src/utils_env.c src/ft_split_token.c src/builts_in.c src/built_in_exit.c \
src/dollar_vars.c src/exec_builtsin_0.c src/exec_builtsin_1.c src/exec_builtsin_2.c src/here_doc.c src/parsing_dolar.c src/parsing.c src/parsing1.c \
src/path_finding.c src/pipex_nodes.c src/pipex_nodes2.c src/shavings.c src/ko_lst.c src/ft_delete.c src/ft_quotes.c src/ft_signal.c src/ft_signal_utils.c\
src/ft_rm_cwd.c src/ft_rm_cwd_utils.c src/ft_split_token_utils.c src/dollar_vars_utils.c
OBJDIR	:= obj
OBJS	:= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(HEADERS) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	@$(MAKE) -C libft

clean:
	@rm -rf $(OBJDIR)
	$(MAKE) -C libft clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C libft fclean

norme:
	@cd libft && norminette
	@norminette $(SRCS) minishell.h

re: fclean all

.PHONY: all, clean, fclean, re
