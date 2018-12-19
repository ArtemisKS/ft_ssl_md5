/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:55:46 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/24 17:55:49 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buf1, const void *buf2, size_t count)
{
	size_t			i;
	unsigned char	*c;
	unsigned char	*c2;

	i = 0;
	c = (unsigned char*)buf1;
	c2 = (unsigned char*)buf2;
	while (i < count)
	{
		if (c[i] != c2[i])
			return (c[i] - c2[i]);
		i++;
	}
	return (0);
}
