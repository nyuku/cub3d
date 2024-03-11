/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstartw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvonwar42@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:38:50 by lvon-war          #+#    #+#             */
/*   Updated: 2023/11/27 18:59:47 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strstartw(char *str, char c)
{
	if (str && str[0] == c)
		return (1);
	return (0);
}
