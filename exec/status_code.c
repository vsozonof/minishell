/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:33:24 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/26 12:33:37 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_and_print_statuscode(int *pid, int i)
{
	int		wstatus;
	int		statusCode;

	waitpid(pid[i], &wstatus, 0);
	statusCode = -1;
	fprintf(stderr, "voici mon status: %d\n", wstatus);
	fprintf(stderr, "voici mon status: %d\n", WIFEXITED(wstatus));
	if (WIFEXITED(wstatus))
	{
		statusCode = WEXITSTATUS(wstatus);
		if (statusCode != 0)
		{
			write(2, "failure status code: \n", 23);
			write(2, &statusCode, 3);
			write(2, "\n", 1);
		}
		statusCode = WIFSIGNALED(wstatus);
		if (statusCode != 0)
		{
			write(2, "failure with a signal is unknown\n", 34);
			write(2, &statusCode, 3);
			write(2, "\n", 1);
		}
	}
	return (statusCode);
}
