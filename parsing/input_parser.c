/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:14:23 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/23 17:11:47 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_parser(t_prompt *prompt)
{
	t_data	data;
	int		i;
	int		c;

	i = 0;
	init_str(&data, prompt);
	while (prompt->input[i] && !ft_is_whitespace(prompt->input[i]))
		i++;
	c = 0;
	while (prompt->input[i] && ft_is_whitespace(prompt->input[i]))
	{
		i++;
		c++;
	}
	data.input = ft_substr(data.input, i, c);
}
