/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damedina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:39:16 by damedina          #+#    #+#             */
/*   Updated: 2024/08/21 18:39:19 by damedina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	close_window(t_fractol *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->img);
	mlx_destroy_window(fractol->mlx, fractol->win);
	mlx_destroy_display(fractol->mlx);
	free(fractol);
	exit(0);
}

int	handle_key(int key, t_fractol *fractol)
{
	if (key == ESC)
		close_window(fractol);
	if (key == UP)
		fractol->offset_y -= 0.3 * fractol->zoom;
	if (key == DOWN)
		fractol->offset_y += 0.3 * fractol->zoom;
	if (key == LEFT)
		fractol->offset_x -= 0.3 * fractol->zoom;
	if (key == RIGHT)
		fractol->offset_x += 0.3 * fractol->zoom;
	if (!ft_strncmp(fractol->fractal, "mandelbrot\0", 11))
		mandelbrot(fractol);
	else if (!ft_strncmp(fractol->fractal, "magnet\0", 7))
		magnet(fractol);
	else
		julia(fractol, fractol->c_julia[0], fractol->c_julia[1]);
	return (0);
}

int	handle_mouse(int button, int x, int y, t_fractol *fractol)
{
	double	mouse_x;
	double	mouse_y;

	mouse_x = (x - WIDTH / 2) * fractol->zoom / WIDTH + fractol->offset_x;
	mouse_y = (y - HEIGHT / 2) * fractol->zoom / HEIGHT + fractol->offset_y;
	if (button == MOUSE_UP)
		fractol->zoom *= 1.1;
	else if (button == MOUSE_DOWN)
		fractol->zoom /= 1.1;
	fractol->offset_x = mouse_x - (x - WIDTH / 2) * fractol->zoom / WIDTH;
	fractol->offset_y = mouse_y - (y - HEIGHT / 2) * fractol->zoom / HEIGHT;
	if (!ft_strncmp(fractol->fractal, "mandelbrot\0", 11))
		mandelbrot(fractol);
	else if (!ft_strncmp(fractol->fractal, "magnet\0", 7))
		magnet(fractol);
	else
		julia(fractol, fractol->c_julia[0], fractol->c_julia[1]);
	return (0);
}

void	handle_events(t_fractol *fractol)
{
	mlx_key_hook(fractol->win, handle_key, fractol);
	mlx_hook(fractol->win, 17, 0, close_window, fractol);
	mlx_mouse_hook(fractol->win, handle_mouse, fractol);
}
