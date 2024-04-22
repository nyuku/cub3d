/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:17:14 by angnguye          #+#    #+#             */
/*   Updated: 2024/04/22 18:58:52 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
int	parsing_cub(int argc, char **argv, t_map *map)
{
	int	line_texture;

	line_texture = 0;
	if (argc != 2)
		error_handler("Pas le bon nbre d'arguments\n", 1);
	
	int line_p = map_count_line(argv[1]);
	check_map_ext(argv[1], "cub");
	check_map_ext(argv[1], "jpg");
	check_map_ext(argv[1], "png");
	init_map_cub(argv[1], map, line_p);
	if (check_texture(map, &line_texture) == ERROR)
	{
		free_map(map);
		return (ERROR);
	}
	
	// ft_printf("\nVoici le path de North:%s\n", map->texture_north);
	// ft_printf("Voici le path de South:%s\n", map->texture_south);
	// ft_printf("Voici le path de West:%s\n", map->texture_west);
	// ft_printf("Voici le path de East:%s\n", map->texture_east);

	// ft_printf("Voici les coordonnés de Floor %d-%d-%d\n", map->floor_color->r,map->floor_color->g,map->floor_color->b);
	// ft_printf("Voici les coordonnés de Ceiling  %d-%d-%d\n", map->ceiling_color->r,map->ceiling_color->g,map->ceiling_color->b);
	
	// ft_printf("\n\n\n\n-------------------------------------------------------------\n\t\t\ttableau receuilli\n");
	// ft_printf("longueur du tableau : %d\n", map->map_nb_lines);
	// on a r4cuperer l'integralite du fichier
	
	// int i = 0;
	// while (map->map[i] != NULL)
    // {
    //     ft_printf("%s\n", map->map[i]); 
    //     i++;
    // }
	// ft_printf("\n");
	int m = 0;
	m =check_carte(map, line_texture);
	init_mapping(m, map);
	t_point_pars p;
	p.player_j = 0;  // Remplace valeur_initiale_x par la valeur désirée
	p.player_i = 0; 
	path_finding(map, p);
	return (SUCCESS);
}

// -check- l'extension "ext"
//[c,u,b] et [x,p,m]
int	check_map_ext(char *argv, char *ext)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	// if ((argv[i - 1] != ext[2]) \
	// && (argv[i - 2] != ext[1]) && (argv[i - 3] != ext[0]))
	// {
	// 	ft_printf("ext: %s\n", ext);
	// 	error_handler("Error: wrong files extensions", 1);
	// 	return(ERROR);
	// }
	// return (SUCCESS);
	if ((argv[i - 1] == ext[2]) \
	&& (argv[i - 2] == ext[1]) && (argv[i - 3] == ext[0]))
	{
		
		return (SUCCESS);
		
	}
	// ft_printf("ext: %s\n", ext);
	// error_handler("Error: wrong files extensions", 1);
	return(ERROR);
}

// -launcher- lit le tableau et check si les elements de textures
int	check_texture(t_map *map, int *line_texture)
{
	int		e;// pour lire le fichier ligne par ligne
	int		count; // texture
	int		texture;//indice de check
	char	**map_tab;

	texture = 0;
	e = 0;
	count = 0;
	map_tab = map->map;
	while (map_tab && (count < 6))
	{
		//boucle pour passer toute les strucxture...mais garanti pas 1
		texture = 0;
		// int i = 0;
		while (map_tab[e] && *(skip_space(map_tab[e])) == '\0')  //(map_tab[e][0] == '\0' || map_tab[e][0] == '\n' || map_tab[e][0] == ' ' || map_tab[e][0] == '\t')) {
        	e++;
		while(texture <= 4)
		{
			
			if (set_texture(map_tab[e], map, &texture) == SUCCESS)// probleme si vide
			{
				count++;
				break;
			}
			texture++;
		}
		if (count == 0)
		{
			error_handler("must have texture at the begenning and .xpm files\n",1);
			return (ERROR);
		}
		e++;
	}
	*line_texture = e;
	if (count != 6)
	{
		error_handler("wrong texture\n", 1);
		return (1);
	}
	return (SUCCESS);
}

// -check- NO, SO, WE, EA, F, C
//check un a la fois... et si doublon
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

	if (!str)
		return (ERROR);
	str = skip_space(str);
	if (*str == '\0')
	{
		//ft_printf("plop1\n");
		return (ERROR);
		
	}
	if (*texture <= 4 && ft_strncmp(str, identifiers[*texture], 2) == 0)
	{
		if (check_map_ext(str,"jpg")== SUCCESS)
		{
			error_handler("jpeg not supported\n",1);
		}
		if (check_map_ext(str,"png")== SUCCESS)
		{
			error_handler("png not supported\n",1);
		}
		if (check_map_ext(str, "xpm") == SUCCESS)
		{	
			if(*texture_pointers[*texture] == NULL)
			{	
				*texture_pointers[*texture] = ft_strdup(skip_space(str + 2));
				(*texture)++;
				return (SUCCESS);
			}
			error_handler("texture deja présente\n",1);
			return(ERROR);
		}
		

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
