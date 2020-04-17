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

int		parse_file(char *file)
{
	int		fd;
	int		res;
	char	*line;

	res = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putstr("Error\nCannot open the file\n");
		return (1);
	}
	while (res)
	{
		res = get_next_line(fd, &line);
		if (res == -1)
		{
			ft_putstr("Error\nCannot read the file\n");
			return (1);
		}
		parse_line(line);
		free(line);
	}
	if (close(fd) == -1)
	{
		ft_putstr("Error\nCannot close the file\n");
		return (1);
	}
	return (0);
}

int		parse_line(char *line)
{
	(void)line;
	//ft_putstr(line);
	//ft_putstr("\n");
	return (0);
}
