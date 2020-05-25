/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:43:40 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 15:59:53 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	delete_shape(void *element)
{
	t_shape	*shape;

	shape = (t_shape *)element;
	if (shape->center)
		free(shape->center);
	if (shape->position)
		free(shape->position);
	if (shape->normal)
		free(shape->normal);
	if (shape->p1)
		free(shape->p1);
	if (shape->p2)
		free(shape->p2);
	if (shape->p3)
		free(shape->p3);
	if (shape->color)
		free(shape->color);
	if (shape)
		free(shape);
}

void	delete_camera(void *element)
{
	t_camera	*camera;

	camera = (t_camera *)element;
	if (camera->origin)
		free(camera->origin);
	if (camera->direction)
		free(camera->direction);
	if (camera->up)
		free(camera->up);
	if (camera->right)
		free(camera->right);
	if (camera)
		free(camera);
}

void	delete_light(void *element)
{
	t_light	*light;

	light = (t_light *)element;
	if (light->origin)
		free(light->origin);
	if (light->color)
		free(light->color);
	if (light)
		free(light);
}

void	ft_lstclear_img(t_list **lst, void (*del)(void *))
{
	t_list	*element;
	t_list	*delete;

	element = *lst;
	while (element)
	{
		delete = element;
		element = element->next;
		(*del)(delete->content);
		free(delete);
	}
	*lst = NULL;
}

void	delete_images(t_list **lst, t_scene *scene)
{
	t_list	*element;
	t_list	*delete;
	t_image	*img;

	element = *lst;
	while (element)
	{
		delete = element;
		element = element->next;
		img = (t_image *)delete->content;
		mlx_destroy_image(scene->win->mlx_ptr, img->mlx_img);
		free(delete);
	}
	*lst = NULL;
}
