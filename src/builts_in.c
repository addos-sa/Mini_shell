/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:09:22 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/11 19:13:33 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_in(t_env **env, t_token *token)
{
	if (ft_strncmp(token->word, "echo", 5) == 0)
		echo_builtin(token);
	if (ft_strncmp(token->word, "cd", 3) == 0)
		cd_builtin(env, token);
	if (ft_strncmp(token->word, "pwd", 4) == 0)
		pwd_builtin(token);
	if (ft_strncmp(token->word, "export", 7) == 0)
		export_builtin(env, token);
	if (ft_strncmp(token->word, "unset", 6) == 0)
		unset_builtin(env, token);
	if (ft_strncmp(token->word, "env", 4) == 0)
		env_builtin(env, token);
	return ;
}

int	is_a_builtin(t_token *token)
{
	if (!token)
		return (0);
	if (ft_strncmp(token->word, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(token->word, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(token->word, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(token->word, "export", 7) == 0)
		return (1);
	if (ft_strncmp(token->word, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(token->word, "env", 4) == 0)
		return (1);
	return (0);
}

int	commands(t_env **env, t_token *token, char **envp)
{
	if (!token)
		return (0);
	if (is_exit(&token, env) == 1)
	{
		free_split(envp);
		return (1);
	}
	if (is_a_builtin(token) == 1)
	{
		if (envp)
			free_split(envp);
		built_in(env, token);
		if (envp != NULL)
			exit (0);
		return (1);
	}
	return (0);
}
