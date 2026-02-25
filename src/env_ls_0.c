/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ls_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:15:58 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/15 15:43:51 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_env *env)
{
	t_env	*temp;

	if (!env)
		return ;
	while (env)
	{
		temp = env->next;
		free(env->name);
		free(env->data);
		free(env);
		env = temp;
	}
	env = NULL;
	return ;
}

int	ft_search_equal(char *save)
{
	int	i;

	i = 0;
	while (save[i])
	{
		if (save[i] == '=' || save[i] == '\0')
			return (i);
		i++;
	}
	return (i);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = ft_lstlast_env(*lst);
		last->next = new;
	}
}
