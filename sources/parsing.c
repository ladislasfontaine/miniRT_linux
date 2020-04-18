#include "minirt.h"

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
		if (parse_line(line) == -1)
			return (1);
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
	int		i;
	int		ret;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (0);
	if (ft_strncmp(line + i, "R ", 2) == 0)
		ret = parse_resolution(line + i + 2);
	else
	{
		ft_putstr("Error\nUnknown identifier in the .rt file\n");
		return (-1);
	}
	// different function according to the identifier
	return (ret);
}
