/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:48:49 by lvon-war          #+#    #+#             */
/*   Updated: 2024/03/11 12:20:26 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "My Window");
	mlx_pixel_put(mlx, win, 400, 300, 0xFFFFFF);
	mlx_hook(win, CLOSE_WINDOW_KEY, 0, &exit_hook, NULL);
	error_handler("Error: something went wrong", 1);
	mlx_loop(mlx);
	free(mlx);

	return (0);
}
