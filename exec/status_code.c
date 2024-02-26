/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:33:24 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/26 16:51:53 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_and_print_statuscode(t_data *data, char *cmd)
{
	int		wstatus;
	int		statusCode;

	statusCode = ((wstatus = 0));
	if (WIFEXITED(wstatus))
		statusCode = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		statusCode = 128 + WTERMSIG(wstatus);
	if (statusCode == 131)
		write(2, "Quit (core dumped)\n", 20);
	if (statusCode == 126)
		set_status(data, statusCode, "Permission denied", cmd);
	if (statusCode == 127)
		set_status(data, statusCode, "Command not found", cmd);
	if (statusCode == 128)
		set_status(data, statusCode, "Invalid exit argument", cmd);
	// set_status(data, statusCode, NULL, NULL);
	return (statusCode);
}
