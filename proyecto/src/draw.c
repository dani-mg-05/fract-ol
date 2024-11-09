/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damedina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:18:50 by damedina          #+#    #+#             */
/*   Updated: 2024/10/09 18:18:52 by damedina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	get_color(int i)
{
	int	red;
	int	green;
	int	blue;

	red = (int)(sin(0.2 * i) * 127 + 128);
	green = (int)(sin(0.2 * i + 2) * 127 + 128);
	blue = (int)(sin(0.2 * i + 4) * 127 + 128);
	return ((red << 16) | (green << 8) | blue);
}

void	draw_pixel(t_fractol *fractol, int x, int y, int color)
{
	char	*dst;

	dst = fractol->addr + (y * fractol->size_line
			+ x * (fractol->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
