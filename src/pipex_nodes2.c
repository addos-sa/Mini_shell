/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_nodes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:39:28 by addos-sa          #+#    #+#             */
/*   Updated: 2025/12/16 10:44:54 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

int	here_doc(t_token *cmm)
{
	int		here_doc[2];
	pid_t	pid;

	pipe(here_doc);
	pid = fork();
	if (pid == 0)
	{
		close(here_doc[0]);
		inside_doc(cmm->infile, here_doc);
		exit(0);
	}
	close(here_doc[1]);
	waitpid(pid, NULL, 0);
	return (here_doc[0]);
}

int	which_open(t_token	*cmm, int which)
{
	int	fd;

	if (which == 1)
	{
		if (cmm->in == 2)
			return (here_doc(cmm));
		else
			fd = open(cmm->infile, O_RDONLY);
	}
	else
	{
		if (cmm->out == 2)
			fd = open(cmm->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmm->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	if (fd == -1)
	{
		if (which == 1)
			ft_printf("%s: No such file or directory\n", cmm->infile);
		exit(1);
	}
	return (fd);
}

void	command(t_token **cmm, char ***envp, t_env **env)
{
	char	**split;
	char	*path;

	path = NULL;
	split = ft_split((*cmm)->word, ' ');
	if (!ft_strnstr((*cmm)->word, "./", 3))
		path = find_path(cmm, *envp, env);
	else if (split)
		path = ft_strdup(split[0]);
	if (!ft_strnstr((*cmm)->word, "./", 3))
		is_the_direction(cmm, *envp);
	if (!path)
	{
		ft_printf("%s: command not found\n", split[0]);
		free_split(split);
		exit(127);
	}
	if (execve(path, split, *envp) == -1)
	{
		perror("execve");
		free_split(split);
		free(path);
		exit(1);
	}
}

void	picking_doors(t_token *cmm)
{
	int	infile;
	int	outfile;

	if (cmm->in == -1 || cmm->out == -1)
		exit(1);
	if (cmm->in >= 1)
	{
		infile = which_open(cmm, 1);
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (cmm->out >= 1)
	{
		outfile = which_open(cmm, 0);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
}
