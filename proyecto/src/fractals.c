/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damedina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 04:52:54 by damedina          #+#    #+#             */
/*   Updated: 2024/10/05 13:33:07 by damedina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	apply_mandelbrot(t_fractol *fractol)
{
	int		i;
	double	c[2];
	double	z[2];
	double	real_tmp;

	c[0] = (fractol->x - WIDTH / 2) * fractol->zoom
		/ WIDTH + fractol->offset_x;
	c[1] = (fractol->y - HEIGHT / 2) * fractol->zoom
		/ HEIGHT + fractol->offset_y;
	z[0] = 0;
	z[1] = 0;
	i = -1;
	while (++i < 100 && (z[0] * z[0] + z[1] * z[1]) < 4)
	{
		real_tmp = z[0];
		z[0] = z[0] * z[0] - z[1] * z[1] + c[0];
		z[1] = 2 * real_tmp * z[1] + c[1];
	}
	if (i == 100)
		draw_pixel(fractol, fractol->x, fractol->y, 0x000000);
	else
		draw_pixel(fractol, fractol->x, fractol->y, get_color(i));
}

void	mandelbrot(t_fractol *fractol)
{
	fractol->fractal = "mandelbrot";
	fractol->x = -1;
	while (++fractol->x < WIDTH)
	{
		fractol->y = -1;
		while (++fractol->y < HEIGHT)
			apply_mandelbrot(fractol);
	}
	mlx_clear_window(fractol->mlx, fractol->win);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}

void	apply_julia(t_fractol *fractol)
{
	int		i;
	double	c[2];
	double	z[2];
	double	real_tmp;

	c[0] = fractol->c_julia[0];
	c[1] = fractol->c_julia[1];
	z[0] = (fractol->x - WIDTH / 2) * fractol->zoom
		/ WIDTH + fractol->offset_x;
	z[1] = (fractol->y - HEIGHT / 2) * fractol->zoom
		/ HEIGHT + fractol->offset_y;
	i = -1;
	while (++i < 100 && (z[0] * z[0] + z[1] * z[1]) < 4)
	{
		real_tmp = z[0];
		z[0] = z[0] * z[0] - z[1] * z[1] + c[0];
		z[1] = 2 * real_tmp * z[1] + c[1];
	}
	if (i == 100)
		draw_pixel(fractol, fractol->x, fractol->y, 0x000000);
	else
		draw_pixel(fractol, fractol->x, fractol->y, get_color(i));
}

void	julia(t_fractol *fractol, double c_real, double c_imaginary)
{
	fractol->fractal = "julia";
	fractol->c_julia[0] = c_real;
	fractol->c_julia[1] = c_imaginary;
	fractol->x = 0;
	while (fractol->x < WIDTH)
	{
		fractol->y = 0;
		while (fractol->y < HEIGHT)
		{
			apply_julia(fractol);
			fractol->y++;
		}
		fractol->x++;
	}
	mlx_clear_window(fractol->mlx, fractol->win);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}
