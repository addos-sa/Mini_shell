/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_cwd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:48:18 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/15 17:02:28 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	how_many_slash(char *pwd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pwd[i])
	{
		if (pwd[i] == '/')
			j++;
		i++;
	}
	return (j);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	fill_paths(char **paths, t_paths *data)
{
	while (data->i != 0)
	{
		if (data->pwd[data->i] == '/' && data->j < data->slash)
		{
			paths[data->j] = malloc(data->i + 1);
			if (!paths[data->j])
			{
				free_paths(paths);
				return ;
			}
			ft_strlcpy(paths[data->j], data->pwd, data->i + 1);
			data->j++;
		}
		data->i--;
	}
	paths[data->j] = NULL;
}

char	**divide_paths(char *pwd)
{
	char	**paths;
	t_paths	data;

	if (!pwd)
		return (NULL);
	data.slash = how_many_slash(pwd);
	if (data.slash == 0)
		return (NULL);
	paths = malloc(sizeof(char *) * (data.slash + 1));
	if (!paths)
		return (NULL);
	data.pwd = pwd;
	data.i = ft_strlen(pwd);
	data.j = 0;
	fill_paths(paths, &data);
	return (paths);
}

int	divide_paths_null(char **paths)
{
	if (paths == NULL)
	{
		if (chdir("/home") == -1)
		{
			ft_printf("ERROR HOME DELETED");
			exit(EXIT_FAILURE);
		}
		return (1);
	}
	return (0);
}
