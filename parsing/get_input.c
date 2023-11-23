/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:42:18 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/23 14:23:11 by tpotilli         ###   ########.fr       */
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
