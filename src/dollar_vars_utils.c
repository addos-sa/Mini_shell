/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:26:02 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/15 16:21:27 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(const char *name, t_env *env)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (ft_strncmp(cur->name, name, ft_strlen(name) + 1) == 0)
		{
			if (cur->data)
				return (cur->data);
			else
				return ("");
		}
		cur = cur->next;
	}
	return ("");
}

char	*expand_dollar_build(const char *str,
	int *ii, char **ptrs, t_env *env)
{
	ptrs[0] = ft_substr(str, ii[0] + 1, ii[1] - (ii[0] + 1));
	ptrs[1] = (char *)get_env_value(ptrs[0], env);
	ptrs[2] = ft_substr(str, 0, ii[0]);
	ptrs[3] = ft_strdup(str + ii[1]);
	ptrs[4] = ft_strjoin(ptrs[2], ptrs[1]);
	free(ptrs[0]);
	free(ptrs[2]);
	ptrs[0] = ft_strjoin(ptrs[4], ptrs[3]);
	free(ptrs[4]);
	free(ptrs[3]);
	return (ptrs[0]);
}

char	*expand_dollar_once(const char *str, t_env *env, int *found)
{
	int		ii[2];
	char	*ptrs[5];

	ii[0] = 0;
	while (str[ii[0]])
	{
		if (str[ii[0]] == '$' && str[ii[0] + 1]
			&& str[ii[0] + 1] != ' ' && str[ii[0] + 1] != '\t')
		{
			ii[1] = ii[0] + 1;
			while (str[ii[1]] && str[ii[1]] != ' ' && str[ii[1]] != '\t')
				ii[1]++;
			*found = 1;
			return (expand_dollar_build(str, ii, ptrs, env));
		}
		ii[0]++;
	}
	*found = 0;
	return (ft_strdup(str));
}

char	*expand_all_dollars(const char *str, t_env *env)
{
	char	*res;
	char	*tmp;
	int		found;

	res = ft_strdup(str);
	found = 1;
	while (found)
	{
		tmp = expand_dollar_once(res, env, &found);
		free(res);
		res = tmp;
	}
	return (res);
}

char	*strip_quotes(char *str)
{
	size_t	len;
	char	*result;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len < 2)
		return (NULL);
	if (str[0] == '\'' && str[len - 1] == '\'')
	{
		result = ft_substr(str, 1, len - 2);
		return (result);
	}
	else if (str[0] == '"' && str[len - 1] == '"')
	{
		result = ft_substr(str, 1, len - 2);
		return (result);
	}
	return (NULL);
}
