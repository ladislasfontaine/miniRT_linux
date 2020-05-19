/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:25 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/19 16:47:57 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// OK cas d'erreur lorsqu'il n'y a pas de résolution ou que le fichier est vide ou pas de caméra (no camera to see the scene)
// OK gestion de la lumière d'ambiance
// gestion des couleurs, additions, ratio de luminosité
// OK mettre printf dans le dossier de la libft pour avoir le dossier libft à la racine du projet (comme dit dans sujet)
// OK utiliser les images de la mlx
// OK pouvoir changer de caméra lorsqu'il y en a plusieurs (et changer l'image dans la fenêtre)
// option -save à gérer
// gérer la taille de l'écran pour resize si besoin
// vérifier les translations et rotations des objets (principalement pour le cylindre)
// norm
// leaks
// faire une fonction error_message
// protéger chaque malloc

int		main(int ac, char **av)
{
	t_scene		*scene;

	scene = init_scene();
	if (arguments_error(ac, av) || parse_file(av[1], scene)
		|| scene_error(scene))
	{
		clear_scene(scene);
		return (1);
	}
	if (!(scene->win = init_window(scene)))
	{
		ft_putstr("Error\nWindow initialization failed\n");
		clear_scene(scene);
		return (1);
	}
	create_images(scene);
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
	if (scene->res->h <= 0 || scene->res->w <= 0)
	{
		ft_putstr("Error\nNo resolution information in the scene\n");
		return (1);
	}
	if (scene->cameras == NULL)
	{
		ft_putstr("Error\nNo camera to see the scene\n");
		return (1);
	}
	return (0);
}
