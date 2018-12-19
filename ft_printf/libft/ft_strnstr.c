/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 20:29:30 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/24 20:29:32 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t slen)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	if (!to_find[i])
		return ((char*)str);
	while (str[i] != '\0' && j < slen - ft_strlen((char*)to_find) + 1)
	{
		if (slen < ft_strlen((char*)to_find))
			return (NULL);
		while (*(str + i) == *(to_find + i))
			if (*(to_find + i + 1) == '\0')
				return ((char*)str);
			else if (*(str + i++) == '\0')
				return (0);
		str++;
		j++;
		i = 0;
	}
	return (0);
}
