/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:41:34 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/22 09:49:30 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_single(t_cmd *cmd)
{
	int	check;
	// int	du1;
	// int	du2;

	check = builtin_checker(cmd->cmd);
	fprintf(stderr, "voici mon check %d\n", check);
	if (check >= 1 && check <= 7)
	{
		// if (cmd->nb_redir > 0)
		// {
		// 	if (redir_builtin(cmd, check, du1, du2) == 1)
		// 		return (1);
		// }
		// builtin_manager(cmd, check);
		return (0);
	}
	return (1);
}

int	builtin_checker(char *tmp)
{
	int		token;

	token = 0;
	if (ft_strncmp(tmp, "cd", 2) == 0)
		token = 1;
	if (ft_strncmp(tmp, "echo", 4) == 0)
		token = 2;
	else if (ft_strncmp(tmp, "env", 3) == 0)
		token = 3;
	else if (ft_strncmp(tmp, "exit", 4) == 0)
		token = 4;
	else if (ft_strncmp(tmp, "export", 6) == 0)
		token = 5;
	if (ft_strncmp(tmp, "pwd", 3) == 0)
		token = 6;
	else if (ft_strncmp(tmp, "unset", 5) == 0)
		token = 7;
	return (token);
}

// void	builtin_manager(t_cmd *cmd, int token)
// {
// 	if (token == 1)
// 		execute_cd(cmd);
// 	else if (token == 2)
// 		execute_echo(cmd);
// 	else if (token == 3)
// 		execute_env(cmd);
// 	else if (token == 4)
// 		execute_exit(cmd);
// 	else if (token == 6)
// 		execute_pwd(cmd);
// 	else if (token == 5)
// 		execute_export(cmd);
// 	else if (token == 7)
// 		execute_unset(cmd);
// }

// int	redir_builtin(t_cmd *cmd, int check, int du1, int du2)
// {
// 	if (cmd->nb_redir > 0)
// 	{
// 		du1 = dup(0);
// 		du2 = dup(1);
// 		if (!cmd->first || !cmd->last)
// 		{
// 			close_all_redirs(cmd);
// 			close(du1);
// 			close(du2);
// 			return (-1);
// 		}
// 		redirection_dup1_in(cmd, data->first[0], data->last[0]);
// 	}
// 	builtin_manager(cmd, check);
// 	if (data->n_redirs > 0)
// 	{
// 		close_all_redirs(data);
// 		dup2(du1, 0);
// 		dup2(du2, 1);
// 		close(du1);
// 		close(du2);
// 	}
// 	return (0);
// }