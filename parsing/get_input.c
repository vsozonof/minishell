/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:42:18 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/20 13:47:46 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input(void)
{
	t_data	ptr;

	init_sbase(&ptr);
	while (42)
	{
		printf("%s@%s:%s", ptr.user, ptr.post, ptr.w_d);
		ptr.input = readline(" $> ");
		if (ptr.input)
		{
			add_history(ptr.input);
			input_parser(&ptr);
		}
		else
			break ;
	}
}