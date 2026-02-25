/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:42:14 by addos-sa          #+#    #+#             */
/*   Updated: 2025/12/16 10:43:58 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_found(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	return (envp[i]);
}

char	*find_path(t_token **token, char **envp, t_env **env)
{
	int		i;
	char	**cmm;
	char	**paths;
	char	*exist;
	char	*direc;

	i = -1;
	paths = ft_split(path_found(envp) + 5, ':');
	cmm = ft_split((*token)->word, ' ');
	commands(env, *token, envp);
	while (paths[++i])
	{
		exist = ft_strjoin(paths[i], "/");
		direc = ft_strjoin(exist, cmm[0]);
		free(exist);
		if (access(direc, F_OK | X_OK) == 0)
		{
			free_split(paths);
			free_split(cmm);
			return (direc);
		}
		free(direc);
	}
	free_split(paths);
	return (free_split(cmm));
}
