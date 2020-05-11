/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:31:58 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/11 10:17:53 by lafontai         ###   ########.fr       */
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
# include "keys.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"

# define RAY_MIN 0.0001f
# define RAY_MAX 1.0e30f
# define PLANE		1
# define SPHERE		2
# define CYLINDER	3
# define SQUARE		4
# define TRIANGLE	5

typedef struct	s_data
{
    void          *mlx_ptr;
    void          *mlx_win;
}				t_data;

typedef struct	s_color
{
    int		r;
    int		g;
    int		b;
}				t_color;

typedef struct	s_resolution
{
    int		w;
    int		h;
}				t_resolution;

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

typedef struct	s_camera
{
	t_vector	*origin;
	t_vector	*direction;
	t_vector	*up;
	t_vector	*right;
	float		fov;
}				t_camera;

typedef struct	s_light
{
	t_vector	*origin;
	float		brightness;
	t_color		*color;
}				t_light;

typedef struct	s_ambient
{
	t_color		*color;
	float		ratio;
}				t_ambient;

typedef struct	s_shape
{
	int			id;
	float		diameter;
	float		height;
	float		side;
	t_vector	*center;
	t_vector	*position;
	t_vector	*normal;
	t_vector	*p1;
	t_vector	*p2;
	t_vector	*p3;
	t_color		*color;
}				t_shape;

typedef struct	s_intersec
{
	t_ray		*ray;
	float		t;
	t_shape		*shape;
	t_vector	*normal;
	t_color		*color;
	t_color		*reflect;
	// add details about surface, materials, etc
}				t_intersec;

typedef struct	s_scene
{
	t_resolution	*resolution;
	t_ambient		*ambient;
	t_list			*cameras;
	t_list			*shapes;
	t_list			*lights;
	t_data			*window;
}				t_scene;


/* ERRORS */
int		arguments_error(int ac, char **av);
/* PARSING */
int		parse_file(char *file, t_scene *scene);
int		parse_line(char *line, t_scene *scene);
int		parse_int(char *line, int *n);
int		parse_float(char *line, float *f);
int		parse_color(char *line, t_color *color);
int		parse_vector(char *line, t_vector *vector);
int		parse_resolution(char *line, t_scene *scene);
int		parse_ambient(char *line, t_scene *scene);
int		parse_camera(char *line, t_scene *scene);
int		parse_light(char *line, t_scene *scene);
int		parse_sphere(char *line, t_scene *scene);
int		parse_plane(char *line, t_scene *scene);
int		parse_square(char *line, t_scene *scene);
int		parse_cylinder(char *line, t_scene *scene);
int		parse_triangle(char *line, t_scene *scene);
int		is_space(char *line);
/* SCENE */
t_scene	*init_scene(void);
void	clear_scene(t_scene *scene);
/* WINDOW */
t_data	*init_window(t_scene *scene);
void	listen_events(t_scene *scene);
int		get_key(int key, t_scene *scene);
int		get_mouse(int key, int x, int y, t_scene *scene);
void	color_window(t_scene *scene);
void	check_all_shapes(t_list *shapes, t_intersec *intersec);
void	check_all_lights(t_scene *scene, t_intersec *intersec);
int		close_and_quit(t_scene *scene);
/* VECTORS */
t_vector	*init_vector(float x, float y, float z);
t_vector	*get_point(t_vector *origin, t_vector *dir, float t);
float		square(float x);
float		length_square(t_vector *u);
float		length(t_vector *u);
float		normalize(t_vector *u);
float		dot_product(t_vector *u, t_vector *v);
t_vector	*cross_product(t_vector *u, t_vector *v);
t_vector	*vector_diff(t_vector *u, t_vector *v);
int			check_normal_vector(t_vector *u);
/* RAYS */
t_ray		*init_ray(t_vector *u, t_vector *v, float t);
t_vector	*point_on_ray(t_ray ray, float t);
/* INTERSECTIONS */
t_intersec	*init_intersection(t_ray *ray);
int			intersected(t_intersec *intersec);
t_vector	*intersection(t_intersec *intersec);

t_shape		*init_shape(void);
/* PLANE */
t_shape	*init_plane(t_shape *plane, t_vector *position, t_vector *normal);
int		plane_intersection(t_intersec *intersec, t_shape *plane);
/* SPHERE */
t_shape	*init_sphere(t_shape *sphere);
int		sphere_intersection(t_intersec *intersec, t_shape *sphere);
int		sphere_points(t_intersec *intersec, float a, float b, float discriminant);
int		sphere_normal_vector(t_intersec *intersec);
/* SQUARE */
int		square_intersection(t_intersec *intersec, t_shape *square);
/* CAMERA */
t_camera	*init_camera(t_vector *origin, t_vector *orientation, float fov);
t_camera	*init_camera_null(void);
t_ray		*make_ray(t_scene *scene, t_camera *camera, float u, float v);
/* LIGHT */
t_light	*init_light_null(void);
void	add_light_to_pixel(t_intersec *intersec, float ratio);
/* COLOR */
t_color		*init_color(int r, int g, int b);
int		check_color_range(t_color *color);
int		rgb_to_int(t_color *color);

#endif
