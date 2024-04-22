/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:49:18 by angela            #+#    #+#             */
/*   Updated: 2024/04/22 18:16:32 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void free_map(t_map *map)
{
    int i;

    i = 0;
    if (map != NULL) 
	{
        if (map->texture_north != NULL)
			free(map->texture_north);
        if (map->texture_south != NULL)
			free(map->texture_south);
        if (map->texture_west != NULL)
			free(map->texture_west);
        if (map->texture_east != NULL)
			free(map->texture_east);
        if (map->floor_color != NULL)
			free(map->floor_color);
        if (map->ceiling_color != NULL)
			free(map->ceiling_color);

        if (map->map != NULL) 
		{
            while (i < map->map_nb_lines)
            {
                free(map->map[i]);
                i++;
            }
            free(map->map);
        }
        free(map);
    }
}

//init les structs...a mettre ailleurs dans un autre fichier
t_map	*init_parsing(void)
{
	t_map *map = malloc(sizeof(t_map));
	t_map *color = malloc(sizeof(color));
	if (map == NULL)
	{
		error_handler("peut pas malloc pour map\n", 1);
		return (NULL);
	}
	map->floor_color = malloc(sizeof(t_color));
	if (map->floor_color == NULL)
	{
		free(map);
		error_handler("Erreur d'allocation pour floor_color\n", 1);
		return (NULL);
	}
	map->texture_north = NULL;
    map->texture_south = NULL;
    map->texture_west = NULL;
    map->texture_east = NULL;
	
	map->ceiling_color = malloc(sizeof(t_color));
	if (map->ceiling_color == NULL) {
		free(map->floor_color);
		free(map);
		error_handler("Erreur d'allocation pour ceiling_color\n", 1);
		return (NULL);
	}
	map->player_orientation = '-';
	return(map);
}