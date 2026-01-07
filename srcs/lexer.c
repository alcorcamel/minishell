/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:53:41 by rbourdon          #+#    #+#             */
/*   Updated: 2026/01/07 19:13:09 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_remi.h"

static int	ft_isspaces(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static t_token	*ft_lstnew(t_token_type type)
{
	t_token	*ret;

	ret = (t_token *)malloc(sizeof(t_token));
	if (!ret)
		return (NULL);
	ret->type = type;
	ret->next = NULL;
	return (ret);
}

static void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

static void	ft_operator_assignment(t_token **lst_begin, char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	if (s[i] == '|')
		ft_lstadd_back(lst_begin, ft_lstnew(TOKEN_PIPE));
	else if (s[i] == '>')
		ft_lstadd_back(lst_begin, ft_lstnew(TOKEN_REDIR_OUT));
	else if (s[i] == '<')
		ft_lstadd_back(lst_begin, ft_lstnew(TOKEN_REDIR_IN));
	else if (s[i] == '(')
		ft_lstadd_back(lst_begin, ft_lstnew(TOKEN_LBRACKET));
	else if (s[i] == ')')
		ft_lstadd_back(lst_begin, ft_lstnew(TOKEN_RBRACKET));
}

static int	ft_double_size_operator(char *s, t_token **lst_begin, int *j)
{
	int	i;

	if (!s)
		return (0);
	i = 1;
	if (s[i + 1] && s[i + 1] == s[i])
	{
		if (s[i] == '|')
			ft_lstadd_back(lst_begin, ft_lstnew(TOKEN_OR));
		else if (s[i] == '&')
			ft_lstadd_back(lst_begin, ft_lstnew(TOKEN_AND));
		else if (s[i] == '>')
			ft_lstadd_back(lst_begin, ft_lstnew(TOKEN_APPEND));
		else if (s[i] == '<')
			ft_lstadd_back(lst_begin, ft_lstnew(TOKEN_HEREDOC));
		(*j) += 1;
		return (1);
	}
	return (0);
}


static int	ft_is_brace(char *s)
{
	if (!s)
		return (0);
	if (*s == '(' || *s == ')')
		return (1);
	return (0);
	}

static int	ft_is_an_operator(char *s)
{
	if (!s)
		return (0);
	if (*s == '<' || *s == '>' || *s == '|' || *s == '&')
		return (1);
	return (0);
}

static void	ft_sqdq_helper(char c, int *sq, int *dq)
{
	if (c == '\'' && *sq == 0)
		*sq = 1;
	else if (c == '\'' && *sq == 1)
		*sq = 0;
	else if (c == '\"' && *dq == 0)
		*dq = 1;
	else if (c == '\"' && *dq == 1)
		*dq = 0;
}

static char	*ft_read_word(char *s, int *j, t_token *begin)
{
	// int		in_sq;
	// int		in_dq;
	int		i;
	t_token	*tmp;
	char	*buffer;

	// in_sq = 0;
	// in_dq = 0;
	i = -1;
	if (!s)
		return (NULL);
	tmp = ft_lstnew(TOKEN_WORD);
	if (!tmp)
		return (NULL);
	ft_lstadd_back(begin, tmp);

	// while (s[++i] && !ft_is_an_operator(s + i) && ((!ft_isspaces(s[i])
	// 	&& in_sq == 0) || (ft_isspaces(s[i]) && in_sq == 1)))
	while (s[++i] && !ft_is_an_operator(s + i))
	{
		ft_sqdq_helper(s[i], &in_sq, &in_dq);



	}
}

t_token	*ft_lexer(char *l)
{
	int		i;
	t_token	**lst_begin;

	i = -1;
	if (!l)
		return (NULL);
	*lst_begin = ft_lstnew(TOKEN_BEGIN);
	while (l[++i])
	{
		while (ft_isspaces(l[i]))
			i++;
		if (ft_is_brace(l + i))
			ft_operator_assignment(lst_begin, l + i);
		if ((l[i] == '\'' || l[i] == '\"') && !ft_is_an_operator(l + i) && !ft_isspaces(l[i]))
			ft_read_word(l + i, &i, *lst_begin);
		if (ft_is_an_operator(l + i))
		{
			if (ft_double_size_operator(l + i, lst_begin, &i) == 0)
				ft_operator_assignment(lst_begin, l + i)
		}



	}
}
