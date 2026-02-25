/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:13:12 by addos-sa          #+#    #+#             */
/*   Updated: 2025/12/16 11:59:37 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shaving_infiles(char **split, t_token **cmm)
{
	int		i;
	t_token	*temp;

	i = 1;
	while (split[i] != NULL)
	{
		temp = init_tk();
		if (!temp)
		{
			free_split(split);
			return ;
		}
		temp->word = ft_strdup(split[0]);
		temp->in = 1;
		temp->infile = ft_strdup(split[i]);
		ft_lstadd_back_token(cmm, temp);
		i++;
	}
}

void	shaving_infiles_neg(char **split, t_token **cmm)
{
	int		i;
	t_token	*temp;
	char	*aux;

	i = 2;
	while (split[i] != NULL)
	{
		temp = init_tk();
		if (!temp)
		{
			free_split(split);
			return ;
		}
		aux = ft_strjoin(split[0], " ");
		temp->word = ft_strjoin(aux, split[1]);
		free(aux);
		temp->in = 1;
		temp->infile = ft_strdup(split[i]);
		ft_lstadd_back_token(cmm, temp);
		i++;
	}
}

void	infiles_extras(t_token **cmm)
{
	char	**split;

	split = ft_split_token((*cmm)->word, ' ');
	if (!split[1] || (ft_strnstr(split[1], "-", 1) != 0 && !split[2]))
	{
		free_split(split);
		return ;
	}
	if (!split || (split[1] && ft_strnstr(split[1], "-", 1) != 0 && !split[2]))
	{
		free_split(split);
		return ;
	}
	free_tokens(cmm);
	if (split[1] && ft_strnstr(split[1], "-", 1) != 0)
		shaving_infiles_neg(split, cmm);
	else
		shaving_infiles(split, cmm);
	free_split(split);
}

void	is_there_a_dolar(t_token **token, t_env *envp)
{
	t_token	*current;

	if (!token || !*token)
		return ;
	current = *token;
	while (current)
	{
		current->word = expand_dolar(current->word, envp);
		current->infile = expand_dolar(current->infile, envp);
		current->outfile = expand_dolar(current->outfile, envp);
		current = current->next;
	}
}

t_token	*init_tk(void)
{
	t_token	*token;

	token = malloc (sizeof(t_token) * 1);
	if (!token)
		return (NULL);
	token->infile = NULL;
	token->outfile = NULL;
	token->in = 0;
	token->out = 0;
	token->word = NULL;
	token->next = NULL;
	return (token);
}
