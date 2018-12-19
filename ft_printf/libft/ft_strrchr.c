/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:45:40 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/24 19:45:41 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int sym)
{
	int i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	while (i >= 0)
	{
		if (*str == sym)
			return ((char*)str);
		str--;
		i--;
	}
	return (NULL);
}
