/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:01:44 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/10 15:45:51 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*temp;

	if (!tokens)
		return ;
	while (*tokens)
	{
		temp = (*tokens)->next;
		free((*tokens)->word);
		if ((*tokens)->outfile)
			free((*tokens)->outfile);
		if ((*tokens)->infile)
			free((*tokens)->infile);
		free ((*tokens));
		(*tokens) = temp;
	}
	tokens = NULL;
	return ;
}

t_token	*ft_lstnew_token(void *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->word = content;
	new->next = NULL;
	return (new);
}

t_token	*ft_lstlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = ft_lstlast_token(*lst);
		last->next = new;
	}
}

t_token	*ft_token_maker(char *line, t_env *env)
{
	int		i;
	char	**tokens;
	t_token	*tkn;
	t_token	*temp;

	i = 0;
	tokens = ft_split_token(line, ' ');
	tkn = NULL;
	while (tokens[i])
	{
		temp = ft_lstnew_token(tokens[i]);
		ft_lstadd_back_token(&tkn, temp);
		i++;
	}
	free(tokens);
	expand_env_vars(tkn, env);
	return (tkn);
}
