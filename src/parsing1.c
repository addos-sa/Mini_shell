/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:03:53 by addos-sa          #+#    #+#             */
/*   Updated: 2025/12/16 11:41:43 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_neg(char *neg, char **word)
{
	char	*full;

	full = ft_strjoin(" ", neg);
	neg = full;
	full = ft_strjoin((*word), neg);
	free (neg);
	free (*word);
	return (full);
}

void	existance(char *info, int f, t_token **token, char *is_needed)
{
	int	fd;

	if ((is_needed || ft_strncmp(is_needed, "<<", 3) == 0) || info[0] == '$')
		return ;
	if (f == 1)
	{
		fd = open(info, O_RDONLY, O_APPEND);
		if (fd == -1)
		{
			if ((*token)->in != 2)
				(*token)->in = -1;
			error_hand(1, token, info);
			return ;
		}
		else
			close (fd);
	}
	else if (f == 2)
	{
		fd = open(info, O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			error_hand(2, token, info);
		else
			close (fd);
	}
}

void	error_hand(int p, t_token **token, char *info)
{
	if (p == 1)
		ft_printf("%s: No such file or directory", info);
	else if (p == 2)
		ft_printf("%s: Failed to create the file", info);
	else if (p == 3)
	{
		if (!(*token)->word || ft_strrchr((*token)->word, '-') == NULL)
			(*token)->word = add_neg(info, &(*token)->word);
	}
	else if (p == 4)
		ft_printf("%s: cannot access '%s': No such file or directory",
			(*token)->word, info);
}
