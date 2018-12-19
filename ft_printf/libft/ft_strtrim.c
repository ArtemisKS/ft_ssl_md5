/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 19:23:32 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/27 19:23:33 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	has_whitesp(char *s)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (s[i] < 33)
	{
		i++;
		c++;
	}
	while (s[i])
		i++;
	if (s[i - 1] > 33 && c == 0)
		return (0);
	return (1);
}

static void	trim(char *s1, char *t, int j, int i1)
{
	int fl;

	fl = 0;
	while (*s1)
	{
		while (*(s1 + j) && *(s1 - j) && (*(s1 + j) < 33 || *(s1 - j) < 33))
			if (*(s1 + ++j) >= 33 && *(s1 - j) >= 33)
			{
				fl = 1;
				break ;
			}
		if (*s1 >= 33)
			fl = 1;
		if (fl)
		{
			t[i1] = *s1;
			i1++;
		}
		fl = 0;
		j = 0;
		s1++;
	}
	t[i1] = '\0';
}

static char	*mallc(char *t)
{
	int		i;
	int		j;
	char	*res;

	i = ft_strlen(t);
	j = 0;
	if (!(res = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		res[j] = t[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

char		*ft_strtrim(char const *s)
{
	size_t	i;
	int		i1;
	char	*s1;
	char	*t;
	int		j;

	if (!s)
		return (NULL);
	j = 0;
	i1 = 0;
	s1 = (char*)s;
	i = ft_strlen(s1);
	if (!(t = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (!has_whitesp(s1))
		t = ft_strdup(s1);
	else
	{
		trim(s1, t, j, i1);
	}
	t = mallc(t);
	return (t);
}
