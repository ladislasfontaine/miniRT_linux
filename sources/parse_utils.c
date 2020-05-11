/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:50 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/11 10:19:54 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		is_space(char *line)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

int		parse_int(char *line, int *n)
{
	if (ft_isdigit(line[0]) || line[0] == '-')
	{
		*n = ft_atoi(line);
		return (ft_numlen(*n));
	}
	return (-1);
}

int		parse_float(char *line, float *f)
{
	int		i;
	int		integer;
	int		decimal;
	int		len;

	i = 0;
	len = 0;
	decimal = 0;
	if (ft_isdigit(line[i]) || line[i] == '-')
		integer = ft_atoi(line);
	else
		return (-1);
	i += ft_numlen(integer);
	if (line[i] != '.')
	{
		*f = integer;
		return (i);
	}
	else if (line[i] == '.' && ft_isdigit(line[i + 1]))
	{
		i++;
		while (line[i] == '0' && line[i])
		{
			len++;
			i++;
		}
		if (ft_isdigit(line[i]))
		{
			decimal = ft_atoi(line + i);
			i += ft_numlen(decimal);
			len += ft_numlen(decimal);
		}
	}
	else
		return (-1);
	*f = (float)integer + ((float)decimal / pow(10.0, (double)len));
	return (i);
}

int		parse_color(char *line, t_color *color)
{
	int	i;

	i = 0;
	if (ft_isdigit(line[i]))
		i += parse_int(line + i, &color->r);
	else
		return (-1);
	if (line[i] == ',')
		i++;
	else
		return (-1);

	if (ft_isdigit(line[i]))
		i += parse_int(line + i, &color->g);
	else
		return (-1);
	if (line[i] == ',')
		i++;
	else
		return (-1);

	if (ft_isdigit(line[i]))
		i += parse_int(line + i, &color->b);
	else
		return (-1);
	return (i);
}

int		parse_vector(char *line, t_vector *vector)
{
	int	i;

	i = 0;
	if (ft_isdigit(line[i]) || line[i] == '-')
		i += parse_float(line + i, &vector->x);
	else
		return (-1);
	if (line[i] == ',')
		i++;
	else
		return (-1);

	if (ft_isdigit(line[i]) || line[i] == '-')
		i += parse_float(line + i, &vector->y);
	else
		return (-1);
	if (line[i] == ',')
		i++;
	else
		return (-1);

	if (ft_isdigit(line[i]) || line[i] == '-')
		i += parse_float(line + i, &vector->z);
	else
		return (-1);
	return (i);
}
