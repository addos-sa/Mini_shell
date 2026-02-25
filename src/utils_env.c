/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:08:01 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/15 17:15:53 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_env_data(char *var, t_env *env_cp)
{
	t_env	*temp;

	temp = env_cp;
	while (temp)
	{
		if (ft_strncmp(var, temp->name, ft_strlen(var) + 1) == 0)
			return (temp->data);
		temp = temp->next;
	}
	return (NULL);
}

int	already_exist_env_export(t_env *env, t_token *token)
{
	t_env	*env_t;
	int		lenght;
	char	*temp;

	env_t = env;
	temp = token->infile;
	lenght = ft_search_equal(temp);
	while (env_t)
	{
		if (ft_strncmp(temp, env_t->name, lenght) == 0)
		{
			free(env_t->data);
			env_t->data = ft_strdup(&temp[lenght + 1]);
			return (1);
		}
		env_t = env_t->next;
	}
	return (0);
}

void	env_export(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(temp->name, 1);
		write(1, "=", 1);
		if (temp->data)
		{
			write(1, "\"", 1);
			ft_putstr_fd(temp->data, 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		if (temp->next)
			temp = temp->next;
		else
			return ;
	}
}
