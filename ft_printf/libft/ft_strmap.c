/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 20:21:25 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/26 20:21:26 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	size_t	sz;
	char	*c;

	i = 0;
	if (!s || !f)
		return (NULL);
	sz = ft_strlen((char*)s);
	if (!(c = (char*)malloc(sizeof(char) * (sz + 1))))
		return (NULL);
	while (i < sz)
	{
		c[i] = f(s[i]);
		i++;
	}
	c[i] = '\0';
	return (c);
}
