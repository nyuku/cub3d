/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnguye <angnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:17:14 by angnguye          #+#    #+#             */
/*   Updated: 2024/04/01 22:19:39 by angnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// check l'extension "ext"
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

// lis la map receuilli et check si les elements de textures sont correct
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

//Bigmama
//recupere la str de couleur, converti en int
//vérifie s que chiffre et dans bon scope
//verifie bien 3 chiffre
//remet dans un int * le contenu selon F OU C
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

// skip potentielle espace avant indice, puis re skip pour avoir le path
// check que ce soit que ce qu'on cherche

int	set_texture(char *str, t_map *map, int *texture)
{
	char	**texture_pointers;
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
/*
big mama
note:
- Appel de fonction en main?
- nb: init "t_map" qq part
- appel de fonction:
	if (!parsing_map(argc,argv)
		return(exit_game)

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
	if (argc != 2)
		error_handler("Pas le bon nbre d'arguments\n", 1);
	check_map_ext(argv[1], "cub");
	init_map_cub(argv[1], map);
	check_texture(map);
	return (SUCCESS);
}

//int main(int argc, char **argv)
//{
//	t_map *map = malloc(sizeof(t_map));
//    if (map == NULL)
//        return (printf("beurk\n"));
//
//	printf("plop\n");
//	parsing_cub(argc,argv, map);
//
//	printf("Voici le path de North: %s\n", map->texture_north);
//	printf("Voici le path de South: %s\n", map->texture_south);
//	printf("Voici le path de West: %s\n", map->texture_west);
//	printf("Voici le path de East: %s\n", map->texture_east);
////	printf("Voici les coordonnés de Floor %s\n", map->floor_color);
////	printf("Voici les coordonnés de Ceiling %s\n", map->ceiling_color);
//
//	return (0);
//}