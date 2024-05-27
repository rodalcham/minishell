/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:08:51 by lglauch           #+#    #+#             */
/*   Updated: 2024/05/26 23:25:25 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_spc(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	is_op(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

// char	**my_completion_function(const char *text, int start, int end)
// {
// 	char	**matches;

// 	matches = NULL;
// 	(void)end;
// 	if (start == 0 && text[0] == 0)
// 		rl_attempted_completion_over = 1;
// 	else if (start == 0 && text[0] == ' ')
// 		matches = rl_completion_matches(text, rl_completion_entry_function);
// 	return (matches);
// }


char *make_unclosed_quotes(char *str)
{
    char *new_input;
    char *new_str;

    new_input = readline("> ");
    if (!new_input)
	{
        return (NULL);
	}
    new_str = malloc(sizeof(char) * (strlen(str) + strlen(new_input) + 2));
    if (!new_str)
    {
        free(new_input);
        return (NULL);
    }
    strcpy(new_str, str);
    strcat(new_str, " ");    //if not in libft write them
    strcat(new_str, new_input);
    free(str);
    free(new_input);
	if (handle_unclosed_quotes(new_str)) 
		return (make_unclosed_quotes(new_str));
    return (new_str);
}
char	*handle_unclosed_quotes(char *str)
{
    int	i;
    int	single;
    int	double_quotes;

    i = 0;
    single = 0;
    double_quotes = 0;
    while (str[i])
    {
        if (str[i] == '\'' && double_quotes == 0)
            single = !single;
        if (str[i] == '\"' && single == 0)
            double_quotes = !double_quotes;
        i++;
    }
    if (single == 1 || double_quotes == 1)
        str = make_unclosed_quotes(str);
    return (str);
}
