/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angnguye <angnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:23:39 by angnguye          #+#    #+#             */
/*   Updated: 2024/04/03 19:15:48 by angnguye         ###   ########.fr       */
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
	map->map = map_harvest(argv, map->map_nb_lines);
}

//compte le nombre de ligne, pour savoir la bonne taille de tableau->map.cub
//ignore les lignes entières vides
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
	tableau_stock = malloc(sizeof(char *) * (line_map + 1));
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
