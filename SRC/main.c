/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:48:49 by lvon-war          #+#    #+#             */
/*   Updated: 2024/04/22 11:29:42 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//do thing every frame
int	animation(t_data *d, int frame)
{
	static t_RGB	color;

	if (frame == 100000)
		frame = 0;
	if (frame % 10 == 0)
	{
		color = int_to_rgb(rand());
		if (d->world.nb_sprite > 0)
			sprite_edit(d, 0, sprite_create((t_point2d){10, WH - 210},
					(t_point2d){200, 200}, color));
	}
	if (frame % 2 == 0)
	{
		raycast(d);
		clear_img(d);
		display_world_object(d);
		display_world_sprite(d);
		if (d->option.minimap)
			display_minimap(d);
		displayimg(d);
	}
	return (frame);
}

int	loopydyloop(void *param)
{
	struct data		*d;
	static int		frame;

	frame++;
	d = (t_data *)param;
	frame = animation(d, frame);
	return (0);
}

// int	main(void)
// {
// 	t_data	*data;

// 	data = initdata();
// 	init_world(data);
// 	minimap_init(data);
// 	player_init(data);
// 	initoption(data);
// 	clear_img(data);
// 	test(data);
// 	raycast(data);
// 	mlx_key_hook(data->win.ptr, &keyhook, data);
// 	mlx_loop_hook(data->win.mlx, loopydyloop, data);
// 	mlx_loop(data->win.mlx);
// 	free_data(data);
// 	error_handler("Failed to init data", 1);
// 	return (0);
// }
//Main pour test le parsing
int main(int argc, char **argv)
{
	t_map *map = init_parsing();
	parsing_cub(argc,argv, map);
	free_map(map);

}