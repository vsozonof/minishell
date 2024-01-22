/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:55:02 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/22 19:02:31 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int single_arg(t_data *data)
{
    char    **buf;
    char    *fre;
    char    **cmd_argument;

    buf = arg(data->input);
    cmd_argument = ft_split(data->input, ' ');
    fre = ft_do_process(data->pr->nv, buf[0]);
    if (!fre || !cmd_argument)
    {
        perror("wrong commd\n");
        ft_freedb(buf);
        ft_freedb(data->cmds);
        ft_freedb(cmd_argument);
        return (0);
    }
    execve(fre, cmd_argument, data->pr->nv);
    ft_freedb(buf);
    free(fre);
    return (0);
}
