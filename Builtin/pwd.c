/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:09:39 by tpotilli          #+#    #+#             */
/*   Updated: 2023/11/25 12:16:09 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pwd(t_data *data)
{
	unsigned int i;

	i = 0;
	while (ft_strncmp(data->envp[i], "PWD=", 4) != 0)
		i++;
	printf("%s\n", (data->envp[i] + 4));
}

//getcwd