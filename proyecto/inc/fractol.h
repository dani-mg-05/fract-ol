/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damedina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:57:09 by damedina          #+#    #+#             */
/*   Updated: 2024/09/30 16:43:00 by damedina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# define WIDTH 1000
# define HEIGHT 1000

# define ESC 65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define MOUSE_UP 4
# define MOUSE_DOWN 5

typedef struct s_fractol
{
	char	*fractal;
	double	c_julia[2];
	void	*mlx;
	void	*win;
	void	*img;
	int		x;
	int		y;
	double	zoom;
	double	offset_x;
	double	offset_y;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_fractol;

void	handle_events(t_fractol *fractol);
int		get_color(int i);
void	draw_pixel(t_fractol *fractol, int x, int y, int color);
void	mandelbrot(t_fractol *fractol);
void	julia(t_fractol *fractol, double c_real, double c_imaginary);
void	magnet(t_fractol *fractol);

#endif
