/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:07:01 by tpotilli          #+#    #+#             */
/*   Updated: 2023/11/25 15:59:35 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int command_manager(t_data *data)
{
	int		token;
	t_data	*tmp;

	tmp = data;
	token = 0;
	// token = get_kind_input(tmp, token);
	// if (token == 1)
	builtin_manager(tmp);
	// else if (token == 2)
	// 	command_exec();
	// else if (token == 3)
	// 	return (printf("Wrong input\n"), 1);
	return (0);
}

void	builtin_manager(t_data *tmp)
{
	// if (ft_strncmp(tmp->input, "cd", 2) == 0)
	// 	execute_cd(tmp);
	// else if (ft_strncmp(tmp->input, "echo", 4) == 0)
	// 	execute_echo(tmp);
	if (ft_strncmp(tmp->input, "env", 3) == 0)
		execute_env(tmp);
	else if (ft_strncmp(tmp->input, "exit", 2) == 0)
		execute_exit(tmp);
	// else if (ft_strncmp(tmp->input, "export", 6) == 0)
	// 	execute_export(tmp);
	if (ft_strncmp(tmp->input, "pwd", 3) == 0)
		execute_pwd(tmp);
	// else if (ft_strncmp(tmp->input, "unset", 5) == 0)
	// 	execute_unset(tmp);
}

// void	command_exec(char *input)
// {
// }

// void	builtin_manager(char *input)
// {

// }

// int		get_kind_input(t_data *data, int token)
// {
// 	int i;
// 	int	token;

	
// 	return (token);
// }
