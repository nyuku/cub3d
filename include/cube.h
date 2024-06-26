/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:49:18 by lvon-war          #+#    #+#             */
/*   Updated: 2024/04/22 11:32:57 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvonwar42@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:54:56 by lvon-war          #+#    #+#             */
/*   Updated: 2023/05/25 16:52:02 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# define M_PI 3.14159265358979323846
# define WL 1920
# define WH 1080
# define FOV 90
# define BLUE 0x0000FF
# define DARKBLUE 0x000080
# define DARKRED 0x8B0000
# define YELLOW 0xFFFF00
# define RED 0xFF0000
# define GREEN 0x00FF00

//standard library
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

//libft and mlx library
# include "mlx.h"
# include "ft_libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

//lib from cube3d
# include "keycode.h"
# include "controls.h"
# include "display.h"
# include "map.h"
# include "calc.h"

//utils
# include "struct.h"
# include "utils.h"

//object
# include "object.h"

//sprite
# include "sprite.h"

//player
# include "player.h"

//vector
# include "vector.h"

//test
# include "test.h"

//parsing
# include "parsing.h"

#endif /*!CUBE_H */