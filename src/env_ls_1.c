/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ls_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:43:25 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/15 16:21:33 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew_env(char *env)
{
	t_env	*new;
	int		length;

	length = ft_search_equal(env);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = NULL;
	if (!ft_set_env_name(new, env, length))
		return (NULL);
	if (!ft_set_env_data(new, env, length))
	{
		free(new->name);
		free(new);
		return (NULL);
	}
	return (new);
}

int	ft_set_env_name(t_env *new, char *env, int length)
{
	new->name = malloc(sizeof(char) * (length + 1));
	if (!new->name)
		return (0);
	ft_strlcpy(new->name, env, length + 1);
	return (1);
}

int	ft_set_env_data(t_env *new, char *env, int length)
{
	if (env[length] == '=')
	{
		new->data = malloc(sizeof(char) * (ft_strlen(env) - length));
		if (!new->data)
			return (0);
		ft_strlcpy(new->data, &env[length + 1], ft_strlen(env) - length);
	}
	else
	{
		new->data = NULL;
	}
	return (1);
}

t_env	*ft_env_maker(char **env)
{
	int		i;
	t_env	*env_cp;
	t_env	*temp;

	i = 0;
	env_cp = NULL;
	while (env[i])
	{
		temp = ft_lstnew_env(env[i]);
		ft_lstadd_back_env(&env_cp, temp);
		i++;
	}
	return (env_cp);
}
