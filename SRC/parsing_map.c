/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnguye <angnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:58:24 by angela            #+#    #+#             */
/*   Updated: 2024/04/03 21:22:24 by angnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
         ft_printf("je test la str suivante %s\n", str);
		if (ft_strncmp(str, identifiers[i], ft_strlen(identifiers[i])) == 0)
        {
			ft_printf("on a trouvé le caractere %s\n", identifiers[i]);
			return (SUCCESS);
		}
		 ft_printf("je suis en train de test le caractere %s\n", identifiers[i]);
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
    while (i > 0 && map->map[i])
	{
        i--;
		if (is_struc(map->map[i]) == SUCCESS)//passe le contrle x6
        {
			ft_printf("valeur de i : %d\n",i);
			error_handler("oh nooo on est dans les textures\n",1);
			return (i);//la position du debut de la map bonne fin (map->nb_line - i-1) dans le tableau.pas .cub
		}
        else if (check_character(map->map[i], map) == ERROR)
		{
            ft_printf("valeur de i : %d\n",i);
			error_handler("map with wrong character\n", 1);
            return (ERROR);
        }
    }
    if (i < 0)
	{ // Si i est < 0, cela signifie que nous n'avons pas trouvé d'identifiant de configuration
        error_handler("No configuration identifier found\n", 1);
        return (ERROR);
    }
	ft_printf("manque les textures :(\n"); // mais deja traité si pas de texture
	
    return (ERROR); //la position du debut de la map
}
