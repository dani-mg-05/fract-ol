/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damedina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:56:02 by damedina          #+#    #+#             */
/*   Updated: 2024/09/30 17:07:21 by damedina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	check_double(char *str)
{
	int	i;
	int	dot;

	dot = 0;
	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) || (str[i] == '.' && i > 0 && !dot))
		{
			if (str[i] == '.' && !dot)
				dot = !dot;
		}
		else
			return (0);
	}
	return (1);
}

double	to_double(char *str)
{
	double	integer_part;
	double	decimal_part;
	int		sign;

	if (str[0] == '-')
		sign = -1;
	else
		sign = 1;
	integer_part = ft_atoi(str) + 0.0;
	str = ft_strchr(str, '.');
	if (!str)
		return (integer_part);
	decimal_part = ft_atoi(str + 1) / (pow(10, ft_strlen(str + 1)));
	if (integer_part == 0 && sign == -1)
		return (-1 * (integer_part + decimal_part));
	return (integer_part + sign * decimal_part);
}

int	check_args(int argc, char **argv)
{
	if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot\0", 11))
		return (1);
	if (argc == 2 && !ft_strncmp(argv[1], "magnet\0", 11))
		return (1);
	if (argc == 4 && !ft_strncmp(argv[1], "julia\0", 6))
	{
		if (check_double(argv[2]) && check_double(argv[3]))
			return (1);
	}
	ft_putendl_fd("Usage:", 2);
	ft_putendl_fd("\t-> ./fractol [mandelbrot]", 2);
	ft_putendl_fd("\t-> ./fractol [julia] [c_real] [c_imaginary]", 2);
	ft_putendl_fd("\t-> ./fractol [magnet]", 2);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractol	*fractol;

	if (!check_args(argc, argv))
		return (1);
	fractol = (t_fractol *)malloc(sizeof(t_fractol));
	if (!fractol)
		return (1);
	fractol->zoom = 4;
	fractol->offset_x = 0;
	fractol->offset_y = 0;
	fractol->mlx = mlx_init();
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, "fract-ol");
	fractol->img = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	fractol->addr = mlx_get_data_addr(fractol->img, &fractol->bits_per_pixel,
			&fractol->size_line, &fractol->endian);
	if (!ft_strncmp(argv[1], "mandelbrot\0", 11))
		mandelbrot(fractol);
	else if (!ft_strncmp(argv[1], "magnet\0", 7))
		magnet(fractol);
	else
		julia(fractol, to_double(argv[2]), to_double(argv[3]));
	handle_events(fractol);
	mlx_loop(fractol->mlx);
	free(fractol);
	return (0);
}
