/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 04:46:20 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/30 05:22:51 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_updater(t_data *data, int status, char *str)
{
	if (str)
		pr_error(str);
	free(data->c_status);
	data->i_status = status;
	data->c_status = ft_itoa(status);
}
