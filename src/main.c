/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addos-sa <addos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:39:45 by rardila-          #+#    #+#             */
/*   Updated: 2025/12/16 12:29:49 by addos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*build_prompt_base(char *usr, char *cwd)
{
	char	*temp;
	char	*prompt;

	temp = ft_strjoin(PINK, usr);
	if (!temp)
		return (NULL);
	prompt = ft_strjoin(temp, "-> ");
	free(temp);
	if (!prompt)
		return (NULL);
	temp = ft_strjoin(prompt, cwd);
	free(prompt);
	return (temp);
}

char	*generate_prompt(t_env *env_cp, int argc, char **argv)
{
	char	*usr;
	char	*cwd;
	char	*temp;
	char	*prompt;

	(void)argc;
	(void)argv;
	usr = search_env_data("USER", env_cp);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_rm_cwd(env_cp);
		cwd = getcwd(NULL, 0);
	}
	temp = build_prompt_base(usr, cwd);
	free(cwd);
	if (!temp)
		return (NULL);
	prompt = ft_strjoin(temp, " // ");
	free(temp);
	if (!prompt)
		return (NULL);
	temp = ft_strjoin(prompt, NC);
	free(prompt);
	return (temp);
}

int	alone_pipe(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!line || line[0] == '|')
	{
		ft_printf("Syntax error near unexpected token '|'\n");
		return (1);
	}
	while (line[i] != '\0')
	{
		if (flag == 0 && line[i] != '|' && line[i] != ' ' && line[i] != '\t')
			flag = 1;
		if (line[i] == '|' && flag == 0 && line[i] != ' ' && line[i] != '\t')
		{
			ft_printf("Syntax error near unexpected token '|'\n");
			return (1);
		}
		if (line[i] == '|')
			flag = 0;
		i++;
	}
	return (0);
}

int	process_line(char *line, t_env **env_cp)
{
	t_token	*token;

	if (no_dquote(line) == 0 && alone_pipe(line) == 0)
	{
		token = pars(ft_split_token(line, ' '), *env_cp);
		if (is_exit(&token, env_cp) == 1)
		{
			free(line);
			return (1);
		}
		if (is_built_alone(&token) == 0 || is_there_a_pipe(line) == 1)
			pipex_nodes(&token, *env_cp);
		else if (*env_cp != NULL)
			commands(env_cp, token, NULL);
		free_tokens(&token);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_cp;
	char	*line;
	char	*prompt;

	env_cp = ft_env_maker(env);
	ft_init_signals();
	while (1)
	{
		prompt = generate_prompt(env_cp, argc, argv);
		if (prompt == NULL)
			return (1);
		line = readline(prompt);
		free(prompt);
		if (line == NULL)
		{
			ft_printf("exit\n");
			break ;
		}
		add_history(line);
		if (process_line(line, &env_cp) == 1)
			return (0);
		free(line);
	}
	free_env(env_cp);
	return (0);
}
