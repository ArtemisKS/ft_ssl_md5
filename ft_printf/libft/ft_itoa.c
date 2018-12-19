/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 18:59:28 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/28 18:59:29 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int n)
{
	int i;

	i = 0;
	if (n < 0)
		i++;
	else if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_putnum(int nb, char *c, int i)
{
	unsigned int u_nb;

	u_nb = nb;
	if (nb < 0)
	{
		c[0] = '-';
		u_nb *= (-1);
	}
	if (u_nb > 9)
	{
		ft_putnum(u_nb / 10, c, --i);
	}
	if (u_nb <= 9)
		--i;
	c[i] = (u_nb % 10 + '0');
}

char		*ft_itoa(int n)
{
	char	*res;
	int		sz;

	sz = intlen(n);
	if (!(res = (char*)malloc(sizeof(char) * (sz + 1))))
		return (NULL);
	ft_putnum(n, res, sz);
	res[sz] = '\0';
	return (res);
}
