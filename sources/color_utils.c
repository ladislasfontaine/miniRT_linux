/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 16:03:51 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/21 17:27:57 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color		color_add(t_color c1, t_color c2)
{
	t_color	c;

	c.r  = (c1.r > c2.r) ? c1.r : c2.r;
	c.g  = (c1.g > c2.g) ? c1.g : c2.g;
	c.b  = (c1.b > c2.b) ? c1.b : c2.b;
	return (c);
}

t_color		color_mix_light(t_color c1, t_color light)
{
	t_color	c;

	c.r  = (float)c1.r * (float)light.r / 255.0;
	c.g  = (float)c1.g * (float)light.g / 255.0;
	c.b  = (float)c1.b * (float)light.b / 255.0;
	return (c);
}

t_color		color_multiply(t_color c1, float ratio)
{
	t_color	c;

	if (ratio > 1)
		ratio = 1;
	c.r  = (float)c1.r * ratio;
	c.g  = (float)c1.g * ratio;
	c.b  = (float)c1.b * ratio;
	return (c);
}
