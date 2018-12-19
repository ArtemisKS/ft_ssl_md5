/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 21:30:06 by akupriia          #+#    #+#             */
/*   Updated: 2017/09/25 21:30:07 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;

	i = 0;
	if (!to_find[i])
		return ((char*)str);
	while (str[i] != '\0')
	{
		while (*(str + i) == *(to_find + i))
			if (*(to_find + i + 1) == '\0')
				return ((char*)str);
			else if (*(str + i++) == '\0')
				return (0);
		str++;
		i = 0;
	}
	return (0);
}
