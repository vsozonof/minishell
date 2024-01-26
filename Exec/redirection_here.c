/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_here.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:47:57 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/26 20:29:36 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*redirection_manager(int pipe, int token, int pipe2, t_data *data)
{
	char	*cmd;
	int		i;

	cmd = NULL;
	if (is_any_redirection(data) == 1)
		return (cmd);
	i = data->tab[0];
	data->n_redirs--;
	cmd = check_redirection(pipe, pipe2, data);
	if (cmd != NULL)
		return (cmd);
	// else if ()
	// if (data->tab[i][1] == 1)
	// {
	// 	if (dup2(0, 0) < 0)
	// 		return (printf("problem with dup2 1"), -1);
	// 	if (dup2(pipe2, 1) < 0)
	// 		return (printf("problem with dup2 2"), -1);
	// }
	// else if (data->tab[i][1] == 3)
	
	// else if (data->tab[i][1] == 2)

	else if (data->tab[i][1] == 4)
	
	return (cmd);
}

char	*check_redirection(int pipe, int pipe2, t_data *data)
{
	int	fd;
	int	fd2;

	fd = verif_arg_fd(data->cmds[]);
	if ()
}

int	is_any_redirection(t_struct *data)
{
	if (data->n_redirs > 0)
		return (0);
	return (1);
}
