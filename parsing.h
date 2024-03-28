#ifndef PARSING_H
#define PARSING_H


# include	<ctype.h>
# include	<string.h>
# include	<stdlib.h>
# include	<unistd.h>

typedef struct color
{
	char	r;
	char	g;
	char	b;
}t_color;

typedef struct	map
{
	char		**map;
	int			map_nb_lines;
	char		player_orientation;
	char		*texture_north;
	char		*texture_south;
	char		*texture_west;
	char		*texture_east;
	t_color 	*floor_color;
	t_color 	*ceiling_color;

} t_map;


#endif