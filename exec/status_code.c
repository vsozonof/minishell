/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:33:24 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/27 11:22:28 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_and_print_statuscode(t_data *data, int status)
{
	int		wstatus;

	status = ((wstatus = 0));
	if (WIFEXITED(wstatus))
		status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		status = 128 + WTERMSIG(wstatus);
	fprintf(stderr, "status = %d\n", status);
	if (status == 131)
	{
		write(2, "Quit (core dumped)\n", 20);
		set_status(data, status, NULL, NULL);
	}
	if (status == 126)
		set_status(data, status, NULL, NULL);
	if (status == 127)
		set_status(data, status, NULL, NULL);
	// set_status(data, status, NULL, NULL);
	return (status);
}
