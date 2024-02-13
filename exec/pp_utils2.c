/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:09:52 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/13 15:29:13 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipe(int **pipefd, t_data *data)
{
	(void)data;

	close(pipefd[0][0]);
	close(pipefd[0][1]);
	close(pipefd[1][1]);
	close(pipefd[1][0]);
}

int	len_db_tab(char **str)
{
	int		j;

	j = 0;
	while (str[j])
		j++;
	return (j);
}

char *copy_arg(char *dest, char *src)
{
	int	i;

	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(src) + 1));
	dest = NULL;
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*arg_helper(char **buf, char *tmp, t_data *data, int i)
{
	if (data->tab[data->index_redirs][1] == 1)
	{
		tmp = copy_arg(tmp, buf[1]);
		return (ft_freedb(buf), tmp);
	}
	else if (data->tab[data->index_redirs][1] == 3)
	{
		i--;
		tmp = copy_arg(tmp, buf[i]);
		return (ft_freedb(buf), tmp);
	}
	return (NULL);
}

int	ft_count_space(char *buf)
{
	int	i;
	int	c;
	int	cpt;
	
	i = ((c = 0));
	(void)i;
	cpt = 0;
	while (buf[c] && buf[c + 1])
	{
		if (buf[c] == ' ' && buf[c + 1] == ' ')
			cpt++;
		c++;
	}
	return (cpt);
}

int	len_buf(char *buf, char *input, t_data *data, int act_redir)
{
	int		len;
	int		i;
	(void)data;
	(void)act_redir;
	(void)buf;

	len = ((i = 0));
	while (input[i])
	{
		if (input[i] == ' ' && input[i + 1] == '>')
		{
			i += 3;
			while (ft_isalnum(input[i]))
				i++;
			if (!input[i])
				break;
		}
		len++;
		i++;
	}
	if (input[i] == ' ')
		len--;
	return (len);
}
