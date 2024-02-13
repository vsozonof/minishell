/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils-2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:30:26 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/13 06:35:30 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ! Redirection Checker
// ? This function will check if the filename
// ? that follows a redirection token is valid or not
// * 1. \0
// * 2. >> ou << |
// * 3. > ou < |
// * 4. ><
// * 5. < >
// * 6. >> ou << et > >> < <<

int	redir_checker(char *str, int i, t_data *data)
{
	if (str[i] == str[i - 1])
		if (!double_redir_checker(str, (i + 1), data))
			return (0);
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '\0')
		return (set_status(data, 2, "syntax error near `\\n'", NULL), 0);
	else if (str[i] == '>' || str[i] == '<')
		return (set_status(data, 2, "syntax error near `\\n'", NULL), 0);
	else if ((str[i - 1] == '<' || str[i - 1] == '>')
		&& (str[i] == '<' || str[i] == '>') && str[i + 1] == '|')
		return (set_status(data, 2, "syntax error near `|'", NULL), 0);
	else if ((str[i - 1] == '<' || str[i - 1] == '>')
		&& (str[i] == '|' || str[i + 1] == '|'))
		return (set_status(data, 2, "syntax error near `|'", NULL), 0);
	else if (str[i] == '<' && str[i - 1] == '>')
		return (set_status(data, 2, "syntax error near `<'", NULL), 0);
	else if (str[i] == '>' && str[i - 1] == '<')
		return (set_status(data, 2, "syntax error near `\\n'", NULL), 0);
	else if (str[i] == str[i - 1] && is_token(str, (i + 1)))
		return (set_status(data, 2, "syntax error near `\\n'", NULL), 0);
	return (1);
}

int	is_there_redirs(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if ((str[i] == '>' || str[i] == '<') && is_in_quotes(str, i) != 1)
			return (1);
	return (0);
}

int	is_valid_char_after_redir(int c)
{
	if (ft_isprint(c))
		return (1);
	return (0);
}

void	extract_redir_cmds(char **splitted, t_data *data)
{
	int	i;
	int	c;
	int	count;
	char *tmp;
	int	j;

	j = 0;
	while (splitted[j])
		j++;
	i = ((c = 0));
	count = cmd_counter(splitted);
	data->redir_tab = malloc(sizeof(char *) * (count + 1));
	if (!data->redir_tab)
		return ;
	while (splitted[c])
	{
		if (c < j && (splitted[c][0] == '<' || splitted[c][0] == '>'))
			c += 2;
		if (c < j && splitted[c][0] == '|')
			c++;
		if (c < j && splitted[c][0] != '<' && splitted[c][0] != '>'
			&& splitted[c][0] != '|')
		{
			data->redir_tab[i] = ft_strdup(splitted[c]);
			if (splitted[c + 1] && (splitted[c + 1][0] != '<' && splitted[c + 1][0] != '>'
				&& splitted[c + 1][0] != '|'))
			{
				tmp = data->redir_tab[i];
				data->redir_tab[i] = ft_strjoin(data->redir_tab[i], " ");
				free(tmp);
				tmp = data->redir_tab[i];
				data->redir_tab[i] = ft_strjoin(data->redir_tab[i], splitted[c + 1]);
				free(tmp);
				c += 2;
				i++;
			}
			else
			{
				i++;
				c++;
			}
		}
	}
	data->redir_tab[i] = NULL;
	ft_split_free(splitted);
}

int	cmd_counter(char **splitted)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (splitted[i])
	{
		if (splitted[i][0] == '<' || splitted[i][0] == '>')
			count -= 2;
		i++;
		count++;
	}
	return (count);
}
