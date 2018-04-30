#include "opencl.h"

int						ray_sphere_inter(t_sphere *s, t_ray *ray, float *t)
{
	float3				rayToCenter;
	float3				dist;
	float				small_delta;];

	dist = ray->pos - sphere->pos;
	dotProduct = dot(ray->dir, dist);
	small_delta = dotProduct * dotProduct - dot(dist, dist) + sphere->radius * sphere->radius;
	if (small_delta < 0.0f)
		return (0);
	*t = -dotProduct - sqrt(small_delta);
	if (*t < 0.0f)
		*t = -dotProduct + sqrt(small_delta);
	return (*t >= 0.0f);
}

int						ray_plane_inter(t_plane *plane, t_ray *ray, float *t)
{
	float				dotProduct;

	dotProduct = dot(ray->dir, plane->normal);
	if (dotProduct == 0.0f)
		return (0);
	*t = -dot(plane->normal, ray->pos - plane->pos) / dotProduct;
	return (*t >= 0.0f);
}
