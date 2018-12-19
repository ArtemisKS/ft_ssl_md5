/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 20:01:34 by akupriia          #+#    #+#             */
/*   Updated: 2017/11/10 20:01:35 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_power(int n, int pow)
{
	double res;

	res = 1;
	if (pow == 0)
		return (1);
	if (pow < 0)
		res /= ft_power(n, pow * (-1));
	if (pow > 0)
		while (pow)
		{
			res *= n;
			pow--;
		}
	return (res);
}
