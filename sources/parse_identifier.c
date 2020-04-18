#include "minirt.h"

int		parse_resolution(char *line)
{
	int	w;
	int	h;

	w = parse_int(line);
	h = parse_int(line);
	// besoin de la taille du chiffre + des espaces le précédant
	if (w == -1 || h == -1)
	{
		ft_putstr("Error\nProblem parsing the resolution line\n");
		return (-1);
	}
	return (0);
}
