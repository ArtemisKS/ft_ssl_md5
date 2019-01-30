/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:57:31 by akupriia          #+#    #+#             */
/*   Updated: 2019/01/30 15:13:41 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "ft_ssl.h"
#define A 					0
#define B 					1
#define C 					2
#define D 					3
#define F(B, C, D) 			((B) & (C)) | (~(B) & (D))
#define G(B, C, D) 			((B) & (D)) | ((C) & ~(D))
#define H(B, C, D) 			(B) ^ (C) ^ (D)
#define I(B, C, D) 			(C) ^ (B | ~(D))

#define UINT32_BIT			(sizeof(uint32_t) * 8)
#define ROTATE_LEFT(x, n)	(((x) << (n)) | ((x) >> (32-(n))))

#endif