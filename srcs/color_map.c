/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 16:17:45 by gtorresa          #+#    #+#             */
/*   Updated: 2016/02/09 16:27:48 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_data	*read_c_color(t_data *data)
{
	C_SP = 20;
	data->p.color_ref = (int*)malloc(sizeof(data->p.color_ref) * 20);
	data->p.color_ref[0] = 16025622;
	data->p.color_ref[1] = 15697162;
	data->p.color_ref[2] = 15360016;
	data->p.color_ref[3] = 15022613;
	data->p.color_ref[4] = 14685467;
	data->p.color_ref[5] = 11735099;
	data->p.color_ref[6] = 8784988;
	data->p.color_ref[7] = 5900413;
	data->p.color_ref[8] = 2950302;
	data->p.color_ref[9] = 16428832;
	data->p.color_ref[10] = 14604544;
	data->p.color_ref[11] = 16541348;
	data->p.color_ref[12] = 9105664;
	data->p.color_ref[13] = 7272960;
	data->p.color_ref[14] = 5831216;
	data->p.color_ref[15] = 4389472;
	data->p.color_ref[16] = 2947729;
	data->p.color_ref[17] = 1505985;
	data->p.color_ref[18] = 64242;
	data->p.color_ref[19] = 4242;
	return (data);
}
