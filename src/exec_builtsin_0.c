/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtsin_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:55:46 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/15 17:35:48 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_builtin(t_token *token)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = token;
	if (!token->infile)
	{
		write (1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(token->infile, "-n ", 3) == 0
		|| ft_strncmp(token->infile, "-n", 3) == 0)
		ft_putstr_fd(temp->infile + 3, 1);
	else
	{
		ft_putstr_fd(temp->infile, 1);
		write (1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}

int	pwd_builtin(t_token *token)
{
	char	*temp;

	if (token->infile)
	{
		ft_putstr_fd("pwd: too many arguments\n", 1);
		return (EXIT_FAILURE);
	}
	temp = getcwd(NULL, 0);
	ft_putstr_fd(temp, 1);
	write(1, "\n", 1);
	free(temp);
	return (EXIT_SUCCESS);
}

int	env_builtin(t_env **env, t_token *token)
{
	t_env	*temp;

	(void)token;
	temp = *env;
	while (temp)
	{
		if (temp->data)
		{
			ft_putstr_fd(temp->name, 1);
			write(1, "=", 1);
			if (temp->data)
				ft_putstr_fd(temp->data, 1);
			write(1, "\n", 1);
		}
		if (temp->next)
			temp = temp->next;
		else
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	export_builtin(t_env **env, t_token *token)
{
	t_env	*last;
	char	*temp;

	if (!token->infile)
	{
		env_export(*env);
		return (EXIT_SUCCESS);
	}
	if (already_exist_env_export(*env, token) == 1)
		return (EXIT_SUCCESS);
	else
	{
		temp = token->infile;
		last = ft_lstnew_env(temp);
		ft_lstadd_back_env(env, last);
		return (EXIT_SUCCESS);
	}
}
