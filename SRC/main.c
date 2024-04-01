/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:48:49 by lvon-war          #+#    #+#             */
/*   Updated: 2024/03/29 17:20:49 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//remove after testing
void	test(t_data *d)
{
	t_RGB	**texture;

	texture = malloc(sizeof(t_RGB *) * 4);
	if (!texture)
		error_handler("Failed to init data", 1);
	texture[0] = texture_monchrome_create((t_point2d){100, 100},
			int_to_rgb(RED));
	texture[1] = texture_monchrome_create((t_point2d){100, 100},
			int_to_rgb(GREEN));
	texture[2] = texture_monchrome_create((t_point2d){100, 100},
			int_to_rgb(BLUE));
	texture[3] = texture_monchrome_create((t_point2d){100, 100},
			int_to_rgb(RED));
	sprite_add(d, sprite_create((t_point2d){10, WH - 210},
			(t_point2d){200, 200}, int_to_rgb(BLUE)));
	object_add(d, object_create((t_point){40 * d->scale, 0.5 * d->scale, 50 * d->scale},
			(t_point){1 * d->scale, 1 * d->scale, 1 * d->scale}, texture));
	object_add(d, object_create((t_point){50 * d->scale, 5 * d->scale, 50 * d->scale},
			(t_point){10 * d->scale, 10 * d->scale, 10 * d->scale}, texture));
}

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
	display_world_object(d);
	display_world_sprite(d);
	display_minimap(d);
	displayimg(d);
	return (0);
}

//int	main(void)
//{
//	t_data	*data;
//
//	data = initdata();
//	init_world(data);
//	minimap_init(data);
//	player_init(data);
//	clear_img(data);
//	test(data);
//	raycast(data);
//	mlx_key_hook(data->win.ptr, &keyhook, data);
//	mlx_loop_hook(data->win.mlx, loopydyloop, data);
//	mlx_loop(data->win.mlx);
//	free_data(data);
//	error_handler("Failed to init data", 1);
//	return (0);
//}


//parsing test
int main(int argc, char **argv)
{
	t_map *map = malloc(sizeof(t_map));
	t_map *color = malloc(sizeof(color));
	if (map == NULL)
		return (ft_printf("beurk\n"));

	map->floor_color = malloc(sizeof(t_color));
	if (map->floor_color == NULL) {
		free(map); // N'oublie pas de libérer la mémoire allouée précédemment
		return (ft_printf("Erreur d'allocation pour floor_color\n"));
	}

// Allocation et initialisation de ceiling_color
	map->ceiling_color = malloc(sizeof(t_color));
	if (map->ceiling_color == NULL) {
		free(map->floor_color); // Libère la mémoire allouée précédemment
		free(map); // N'oublie pas de libérer la mémoire allouée précédemment
		return (ft_printf("Erreur d'allocation pour ceiling_color\n"));
	}


	parsing_cub(argc,argv, map);

	ft_printf("Voici le path de North: %s\n", map->texture_north);
	ft_printf("Voici le path de South: %s\n", map->texture_south);
	ft_printf("Voici le path de West: %s\n", map->texture_west);
	ft_printf("Voici le path de East: %s\n", map->texture_east);

	ft_printf("Voici les coordonnés de Floor %d-%d-%d\n", map->floor_color->r,map->floor_color->g,map->floor_color->b);
	ft_printf("Voici les coordonnés de Ceiling  %d-%d-%d\n", map->ceiling_color->r,map->ceiling_color->g,map->ceiling_color->b);

	return (0);
}