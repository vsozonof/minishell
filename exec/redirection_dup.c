/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:15:17 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/25 14:57:45 by tpotilli         ###   ########.fr       */
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

int	*redirection_create(t_data *data)
{
	int			file;
	int			*file_tab;
	t_redir		*nav;
	int			i;

	nav = data->exec->redirs;
	file = ((i = 0));
	file_tab = malloc(sizeof(int) * data->n_redirs);
	if (!file_tab)
	{
		fprintf(stderr, "a problem append with a malloc\n");
		free_problem(data, NULL);
	}
	while (nav)
	{
		file_tab[i] = create_file(nav, file);
		if (file_tab[i] == -1 || nav->file == NULL)
		{
			fprintf(stderr, "%s : No such file or directory\n", nav->file);
			free_problem(data, file_tab);
		}
		i++;
		nav = nav->next;
	}
	return (file_tab);
}

int	create_file(t_redir *nav, int file)
{
	if (nav->type == 2)
	{
		file = ft_create_fd(nav->file, O_RDONLY);
		if (file == -1)
			return (-1);
		if (redirection_dup1_in(file) == -1)
			return (-1);
	}
	else if (nav->type == 1)
	{
		file = ft_create_fd(nav->file, O_WRONLY | O_CREAT | O_TRUNC);
		if (file == -1)
			return (-1);
		if (redirection_dup1_out(file) == -1)
			return (-1);
	}
	else
	{
		if (other_type_redir(nav, file) == -1)
			return (-1);
	}
	return (file);
}

int	other_type_redir(t_redir *nav, int file)
{
	if (nav->type == 3)
	{
		file = ft_create_fd(nav->file, O_RDONLY);
		if (file == -1)
			return (-1);
		if (redirection_dup1_in(file) == -1)
			return (-1);
		unlink(nav->file);
	}
	else if (nav->type == 4)
	{
		file = ft_create_fd(nav->file, O_WRONLY | O_APPEND);
		if (file == -1)
			return (-1);
		if (redirection_dup1_out(file) == -1)
			return (-1);
	}
	return (file);
}

int	redirection_dup1_in(int file)
{
	if (dup2(file, 0) < 0)
	{
		close(file);
		return (printf("problem with dup2 infile"), -1);
	}
	return (0);
}

int	redirection_dup1_out(int file)
{
	if (dup2(file, 1) < 0)
	{
		close(file);
		return (printf("problem with dup2 1"), -1);
	}
	return (0);
}
