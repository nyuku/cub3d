/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnguye <angnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:17:14 by angnguye          #+#    #+#             */
/*   Updated: 2024/04/04 19:14:21 by angnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

/*
-Main parsing-
note:
- nb: init "t_map" qq part

But:
- stocke la map->struct
- check extension
- présence d'une map
- présence des élements de structures
- vérifiér viabilité
!
*/
int	parsing_cub(int argc, char **argv)
{
	if (argc != 2)
		error_handler("Pas le bon nbre d'arguments\n", 1);
	t_map *map;
	map = init_parsing();
	check_map_ext(argv[1], "cub");
	init_map_cub(argv[1], map);
	check_texture(map);
	
	// ft_printf("Voici le path de North: %s\n", map->texture_north);
	// ft_printf("Voici le path de South: %s\n", map->texture_south);
	// ft_printf("Voici le path de West: %s\n", map->texture_west);
	// ft_printf("Voici le path de East: %s\n", map->texture_east);

	// ft_printf("Voici les coordonnés de Floor %d-%d-%d\n", map->floor_color->r,map->floor_color->g,map->floor_color->b);
	// ft_printf("Voici les coordonnés de Ceiling  %d-%d-%d\n", map->ceiling_color->r,map->ceiling_color->g,map->ceiling_color->b);
	ft_printf("longueur du fichier %d\n", map->map_nb_lines);
	int i = 0;
	while (map->map[i] != NULL)
    {
        ft_printf("%s\n", map->map[i]); 
        i++;
    }
	ft_printf("\n");
	int m = check_carte(map);
	init_mapping(m, map);

	i = 0;
	while (map->mapping[i] != NULL)
    {
        ft_printf("%s\n", map->mapping[i]); 
        i++;
    }
	
	return (SUCCESS);
}

// -check- l'extension "ext"
//[c,u,b] et [x,p,m]
void	check_map_ext(char *argv, char *ext)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if ((argv[i - 1] != ext[2]) \
	&& (argv[i - 2] != ext[1]) && (argv[i - 3] != ext[0]))
		error_handler("Error: wrong files extensions", 1);
}

// -launcher- lis le tableau et check si les elements de textures
void	check_texture(t_map *map)
{
	int		e;
	int		count;
	int		texture;
	char	**map_tab;

	texture = 0;
	e = 0;
	count = 0;
	map_tab = map->map;
	while (map_tab && (count < 6))
	{
		if (!set_texture(map_tab[e], map, &texture))
		{
			count++;
		}
		else
			error_handler("wrong texture\n", 1);
		e++;
	}
}

// -check- NO, SO, WE, EA, F, C
int	set_texture(char *str, t_map *map, int *texture)
{
	char	**texture_pointers[4];
	char	*identifiers[4];

	texture_pointers[0] = &map->texture_north;
	texture_pointers[1] = &map->texture_south;
	texture_pointers[2] = &map->texture_west;
	texture_pointers[3] = &map->texture_east;
	identifiers[0] = "NO";
	identifiers[1] = "SO";
	identifiers[2] = "WE";
	identifiers[3] = "EA";
	str = skip_space(str);
	if (*texture <= 4 && ft_strncmp(str, identifiers[*texture], 2) == 0)
	{
		check_map_ext(str, "xpm");
		*texture_pointers[*texture] = ft_strdup(skip_space(str + 2));
		(*texture)++;
		return (SUCCESS);
	}
	else if ((ft_strncmp(str, "F ", 2) == 0) || (ft_strncmp(str, "C ", 2) == 0))
	{
		set_floor_ceiling(str, map);
		return (SUCCESS);
	}
	return (ERROR);
}

//-check- 
//-launcher- F et C si bien des nombre 0-255
void	set_floor_ceiling(char *str, t_map *map)
{
	int		*rgb;
	char	letter;

	letter = *str;
	rgb = set_color(str);
	if (rgb == NULL)
	{
		error_handler("pas reussi a recup les données RGB\n", 1);
		return ;
	}
	init_floor_ceiling(rgb, map, letter);
	free(rgb);
}
