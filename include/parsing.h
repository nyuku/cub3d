#ifndef PARSING_H
# define PARSING_H

# define BUFFER_SIZE 10
# define ERROR 1
# define SUCCESS 0



# include "struct.h"

void	check_map_ext(char *argv, char * ext);

int		map_count_line(char *argv);
char	**map_harvest(char *map_sample, int line_map);
void	init_map_cub(char *argv, t_map *map);
char	*skip_space(char *str);
void	check_texture(t_map *map);
void	free_split(char **split_str);
int		*set_color(char *str);
int		parsing_cub(int argc, char **argv, t_map *map);
int		set_texture(char *str, t_map *map, int *texture);
int     check_single_component(char *str, int *value);
int		*check_components(char **split_str, int *rgb);
void	init_floor_ceiling(int *rgb, t_map *map, char letter);
int	check_str_digit(char **split_str, int *rgb,int i);

#endif