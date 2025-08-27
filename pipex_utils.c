/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:35:10 by addos-sa          #+#    #+#             */
/*   Updated: 2025/08/27 10:32:13 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	error_hand(char *what, char *cmm)
{
	if (what[0] != 'f' && what[0] != 'c')
		ft_printf("Failed to create-> %s\n", what);
	else if (what[0] != 'c')
		ft_printf("Failed at opening %s\n", what);
	else
		ft_printf("zsh: %s not found: %s\n", what, cmm);
	exit(1);
}

char	*direction(char *cmm) //cambiar esto entero
{
	char	*full_direc;
	char	*text;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (cmm[j] != '\0')
		j++;
	full_direc = malloc((9 + j + 1) * sizeof(char));
	if (!full_direc)
		return (NULL);
	text = "/usr/bin/";
	j = 0;
	while (text[++i] != '\0')
		full_direc[i] = text[i];
	while (cmm[j] != '\0')
	{
		full_direc[i + j] = cmm[j];
		j++;
	}
	full_direc[i + j] = '\0';
	return (full_direc);
}
