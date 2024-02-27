/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:33:24 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/27 23:19:50 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_and_print_statuscode(t_data *data, int status)
{
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	if (status == 131)
	{
		write(2, "Quit (core dumped)\n", 20);
		set_status(data, status, NULL, NULL);
	}
	if (status == 126)
		set_status(data, status, NULL, NULL);
	if (status == 127)
		set_status(data, status, NULL, NULL);
	if (status == 1)
		set_status(data, status, NULL, NULL);
	return (status);
}
