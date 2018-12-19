/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 21:16:00 by akupriia          #+#    #+#             */
/*   Updated: 2017/11/09 21:16:01 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (i == 0 && str[i] != c)
			count++;
		while (str[i] == c && str[i + 1])
		{
			if (str[i + 1] != c)
				count++;
			i++;
		}
		if (str[i])
			i++;
	}
	return (count);
}

static int		ft_wordlen(char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i])
	{
		i++;
		j++;
	}
	return (j);
}

static char		*parse_word(char **str, char c, char *word, int j)
{
	while (**str)
	{
		if (**str != c)
		{
			while (**str != c)
			{
				word[j] = **str;
				if (**str != '\0')
				{
					(*str)++;
					j++;
				}
				else
				{
					j++;
					break ;
				}
			}
			break ;
		}
		(*str)++;
	}
	word[j] = '\0';
	return (word);
}

static char		*first_word(char **str, char c)
{
	char	*word;
	int		j;

	j = 0;
	if (!(word = (char*)malloc(sizeof(char) * (ft_wordlen(*str, c) + 1))))
		return (NULL);
	word = parse_word(str, c, word, j);
	return (word);
}

t_list			*ft_lstsplit(char const *s, char c)
{
	t_list	*res;
	t_list	*new;
	char	*s1;
	char	*t;
	int		cw;

	if (!s)
		return (NULL);
	s1 = (char*)s;
	cw = count_words(s1, c);
	if (!(res = (t_list *)malloc(sizeof(t_list) * (cw + 1))))
		return (NULL);
	res = NULL;
	while (cw--)
	{
		t = ft_strdup(first_word(&s1, c));
		new = ft_lstnew(t, ft_strlen(t));
		ft_lstadd(&res, new);
	}
	return (res);
}
