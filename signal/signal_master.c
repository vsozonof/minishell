/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:27:48 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/22 05:38:24 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signum)
{
	t_prompt	ptr;
	char		*tmp;

	if (signum == SIGINT)
	{
		ptr.user = getenv("LOGNAME");
		tmp = getenv("SESSION_MANAGER");
		ptr.post = ft_substr(tmp, 6, 12);
		ptr.w_d = getcwd(NULL, 0);
		printf("\n%s at %s in: %s$>", ptr.user, ptr.post, ptr.w_d);
		free(ptr.post);
	}
	else if (signum == SIGQUIT)
		(void)signum;
}