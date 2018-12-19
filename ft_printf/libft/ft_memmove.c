/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 15:05:07 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/24 15:05:11 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destptr, const void *srcptr, size_t num)
{
	char		*tmp;
	char		*tmp1;

	tmp = (char*)destptr;
	tmp1 = (char*)srcptr;
	if (tmp1 < tmp)
	{
		while (num--)
			tmp[num] = tmp1[num];
	}
	else
		ft_memcpy(tmp, tmp1, num);
	return (tmp);
}
