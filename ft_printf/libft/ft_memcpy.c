/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 18:02:16 by angavrel          #+#    #+#             */
/*   Updated: 2019/02/01 21:42:14 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static void	go_fast(unsigned char **cdst, unsigned char **csrc, size_t *n)
{
	unsigned long	*ldst;
	unsigned long	*lsrc;
	size_t			a;

	ldst = (unsigned long *)*cdst;
	lsrc = (unsigned long *)*csrc;
	a = *n;
	while (a >= 8)
	{
		*ldst++ = *lsrc++;
		a -= 8;
	}
	*n = a;
	*csrc = (unsigned char *)lsrc;
	*cdst = (unsigned char *)ldst;
}

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*cdst;
	unsigned char	*csrc;

	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	while (((sizeof(unsigned long) - 1)) && n)
	{
		*cdst++ = *csrc++;
		--n;
	}
	if (n >= 8)
		go_fast(&cdst, &csrc, &n);
	while (n-- > 0)
		*cdst++ = *csrc++;
	return (dst);
}
