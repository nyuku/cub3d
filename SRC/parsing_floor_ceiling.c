/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_floor_ceiling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:39:05 by angnguye          #+#    #+#             */
/*   Updated: 2024/04/02 18:04:15 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
//Fini de set les informations dans la structure
void	init_floor_ceiling(int *rgb, t_map *map, char letter)
{
	if (letter == 'C')
	{
		map->ceiling_color->r = rgb[0];
		map->ceiling_color->g = rgb[1];
		map->ceiling_color->b = rgb[2];
	}
	else if (letter == 'F')
	{
		map->floor_color->r = rgb[0];
		map->floor_color->g = rgb[1];
		map->floor_color->b = rgb[2];
	}
}

//check if nombre et le converti en int
int	check_str_digit(char **split_str, int *rgb, int i)
{
	char	*current;

	current = split_str[i];
	while (*current)
	{
		if (!ft_isdigit(*current))
		{
			free(rgb);
			free_split(split_str);
			return (ERROR);
		}
		current++;
	}
	return (SUCCESS);
}

// Vérifie les composants RGB et les convertit
// int	*check_components(char **split_str, int *rgb)
// {
// 	int	i;
// 	int	value;

// 	i = 0;
// 	while (split_str[i] != NULL && i < 3)
// 	{
// 		if (!check_single_component(split_str[i], &value))
// 		{
// 			free(rgb);
// 			free_split(split_str);
// 			return (NULL);
// 		}
// 		rgb[i] = value;
// 	}
// 	if (i != 3)
// 	{
// 		free(rgb);
// 		free_split(split_str);
// 		return (NULL);
// 	}
// 	return (rgb);
// }

int	*check_components(char **split_str, int *rgb)
{
	int		i;

	i = 0;
	while (split_str[i] != NULL && i <= 3)
	{
		if (check_str_digit(split_str, rgb, i) == ERROR)
			return (NULL);
		rgb[i] = ft_atoi(split_str[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free(rgb);
			free_split(split_str);
			return (NULL);
		}
		i++;
	}
	return (rgb);
}

//recupere la str de F ou C converti en int* avec les check.
int	*set_color(char *str)
{
	char	**split_str;
	int		*rgb;
	int		i;

	i = 0;
	split_str = NULL;
	rgb = (int *)malloc(sizeof(int) * 3);
	if (rgb == NULL)
	{
		free_split(split_str);
		return (NULL);
	}
	str++;
	str = skip_space(str);
	split_str = ft_split(str, ',');
	while (split_str[i] != NULL)
		i++;
	if (i != 3)
	{
		free_split(split_str);
		return (NULL);
	}
	check_components(split_str, rgb);
	//free_split(split_str);
	return (rgb);
}

// int	*set_color(char *str)
// {
// 	int		i;
// 	char	**split_str;
// 	int		*rgb;
// 	char	*current;

// 	rgb = (int *)malloc(sizeof(int) * 3);
// 	i = 0;
// 	str++;
// 	str = skip_space(str);
// 	split_str = ft_split(str, ',');
// 	while (split_str[i] != NULL)
// 		i++;
// 	if (i != 3)
// 	{
// 		free_split(split_str);
// 		return (NULL);
// 	}
// 	i = 0;
// /*

// */
// 	while (split_str[i] != NULL && i <= 3)
// 	{
// 		current = split_str[i];
// 		while (*current)
// 		{
// 			if (!ft_isdigit(*current))
// 			{
// 				free_split(split_str);
// 				return (NULL);
// 			}
// 			current++;
// 		}
// 		rgb[i] = ft_atoi(split_str[i]);
// 		if (rgb[i] < 0 || rgb[i] > 255)
// 		{
// 			free_split(split_str);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	return (rgb);
// }
