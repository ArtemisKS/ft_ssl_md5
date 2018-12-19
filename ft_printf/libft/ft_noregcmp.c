/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_noregcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:50:29 by akupriia          #+#    #+#             */
/*   Updated: 2017/11/10 19:50:41 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_noregcmp(const char *s1, const char *s2)
{
	char	*ss1;
	char	*ss2;
	int		i;

	ss1 = (char*)s1;
	ss2 = (char*)s2;
	i = 0;
	while (ss1[i])
	{
		ss1[i] = ft_tolower(ss1[i]);
		i++;
	}
	i = 0;
	while (ss2[i])
	{
		ss2[i] = ft_tolower(ss2[i]);
		i++;
	}
	return (ft_strcmp(ss1, ss2));
}
