/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvonwar@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:29:59 by lvon-war          #+#    #+#             */
/*   Updated: 2024/03/18 19:36:06 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "struct.h"

void		pop_sprite(t_data *d, int index);
void		put_sprite(t_data *d, t_sprite s);
void		sprite_add(t_data *d, t_sprite s);
t_object	*create_object(t_point pos, t_point2d size, t_RGB color);
t_sprite	create_sprite(t_point2d pos, t_point2d size, t_RGB color);

#endif /* OBJECT_H */