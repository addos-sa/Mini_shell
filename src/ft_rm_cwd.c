/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_cwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:29:56 by addos-sa          #+#    #+#             */
/*   Updated: 2025/12/15 17:01:50 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_rm_cwd(t_env *env)
{
	char	*cwd;
	char	**paths;
	int		i;

	i = 0;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		paths = divide_paths(search_env_data("PWD", env));
		if (divide_paths_null(paths) == 1)
			return ;
		else
		{
			while (paths[i])
			{
				if (chdir(paths[i]) == 0)
				{
					free_paths(paths);
					return ;
				}
				i++;
			}
		}
	}
	return ;
}
