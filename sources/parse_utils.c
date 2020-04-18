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

int		parse_int(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
		return (ft_atoi(line + i));
	return (-1);
}
/*
float	parse_float(char *line)
{
	int	i;
	int	integer;
	int	decimal;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]) || line[i] == '-')
		integer = ft_atoi(line + i);
	ft_numlen
	return (-1);
}
*/