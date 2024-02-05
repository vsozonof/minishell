/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:45:18 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/05 13:00:23 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_do_here_doc(t_data *data)
{
    char    *path;
    int     file;

    path = NULL;
    file = get_name_heredoc();
    if (ft_create_fd(, O_WRONLY | O_CREAT | O_TRUNC))
        return (-1);
    return (path);
}

int get_name_heredoc()
{
    char	*buf;
    int		i;
	int		fd;

	fd = open("/dev/random", O_RDONLY);
	if (!fd)
		return (fprintf(stderr, "problem with fd in here_doc\n"), -1);
	read(fd, buf, 14);
	i = 1;
	str[0] = '.';
	while (i < 15)
	{
		str[i] = (str[i] % 25) + 'a';
		i++;
	}
    buf[16] = '.';
    buf[17] = 't';
    buf[18] = 'x';
    buf[19] = 't';
    buf[20] = '\0';
	close(fd);
	return (str);
}
