/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:42:38 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/25 13:57:13 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_problem(t_data *data, int *file)
{
	fprintf(stderr, "%d\n", data->n_redirs);
	if (data->n_redirs > 0)
		close_all_open_redirs(file, data->n_redirs - 1);
	free_master(data);
	free_end_of_program(data->pr);
}
