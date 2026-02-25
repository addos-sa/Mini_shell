/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ko_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rardila- <rardila-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:27:27 by addos-sa          #+#    #+#             */
/*   Updated: 2025/12/15 11:59:28 by rardila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(t_token *cmm)
{
	if (cmm->in == -1)
		ft_printf("%s: No such file or directory\n",
			cmm->word, cmm->infile);
	else if (cmm->in == -2)
		ft_printf("%s: No such file or directory\n", cmm->word);
}

void	delete_lst_part(t_token **cmm)
{
	t_token	*current;

	current = *cmm;
	(*cmm) = (*cmm)->next;
	current->next = (*cmm)->next;
	print_error(*cmm);
	free_tokens(cmm);
	*cmm = current;
}
