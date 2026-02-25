/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:12:19 by addos-sa          #+#    #+#             */
/*   Updated: 2025/12/16 12:19:06 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	double_quote_rm(char ch, int *flag, int *type)
{
	if (ch == '"' && *flag == 0 && *type == 0)
	{
		*flag = 1;
		*type = 1;
		return (1);
	}
	if (ch == '"' && *flag == 1 && *type == 1)
	{
		*flag = 0;
		*type = 0;
		return (1);
	}
	return (0);
}

static int	single_quote_rm(char ch, int *flag, int *type)
{
	if (ch == '\'' && *flag == 0 && *type == 0)
	{
		*flag = 1;
		*type = 2;
		return (1);
	}
	if (ch == '\'' && *flag == 1 && *type == 2)
	{
		*flag = 0;
		*type = 0;
		return (1);
	}
	return (0);
}

char	*remove_quotes_dquote(char *word)
{
	int		j;
	int		i;
	int		flag;
	int		type;
	char	*cpy;

	j = 0;
	i = 0;
	flag = 0;
	type = 0;
	if (!word)
		return (word);
	cpy = malloc(sizeof(char) * (ft_strlen(word) + 1));
	while (word[i])
	{
		if (double_quote_rm(word[i], &flag, &type)
			|| single_quote_rm(word[i], &flag, &type))
			i++;
		else
			cpy[j++] = word[i++];
	}
	cpy[j] = '\0';
	free(word);
	return (cpy);
}

int	those_ones(t_token *token, int c)
{
	if (!token->word)
		return (1);
	if (ft_strncmp(token->word, "mkdir", 6)
		|| ft_strncmp(token->word, "rmdir", 6)
		|| ft_strncmp(token->word, "touch", 6)
		|| ft_strncmp(token->word, "chmod", 6)
		|| ft_strncmp(token->word, "chown", 6)
		|| ft_strncmp(token->word, "locate", 7)
		|| ft_strncmp(token->word, "mv", 3)
		|| ft_strncmp(token->word, "cp", 3)
		|| ft_strncmp(token->word, "find", 5)
		|| ft_strncmp(token->word, "ls", 3)
		|| ft_strncmp(token->word, "head", 5)
		|| ft_strncmp(token->word, "tail", 5))
		return (1);
	if (ft_strncmp(token->word, "grep", 5) || ft_strncmp(token->word, "rm", 3))
		return (1);
	if (ft_strncmp(token->word, " ", c) && !ft_strncmp(token->word, "./", 2))
		return (0);
	if (ft_strncmp(token->word, "./", 2))
		return (1);
	return (0);
}
