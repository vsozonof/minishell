/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:29:44 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/20 09:19:05 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	ptr;

	init_sbase(&ptr);
	while (42)
	{
		printf("%s@%s:%s", ptr.user, ptr.post, ptr.w_d);
		ptr.input = readline(" $> ");
		add_history(ptr.input);
		input_parser(&ptr);
	}
}
