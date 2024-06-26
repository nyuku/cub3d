/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:47:35 by angela            #+#    #+#             */
/*   Updated: 2024/04/22 11:14:31 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define BUFFER_SIZE 10
# define ERROR 1
# define SUCCESS 0
# define P_LEFT 1
# define P_RIGHT 2
# define P_UP 3
# define P_DOWN 4

# include "struct.h"
# include <stdbool.h>

// parsing.c
int		parsing_cub(int argc, char **argv, t_map *map);
int     check_map_ext(char *argv, char *ext);
int     check_texture(t_map *map, int *line_texture);
int		set_texture(char *str, t_map *map, int *texture);
void	set_floor_ceiling(char *str, t_map *map);

//parsing_floor_ceiling.c
int		*set_color(char *str);
int		check_str_digit(char **split_str, int *rgb, int i);
int		*check_components(char **split_str, int *rgb);
void	init_floor_ceiling(int *rgb, t_map *map, char letter);

//parsing_utils.c
void	init_map_cub(char *argv, t_map *map, int nb_line);
int		map_count_line(char *argv);
char	**map_harvest(char *map_sample, int line_map);
char	*skip_space(char *str);
void	free_split(char **split_str, int error);

//parsing_map.c
int 	is_struc(char *str);
int		check_character(char *str, t_map *map);
int		check_carte(t_map *map, int line_texture);
int		init_mapping(int i, t_map *map);

void	find_player_coordinates(t_map *map);
bool    **init_marking_array(t_map *map);
int     path_finding(t_map *map, t_point_pars p);
int     check_direction(t_map *map, t_point_pars p, int direction);
int     check_open_map(t_map *map, t_point_pars p);

// parsing_utils_bis.c
void    free_map(t_map *map);
t_map	*init_parsing(void);

#endif