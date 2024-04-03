/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_floor_ceiling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:39:05 by angnguye          #+#    #+#             */
/*   Updated: 2024/04/02 18:53:47 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//-launcher-recupere du tableau les lignes F ou C
// converti en char*->int* avec les check.
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
		free_split(split_str, 1);
		return (NULL);
	}
	str++;
	str = skip_space(str);
	split_str = ft_split(str, ',');
	while (split_str[i] != NULL)
		i++;
	if (i != 3)
	{
		free_split(split_str, 1);
		return (NULL);
	}
	check_components(split_str, rgb);
	free_split(split_str, 0);
	return (rgb);
}

//-check- if char = nombre et le converti en int
int	check_str_digit(char **split_str, int *rgb, int i)
{
	char	*current;

	current = split_str[i];
	while (*current)
	{
		if (!ft_isdigit(*current))
		{
			free(rgb);
			free_split(split_str, 1);
			return (ERROR);
		}
		current++;
	}
	return (SUCCESS);
}

//-check- pour Floor et ceiling si c'est bien des RGB numeriques
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
			free_split(split_str, 1);
			return (NULL);
		}
		i++;
	}
	return (rgb);
}

//-init-Fini de set les informations dans la structure
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
