/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtsin_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:21:01 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/15 16:24:29 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_env_node(t_env *node)
{
	if (node->data)
		free(node->data);
	free(node->name);
	free(node);
}

int	unset_builtin(t_env **env, t_token *token)
{
	t_env	*prev;
	t_env	*temp;

	if (!token->infile)
		return (EXIT_SUCCESS);
	temp = *env;
	prev = NULL;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->name, token->infile,
				ft_strlen(temp->name)) == 0)
		{
			if (prev == NULL)
				*env = temp->next;
			else
				prev->next = temp->next;
			free_env_node(temp);
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
