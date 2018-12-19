/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:51:34 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/24 14:51:37 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t num)
{
	size_t		i;
	char		*tmp;
	char		*tmp1;

	tmp = (char*)destination;
	tmp1 = (char*)source;
	i = 0;
	while (i < num)
	{
		tmp[i] = tmp1[i];
		if (tmp[i] == c)
			return (destination + i + 1);
		i++;
	}
	return (NULL);
}
