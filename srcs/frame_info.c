/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 11:02:32 by gtorresa          #+#    #+#             */
/*   Updated: 2016/01/21 16:27:28 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		ft_print_text(t_data d, char *name, char *value, int free_val)
{
	static int	x;
	static int	y;

	if (ft_strlen(name) == 0)
	{
		x = 35;
		y = 35;
	}
	else
		y += 20;
	mlx_string_put(d.mlx, d.win, x, y, 0x505050, name);
	mlx_string_put(d.mlx, d.win, x + 100, y, 0x505050, value);
	if (free_val == 1)
		free(value);
	return (y);
}

void	get_frame_info(t_data d)
{
	int		y;

	mlx_string_put(d.mlx, d.win, 35, 35, 0x505050, "Quit = esc");
	y = ft_print_text(d, "", "", 0);
	y = ft_print_text(d, "Filename:", d.filename, 0);
	y = ft_print_text(d, "mouse_x :", ft_itoa(d.mouse_x), 1);
	y = ft_print_text(d, "mouse_y :", ft_itoa(d.mouse_y), 1);
	y = ft_print_text(d, "Map_x   :", ft_itoa(d.p.posx[0]), 1);
	y = ft_print_text(d, "Map_y   :", ft_itoa(d.p.posy[0]), 1);
	y = ft_print_text(d, "Zoom    :", ft_itoa(d.p.zoom), 1);
	y = ft_print_text(d, "Scale   :", ft_itoa(d.p.scale * 1000), 1);
	y = ft_print_text(d, "Rot     :", ft_itoa(d.p.rot * 100), 1);
	y = ft_print_text(d, "C_index :", ft_itoa(d.p.c_index), 1);
	mlx_string_put(d.mlx, d.win, 35, y + 20, 0x505050, "Color   :");
	draw_full_rec(&d, 135, y + 20, d.p.color_ref[d.p.c_index]);
}
