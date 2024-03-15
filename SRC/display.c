/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvonwar@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:54:44 by lvon-war          #+#    #+#             */
/*   Updated: 2024/03/15 19:25:49 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	displayimg(t_data *d)
{
	if (d->img.img)
		mlx_put_image_to_window(d->win.mlx, d->win.ptr, d->img.img, 0, 0);
}

void	put_pixel(t_point p, t_data *d)
{
	int		index;

	if (p.x <= 0 || p.y <= 0 || p.x >= WL || p.y >= WH)
		return ;
	index = ((WH - (int)p.y) * d->img.line_size + (int)p.x * d->img.bpp / 8);
	d->img.addr[index] = p.color.blue;
	d->img.addr[index + 1] = p.color.green;
	d->img.addr[index + 2] = p.color.red;
}

void	put_line(t_vector AB, t_data *d)
{
	t_point	delta;
	t_point	inc;
	double	steps;

	delta.x = AB.b.x - AB.a.x;
	delta.y = AB.b.y - AB.a.y;
	if (fabs(delta.x) > fabs(delta.y))
		steps = fabs(delta.x);
	else
		steps = fabs(delta.y);
	delta.x = delta.x / steps;
	delta.y = delta.y / steps;
	inc.x = AB.a.x;
	inc.y = AB.a.y;
	while ((int)(inc.x - AB.b.x) < 1 &&
		(int)(inc.y - AB.b.y) < 1)
	{
		if (break_point(AB, inc))
			break ;
		put_pixel((t_point){inc.x, inc.y, 0, AB.a.color}, d);
		inc.x += delta.x;
		inc.y += delta.y;
	}
}

void	put_square(t_point center, int x, int y, t_data *d)
{
	int	i;
	int	j;

	j = 0;
	while (j < y)
	{
		i = 0;
		while (i < x)
		{
			put_pixel((t_point){center.x + i, center.y + j,
				0, center.color}, d);
			i++;
		}
		j++;
	}
}
