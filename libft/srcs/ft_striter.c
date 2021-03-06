/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:43:12 by gtorresa          #+#    #+#             */
/*   Updated: 2015/12/03 19:27:48 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	while (*s)
	{
		(*f)(s);
		s++;
	}
}
