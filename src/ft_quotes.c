/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:05:14 by addos-sa          #+#    #+#             */
/*   Updated: 2025/12/03 12:41:15 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_double_quote(char ch, int *flag, int *type)
{
	if (ch == '"' && *flag == 0 && *type == 0)
	{
		*flag = 1;
		*type = 1;
	}
	else if (ch == '"' && *flag == 1 && *type == 1)
	{
		*flag = 0;
		*type = 0;
	}
}

static void	handle_single_quote(char ch, int *flag, int *type)
{
	if (ch == '\'' && *flag == 0 && *type == 0)
	{
		*flag = 1;
		*type = 2;
	}
	else if (ch == '\'' && *flag == 1 && *type == 2)
	{
		*flag = 0;
		*type = 0;
	}
}

int	no_dquote(char *line)
{
	int	i;
	int	flag;
	int	type;

	i = 0;
	flag = 0;
	type = 0;
	while (line[i])
	{
		handle_double_quote(line[i], &flag, &type);
		handle_single_quote(line[i], &flag, &type);
		i++;
	}
	if (flag == 1)
		return (1);
	else
		return (0);
}

void	make_built_in(t_token **token)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split((*token)->word, ' ');
	if (!split)
		return ;
	while (split[0][i] != '\0')
		i++;
	(*token)->infile = ft_strdup((*token)->word + (i + 1));
	free((*token)->word);
	(*token)->word = ft_strdup(split[0]);
	free_split(split);
}

int	is_a_builtin_space(t_token *token)
{
	int	i;

	i = 0;
	if (!token->word)
		return (0);
	while (token->word[i] != '\0' && token->word[i] != ' ')
		i++;
	if (token->word[i] == ' ' && token->word[i + 1] == '\0')
		return (0);
	if (ft_strncmp(token->word, "echo ", 5) == 0)
		return (1);
	if (ft_strncmp(token->word, "cd ", 3) == 0)
		return (1);
	if (ft_strncmp(token->word, "pwd ", 4) == 0)
		return (1);
	if (ft_strncmp(token->word, "export ", 7) == 0)
		return (1);
	if (ft_strncmp(token->word, "unset ", 6) == 0)
		return (1);
	if (ft_strncmp(token->word, "env ", 4) == 0)
		return (1);
	return (0);
}
