/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:32:03 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/15 15:36:44 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_env_var(char *str, t_env *env)
{
	char	*unquoted;
	char	*result;

	if (!str)
		return (NULL);
	unquoted = strip_quotes(str);
	if (unquoted)
	{
		free(str);
		if (str[0] == '\'')
			return (unquoted);
		result = expand_all_dollars(unquoted, env);
		free(unquoted);
		return (result);
	}
	result = expand_all_dollars(str, env);
	if (str != result)
		free(str);
	return (result);
}

void	expand_env_vars(t_token *tokens, t_env *env)
{
	t_token	*temp;
	char	*expanded;

	temp = tokens;
	while (temp)
	{
		if (temp->word)
		{
			expanded = expand_env_var(temp->word, env);
			if (expanded)
				temp->word = expanded;
		}
		temp = temp->next;
	}
}
