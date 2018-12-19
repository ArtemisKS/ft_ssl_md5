/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uni.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:58:58 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:58:59 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		size_bin(int value)
{
	char	*vbin;
	int		len;

	vbin = ft_itoa_base(value, 2);
	len = ft_strlen(vbin);
	ft_strdel(&vbin);
	return (len);
}

char	*print_uni_7(int value, t_spec *ts, int i)
{
	unsigned char	octet;
	char			*res;

	octet = value;
	res = (char *)ft_strnew(5);
	res[0] = octet;
	ts->ia[i]++;
	return (res);
}

char	*print_uni_11(int value, t_spec *ts, int i, t_uni *tu)
{
	unsigned int	v;
	unsigned char	octet;
	char			*res;

	v = value;
	tu->o2 = (v << 26) >> 26;
	tu->o1 = ((v >> 6) << 27) >> 27;
	octet = (tu->mask1 >> 8) | tu->o1;
	res = (char *)ft_strnew(5);
	res[0] = octet;
	ts->ia[i]++;
	octet = ((tu->mask1 << 24) >> 24) | tu->o2;
	res[1] = octet;
	ts->ia[i]++;
	return (res);
}

char	*print_uni_16(int value, t_spec *ts, int i, t_uni *tu)
{
	unsigned int	v;
	unsigned char	octet;
	char			*res;

	v = value;
	tu->o3 = (v << 26) >> 26;
	tu->o2 = ((v >> 6) << 26) >> 26;
	tu->o1 = ((v >> 12) << 28) >> 28;
	octet = (tu->mask2 >> 16) | tu->o1;
	res = (char *)ft_strnew(5);
	res[0] = octet;
	ts->ia[i]++;
	octet = ((tu->mask2 << 16) >> 24) | tu->o2;
	res[1] = octet;
	ts->ia[i]++;
	octet = ((tu->mask2 << 24) >> 24) | tu->o3;
	res[2] = octet;
	ts->ia[i]++;
	return (res);
}

char	*print_uni_21(int value, t_spec *ts, int i, t_uni *tu)
{
	unsigned int	v;
	unsigned char	octet;
	char			*res;

	v = value;
	tu->o4 = (v << 26) >> 26;
	tu->o3 = ((v >> 6) << 26) >> 26;
	tu->o2 = ((v >> 12) << 26) >> 26;
	tu->o1 = ((v >> 18) << 29) >> 29;
	octet = (tu->mask3 >> 24) | tu->o1;
	res = (char *)ft_strnew(10);
	res[0] = octet;
	ts->ia[i]++;
	octet = ((tu->mask3 << 8) >> 24) | tu->o2;
	res[1] = octet;
	ts->ia[i]++;
	octet = ((tu->mask3 << 16) >> 24) | tu->o3;
	res[2] = octet;
	ts->ia[i]++;
	octet = ((tu->mask3 << 24) >> 24) | tu->o4;
	res[3] = octet;
	ts->ia[i]++;
	return (res);
}
