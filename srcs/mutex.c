/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 08:17:45 by gtorresa          #+#    #+#             */
/*   Updated: 2016/02/11 12:48:58 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

pthread_mutex_t		*get_mutex(int rw)
{
	static pthread_mutex_t	t_mutex = PTHREAD_MUTEX_INITIALIZER;

	return (&t_mutex);
}
