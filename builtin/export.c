/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:49:13 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/29 06:01:14 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_export(t_data *data)
{
	int		i;
	char	*args;

	i = 0;
	args = export_extract_arg(data->input);
	if (!args)
		return (free(args), export_no_args(data->env));
	else if (!export_valid_args_counter(args))
		return (export_error_handler(args, NULL, NULL));
	else
	{
		while (args[i])
		{
			if (export_is_valid_arg(args, i))
			{
				i = export_is_valid_arg(args, i);
				export_finalizer(args, i);
			}
			else
				i++;
		}
	}
}

void	export_finalizer(char *args, int i)
{
	char	*var_name;
	char	*var_value;

	var_name = extract_var_name(args, i);
	var_value = extract_var_value(args, i);
	printf("var = [%s]\n", var_value);
}
