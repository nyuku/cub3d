/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:58:24 by angela            #+#    #+#             */
/*   Updated: 2024/04/05 18:01:53 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
	map->mapping =  ft_calloc(i + 1, sizeof(char *));
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
    while (i <= 5)
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
				ft_printf("on a trouvé le player\n");
				str++;
			}
			else
			{
				ft_printf("on a deja un player\n");
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
int	check_carte(t_map *map)
{
    int	i;
	i = map->map_nb_lines;
	ft_printf("valeur de i : %d\n", i);
	i--;
    while (i >= 0 && map->map[i])
	{
		ft_printf("\n\n\nce qu'il y a dans la str: %s", map->map[i]);
		if (is_struc(map->map[i]) == SUCCESS)//passe le contrle x6
        {
			ft_printf("valeur de i, grandeur de la map et on a lu la map: %d\n",i);
			return (i+1);//la position du debut de la map bonne fin (map->nb_line - i-1) dans le tableau.pas .cub
		}
        else if (check_character(map->map[i], map) == ERROR)
		{
            ft_printf("valeur de i : %d\n",i);
			error_handler("map with wrong character\n", 1);
            return (ERROR);
        }
		i--;
    }
    if (i < 0)
	{ // Si i est < 0, cela signifie que nous n'avons pas trouvé d'identifiant de configuration
        error_handler("No configuration identifier found\n", 1);
        return (ERROR);
    }
	ft_printf("manque les textures :(\n"); // mais deja traité si pas de texture
	
    return (ERROR); //la position du debut de la map
}
