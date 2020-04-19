#include "minirt.h"

/*
** create functions:
**
** parse identifier
** specific function for each identifier
** parse vector
** parse rgb color
** parse float
** parse int
*/

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
	if (ft_isdigit(line[0]))
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

	i = 0;
	if (ft_isdigit(line[i]) || line[i] == '-')
		integer = ft_atoi(line);
	else
		return (-1);
	i += ft_numlen(integer);
	if (line[i] == ' ' || !line[i])
		return (integer);
	else if (line[i] == '.' && ft_isdigit(line[i + 1]))
	{
		i++;
		decimal = ft_atoi(line + i);
		i += ft_numlen(decimal);
	}
	else
		return (-1);
	*f = (float)integer + ((float)decimal / pow(10.0, (double)ft_numlen(decimal)));
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
