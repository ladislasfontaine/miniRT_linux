#include "minirt.h"

int		parse_file(char *file)
{
	int		fd;
	int		res;
	char	*line;

	res = 1;
	fd = open(file, O_RDONLY);
	while (res)
	{
		res = get_next_line(fd, &line);
		parse_line(line);
		free(line);
	}
	close(fd);
	return (0);
}

int		parse_line(char *line)
{
	(void)line;
	//ft_putstr(line);
	//ft_putstr("\n");
	return (0);
}
