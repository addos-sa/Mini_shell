/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:13:53 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/15 17:20:30 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_exit(t_token **token, t_env **env)
{
	if (!*token)
		return (0);
	if (!(*token)->word)
		return (0);
	if (ft_strncmp((*token)->word, "exit", 5) == 0)
	{
		free_tokens(token);
		free_env(*env);
		ft_putstr_fd("exit\n", 1);
		return (1);
	}
	else
		return (0);
}

int	is_built_alone(t_token **token)
{
	int		i;
	char	*code;
	t_token	*current;

	i = 0;
	if (!*token)
		return (0);
	current = *token;
	code = (*token)->word;
	if (!*token || !(*token)->word || is_a_builtin(current) == 0
		|| ft_strncmp((*token)->word, "echo", 5) == 0
		|| ft_strncmp((*token)->word, "env", 4) == 0)
		return (0);
	while (current != NULL)
	{
		if (ft_strncmp(current->word, code, ft_strlen(code) + 1) != 0)
			return (0);
		current = current->next;
	}
	return (1);
}

int	is_there_a_pipe(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i] != '\0')
	{
		if (line[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

char	**unite_split(char *first, t_token **cmm)
{
	int		i;
	char	**split;

	i = 1;
	split = ft_split((*cmm)->word, ' ');
	while (split[i] != NULL)
		i++;
	if (i == 1)
	{
		free_split(split);
		return (ft_split(first, ' '));
	}
	i = 1;
	while (split[i] != NULL)
	{
		first = add_char_to_str(first, ' ');
		first = join_and_free(first, split[i]);
		i++;
	}
	free_split(split);
	split = ft_split(first, ' ');
	return (split);
}

void	is_the_direction(t_token **cmm, char **envp)
{
	char	**split;

	if (ft_strchr((*cmm)->word, '/'))
	{
		split = ft_split((*cmm)->word, ' ');
		execve(split[0], split, envp);
		free_split(split);
	}
}
