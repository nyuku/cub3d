/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnguye <angnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:23:39 by angnguye          #+#    #+#             */
/*   Updated: 2024/04/04 18:10:37 by angnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
/*
Fonctions pour récupérer les infos du fichier.cub
*/

// -launcher- la fonction de compter et remplir le tableau
void	init_map_cub(char *argv, t_map *map)
{
	map->map_nb_lines = map_count_line(argv);
	ft_printf("nombre de ligne %d\n", map->map_nb_lines);
	map->map = map_harvest(argv, map->map_nb_lines);
}
// //new
// int map_count_line(char *argv)
// {
//     int fd;
//     int count = 0;
//     int config_lines_counted = 0;
//     char *gnl_return;
//     char *tmp;

//     fd = open(argv, O_RDONLY);
//     if (fd == -1) {
//         error_handler("Cannot open file", 1);
//         return (ERROR); // Assurez-vous que error_handler existe ou gérez l'erreur comme nécessaire
//     }

//     gnl_return = get_next_line(fd);
//     while (gnl_return) {
//         tmp = gnl_return;
//         while (*tmp == ' ' || *tmp == '\t') // skip les espaces du la str analysée
//             tmp++;
//         if (config_lines_counted < 6) {
//             if (*tmp != '\n' && *tmp != '\0' && is_struc(tmp) == SUCCESS) {
//                 config_lines_counted++;
//                 count++; // on compte la ligne de configuration
//             }
//         } else { // On commence à compter toutes les lignes une fois les configurations comptées
//             count++;
//             //ft_printf("on lit au dela des textures ligne:%d\n", count);
//         }

//         free(gnl_return);
//         gnl_return = get_next_line(fd);
//     }
//     if (count < 6) // Si on a moins de 6 lignes de configuration, on considère que la map est pauvre
//         error_handler("poor map", 1);

//     close(fd);

//     return count; // Retourne le nombre total de lignes comptées
// }
// //new
// char **map_harvest(char *map_sample, int line_map) {
//     int fd;
//     char **tableau_stock;
//     char *line;
//     int i = 0;
//     int config_lines_counted = 0; // Nouveau
//     char *tmp;

//     fd = open(map_sample, O_RDONLY);
//     if (fd == -1) return (NULL);

//     tableau_stock = malloc(sizeof(char *) * (line_map + 1)); // +1 pour le NULL à la fin
//     if (!tableau_stock) {
//         close(fd);
//         return (NULL);
//     }

//     while (i < line_map) {
//         line = get_next_line(fd);
//         if (line == NULL) break; // Fin du fichier ou erreur de lecture

//         tmp = line;
//         while (*tmp == ' ' || *tmp == '\t') tmp++; // Skip les espaces

//         // Logique pour inclure la ligne dans le tableau
//         if (config_lines_counted < 6) {
//             if (*tmp != '\n' && *tmp != '\0' && is_struc(tmp) == SUCCESS) {
//                 tableau_stock[i++] = ft_strdup(line);
//                 config_lines_counted++;
//             }
//         } else {
//             // Après les lignes de configuration, inclure toutes les lignes
//             tableau_stock[i++] = ft_strdup(line);
//         }

//         free(line);
//     }

//     tableau_stock[i] = NULL; // Marqueur de fin du tableau
//     close(fd);
//     return tableau_stock;
// }

//compte le nombre de ligne, pour savoir la bonne taille de tableau->map.cub
//ignore les lignes entières vides
// int	map_count_line(char *argv)
// {
// 	int		fd;
// 	int		count;
// 	char	*gnl_return;
// 	char	*tmp;
// 	int map = 0;

// 	count = 0;
// 	fd = open(argv, O_RDONLY);
// 	if (fd == -1)
//     {
//         error_handler("Cannot open file", 1);
//         return (ERROR); // Assurez-vous que error_handler existe ou gérez l'erreur comme nécessaire
//     }
// 	gnl_return = get_next_line(fd);
// 	while (gnl_return)
// 	{
// 		tmp = gnl_return;
// 		while (*tmp == ' ' || *tmp == '\t')//skip les espaces du la str analisé
// 				tmp++;
// 		if (count <= 6)
// 		{
// 			// while (*tmp == ' ' || *tmp == '\t')//skip les espaces du la str analisé
// 			// 	tmp++;
// 			if (*tmp != '\n' && *tmp != '\0' && is_struc(tmp) == SUCCESS)
// 			{
// 				count++;//on compte la ligne
// 			}
// 		}
// 		else // apres les struct
// 		{
// 			if(*tmp == '1')// c'est une map
// 					map = 1;
// 			if (map == 1)//on print tout des que c'est une map
//             {
                
// 				ft_printf("on lit au dela des textures ligne:%d\n", count + 1);
// 				count++;
//             }
            
// 		}
// 		free(gnl_return);
// 		gnl_return = get_next_line(fd);
// 	}
// 	if (count < 6)
// 		error_handler("poor map", 1);
// 	close (fd);
	
// 	return (count);
// }

// -tableau-récupère la map avec gnl et la met dans un tableau
// char	**map_harvest(char *map_sample, int line_map)
// {
// 	int		fd;
// 	char	**tableau_stock;
// 	char	*line;
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	fd = open(map_sample, O_RDONLY);
// 	tableau_stock = malloc(sizeof(char *) * (line_map + 1));
// 	if (!tableau_stock)
// 		return (NULL);
// 	line = get_next_line(fd);
// 	while (i < line_map)
// 	{
// 		// tmp = line;
// 		// while (*tmp == ' ' || *tmp == '\t')
// 		// 	tmp++;
// 		// if (*tmp != '\n' && *tmp != '\0')
// 		// 	tableau_stock[i++] = ft_strdup(line);
// 		// free (line);
// 		// line = get_next_line(fd);
// 		tmp = line;
// 		if (i <= 6)
// 		{
// 			while (*tmp == ' ' || *tmp == '\t')//skip les espaces du la str analisé
// 				tmp++;
// 			if (*tmp != '\n' && *tmp != '\0')
// 			{
// 				if (is_struc(tmp) == SUCCESS)
// 					tableau_stock[i++] = ft_strdup(line);
// 			}
// 		}
// 		else // apres les struct
// 		{
// 			tableau_stock[i++] = ft_strdup(line);
// 		}
// 		free (line);
// 		line = get_next_line(fd);
// 	}
// 	close (fd);
// 	return (tableau_stock);
// }
int	map_count_line(char *argv)
{
	int		fd;
	int		count;
	char	*gnl_return;
	char	*tmp;

	count = 0;
	fd = open(argv, O_RDONLY);
	gnl_return = get_next_line(fd);
	while (gnl_return)
	{
		tmp = gnl_return;
		while (*tmp == ' ' || *tmp == '\t')
			tmp++;
		if (*tmp != '\n' && *tmp != '\0')
			count++;
		free(gnl_return);
		gnl_return = get_next_line(fd);
	}
	if (count == 0)
		error_handler("empty map", 1);
	close (fd);
	return (count);
}

// -tableau-récupère la map avec gnl et la met dans un tableau
char	**map_harvest(char *map_sample, int line_map)
{
	int		fd;
	char	**tableau_stock;
	char	*line;
	int		i;
	char	*tmp;

	i = 0;
	fd = open(map_sample, O_RDONLY);
	tableau_stock =  ft_calloc(line_map + 1, sizeof(char *));
//malloc(sizeof(char *) * (line_map + 1));
	if (!tableau_stock)
		return (NULL);
	line = get_next_line(fd);
	while (i < line_map)
	{
		tmp = line;
		while (*tmp == ' ' || *tmp == '\t')
			tmp++;
		if (*tmp != '\n' && *tmp != '\0')
			tableau_stock[i++] = ft_strdup(line);
		free (line);
		line = get_next_line(fd);
	}
	close (fd);
	return (tableau_stock);
}

//skip les espaces
char	*skip_space(char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n')// ajout de \n et \t
		str++;
	return (str);
}

//libère le tableau avec option message d'erreur
void	free_split(char **split_str, int error)
{
	int	j;

	j = 0;
	while (split_str[j])
	{
		free(split_str[j]);
		j++;
	}
	free(split_str);
	if (error == 1)
		error_handler("Error: Invalid color format\n", 1);
}
