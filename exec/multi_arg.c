/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:36:45 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/28 04:45:32 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//command a essayer :
/*
cat > test1 > test2 < test3 | wc
ls > out > out1 > out2 < Makefile | cat < Makefile
cat > test1 > test2 < test3 | wc > test4 < test5 | wc > test6
*/

/*
**	This function takes as parameter: 
**
**	data -> the struct who contains all variables
**  to exec our program
**
** =====================================================
** =====================================================
**
**  Pipex_exec will check if we can execute the command
**  with the function ft_do_process (we also get the path)
**  then we go to ft_pipex to start the execution
*/

int	pipex_exec(t_data *data)
{
	int		i;

	data->index_here_doc = 0;
	i = ft_pipex(data);
	if (i == -1)
	{
		get_and_print_statuscode(data, i);
		return (-1);
	}
	get_and_print_statuscode(data, i);
	free_all_pipe(data->pipefd);
	free(data->pid);
	return (0);
}

/*
**	This function takes as parameter: 
**
**
** =====================================================
** =====================================================
**
**
*/