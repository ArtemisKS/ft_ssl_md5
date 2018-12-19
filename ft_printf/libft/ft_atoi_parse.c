/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 12:45:04 by angavrel          #+#    #+#             */
/*   Updated: 2017/05/28 07:19:53 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_parse(char **s)
{
	int		sign;
	int		r;

	r = 0;
	sign = 1;
	if (**s == '-' || **s == '+')
		sign = 44 - *(*s)++;
	while (**s >= '0' && **s <= '9')
		r = r * 10 + *(*s)++ - '0';
	return (sign * r);
}
