/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:58:24 by angela            #+#    #+#             */
/*   Updated: 2024/04/03 00:05:57 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
//a repere un player N,W,E.S... peut seulemeny y avoir 1.
//gerer espace enlever par ngl

// int is_struc(char *str)
// {
// 	char	*identifiers[6];
//     int		i;

// 	i=0;
// 	identifiers[0] = "NO";
// 	identifiers[1] = "SO";
// 	identifiers[2] = "WE";
// 	identifiers[3] = "EA";
// 	identifiers[4] = "F";
// 	identifiers[5] = "C";
// 	str = skip_space(str);
// 	while(i < 6)
//     {
// 		if (ft_strncmp(str, identifiers[i], 2) == 0)
// 			return (SUCCESS);
// 		i++;
// 		ft_printf("plop\n");
// 	}
// 	ft_printf("ce n'et pas un element\n");
// 	return (ERROR);
// }
// int check_character(char *str)
// {
//     while(*str)
//     {
//         if (!((*str == '1') || (*str == '0') || (*str == ' ') || (*str == '\t')))
//             return (ERROR);
//         str++;
// 		error_handler("toujours un bon caracger\n",1);
//     }
//     return (SUCCESS);
// }

// // va lire la map depuis le bas? on a deja receuillk dans un tableau
// //probleme mon gnl a viré tout les retour a la ligne
// int   check_carte(t_map *map)
// {
//     int i;
//     int count;

//     count = 0;
//     i = map->map_nb_lines;
// 	ft_printf("nombre de ligne%d\n",map->map_nb_lines);
//     while (i > 0)
//     {
//         if (check_character(map->map[i]) == ERROR)
//         {
//             error_handler("map with wrong character\n",1);
//         }
// 		if (is_struc(map->map[i])== ERROR)
// 		{
// 			error_handler("pas dde map\n",1);
// 		}
//         i--;
//         count++;
//     }
// 	ft_printf("count : %d\n", count);
//     return (count);
// }

int is_struc(char *str) {
    char *identifiers[6] = {"NO", "SO", "WE", "EA", "F", "C"};
    int i = 0;
    str = skip_space(str); // Assurez-vous que cette fonction ignore correctement les espaces et les tabulations
    while (i < 6) {
        if (ft_strncmp(str, identifiers[i], ft_strlen(identifiers[i])) == 0) // Utilisez la longueur de l'identifiant
            return (SUCCESS); // Trouvé un identifiant de configuration
        i++;
    }
    return (ERROR); // Aucun identifiant de configuration trouvé
}

// Vérifiez chaque ligne de la carte pour s'assurer qu'elle contient uniquement '1', '0', ' ' ou '\t'
int check_character(char *str) {
    while (*str) {
        if (!(*str == '1' || *str == '0' || *str == ' ' || *str == '\t'))
            return (ERROR);
        str++;
    }
    return (SUCCESS);
}

// Parcourt la carte de bas en haut jusqu'à ce qu'un identifiant de configuration soit trouvé
int check_carte(t_map *map) {
    int i = map->map_nb_lines - 1; // Assurez-vous que l'indexation commence à 0
    //int count = 0;
    while (i >= 0) {
        if (is_struc(map->map[i]) == SUCCESS) // Si la ligne actuelle est un élément de configuration, arrêtez la vérification
            break;
        if (check_character(map->map[i]) == ERROR) {
            error_handler("map with wrong character\n", 1);
            return (ERROR); // Retournez immédiatement en cas d'erreur
        }
        i--;
       // count++;
    }
    if (i < 0) { // Si i est < 0, cela signifie que nous n'avons pas trouvé d'identifiant de configuration
        error_handler("No configuration identifier found\n", 1);
        return (ERROR);
    }
    return (SUCCESS); // Retournez SUCCESS si tout est correct
}
