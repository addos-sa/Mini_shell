/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:39:02 by addos-sa          #+#    #+#             */
/*   Updated: 2025/08/27 12:58:41 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	sons(char **argv, char **envp, int i)
{
	pid_t	fk;
	int		fd1[2];

	if (pipe(fd1) == -1)
		error_hand("pipe", NULL);
	fk = fork();
	if (fk == -1)
		error_hand("fork", NULL);
	if (fk == 0)
	{
		close(fd1[0]);
		dup2(fd1[1], STDOUT_FILENO);
		command(argv[i], envp);
	}
	else
	{
		close(fd1[1]);
		dup2(fd1[0], STDIN_FILENO);
	}
}

void	inside_doc(int fd1[2], char *cutter)
{
	char	*line;

	close(fd1[0]);
	line = get_next_line(0);
	while (line != NULL)
	{
		if (ft_strncmp(line, cutter, ft_strlen(cutter)) == 0)
		{
			free(line);
			exit(1);
		}
		write(fd1[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	if (line)
		free (line);
}

void	here_doc(char *cutter)
{
	pid_t	fk;
	int		fd1[2];

	if (pipe(fd1) == -1)
		error_hand("pipe", NULL);
	fk = fork();
	if (fk == 0)
		inside_doc(fd1, cutter);
	else
	{
		close(fd1[1]);
		dup2(fd1[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	pipex(char **argv, char **envp, int i, int argc)
{
	int	filein;
	int	fileout;

	filein = open(argv[1], O_RDONLY);
	if (filein == -1 && ft_strncmp(argv[1], "here_doc", 8) != 0)
		error_hand("filein", NULL);
	fileout = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fileout == -1)
		error_hand("fileout", NULL);
	if (i != 3)
		dup2(filein, STDIN_FILENO);
	else
		here_doc(argv[2]);
	if (filein != -1)
		close(filein);
	i++;
	while (i <= argc - 2)
	{
		sons(argv, envp, i);
		i++;
	}
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
	command(argv[i - 1], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;

	if (argc < 5)
		return (0);
	i = 2;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		i = 3;
	pipex(argv, envp, i, argc);
	while (wait(NULL) > 0)
		;
	return (0);
}
