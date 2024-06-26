/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:58:24 by angela            #+#    #+#             */
/*   Updated: 2024/04/15 13:22:56 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdbool.h>
#include <stdlib.h>


int	init_mapping(int i, t_map *map)
{
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
	map->mapping_size = (map->end_map - i) +1;// decallage..
	if (map->mapping_size < 3)
	{
		error_handler("empty map\n",1);
		return(ERROR);
	}
	map->mapping =  ft_calloc(map->map_size + 1, sizeof(char *));//i
	if (!map->mapping)
		return (ERROR);
	while (map->map[i]) // jusqua la fin..depart depuis debut map
	{
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

// Vérifiez depuis le bas chaque ligne de la carte pour s'assurer qu'elle contient uniquement '1', '0', ' ' ou '\t'
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
				str++;
			}
			else
			{
				error_handler("too much player\n",1);
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
//line_texture, la ligne ou la derniere texture a été lu
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
    if (map->player_orientation == '-')
	{ 
        error_handler("No player found\n", 1);
        return (ERROR);
    }
	
	// ft_printf("valeur de i: %d\n",i);
    return (i); //la position du debut de la map
}
