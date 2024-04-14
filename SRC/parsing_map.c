/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:58:24 by angela            #+#    #+#             */
/*   Updated: 2024/04/09 13:46:42 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdbool.h>
#include <stdlib.h>

// int check_direction(t_map *map, int pos_y, int pos_x, int move_y, int move_x)
// {
//     while (pos_x >= 0 && pos_x < ft_strlen(map->mapping[pos_y]) && pos_y >= 0 && pos_y < map->map_size) {
//         if (map->mapping[pos_y][pos_x] == '1') {
//             return 0; // Mur trouvé, chemin bloqué
//         }
//         if (map->mapping[pos_y][pos_x] == ' ' || map->mapping[pos_y][pos_x] == '\n') {
//             return 1; // Chemin ouvert trouvé
//         }
//         pos_x += move_x;
//         pos_y += move_y;
//     }
//     return 1; // Bord atteint sans trouver de mur, chemin ouvert
// }
// int check_left(t_map *map, int pos_y, int pos_x) {
//     return check_direction(map, pos_y, pos_x, 0, -1);
// }

// int check_right(t_map *map, int pos_y, int pos_x) {
//     return check_direction(map, pos_y, pos_x, 0, 1);
// }

// int check_up(t_map *map, int pos_y, int pos_x) {
//     return check_direction(map, pos_y, pos_x, -1, 0);
// }

// int check_down(t_map *map, int pos_y, int pos_x) {
//     return check_direction(map, pos_y, pos_x, 1, 0);
// }
// int check_directions(t_map *map, int pos_y, int pos_x) {
//     if (check_left(map, pos_y, pos_x) == 1) {
//         error_msg(9);
//     }
//     if (check_right(map, pos_y, pos_x) == 1) {
//         error_msg(9);
//     }
//     if (check_up(map, pos_y, pos_x) == 1) {
//         error_msg(9);
//     }
//     if (check_down(map, pos_y, pos_x) == 1) {
//         error_msg(9);
//     }
//     return 0;
// }



// int flood_fill(t_map *map, bool **marked, int x, int y) {
//     // Vérification initiale pour les limites de la carte et si la case a déjà été visitée
//     if (x < 0 || y < 0 || y >= map->map_size || x >= strlen(map->mapping[y]) || marked[y][x]) {
//         return SUCCESS; // Case invalide ou déjà visitée
//     }
//     // Si on rencontre un mur, arrêter
//     if (map->mapping[y][x] == '1') {
//         return SUCCESS;
//     }

//     // Marque la case actuelle comme visitée
//     marked[y][x] = true;

//     // Vérifications directionnelles adaptées du deuxième morceau de code
//     if (check_left(map, y, x) || check_right(map, y, x) || check_up(map, y, x) || check_down(map, y, x)) {
//         return ERROR; // Chemin ouvert trouvé
//     }

//     // Répétition de la vérification pour les cases adjacentes non murales et non marquées
//     int dx[] = {-1, 1, 0, 0};
//     int dy[] = {0, 0, -1, 1};
//     for (int i = 0; i < 4; i++) {
//         if (flood_fill(map, marked, x + dx[i], y + dy[i]) == ERROR) {
//             return ERROR;
//         }
//     }

//     // Si aucune erreur n'est trouvée dans les vérifications, continuer
//     return SUCCESS;
// }


void	find_player_coordinates(t_map *map)
{
    size_t	y;
	int		x;
	bool 	found;
	
	y = 0;
    found = false; // Indicateur pour savoir si le joueur a été trouvé
	while (map->mapping[y])
		y++;
	map->mapping_size = y;
	y = 0;
    while (map->mapping[y])//(y < map->map_size && !found)
	{
        x = 0;
        while (x < ft_strlen(map->mapping[y]) && !found)
		{
			if (map->mapping[y][x] == map->player_orientation)
			{
                map->player_x = x;
                map->player_y = y;
				map->p.player_i = x;
				map->p.player_j = y;
                found = true; // Le joueur a été trouvé
            }
            x++;
        }
        y++;
    }
}


// Structure pour représenter un point sur la carte
typedef struct
{
    int x, y;
} Point;

// Fonction pour initialiser le tableau de marquage
bool **init_marking_array(t_map *map)
{
    bool **marked = malloc(sizeof(char *) * map->map_size);
	size_t i;
    for (i = 0; i < map->map_size; i++) 
	{
        marked[i] = ft_calloc(ft_strlen(map->mapping[i]) + 1, sizeof(bool));
    }

    return marked;
}


int	init_mapping(int i, t_map *map)
{
	//char	*tmp;
	int		m;
	
	m = 0;
	if (i < 3)
	{
		error_handler("ce n'est pas une map valide\n", 1);
		return (ERROR);
	}
	// map->mapping =  ft_calloc(i + 1, sizeof(char *));
	// if (!map->mapping)
	// 	return (ERROR);
    while (map->map[i])
	{
		map->map[i] = skip_space(map->map[i]);
		if (*map->map[i] == '\0')
				i++;
		else
			break;
	}
	map->mapping_size = (size_t)(map->end_map - i) +1;// decallage..
		ft_printf("taille de la map %d\n",map->mapping_size);
	map->mapping =  ft_calloc(map->map_size + 1, sizeof(char *));//i
	if (!map->mapping)
		return (ERROR);
	while (map->map[i]) // jusqua la fin..depart depuis debut map
	{
		// tmp = map->map[i];
		// while (*tmp == ' ' || *tmp == '\t')
		// 	tmp++;
		// if (*tmp != '\n' && *tmp != '\0')
		map->mapping[m] = ft_strdup(map->map[i]);
		i++;
		m++;
	}
	return (SUCCESS);
	
}

//vérifie qu'on est toujours en train de lire la map
//return error
int	is_struc(char *str)
{
    char	*identifiers[6];
	int		i;
	
	identifiers[0] = "NO";
	identifiers[1] = "SO";
	identifiers[2] = "WE";
	identifiers[3] = "EA";
	identifiers[4] = "F";
	identifiers[5] = "C";
	i = 0;
    str = skip_space(str);
    while (i <= 5) // <= ?
	{
         //ft_printf("je test la str suivante %s\n", str);
		if (ft_strncmp(str, identifiers[i], ft_strlen(identifiers[i])) == 0)
        {
			ft_printf("on a trouvé le caractere %s\n", identifiers[i]);
			return (SUCCESS);
		}
		//  ft_printf("je suis en train de test le caractere %s\n", identifiers[i]);
        i++;

    }
    return (ERROR);
}

// Vérifiez chaque ligne de la carte pour s'assurer qu'elle contient uniquement '1', '0', ' ' ou '\t'
//check et init le player
int	check_character(char *str, t_map *map)
{
    while (*str)
	{
        if (*str == 'N' || *str == 'W' || *str == 'E' || *str == 'S')
		{
			if (map->player_orientation == '-')
			{
				map->player_orientation = *str;
				// ft_printf("on a trouvé le player\n");
				str++;
			}
			else
			{
				// ft_printf("on a deja un player\n");
				return (ERROR);
			}
		}
		if (!(*str == '1' || *str == '0' || *str == ' ' || *str == '\t'))
        {
			ft_printf("on a une map avec d'autres caractere\n");
			return (ERROR);
		}
        str++;
    }
    return (SUCCESS);
}

// Parcourt la carte de bas en haut jusqu'à ce qu'un identifiant de configuration soit trouvé
//retourne 
int	check_carte(t_map *map, int line_texture)
{
    int	i;
	
	i = map->map_nb_lines -1;
	//faudrait pouvoir skip les vide de fin
	while (i > line_texture)
	{
		map->map[i] = skip_space(map->map[i]);
		if (*map->map[i] == '\0')
				i--;
		else
			break;
	}
	map->end_map = i;

    while (i > line_texture && map->map[i])
	{
		// ft_printf("je suis a cette str :%s de la ligne %d\n", map->map[i],i);
		if (check_character(map->map[i], map) == ERROR)
		{
			error_handler("map with wrong character\n", 1);
            return (ERROR);
        }
		else
			i--;
    }
    if (i < 0)
	{ 
        error_handler("No configuration identifier found\n", 1);
        return (ERROR);
    }
	
	// ft_printf("valeur de i: %d\n",i);
    return (i); //la position du debut de la map
}
