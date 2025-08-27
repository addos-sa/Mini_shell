/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:27:40 by addos-sa          #+#    #+#             */
/*   Updated: 2025/08/27 10:28:55 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "./src/libft/libft.h"
# include "./src/ft_printf/ft_printf.h"

void	error_hand(char *what, char *cmm);
char	*direction(char *cmm);
void	command(char *cmm, char **envp);
void	son(char **argv, int *fd1, char **envp);
void	father(char **argv, int	*fd1, char **envp);

#endif
