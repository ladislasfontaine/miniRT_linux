/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:25 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/22 16:27:18 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// OK cas d'erreur lorsqu'il n'y a pas de résolution ou que le fichier est vide ou pas de caméra (no camera to see the scene)
// OK gestion de la lumière d'ambiance
// OK mettre printf dans le dossier de la libft pour avoir le dossier libft à la racine du projet (comme dit dans sujet)
// OK utiliser les images de la mlx
// OK pouvoir changer de caméra lorsqu'il y en a plusieurs (et changer l'image dans la fenêtre)
// OK option -save à gérer
// OK faire une fonction error_message
// OK gestion des couleurs, additions, ratio de luminosité
// OK vérifier les translations et rotations des objets (principalement pour le cylindre)
// OK gérer l'intérieur des objets (triangle + square + plane + sphere OK cylinder TO DO)
// OK norm
// OK checker le parsing taille des objets > 0
// vérifier les touches (ESC + Q + E)
// gérer la taille de l'écran pour resize si besoin
// leaks
// protéger chaque malloc

int		main(int ac, char **av)
{
	t_scene		*scene;

	scene = init_scene();
	arguments_error(scene, ac, av);
	parse_file(av[1], scene);
	scene_error(scene);
	init_mlx(scene);
	if (!scene->save)
		init_window(scene);
	create_images(scene);
	if (scene->save)
		save_image(scene);
	listen_events(scene);
	return (0);
}

void	arguments_error(t_scene *scene, int ac, char **av)
{
	if (ac < 2 || ac > 3)
		error_and_quit(scene, "Wrong number of arguments (should be 1 or 2)");
	if (ac == 3 && ft_strcmp(av[2], "-save") != 0)
		error_and_quit(scene, "Unknown option (should be '-save')");
	scene->save = (ac == 3) ? 1 : 0;
	if (ft_strcmp((av[1] + ft_strlen(av[1]) - 3), ".rt") != 0)
		error_and_quit(scene, "Wrong file extension (should be '.rt')");
}

void	scene_error(t_scene *scene)
{
	if (scene->res->h <= 0 || scene->res->w <= 0)
		error_and_quit(scene, "No resolution information in the scene");
	if (scene->cameras == NULL)
		error_and_quit(scene, "No camera to see the scene");
}
