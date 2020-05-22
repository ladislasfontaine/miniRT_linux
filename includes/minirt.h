/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 14:20:39 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/22 16:25:07 by lafontai         ###   ########.fr       */
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
# include "printf.h"
# include "libft.h"
# include "../minilibx/mlx.h"

# define RAY_MIN 0.01f
# define RAY_MAX 1.0e30f
# define PI 3.14159265359
# define PLANE		1
# define SPHERE		2
# define CYLINDER	3
# define SQUARE		4
# define TRIANGLE	5

# define BMP_FILE_NAME "image.bmp"
# define BMP_FILE_HDR_SIZE 14
# define BMP_INFO_HDR_SIZE 40

typedef struct	s_img
{
	void	*mlx_img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}				t_img;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
	int		img_id;
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
}				t_intersec;

typedef struct	s_scene
{
	t_resolution	*res;
	t_ambient		*ambient;
	t_list			*cameras;
	t_list			*shapes;
	t_list			*lights;
	t_list			*imgs;
	t_data			*win;
	int				save;
}				t_scene;

typedef struct	s_triangle
{
	t_vector	*v0v1;
	t_vector	*v0v2;
	t_vector	*pvec;
	t_vector	*tvec;
	t_vector	*normal;
	float		det;
	float		invdet;
	float		u;
	float		v;
	float		t;
}				t_triangle;

typedef struct	s_cyl
{
	t_vector	*cross;
	t_vector	*cross2;
	t_vector	*p0;
	t_vector	*inter;
	t_shape		*plane1;
	t_shape		*plane2;
	float		a;
	float		b;
	float		c;
	float		det;
	float		t;
	float		t1;
	float		t2;
	float		t3;
	float		t4;
}				t_cyl;

typedef struct	s_lights
{
	t_list		*lst_cpy;
	t_light		*light;
	t_vector	*light_dir;
	t_vector	*point;
	t_intersec	*light_ray;
	float		light_ratio;
	float		distance;
}				t_lights;

void			arguments_error(t_scene *scene, int ac, char **av);
void			scene_error(t_scene *scene);
void			error_and_quit(t_scene *scene, char *error);

int				parse_file(char *file, t_scene *scene);
void			parse_line(char *line, t_scene *scene);
int				parse_int(char *line, int *n);
int				parse_float(char *line, float *f);
void			parse_float_two(char *line, int *i, int *len, int *dec);
void			parse_float_three(float *f, t_vector v, int neg);
int				parse_color(char *line, t_color *color);
int				parse_vector(char *line, t_vector *vector);
int				parse_resolution(char *line, t_scene *scene);
int				parse_ambient(char *line, t_scene *scene);
int				parse_camera(char *line, t_scene *scene);
int				parse_light(char *line, t_scene *scene);
int				parse_sphere(char *line, t_scene *scene);
int				parse_plane(char *line, t_scene *scene);
int				parse_square(char *line, t_scene *scene);
void			parse_cylinder(char *line, t_scene *scene);
int				parse_triangle(char *line, t_scene *scene);
int				is_space(char *line);

t_scene			*init_scene(void);
void			clear_scene(t_scene *scene);
void			delete_shape(void *element);
void			delete_camera(void *element);
void			delete_light(void *element);
void			delete_images(t_list **lst, t_scene *scene);

t_img			*init_image(t_scene *scene);
void			create_images(t_scene *sc);
int				color_image(t_scene *scene, t_camera *camera, t_img *img);
int				change_camera(t_scene *scene, int id);
int				save_image(t_scene *scene);
void			bitmap_file_header(t_scene *scene, int padding_size, int fd);
void			bitmap_info_header(t_scene *scene, int fd);
void			create_bmp_image(t_scene *scene, char *file_name);

void			init_mlx(t_scene *scene);
void			init_window(t_scene *scene);
void			listen_events(t_scene *scene);
int				get_key(int key, t_scene *scene);
void			check_all_shapes(t_list *shapes, t_intersec *intersec);
void			check_all_lights(t_scene *scene, t_intersec *intersec);
int				close_and_quit(t_scene *scene);

t_vector		*init_vector(float x, float y, float z);
t_vector		*get_point(t_vector *origin, t_vector *dir, float t);
float			square(float x);
float			length_square(t_vector *u);
float			length(t_vector *u);
float			normalize(t_vector *u);
float			dot_product(t_vector *u, t_vector *v);
t_vector		*cross_product(t_vector *u, t_vector *v);
t_vector		*vector_diff(t_vector *u, t_vector *v);
t_vector		*vector_add(t_vector *u, t_vector *v);
t_vector		*vector_mul(t_vector *u, float n);
void			check_normal_vector(t_scene *scene, t_vector *u);
float			get_angle(t_vector *u, t_vector *v);

t_ray			*init_ray(t_vector *u, t_vector *v, float t);
t_vector		*point_on_ray(t_ray ray, float t);
void			check_rays(t_scene *scene, char *data, t_vector vec,
							t_camera *camera);

t_intersec		*init_intersection(t_ray *ray);
int				intersected(t_intersec *intersec);
t_vector		*intersection(t_intersec *intersec);
void			clear_intersection(t_intersec *intersec);

t_shape			*init_shape(void);
t_shape			*init_plane(t_vector *position, t_vector *normal);
int				plane_intersection(t_intersec *intersec, t_shape *plane);
t_shape			*init_sphere(t_shape *sphere);
int				sphere_intersection(t_intersec *intersec, t_shape *sphere);
int				sphere_points(t_intersec *intersec, float a, float b,
							float discriminant);
int				sphere_normal_vector(t_intersec *intersec, int inside);
t_shape			*init_square(t_vector *c, t_vector *n, float side,
				t_color *color);
int				square_intersection(t_intersec *intersec, t_shape *square);
int				triangle_intersection(t_intersec *intersec, t_shape *tri);
void			triangle_calculations(t_intersec *intersec, t_shape *tri,
				t_triangle *t);
int				cylinder_intersection(t_intersec *intersec, t_shape *cy);
void			find_cylinder_base(t_intersec *intersec, t_shape *cy,
				t_shape *plane);
float			check_cylinder_base(t_shape *plane, t_vector *inter,
				t_vector *n);
t_vector		*cylinder_normal(t_vector *inter, t_shape *cy, float t3);

t_camera		*init_camera(t_vector *origin, t_vector *orientation,
							float fov);
t_camera		*init_camera_null(void);
void			camera_vector_calculation(t_scene *scene, t_camera *camera);
void			clear_camera(t_camera *cam);
t_ray			*make_ray(t_scene *scene, t_camera *camera, float u, float v);
t_light			*init_light_null(void);
void			add_light_to_pixel(t_intersec *intersec, t_light *light,
				float ratio);
t_color			*init_color(int r, int g, int b);
void			check_color_range(t_scene *scene, t_color *color);
void			add_ambient_light(t_scene *scene, t_intersec *intersec);
t_color			color_add(t_color c1, t_color c2);
t_color			color_mix_light(t_color c1, t_color light);
t_color			color_multiply(t_color c1, float ratio);

#endif
