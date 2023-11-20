/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:27:48 by vsozonof          #+#    #+#             */
/*   Updated: 2023/11/20 13:53:04 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signum)
{
	t_data	ptr;
	char	*tmp;

	(void)signum;
	ptr.user = getenv("LOGNAME");
	tmp = getenv("SESSION_MANAGER");
	ptr.post = ft_substr(tmp, 6, 12);
	ptr.w_d = getcwd(NULL, 0);
	printf("\n%s@%s:%s $>", ptr.user, ptr.post, ptr.w_d);
}

void	handle_sigquit(int signum)
{
	(void)signum;
}
