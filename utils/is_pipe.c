/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 06:15:38 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/26 06:16:45 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(t_prompt *prompt)
{
	int	i;

	i = -1;
	while (prompt->input[++i])
		if (prompt->input[i] == '|')
			return (1);
	return (0);
}
