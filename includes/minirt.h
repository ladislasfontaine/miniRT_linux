/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:31:58 by marvin            #+#    #+#             */
/*   Updated: 2020/04/12 15:44:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"

# define RAY_MIN 0.0001f
# define RAY_MAX 1.0e30f
# define PLANE 1
# define SPHERE 2

typedef struct    s_data
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 t_data;

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

typedef struct	s_ray
{
	t_vector	*origin;
	t_vector	*direction;
	float		max_t;
}				t_ray;

/*
** 1: plane
** 2: sphere
** 3: cylinder
** 4: square
** 5: triangle
*/

typedef struct	s_shape
{
	int			id;
	float		diameter;
	t_vector	*center;
	t_vector	*position;
	t_vector	*normal;
	int			color_r;
	int			color_g;
	int			color_b;
}				t_shape;

typedef struct	s_intersec
{
	t_ray	*ray;
	float	t;
	t_shape	*shape;
	// add details about surface, materials, etc
}				t_intersec;

typedef struct	s_camera
{
	t_vector	*origin;
	t_vector	*direction;
	t_vector	*up;
	t_vector	*right;
	float		h;
	float		w;
}				t_camera;

/* WINDOW */
t_data	*init_window(void);
void	color_window(t_data data, t_camera camera, t_shape sphere, t_shape plane);
/* VECTORS */
t_vector	*init_vector(float x, float y, float z);
float		square(float x);
float		length_square(t_vector *u);
float		length(t_vector *u);
float		normalize(t_vector *u);
float		dot_product(t_vector *u, t_vector *v);
t_vector	*cross_product(t_vector *u, t_vector *v);
t_vector	*vector_diff(t_vector *u, t_vector *v);
/* RAYS */
t_ray		*init_ray(t_vector *u, t_vector *v, float t);
t_vector	*point_on_ray(t_ray ray, float t);
/* INTERSECTIONS */
t_intersec	*init_intersection(t_ray *ray);
int			intersected(t_intersec *intersec);
t_vector	*intersection(t_intersec *intersec);

t_shape		*init_shape(void);
/* PLANE */
t_shape	*init_plane(t_shape *plane);
int		plane_intersection(t_intersec *intersec, t_shape *plane);
/* SPHERE */
t_shape	*init_sphere(t_shape *sphere);
int		sphere_intersection(t_intersec *intersec, t_shape *sphere);
int		sphere_points(t_intersec *intersec, float a, float b, float discriminant);
/* CAMERA */
t_camera	*init_camera(t_vector *origin, t_vector *orientation, float aspect_ratio, float fov);
t_ray		*make_ray(t_camera *camera, float u, float v);

#endif
