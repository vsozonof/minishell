/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:02:25 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/21 05:45:34 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ! Update les var dans la struct prompt quand changement de dossier

void	execute_cd(t_data *data)
{
	char	*path;
	printf("input = %s\n", data->input);
	if (n_args(data->input) == 0)
	{
		printf("HOME!\n");
		return ;
	}
	else if (n_args(data->input) != 1)
	{
		pr_error("cd: too many arguments.");
		return ;
	}
	path = extract_path(data->input);
	printf("path = %s\n", path);
}

void	update_pwd(t_data *data)
{
	(void)data;
}
