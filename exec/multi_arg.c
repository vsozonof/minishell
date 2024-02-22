/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:36:45 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/22 14:19:56 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//command a essayer :
/*
cat > test1 > test2 < test3 | wc
ls > out > out1 > out2 < Makefile | cat < Makefile
cat > test1 > test2 < test3 | wc > test4 < test5 | wc > test6
*/

// !!! dans redirection manager j'ai baisser mon nb_redirs -> retirer

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

// pour les commande non valide, mettre un flag dans liste chainer qui dit si elles sont executable

int	pipex_exec(t_cmd *cmd)
{
	fprintf(stderr, "je passe par multi\n");
	ft_pipex(cmd);
	return (0);
}

// int	ft_check_access(t_data *data, int i)
// {
// 	char	*buf;

// 	buf = NULL;
// 	data->actual_path = malloc(sizeof(char *) * (len_db_tab(data->cmds) + 1));
// 	if (!data->actual_path)
// 		return (-1);
// 	while (data->cmds[i])
// 	{
// 		buf = arg(data->cmds[i], data);
// 		fprintf(stderr, "voici buf %s et voici cmds %s\n", buf, data->cmds[i]);
// 		if (!data->pr->nv)
// 			return (fprintf(stderr, "problem with env\n"), -1);
// 		data->actual_path[i] = ft_do_process(data->pr->nv, buf);
// 		if (!data->actual_path[i])
// 			data->actual_path[i] = data->cmds[i];
// 		free(buf);
// 		i++;
// 	}
// 	data->actual_path[i] = NULL;
// 	return (0);
// }

//dans le fork faire:
//if (ft_check_access(cmd) == -1)

/*
**	This function takes as parameter: 
**
**
** =====================================================
** =====================================================
**
**
*/