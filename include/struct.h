/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:02:44 by lvon-war          #+#    #+#             */
/*   Updated: 2024/04/22 11:26:16 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct img
{
	int		bpp;
	void	*img;
	char	*addr;
	int		endian;
	int		line_size;
}	t_img;

typedef struct window
{
	void	*ptr;
	void	*mlx;
	int		test;
}	t_window;

typedef struct rgb
{
	int	red;
	int	green;
	int	blue;
}	t_RGB;

typedef struct iterator
{
	int	i;
	int	j;
	int	k;
}	t_iterator;

//in order x, y, z, color
typedef struct pixel
{
	double	x;
	double	y;
	t_RGB	color;
}	t_pixel;	

typedef struct point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct point2d
{
	double	x;
	double	y;
}	t_point2d;

//a = start, b = end
typedef struct vector
{
	t_point	a;
	t_point	b;
}	t_vector;

typedef struct vector2d
{
	t_point2d	a;
	t_point2d	b;
}	t_vector2d;

//triangular polygon
typedef struct polygon
{
	int			seen;
	t_point		normal;
	t_point		verti[3];
	t_vector	edges[3];
	t_RGB		*textaddr;
	t_point2d	texturepos[3];
}	t_polygon;

//for texture : Nord = 0, Sud = 1, Est = 2, West = 3
//pos is the center of the object, all object are cubes
typedef struct object
{
	int			id;
	t_point		pos;
	t_point		rot;
	int			seen;
	t_point		size;
	int			textsize;
	t_point		verti[8];
	t_polygon	poly[12];
	t_RGB		**textures;
}	t_object;

typedef struct sprite
{
	int			id;
	t_point2d	pos;
	t_point2d	size;
	t_RGB		*texture;
}	t_sprite;

//c for current
typedef struct world
{
	int			sky;
	t_point2d	size;
	t_point		spawn;
	int			earth;
	int			nb_obj;
	t_object	*c_obj;
	t_sprite	*c_sprite;
	int			nb_sprite;
}	t_world;

typedef struct player
{
	t_point		pos;
	t_point		size;
	int			speed;
	t_point		angle;
	t_point		cast[2];
	t_sprite	mapsprite;
}	t_player;

typedef struct minimap
{
	t_point2d	pos;
	t_point2d	size;
	t_RGB		color;
	int			scale;
}	t_minimap;

typedef struct option
{
	int		raytoplayer;
	int		playerview;
	int		wireframe;
	int		minimap;
}	t_option;

typedef struct data
{
	t_window	win;
	t_img		img;
	double		fov;
	int			sky;
	int			earth;
	double		focal;
	double		width;
	double		scale;
	t_world		world;
	t_option	option;
	double		height;
	t_player	player;
	t_minimap	minimap;
	int			render_distance;
}	t_data;


//---------PARSING----------
typedef struct color
{
	int	r;
	int	g;
	int	b;
}t_color;


typedef struct point_pars
{
	int	player_j;
	int	player_i;
}				t_point_pars;

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
	char		**mapping;
	int			end_map;
	int		map_size;
	int			player_x;
	int			player_y;
	int		mapping_size;
	t_point_pars		p;
	

} t_map;



#endif /*!STRUCT_H */