/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:48:07 by addos-sa          #+#    #+#             */
/*   Updated: 2025/08/27 13:15:01 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	command(char *cmm, char **envp)
{
	char	**path;
	char	*direc;

	path = ft_split(cmm, ' ');
	if (path[0] != NULL)
		direc = direction(path[0]);
	if (execve(direc, path, envp) == -1)
	{
		free_split(path);
		free(direc);
		error_hand("command", path[0]);
	}
}

void	son(char **argv, int *fd1, char **envp)
{
	int	filein;

	filein = open(argv[1], O_RDONLY, O_APPEND);
	if (filein == -1)
	{
		close(fd1[1]);
		error_hand("filein", NULL);
	}
	close(fd1[0]);
	dup2(fd1[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(filein);
	close(fd1[1]);
	command(argv[2], envp);
}

void	father(char **argv, int	*fd1, char **envp, int cant) //cambios
{
	int	fileout;
	
	close(fd1[1]);
	dup2(fd1[0], STDIN_FILENO);
	if (cant == 4)
	{
		fileout = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fileout == -1)
		{
			close(fd1[0]);
			error_hand("fileout", NULL);
		}
	dup2(fileout, STDOUT_FILENO);
	close(fd1[0]);
	close(fileout);
	}
	command(argv[3], envp);
}

int	one_pipe(int cant, char **argv, char **envp)
{
	int		fd1[2];
	__pid_t	pid1;

	if (cant >= 3 && cant <= 4)
	{
		if (pipe(fd1) == -1)
			error_hand("pipe", NULL);
		pid1 = fork();
		if (pid1 == -1)
			error_hand("fork", NULL);
		if (pid1 == 0)
			son(argv, fd1, envp);
		else
			father(argv, fd1, envp, cant);
	}
	return (0);
}
