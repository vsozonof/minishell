/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:11:39 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/07 15:42:32 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_fd_tab(char **str, int i)
{
	int		j;

	j = 0;
	while (str[i][j])
		j++;
	return (j);
}

int	found_max(char	*argv[])
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	verif_arg_fd(char	*argv[], int i)
{
	int		fd;

	fd = open(argv[i], O_RDONLY, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

//O_WRONLY | O_CREAT | O_TRUNC
int	ft_create_fd(char	*argv, int flag)
{
	int	fd;

	fd = open(argv, flag, 0644);
	if (fd < 0)
		return (printf("problem with fd\n"), -1);
	return (fd);
}
