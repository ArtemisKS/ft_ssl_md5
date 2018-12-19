/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:00:31 by akupriia          #+#    #+#             */
/*   Updated: 2017/11/07 18:00:32 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tl;
	t_list *ntl;

	if (alst && *alst && del)
	{
		tl = *alst;
		while (tl)
		{
			ntl = tl->next;
			del((tl)->content, (tl)->content_size);
			free(tl);
			tl = ntl;
		}
		*alst = NULL;
	}
}
