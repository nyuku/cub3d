/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flood_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:52:36 by angela            #+#    #+#             */
/*   Updated: 2024/04/14 15:20:52 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//on aimerait checker que si la case actuel est un \0 ou le player... que les cases adjacents n'est ni un \n ni un espace.
// car on veut que ce soit border de 0 ou de 1.

#include <stdio.h>

int check_direction(t_map *map, t_point_pars p, int direction)
{
    if (direction == P_LEFT)
    {
        if ((p.player_i - 1) < 0)
        {
            ft_printf("left\n");
            return (ERROR);
        }
    }
    if (direction == P_RIGHT)
    {
        if ((p.player_i +1) >= ((size_t)ft_strlen(map->mapping[p.player_j])))
        {
            ft_printf("right\n");
            return (ERROR);
        }
    }
    if (direction == P_UP)
    {
        if ((p.player_j - 1) < 0)
         {
            ft_printf("up\n");
            return (ERROR);
        }
    }
    if (direction == P_DOWN)
    {
        if ((p.player_j + 1) >= map->mapping_size)
         {
            ft_printf("down, j:%d, size map%d\n",(p.player_j), map->mapping_size);
            return (ERROR);
        }
    }
    return(SUCCESS);
}

    

//verifie si on est pas actuellement dans un bord avec un '0'
//[p.player_j][p.player_i]
//check les max du tableau
	// path_finding((t_point){p.player_j - 1, p.player_i}, mlx);//gauche
	// path_finding((t_point){p.player_j + 1, p.player_i}, mlx);//droite
	// path_finding((t_point){p.player_j, p.player_i - 1}, mlx);//dessus
	// path_finding((t_point){p.player_j, p.player_i + 1}, mlx);//dessous
    
int check_open_map(t_map *map, t_point_pars p)
{
    // Vérifie si le point_pars est au bord ou s'il est un espace
    if (check_direction(map, p, P_LEFT))
        return(ERROR);
    if (check_direction(map, p, P_RIGHT))
        return(ERROR);
    if (check_direction(map, p, P_UP))
        return(ERROR);
    if (check_direction(map, p, P_DOWN))
        return(ERROR);
    return SUCCESS;
}

// Pas de modifications nécessaires dans check_surroundings pour l'instant

int path_finding(t_map *map, t_point_pars p) 
{
    size_t j;
    size_t i;

    j = 0;
    i = 0;
    (void)p; // a retirer comme argument

    while(map->mapping[j] && j < map->mapping_size)
    {
        i = 0;
        while(map->mapping[j][i])
        {
            while(map->mapping[j][i] == '1')
                i++;
            if (map->mapping[j][i] == '0' || map->mapping[j][i] == map->player_orientation)
            {
                ft_printf(" je suis sur une case 0 ouverte a %d,%d\n",j,i);
                if (check_open_map(map, (t_point_pars){j, i}) == ERROR)  // Notez la modification ici
                {
                    error_handler("map ouverte\n",1);
                    return(ERROR);
                }
                i++;
                ft_printf(" on etait sur la case i %d\n",i);
            }
            
            
        }
        ft_printf("\nJJJJ on etait sur la ligne %d,avec la ligne %s\n\n ",j, map->mapping[j]);
        j++;
        
    }
    ft_printf(" map fermé\n");
    return(SUCCESS);

}
    
    // Cette vérification semble incorrecte car vous comparez un caractère à 1.
    // Je l'ai commentée pour le moment.
    // if (map->mapping[p.player_j][p.player_i] == 1) {
    //     return 0;
    // }

    // if ( check_if_edge_or_space(p, map) == ERROR) {
    //     printf("Arrêt: Case invalide (bord ou espace) à [%zu, %zu]\n", p.player_j, p.player_i);
    //     return ERROR;
    // }
 
//     if (!check_surroundings(p, map)) {
//         printf("Arrêt: Case ouverte trouvée à [%zu, %zu]\n", p.player_j, p.player_i);
//         return 1; // La logique ici peut nécessiter un ajustement selon le comportement attendu
//     }

//     path_finding((t_point_pars){p.player_j - 1, p.player_i}, map);
//     path_finding((t_point_pars){p.player_j + 1, p.player_i}, map);
//     path_finding((t_point_pars){p.player_j, p.player_i - 1}, map);
//     path_finding((t_point_pars){p.player_j, p.player_i + 1}, map);
    
//     return 0;
// }


// int check_surroundings(t_point_pars p, t_map *map) {
//     // Vérifie les cases autour du point_pars actuel
//     if (!check_if_edge_or_space((t_point_pars){p.player_j - 1, p.player_i}, map))
//         return 0;
//     if (!check_if_edge_or_space((t_point_pars){p.player_j + 1, p.player_i}, map))
//         return 0;
//     if (!check_if_edge_or_space((t_point_pars){p.player_j, p.player_i - 1}, map))
//         return 0;
//     if (!check_if_edge_or_space((t_point_pars){p.player_j, p.player_i + 1}, map))
//         return 0;
//     return 1; // Si toutes les vérifications passent, la case est bien entourée
// }


// // int check_if_edge_or_space(t_point_pars p, t_map *map) 
// // {
// //     // Vérifie si le point_pars est au bord ou s'il est un espace
// //     if (p.player_j < 0 || p.player_j >= map->mapping_size) // Dépassement vertical
// //         return 1;
// //     if (!map->mapping[p.player_j]) // Ligne inexistante
// //         return 1;
        
// //     size_t line_length = (size_t)(ft_strlen(map->mapping[p.player_j]));
// //     if (p.player_i < 0 || p.player_i >= line_length) // Dépassement horizontal
// //         return 1;
// //     char c = map->mapping[p.player_j][p.player_i];
// //     if (c == ' ' || c == '\n') // Espace ou fin de ligne
// //         return 1;
// //     return 0;
// // }

// // //check actuel
// // int path_finding(t_point_pars p, t_map *map) {
// //     // Vérifiez d'abord si vous êtes dans les limites de la carte et pas sur une ligne inexistante
// //     if (p.player_j < 0 || p.player_j >= map->mapping_size || !map->mapping[p.player_j])
// //         return 1; // Dépassement vertical ou ligne inexistante
// //     size_t line_length = ft_strlen(map->mapping[p.player_j]);
// //     if (p.player_i < 0 || p.player_i >= line_length) // Dépassement horizontal
// //         return 1;
        
// //     if (map->mapping[p.player_j][p.player_i] == 1)
// //         return 0;
// //     // Vérifiez si le point actuel est un bord ou un espace, auquel cas, arrêtez l'exploration.
// //     if (check_if_edge_or_space(p, map))
// //         return 1;
 
    
// //     // Si la case actuelle ne passe pas la vérification des alentours (elle est ouverte), arrêtez l'exploration.
// //     if (!check_surroundings(p, map)) {
// //         // La logique ici dépend de ce que vous voulez faire si la case est ouverte.
// //         // Par exemple, marquer la carte comme ouverte, ou retourner une valeur spécifique.
// //         return 1; // Ici, nous arrêtons simplement l'exploration.
// //     }

// //     // Votre logique récursive pour explorer les cases adjacentes si la case actuelle est valide.
// //     // Assurez-vous d'éviter les boucles infinies en marquant les cases visitées.
// //     // Exemple simple d'appel récursif (vous devez ajouter votre propre logique pour gérer les cases visitées) :
// //     path_finding((t_point_pars){p.player_j - 1, p.player_i}, map);
// //     path_finding((t_point_pars){p.player_j + 1, p.player_i}, map);
// //     path_finding((t_point_pars){p.player_j, p.player_i - 1}, map);
// //     path_finding((t_point_pars){p.player_j, p.player_i + 1}, map);

// //     return 0; // Continuez l'exploration si toutes les conditions ci-dessus sont satisfaites.
// // }