#include "cl_header.h"

int						ray_sphere_inter(t_sphere *s, t_ray *ray, float *t)
{
	flaot3				dist;
	float				dot_product;
	float				distance;

	dist = s->pos - ray->pos;
	dot_product = dot(ray->dir, dis);
	distance = dot_product * dot_product - dot(dist, dist) + s->radius *  s->radius;
	if(distance < 0.0f)
		return (FALSE);
	*t = (dot_product - sqrt(distance));
	if(*t < 0.0f)
	{
		*t = (dot_product + sqrt(distance);
		if(*t < 0.0f)
			return (FALSE);
	}
	return (TRUE);
}


int						ray_plane_inter(t_plane *p, t_ray *ray, float *t)
{
	float dot_product
	
	dot_product = dot(ray->dir, p->normal);
	if ( dot_product == 0)
	{
		return (FALSE);
	}
	*t = dot(p->normal, p->pos - ray->pos) / dot_product ;

	return *t >= 0;
}

float					intersection_obj(t_scene *s, t_ray *ray, void **obj, int *type_obj)
{
	float				dist;
	float				tmin;;
	int					i;

	dist = (float)MAXDIST;
	i = -1;
	while(++i < s->num_sphere)
	{
		if(ray_sphere_inter(s->spheres[i], ray, &tmin))
		{
			if(tmin < dist)
			{
				dist = tmin;
				type_obj = &s->spheres[i];
				*type_obj = SPHERE;
			}
		}
	}
	i = -1;
	while(++i < s->num_sphere)
	{
		if(ray_planes_inter(s->planes[i], ray, &tmin))
		{
			if(tmin < dist)
			{
				dist = tmin;
				type_obj = &s->spheres[i];
				type_obj = PLANE;
			}
		}
	}
	return (dist);
}
