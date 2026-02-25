/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:50:34 by addos-sa          #+#    #+#             */
/*   Updated: 2025/12/16 12:31:07 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	g_signal_flag = 0;

void	ft_set_flag(int i)
{
	g_signal_flag = i;
}

int	ft_get_flag(void)
{
	return (g_signal_flag);
}

void	ft_handler_int(int signal)
{
	(void) signal;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_signal_flag == 0)
	{
		rl_redisplay();
	}
	else
		ft_set_flag(3);
}

void	backslash_control(int signal)
{
	(void) signal;
	if (g_signal_flag == 1)
		ft_putendl_fd("Quit (Core dumped)", 2);
	ft_set_flag(4);
}
