/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:54:08 by tpotilli          #+#    #+#             */
/*   Updated: 2023/11/25 12:57:07 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute_unset(t_data *data)
{
    int		i;
    int		j;

    i = ((j = 0));
    while (data->envp[i])
    {
        if (ft_strncmp(data->envp[i], data->input) == 0)
            //supr
        i++;
    }
}
