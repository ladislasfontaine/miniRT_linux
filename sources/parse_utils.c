/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:50 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 15:17:23 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_float(t_scene *scene, char *line, float *f)
{
	int		i;
	int		num;
	int		decimal;
	int		len;
	int		neg;

	i = 0;
	len = 0;
	decimal = 0;
	neg = (line[i] == '-') ? 1 : 0;
	num = (ft_isdigit(line[i]) || line[i] == '-') ? ft_atoi(line) : 0;
	if (!(ft_isdigit(line[i]) || line[i] == '-'))
		error_and_quit(scene, "Error in float format");
	i += (num == 0 && neg) ? (ft_numlen(num) + 1) : (ft_numlen(num));
	if (line[i] != '.')
	{
		*f = num;
		return (i);
	}
	else if (line[i] == '.' && ft_isdigit(line[i + 1]))
		parse_float_two(line, &i, &len, &decimal);
	else
		error_and_quit(scene, "Error in float format");
	parse_float_three(f, (t_vector){num, decimal, len}, neg);
	return (i);
}

void	parse_float_two(char *line, int *i, int *len, int *dec)
{
	*i += 1;
	while (line[*i] == '0' && line[*i])
	{
		*len += 1;
		*i += 1;
	}
	if (ft_isdigit(line[*i]))
	{
		*dec = ft_atoi(line + *i);
		*i += ft_numlen(*dec);
		*len += ft_numlen(*dec);
	}
}

void	parse_float_three(float *f, t_vector v, int neg)
{
	if (v.x < 0)
		*f = v.x - (v.y / pow(10.0, v.z));
	else
		*f = v.x + (v.y / pow(10.0, v.z));
	if (neg && v.x == 0 && *f > 0.0)
		*f = -*f;
}

int		parse_color(t_scene *scene, char *line, t_color *color)
{
	int	i;

	i = 0;
	if (ft_isdigit(line[i]))
		i += parse_int(scene, line + i, &color->r);
	else
		error_and_quit(scene, "Error in color format");
	if (line[i] == ',')
		i++;
	else
		error_and_quit(scene, "Error in color format");
	if (ft_isdigit(line[i]))
		i += parse_int(scene, line + i, &color->g);
	else
		error_and_quit(scene, "Error in color format");
	if (line[i] == ',')
		i++;
	else
		error_and_quit(scene, "Error in color format");
	if (ft_isdigit(line[i]))
		i += parse_int(scene, line + i, &color->b);
	else
		error_and_quit(scene, "Error in color format");
	i += is_space(line + i);
	return (i);
}

int		parse_vector(t_scene *scene, char *line, t_vector *vector)
{
	int	i;

	i = 0;
	if (ft_isdigit(line[i]) || line[i] == '-')
		i += parse_float(scene, line + i, &vector->x);
	else
		error_and_quit(scene, "Error in vector format");
	if (line[i] == ',')
		i++;
	else
		error_and_quit(scene, "Error in vector format");
	if (ft_isdigit(line[i]) || line[i] == '-')
		i += parse_float(scene, line + i, &vector->y);
	else
		error_and_quit(scene, "Error in vector format");
	if (line[i] == ',')
		i++;
	else
		error_and_quit(scene, "Error in vector format");
	if (ft_isdigit(line[i]) || line[i] == '-')
		i += parse_float(scene, line + i, &vector->z);
	else
		error_and_quit(scene, "Error in vector format");
	i += is_space(line + i);
	return (i);
}
