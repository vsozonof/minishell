/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:52:12 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/12 08:52:39 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status_checker(char	*input, t_data *data)
{
	char		*status;
	long int	i_status;

	status = export_extract_arg(input);
	if (!status)
		return (set_status(data, 12, "malloc error.", NULL), -1);
	if (!ft_int_overflow_checker(status))
		return (set_status(data, 12, "exit", "numeric argument required"), -1);
	i_status = ft_atol(status);
	if (i_status < 0 || i_status > 255)
		i_status = (i_status % 256 + 256) % 256;
	free(status);
	return (i_status);
}

void	execute_exit(t_data *data)
{
	int	status;

	data->input = quote_remover_v2(data->input);
	printf("exit\n");
	if (n_args(data->input) == 0)
		data->exited = 1;
	else if (n_args(data->input) == 1)
	{
		status = status_checker(data->input, data);
		if (!status)
			return ;
		else
		{
			set_status(data, status, NULL, NULL);
			data->exited = 1;
		}
	}
	else
		set_status(data, 127, "exit", "too many arguments");
}
