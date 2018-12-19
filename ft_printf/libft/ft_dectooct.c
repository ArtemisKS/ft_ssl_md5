/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dectooct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 20:17:27 by akupriia          #+#    #+#             */
/*   Updated: 2017/11/10 20:17:28 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_dectooct(int n)
{
	int		octal;
	int		rest;
	int		i;

	octal = 0;
	i = 1;
	while (n)
	{
		rest = n % 8;
		n /= 8;
		octal += rest * i;
		i *= 10;
	}
	return (octal);
}
