/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 14:22:20 by exam              #+#    #+#             */
/*   Updated: 2017/10/13 16:03:43 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		stsize(uintmax_t value, int base)
{
	int			size;

	size = 1;
	while (value >= (uintmax_t)base)
	{
		size++;
		value = value / (uintmax_t)base;
	}
	return (size);
}

char			*ft_itoa_base_u(uintmax_t value, int base)
{
	int			size;
	char		*res;
	char		*tab;

	tab = "0123456789ABCDEF";
	size = stsize(value, base);
	res = (char *)malloc(sizeof(char) * (size + 1));
	res[size] = '\0';
	while (--size > 0 && value >= (uintmax_t)base)
	{
		res[size] = tab[value % base];
		value = value / (uintmax_t)base;
	}
	res[size] = tab[value % base];
	return (res);
}
