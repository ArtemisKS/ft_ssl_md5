/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:51:54 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/27 17:51:55 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	join(char const *s1, char const *s2, char *c, int j)
{
	while (*s1)
	{
		c[j] = *s1;
		j++;
		s1++;
	}
	while (*s2)
	{
		c[j] = *s2;
		j++;
		s2++;
	}
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*c;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
	{
		i++;
		j++;
	}
	if (!(c = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	j = 0;
	join(s1, s2, c, j);
	i > j ? (c[i] = '\0') :
	(c[j] = '\0');
	return (c);
}
