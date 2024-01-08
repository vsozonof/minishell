/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:02:25 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/08 10:33:36 by vsozonof         ###   ########.fr       */
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
	update_pwd(data);
}

void	update_pwd(t_data *data)
{
	unsigned int	i;
	static int		c;

	i = 0;
	while (ft_strncmp(data->envp[i], "PWD=", 4) != 0)
		i++;
	if (c)
		free(data->envp[i]);
	data->envp[i] = ft_strjoin("PWD=", data->pr->w_d);
	c++;
}
