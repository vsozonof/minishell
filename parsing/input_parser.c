/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:14:23 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/20 19:22:31 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_parser(t_prompt *pr, t_data *data)
{
	init_str(data, pr);
	if (!is_there_pipe(pr))
		single_node_handler(data);
	else
	{
		printf("multi node\n");
		// multi_node_handler(data);
	}
	free_master(data);
}

void	single_node_handler(t_data *data)
{
	char	**tab;
	t_cmd	*ptr;

	ptr = malloc(sizeof(t_cmd));
	if (!ptr)
		return ;
	tab = input_to_lst(data);
	if (!tab)
		return (free_master(data));
	put_input_to_lst(data->inp, tab);
	identify_nodes(data->inp);
	// format_node(ptr, data->inp);
	ft_printlst(data->inp);
}

// void	format_node(t_cmd *pr, t_inp *inp)
// {
	
// }

void	multi_node_handler(t_data *data)
{
	(void)data;
}

void	identify_nodes(t_input *p)
{
	t_input	*nav;
	int		flag;

	flag = 0;
	nav = p;
	while (nav)
	{
		if (flag)
		{
			nav->i = 2;
			flag = 0;
		}
		else
			nav->i = node_identifier(nav->str);
		if (nav->i == 1)
			flag = 1;
		nav = nav->next;
	}
}

int	node_identifier(char *str)
{
	int	i;

	i = 0;
	if (token_identifier(str, i))
		return (1);
	else
		return (0);
}

char	**input_to_lst(t_data *data)
{
	int		i;
	char	**tab;
	int		n;

	i = 0;
	n = lexer_counter(data->input, 0, 0);
	printf("n === %d\n", n);
	tab = malloc(sizeof(char *) * (n + 1));
	if (!tab)
		return (NULL);
	while (data->input)
	{
		tab[i] = input_splitter(data);
		if (ft_strlen(data->input) == 0)
		{
			if (data->input)
				free(data->input);
			data->input = NULL;
		}
		i++;
	}
	tab[n] = NULL;
	return (tab);
}

char	*input_splitter(t_data *data)
{
	int		i;
	int		c;
	char	*tmp;
	char	*ret;

	i = 0;
	while (data->input[i] && !is_in_quotes(data->input, i)
		&& ft_is_whitespace(data->input[i]))
		i++;
	c = get_next_split(data->input, i);
	if (c == i)
		return (free(data->input), data->input = NULL, NULL);
	tmp = ft_substr(data->input, c, ft_strlen(data->input));
	if (!tmp)
		return (NULL);
	ret = ft_substr(data->input, i, (c - i));
	if (!ret)
		return (NULL);
	free(data->input);
	data->input = tmp;
	return (ret);
}

int	get_next_split(char *str, int i)
{
	int			c;
	static int	flag;

	c = i;
	if ((str[c] == 39 || str[c] == '"') && !flag)
		c += (quote_skipper(str, c) - c);
	else if (token_identifier(str, c))
	{
		c += token_identifier(str, c);
		flag = 1;
	}
	else
	{
		c += get_next_split_helper(str, c, flag);
		if (flag)
			flag = 0;
	}
	return (c);
}

int	get_next_split_helper(char *str, int c, int flag)
{
	if (!flag)
	{
		while (str[c] && !ft_is_whitespace(str[c]))
		{
			if (token_identifier(str, c))
				break ;
			else if (str[c] == '"' || str[c] == 39)
				c += (quote_skipper(str, c) - c);
			else
				c++;
		}
	}
	else
	{
		while (str[c])
		{
			if (ft_is_whitespace(str[c]) && !is_in_quotes(str, c))
				break ;
			else
				c++;
		}
	}
	return (c);
}

int	put_input_to_lst(t_input *ptr, char **tab)
{
	int		i;
	t_input	*nav;

	i = 0;
	if (!tab)
		return (0);
	nav = ptr;
	while (tab[i])
	{
		nav->str = ft_strdup(tab[i]);
		if (tab[i + 1])
		{
			nav->next = malloc(sizeof(t_input));
			if (!nav->next)
				return (0);
			nav = nav->next;
		}
		else
			nav->next = NULL;
		i++;
	}
	ft_split_free(tab);
	return (1);
}

int	is_special_char(char c)
{
	if (c == 39 || c == '"' || c == '>' || c == '<')
		return (0);
	return (1);
}


// void	input_parser(t_prompt *prompt, t_data *data)
// {
	// init_str(data, prompt);
	// if (!is_piped_input_valid(prompt->input, data))
// 		return (free_manager(data, 0));
// 	if (is_there_pipe(prompt))
// 	{
// 		data->cmds = pipes_splitter(prompt->input, '|', data);
// 		if (!data->cmds)
// 			return (set_status(data, 12, "malloc error.", NULL),
// 				free_manager(data, 0));
// 	}
// 	if (!redirection_and_expand_handler(data))
// 		return (free_manager(data, 0));
// 	if (is_there_pipe(prompt))
// 	{
// 		command_manager(data);
// 		free_manager(data, 2);
// 	}
// 	else if (!is_there_pipe(prompt))
// 	{
// 		if (!get_cmd(data))
// 			return (free_manager(data, 0));
// 		command_manager(data);
// 		free_manager(data, 1);
// 	}
// }

// int	get_cmd(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->input[i] && ft_is_whitespace(data->input[i]))
// 		i++;
// 	data->input = ft_substr(data->pr->input, i, ft_strlen(data->pr->input));
// 	if (!data->input)
// 		return (set_status(data, 12, "malloc error.", NULL), 0);
// 	return (data->n_cmds = 1, 1);
// }
