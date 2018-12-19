/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:20:45 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/24 19:20:46 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int sym)
{
	while (*str)
	{
		if (*str == sym)
			return ((char*)str);
		str++;
	}
	if (*str == sym)
		return ((char*)str);
	return (NULL);
}
