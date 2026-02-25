/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtsin_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fardi <rardila-@student.42malaga.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:24:12 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/11 17:12:19 by fardi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_pwd_env(t_env **env, char *cwd)
{
	t_token	*temp_one;
	char	*temp;
	char	*temp1;

	temp = ft_strdup("PWD=");
	temp_one = ft_lstnew_token("export");
	temp1 = ft_strjoin(temp, cwd);
	temp_one->infile = temp1;
	export_builtin(env, temp_one);
	free(temp);
	free(temp1);
	free(temp_one);
}

static void	update_oldpwd_env(t_env **env, char *cwd)
{
	t_token	*temp_one;
	char	*temp;
	char	*temp1;

	temp = ft_strdup("OLDPWD=");
	temp_one = ft_lstnew_token("export");
	temp1 = ft_strjoin(temp, cwd);
	temp_one->infile = temp1;
	export_builtin(env, temp_one);
	free(temp);
	free(temp1);
	free(temp_one);
}

static int	change_directory(t_token *token)
{
	char	**arg;

	if (!token->infile)
		return (chdir(getenv("HOME")));
	arg = ft_split(token->infile, ' ');
	if (arg[1] != NULL)
	{
		ft_putstr_fd("Too many arguments\n", 1);
		free_split(arg);
		return (-1);
	}
	if (chdir(arg[0]) == -1)
	{
		ft_putstr_fd("No such file or directory\n", 1);
		free_split(arg);
		return (-1);
	}
	free_split(arg);
	return (1);
}

int	cd_builtin(t_env **env, t_token *token)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (EXIT_FAILURE);
	if (change_directory(token) == -1)
	{
		ft_putstr_fd("Error cd\n", 1);
		if (cwd)
			free(cwd);
		return (EXIT_FAILURE);
	}
	update_oldpwd_env(env, cwd);
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (EXIT_FAILURE);
	update_pwd_env(env, cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
