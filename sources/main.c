/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:25 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/15 16:19:45 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** add light color and brightness
** add shine ratio / reflection
** add ft_printf for errors handling with line numbers
** --save option to create an image
** read MLX (use image to show scene)
** error number function
*/

// cas d'erreur lorsqu'il n'y a pas de résolution ou que le fichier est vide ou pas de caméra (no camera to see the scene)
// option -save à gérer
// mettre printf dans le dossier de la libft pour avoir le dossier libft à la racine du projet (comme dit dans sujet)
// gérer la taille de l'écran pour resize si besoin
// pouvoir changer de caméra lorsqu'il y en a plusieurs (et changer l'image dans la fenêtre)
// utiliser les images de la mlx
// gestion de la lumière d'ambiance
// gestion des couleurs, additions, ratio de luminosité
// vérifier les translations et rotations des objets (principalement pour le cylindre)

int		main(int ac, char **av)
{
	t_scene		*scene;

	scene = init_scene();
	if (arguments_error(ac, av) || parse_file(av[1], scene)
		|| scene_error(scene) || !(scene->window = init_window(scene)))
	{
		clear_scene(scene);
		return (1);
	}
	color_window(scene);
	listen_events(scene);
	return (0);
}

int		arguments_error(int ac, char **av)
{
	if (ac < 2 || ac > 3)
	{
		ft_putstr("Error\nWrong number of arguments (should be 1 or 2)\n");
		return (1);
	}
	if (ac == 3 && ft_strcmp(av[2], "-save") != 0)
	{
		ft_putstr("Error\nUnknown option (should be '-save')\n");
		return (1);
	}
	if (ft_strcmp((av[1] + ft_strlen(av[1]) - 3), ".rt") != 0)
	{
		ft_putstr("Error\nWrong file extension (should be '.rt')\n");
		return (1);
	}
	return (0);
}

int		scene_error(t_scene *scene)
{
	if (scene->resolution->h <= 0 || scene->resolution->w <= 0)
	{
		ft_putstr("Error\nNo resolution information in the scene\n");
		return (1);
	}
	return (0);
}
