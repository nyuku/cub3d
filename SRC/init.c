/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:24:15 by lvon-war          #+#    #+#             */
/*   Updated: 2024/03/29 16:42:15 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_world(t_data *d)
{
	d->world.spawn = (t_point){0, 0, 0};
	d->world.size.x = 100 * d->scale;
	d->world.size.y = 100 * d->scale;
	d->world.earth = 0xbf9c6d;
	d->world.sky = 0x9deaed;
	d->world.nb_obj = 0;
	d->world.nb_sprite = 0;
	d->render_distance = (d->world.size.x + d->world.size.y) / 4;
}

#include <stdio.h>
t_data	*initdata(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		error_handler("Failed to init data", 1);
	data->win.mlx = mlx_init();
	data->win.ptr = mlx_new_window(data->win.mlx, WL, WH, "My Window");
	data->img.img = mlx_new_image(data->win.mlx, WL, WH);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_size, &data->img.endian);
	mlx_hook(data->win.ptr, CLOSE_WINDOW_KEY, 0, &exit_hook, NULL);
	mlx_key_hook(data->win.ptr, &keyhook, NULL);
	data->width = WL;
	data->height = WH;
	data->fov = 90;
	data->scale = WL * 0.1;
	data->focal = data->width * 0.5 / tan(degtorad(data->fov * 0.5));
	return (data);
}
