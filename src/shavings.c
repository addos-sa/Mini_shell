/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shavings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:38:15 by addos-sa          #+#    #+#             */
/*   Updated: 2025/12/10 16:51:46 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shavings1_sons(t_token **cmm, char ***envp, t_pipes **pip, t_env **env)
{
	int		i;
	t_token	*temp;

	i = -1;
	temp = *cmm;
	while (++i < (*pip)->cmm_count)
	{
		(*pip)->fk[i] = fork();
		if ((*pip)->fk[i] == -1)
			free_pipex(cmm, pip, envp);
		if ((*pip)->fk[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (i > 0 && temp->in <= 0)
				dup2((*pip)->fd1[i - 1][0], STDIN_FILENO);
			if (i < (*pip)->cmm_count - 1 && temp->out <= 0)
				dup2((*pip)->fd1[i][1], STDOUT_FILENO);
			picking_doors(temp);
			close_all_pipes((*pip)->fd1, (*pip)->cmm_count - 1);
			command(&temp, envp, env);
			exit(1);
		}
		temp = temp->next;
	}
}

char	**shavings1_nodes_envp(t_env *envp)
{
	char	*temp;
	char	**vp;
	int		count_lines;

	count_lines = count_envp(envp);
	vp = (char **)malloc((count_lines + 1) * sizeof(char *));
	if (!vp)
		return (NULL);
	count_lines = 0;
	while (envp != NULL)
	{
		temp = ft_strjoin(envp->name, "=");
		vp[count_lines] = ft_strjoin(temp, envp->data);
		free (temp);
		if (!vp[count_lines])
		{
			free_split(vp);
			return (NULL);
		}
		count_lines++;
		envp = envp->next;
	}
	vp[count_lines] = NULL;
	return (vp);
}

void	shavings_shavings_pars(t_token **token, char **info, int c)
{
	if ((*token)->word)
		error_hand(4, token, info[c]);
	(*token)->word = ft_strdup(info[c]);
}

void	shavings_pars(t_token **token, char **info, int c, int i)
{
	if (i == 1)
	{
		if ((*token)->infile)
			free ((*token)->infile);
		existance(info[c], 1, token, info[c - 1]);
		(*token)->infile = ft_strdup(info[c]);
		if ((*token)->in > -1)
			(*token)->in = ft_strlen(info[c - 1]);
	}
	if (i == 2)
	{
		if ((*token)->infile)
			free ((*token)->infile);
		existance(info[c], 2, token, info[c - 1]);
		(*token)->outfile = ft_strdup(info[c]);
		(*token)->out = ft_strlen(info[c - 1]);
	}
	if (i == 3)
	{
		if ((*token)->word == NULL)
			(*token)->in = -2;
		error_hand(3, token, info[c]);
	}
	if (i == 4)
		shavings_shavings_pars(token, info, c);
}

void	shavings_prepars(t_token **token, char **info, int c)
{
	if (info[c] != NULL && c != 0 && (info[c - 1][0] == '<' ))
		shavings_pars(token, info, c, 1);
	else if (info[c] != NULL && c != 0 && info[c - 1][0] == '>')
		shavings_pars(token, info, c, 2);
	else if (info[c] != NULL && info[c][0] == '-')
		shavings_pars(token, info, c, 3);
	else if (info[c] != NULL && (info[c][0] != '>'
		&& info[c][0] != '<') && (*token)->word)
	{
		(*token)->word = add_char_to_str((*token)->word, ' ');
		(*token)->word = join_and_free((*token)->word, info[c]);
	}
	else if (info[c] != NULL && (info[c][0] != '>' && info[c][0] != '<'))
		shavings_pars(token, info, c, 4);
}
