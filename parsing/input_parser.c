/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:14:23 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/24 18:19:33 by vsozonof         ###   ########.fr       */
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
	while (prompt->input[i] && ft_is_whitespace(prompt->input[i]))
		i++;
	c = i;
	while (prompt->input[c] && !ft_is_whitespace(prompt->input[c]))
		c++;
	printf("i -> %i | c -> %i\n", i, c);
	data.input = ft_substr(prompt->input, i, c);
	i = c;
	// ? La commande se retrouve dans data.input, que tu peux passer a une fonction
	// ? pour exec
	printf("cmd -> %s\n", data.input);
}
