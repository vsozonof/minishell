/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:07:01 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/06 15:29:00 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int command_manager(t_data *data)
{
	// int		check;
	// int		i;

	// i = 0;
	// while (i < data->n_args)
	// {
	pipe_command(data);
		// check = builtin_checker(data);
		// if (check != 0)
		// 	builtin_manager(data, check);
		// i++;
	// }
	// regler la partie des maillon pour l'exec

	// else if (token == 2)
	// 	command_exec();
	// else if (token == 3)
	// 	return (printf("Wrong input\n"), 1);
	return (0);
}

int	builtin_checker(t_data *tmp)
{
	int		token;

	token = 0;
	// if (ft_strncmp(tmp->input, "cd", 2) == 0) // probleme pour arg
	// 	token = 1;
	if (ft_strncmp(tmp->input, "echo", 4) == 0)
		token = 2;
	else if (ft_strncmp(tmp->input, "env", 3) == 0)
		token = 3;
	else if (ft_strncmp(tmp->input, "exit", 4) == 0)
		token = 4;
	else if (ft_strncmp(tmp->input, "export", 6) == 0)
		token = 5;
	if (ft_strncmp(tmp->input, "pwd", 3) == 0)
		token = 6;
	// else if (ft_strncmp(tmp->input, "unset", 5) == 0)
		// token = 7;
	return (token);
}

void	builtin_manager(t_data *tmp, int token)
{
	// printf("token %d\n", token);
	// if (token == 1)
	// 	execute_cd(tmp);
	if (token == 2)
		printf("normalement echo\n");
	else if (token == 3)
		execute_env(tmp);
	else if (token == 4)
		execute_exit(tmp);
	// else if (token == 5)
		// execute_export(tmp);
	else if (token == 6)
		execute_pwd(tmp);
	// else if (token == 7)
		// execute_unset(tmp);
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
