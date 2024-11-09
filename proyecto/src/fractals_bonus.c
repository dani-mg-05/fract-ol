/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damedina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:52:49 by damedina          #+#    #+#             */
/*   Updated: 2024/11/07 17:52:55 by damedina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	calculate_magnet(double z[2], double c[2], double result[2])
{
	double	real_tmp;
	double	numer[2];
	double	denom[2];
	double	global_denom;

	denom[0] = 2 * z[0] + c[0] - 2;
	denom[1] = 2 * z[1] + c[1];
	global_denom = denom[0] * denom[0] + denom[1] * denom[1];
	numer[0] = z[0] * z[0] - z[1] * z[1] + c[0] - 1;
	numer[1] = 2 * z[0] * z[1] + c[1];
	result[0] = (numer[0] * denom[0] + numer[1] * denom[1]) / global_denom;
	result[1] = (numer[1] * denom[0] - numer[0] * denom[1]) / global_denom;
	real_tmp = result[0];
	result[0] = result[0] * result[0] - result[1] * result[1];
	result[1] = 2 * real_tmp * result[1];
}

void	apply_magnet(t_fractol *fractol)
{
	int		i;
	double	c[2];
	double	z[2];
	double	result[2];

	c[0] = (fractol->x - WIDTH / 2) * fractol->zoom
		/ WIDTH + fractol->offset_x;
	c[1] = (fractol->y - HEIGHT / 2) * fractol->zoom
		/ HEIGHT + fractol->offset_y;
	z[0] = 0;
	z[1] = 0;
	i = -1;
	while (++i < 100 && (z[0] * z[0] + z[1] * z[1]) < 4)
	{
		if (2 * z[0] + c[0] - 2 == 0 && 2 * z[1] + c[1] == 0)
			break ;
		calculate_magnet(z, c, result);
		z[0] = result[0];
		z[1] = result[1];
	}
	if (i == 100)
		draw_pixel(fractol, fractol->x, fractol->y, 0x000000);
	else
		draw_pixel(fractol, fractol->x, fractol->y, get_color(i));
}

void	magnet(t_fractol *fractol)
{
	fractol->fractal = "magnet";
	fractol->x = 0;
	while (fractol->x < WIDTH)
	{
		fractol->y = 0;
		while (fractol->y < HEIGHT)
		{
			apply_magnet(fractol);
			fractol->y++;
		}
		fractol->x++;
	}
	mlx_clear_window(fractol->mlx, fractol->win);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}
