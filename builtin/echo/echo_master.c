/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:48:29 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/05 07:55:30 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_echo(t_data *data)
{
	char	*to_print;
	char	*tmp;
	int		flag;
	(void)flag;

	to_print = export_extract_arg(data->input);
	if (!to_print)
		return (ft_putstr("\n"));
	if (ft_strnstr(to_print, "-n ", 3))
	{
		flag = 1;
		tmp = ft_substr(to_print, 3, ft_strlen(to_print));
		free(to_print);
		to_print = tmp;
		if (is_there_quotes(to_print))
			to_print = quote_remover_v2(to_print);
		printf("%s", to_print);
	}
	else
	{
		if (is_there_quotes(to_print))
			to_print = quote_remover_v2(to_print);
		printf("%s\n", to_print);
	}
	free(to_print);
}
