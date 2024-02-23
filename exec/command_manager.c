/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:02:04 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/23 11:45:04 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_manager(t_data *data)
{
	fprintf(stderr, "JE PASSE PAR EXEC\n\n\n\n");
	if (data->n_cmds > 1)
		pipex_exec(data);
	else
	single_arg(data);
	fprintf(stderr, "fin exec\n");
	return (0);
}
