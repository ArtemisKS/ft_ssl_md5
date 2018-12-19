/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:59:37 by akupriia          #+#    #+#             */
/*   Updated: 2017/11/02 19:59:38 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int u_n;

	u_n = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		u_n *= (-1);
	}
	if (u_n > 9)
	{
		ft_putnbr_fd(u_n / 10, fd);
	}
	ft_putchar_fd(u_n % 10 + '0', fd);
}
