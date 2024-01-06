/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:02:25 by tpotilli          #+#    #+#             */
/*   Updated: 2023/12/29 17:51:59 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ! Update les var dans la struct prompt quand changement de dossier

void	execute_cd(t_data *data)
{
	char	*home;

	home = getenv("HOME");
	if (!data->args)
	{
		if (!home)
			return ;
		else
		{
			chdir("~");
			data->pr->w_d = home;
		}
	}
}
