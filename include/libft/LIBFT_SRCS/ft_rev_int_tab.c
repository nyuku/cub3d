/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvonwar42@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:23:03 by lvon-war          #+#    #+#             */
/*   Updated: 2023/05/25 16:46:09 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libft.h"

void	ft_rev_int_tab(int *tab, int size)
{
	size_t	i;
	size_t	j;

	j = size - 1;
	i = 0;
	while (i <= size / 2)
	{
		swap(&tab[i], &tab[j]);
		i++;
		j--;
	}
}