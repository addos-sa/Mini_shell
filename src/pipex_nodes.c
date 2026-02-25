/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:04:36 by addos-sa          #+#    #+#             */
/*   Updated: 2025/12/15 11:10:13 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	counter_commander(t_token **cmm)
{
	int		i;
	t_token	*current;

	i = 0;
	current = *cmm;
	if (!*cmm)
		return (0);
	if (cmm && (*cmm)->next && (*cmm)->in < 0)
	{
		current = (*cmm)->next;
		print_error(*cmm);
		free_tokens(cmm);
		(*cmm) = current;
	}
	while (current != NULL)
	{
		if (current->next && current->next->in < 0)
			delete_lst_part(&current);
		else
		{
			i++;
			current = current->next;
		}
	}
	return (i);
}

int	count_envp(t_env *envp)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = envp;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

static void	update_status_waitpid(t_env **env, int status)
{
	t_token	*temp_one;
	char	*number;

	number = ft_itoa(status);
	temp_one = ft_lstnew_token("export");
	temp_one->infile = ft_strjoin("?=", number);
	export_builtin(env, temp_one);
	free(number);
	free(temp_one->infile);
	free(temp_one);
}

static void	execute_pipe(t_token **cmm, t_env **env, t_pipes *pipes, char **en)
{
	int	i;
	int	status;

	i = -1;
	ft_set_flag(1);
	signal(SIGQUIT, backslash_control);
	shavings1_sons(cmm, &en, &pipes, env);
	close_all_pipes((pipes->fd1), pipes->cmm_count - 1);
	i = -1;
	while (++i < pipes->cmm_count)
		waitpid(pipes->fk[i], &status, 0);
	ft_init_signals();
	if (ft_get_flag() == 3)
		status = 130;
	else if (ft_get_flag() == 4)
		status = 131;
	ft_set_flag(0);
	update_status_waitpid(env, status);
}

void	pipex_nodes(t_token **cmm, t_env *env)
{
	t_pipes	*pipes;
	int		i;
	char	**envp;

	if (!*cmm || !(*cmm)->word)
		return ;
	i = -1;
	pipes = malloc(sizeof(t_pipes));
	pipes->cmm_count = counter_commander(cmm);
	pipes->fd1 = malloc(sizeof(int [2]) * pipes->cmm_count);
	pipes->fk = malloc(sizeof(pid_t) * pipes->cmm_count);
	envp = shavings1_nodes_envp(env);
	while (++i < pipes->cmm_count - 1)
	{
		if (pipe(pipes->fd1[i]) == -1)
			free_pipex(cmm, &pipes, &envp);
	}
	execute_pipe(cmm, &env, pipes, envp);
	free_pipex(cmm, &pipes, &envp);
	free_split(envp);
}
