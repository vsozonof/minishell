/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:15:17 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/22 08:18:27 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	redirection_dup1_in(t_cmd *cmd)
// {
// 	int		i;

// 	i = 0;
// 	if (cmd->first == -1)
// 	{
// 		if (dup2(0, 0) < 0)
// 		{
// 			// close(cmd->tab[cmd->index_redirs][2]);
// 			return (printf("problem with dup2 1"), -1);
// 		}
// 	}
// 	else
// 	{
// 		if (dup2(cmd->tab[first][2], 0) < 0)
// 		{
// 			close(cmd->tab[first][2]);
// 			return (printf("problem with dup2 1"), -1);
// 		}
// 	}
// 	if (redirection_dup1_out(cmd, last, i) == -1)
// 		return (-1);
// 	return (0);
// }

// int	redirection_dup1_out(t_cmd *cmd)
// {
// 	if (last == -1)
// 	{
// 		if (dup2(0, 1) < 0)
// 		{
// 			close(cmd->tab[cmd->index_redirs][2]);
// 			return (printf("problem with dup2 1"), -1);
// 		}
// 	}
// 	else
// 	{
// 		if (dup2(cmd->tab[last][2], 1) < 0)
// 		{
// 			close(cmd->tab[cmd->index_redirs][2]);
// 			return (printf("problem with dup2 1"), -1);
// 		}
// 	}
// 	while (cmd->n_redirs > i)
// 	{
// 		close(cmd->tab[i][2]);
// 		i++;
// 	}
// 	return (0);
// }
