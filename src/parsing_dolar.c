/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dolar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:42:56 by addos-sa          #+#    #+#             */
/*   Updated: 2025/12/16 12:26:22 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

char	*add_char_to_str(char *str, char c)
{
	char	tmp[2];
	char	*result;

	tmp[0] = c;
	tmp[1] = '\0';
	result = ft_strjoin(str, tmp);
	free(str);
	return (result);
}

int	process_variable(char *str, int *i, t_env *envp, char **result)
{
	char	*var_name;
	char	*current;
	int		start;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		current = search_env_data("?", envp);
		if (current)
			*result = join_and_free(*result, current);
		return (*i);
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	current = search_env_data(var_name, envp);
	if (current)
		*result = join_and_free(*result, current);
	free(var_name);
	return (*i);
}

int	flagger(char c, int flag)
{
	if ((flag == 2 && c == '\'') || (flag == 1 && c == '"'))
		flag = 0;
	else if (flag == 0 && c == '"')
		flag = 1;
	else if (flag == 0 && c == '\'')
		flag = 2;
	return (flag);
}

char	*expand_dolar(char *str, t_env *envp)
{
	char	*result;
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	if (!str)
		return (str);
	result = ft_strdup("");
	while (str[i])
	{
		flag = flagger(str[i], flag);
		if (str[i] == '$' && str[i + 1] && flag != 2)
			i = process_variable(str, &i, envp, &result);
		else
			result = add_char_to_str(result, str[i++]);
	}
	free(str);
	result = remove_quotes_dquote(result);
	return (result);
}
