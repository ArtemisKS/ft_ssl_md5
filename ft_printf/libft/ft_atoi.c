/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 16:36:15 by akupriia          #+#    #+#             */
/*   Updated: 2017/09/25 16:36:16 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	cycle(const char *str, int i, unsigned long int a, int b)
{
	while ((str[i] > 47 && str[i] < 58))
	{
		if ((a > 922337203685477580 ||
			(a == 922337203685477580 && str[i] - 48 > 7)) && b == 1)
			return (-1);
		else if ((a > 922337203685477580 ||
			(a == 922337203685477580 && str[i] - 48 > 8)) && b == -1)
			return (0);
		a *= 10;
		a += (str[i] - 48);
		i++;
	}
	return (a * b);
}

int			ft_atoi(const char *str)
{
	int					i;
	unsigned long int	a;
	int					b;

	a = 0;
	b = 1;
	i = 0;
	while (str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\r' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		b = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	if (!(str[i] > 47 && str[i] < 58))
		return (0);
	a = cycle(str, i, a, b);
	return (a);
}
