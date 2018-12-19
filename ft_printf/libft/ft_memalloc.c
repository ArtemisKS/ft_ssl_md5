/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 18:14:37 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/25 18:14:39 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char		*res;
	size_t		i;

	i = 0;
	if (!size)
		return (NULL);
	if (!(res = (void*)malloc(size)))
		return (NULL);
	while (i < size)
	{
		res[i] = 0;
		i++;
	}
	return ((void*)res);
}
