/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:15:17 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/23 11:37:15 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// donc ici je dois:
// voir quel est le type de fd puis cree le fd, le garder en memoire
// et enfin le dup2

// 1 = simple quote vers la gauche <
// 2 = droite >
// 3 = db_gauche <<
// 4 = droite >>

int	redirection_create(t_data *data)
{
	int		file;

	file = 0;
	while (data->exec->redirs)
	{
		fprintf(stderr, "fd = %d\n", data->exec->redirs->type);
		file = create_file(data, file);
		if (file == 1)
			return (1);
		data->exec->redirs = data->exec->redirs->next;
	}
	return (0);
}

int	create_file(t_data *data, int file)
{
	if (data->exec->redirs->type == 2)
	{
		file = ft_create_fd(data->exec->redirs->file, O_RDONLY);
		if (file == 1)
			return (1);
		if (redirection_dup1_in(file) == 1)
			return (1);
	}
	else if (data->exec->redirs->type == 1)
	{
		file = ft_create_fd(data->exec->redirs->file, O_WRONLY | O_CREAT | O_TRUNC);
		if (file == 1)
			return (1);
		if (redirection_dup1_out(file) == 1)
			return (1);
	}
	else
	{
		if (other_type_redir(data, file) == 1)
			return (1);
	}
	return (0);
}

int	other_type_redir(t_data *data, int file)
{
	if (data->exec->redirs->type == 3)
	{
		file = ft_create_fd(data->exec->redirs->file, O_RDONLY);
		if (file == 1)
			return (1);
		if (redirection_dup1_in(file) == 1)
			return 1;
	}
	else if (data->exec->redirs->type == 4)
	{
		file = ft_create_fd(data->exec->redirs->file, O_WRONLY | O_APPEND);
		if (file == 1)
			return (1);
		if (redirection_dup1_out(file) == 1)
			return (1);
	}
	return (0);
}

int	redirection_dup1_in(int file)
{
	if (dup2(file, 0) < 0)
	{
		close(file);
		return (printf("problem with dup2 infile"), 1);
	}
	return (0);
}

int	redirection_dup1_out(int file)
{
	if (dup2(file, 1) < 0)
	{
		close(file);
		return (printf("problem with dup2 1"), 1);
	}
	return (0);
}
