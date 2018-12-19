/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 12:13:21 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/04 12:13:36 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr_start(const char *str, const char *to_find)
{
	int i;

	i = 0;
	if (!to_find[i])
		return ((char*)str);
	while (*(str + i) == *(to_find + i))
		if (*(to_find + i + 1) == 0)
			return ((char*)str);
		else if (*(str + i++) == 0)
			return (0);
	return (0);
}
