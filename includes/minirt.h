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
}				t_shape;

typedef struct	s_intersec
{
	t_ray	*ray;
	float	t;		// initialize to RAY_MAX
	t_shape	*shape;	// initialize to NULL
	// add details about surface, materials, etc
}				t_intersec;

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
int			intersected(t_intersec *intersec);
t_vector	*intersection(t_intersec *intersec);
/* PLANE */
int		plane_intersection(t_intersec *intersec, t_shape *plane);
/* sPHERE */
int		sphere_intersection(t_intersec *intersec, t_shape *sphere);
int		sphere_points(t_intersec *intersec, float a, float b, float discriminant);

#endif
