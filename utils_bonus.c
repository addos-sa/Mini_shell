/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:48:09 by addos-sa          #+#    #+#             */
/*   Updated: 2025/08/27 12:48:04 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*direction(char *cmm)
{
	char	*full_direc;
	char	*text;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (cmm[j] != '\0')
		j++;
	full_direc = malloc((9 + j + 1) * sizeof(char));
	if (!full_direc)
		return (NULL);
	text = "/usr/bin/";
	j = 0;
	while (text[++i] != '\0')
		full_direc[i] = text[i];
	while (cmm[j] != '\0')
	{
		full_direc[i + j] = cmm[j];
		j++;
	}
	full_direc[i + j] = '\0';
	return (full_direc);
}

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
