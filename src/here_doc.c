/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:12:39 by addos-sa          #+#    #+#             */
/*   Updated: 2025/12/16 11:40:53 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	inside_doc(char *cutter, int fd1[2])
{
	char	*line;
	size_t	size_len;

	close(fd1[0]);
	line = get_next_line(0);
	size_len = ft_strlen(cutter);
	while (line != NULL)
	{
		if (ft_strncmp(line, cutter, size_len) == 0
			&& (line[size_len] == '\n' || line[size_len] == '\0'))
		{
			if (line)
				free(line);
			close (fd1[1]);
			return ;
		}
		write(fd1[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	if (line)
		free (line);
	close(fd1[1]);
}

t_token	*construction(char **info, t_env *envp, int *i)
{
	int		c;
	t_token	*token;

	(void)envp;
	c = (*i);
	token = init_tk();
	while (info[*i] != NULL && !(info[*i][0] == '|' && info[*i][1] == '\0'))
		(*i)++;
	while (c < *i)
	{
		shavings_prepars(&token, info, c);
		c++;
	}
	c = ft_strlen(token->word);
	if (is_a_builtin_space(token) == 1)
		make_built_in(&token);
	else if (those_ones(token, c) == 0)
		infiles_extras(&token);
	token->word = remove_quotes_dquote(token->word);
	return (token);
}

t_token	*pars(char **info, t_env *envp)
{
	t_token	*lst;
	t_token	*temp;
	int		i;

	i = 0;
	lst = construction(info, envp, &i);
	if (info[i] != NULL)
		i++;
	while (lst && info[i] != NULL)
	{
		temp = construction(info, envp, &i);
		if (info[i] != NULL)
			i++;
		if (!temp || temp->word == NULL)
		{
			free_tokens(&temp);
			free_tokens(&lst);
			free_split(info);
			return (NULL);
		}
		ft_lstadd_back_token(&lst, temp);
	}
	is_there_a_dolar(&lst, envp);
	free_split(info);
	return (lst);
}

void	free_pipex(t_token **cmm, t_pipes **pipes, char ***envp)
{
	(void)envp;
	free ((*pipes)->fk);
	free ((*pipes)->fd1);
	free (*pipes);
	free_tokens(cmm);
}

void	close_all_pipes(int (*fd1)[2], int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(fd1[i][0]);
		close(fd1[i][1]);
		i++;
	}
}
