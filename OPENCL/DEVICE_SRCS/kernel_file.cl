#include "cl_header.h"

t_ray					reflection_ray(float3 raydir, float3 normal, float3 inter_pos)
{
	t_ray				refl;

	refl.dir = raydir - 2.0f * normal * dot(raydir, normal);
	refl.dir = normalize(refl.dir);
	refl.pos = inter_pos + (float)BIAS * raydir;
	return (refl);
}


t_ray					refraction_ray(float3 raydir, float3 normal, float refr_index, float3 inter_pos)
{
	float cos_incidence;
	float cos_trans_square;
	t_ray				refr;

	cos_incidence = -dot( normal, raydir );
	cos_trans_square = 1.0f - refr_index * refr_index * (1.0f - cos_incidence * cos_incidence);
	refr.dir = (refr_index * raydir) + (refr_index * cos_incidence - sqrt( cos_trans_square )) * normal;
	refr.pos = inter_pos + (float)BIAS * raydir;
	refr.dir = normalize(refr.dir);
	return (refr);
}

t_ray					shadow_ray(float3 inetr_pos, t_light l, float3  raydir, float *light_dist)
{
	t_ray				shadow_ray;

	shadow_ray.pos = inetr_pos + ((float)BIAS) * raydir;
	if(l.light_type <= 0)
	{
		shadow_ray.dir = l.pos - shadow_ray.pos;
		*light_dist = (float)length(shadow_ray.dir);
	}
	else
	{
		shadow_ray.dir = l.pos - shadow_ray.pos;
		*light_dist = (float)length(shadow_ray.dir);
		shadow_ray.dir = l.dir;
	}
	shadow_ray.dir = normalize(shadow_ray.dir);
	return (shadow_ray);
}

void		cut_obj(float3 axe, float3 pos, t_ray ray, float *t)
{
	float3 hit_point = ray.pos + ray.dir * (*t);
	float3 vec = normalize(hit_point - pos);
	if (((float)dot(axe, vec)) > 0.0)
		*t = -1.0f;
}

int						inter_solver(float a, float b, float c, float *t)
{
	float disc = b * b - c;
	if(disc < 0.0f)
		return (FALSE);
	*t = -b - sqrt(disc);
	if(*t < 0.0f)
	{
		*t = -b  + sqrt(disc);
		if(*t < 0.0f)
			return (FALSE);
	}
	return (TRUE);
}


int						ray_sphere_inter(t_sphere s, t_ray ray, float *t)
{
	float3 dist = ray.pos - s.pos;
	float b  = (float)dot(ray.dir, dist);
	float c  = (float)dot(dist, dist) - (s.radius *  s.radius);
	return (inter_solver(1.0f, b, c, t));
}



int						ray_plane_inter(t_plane p, t_ray ray, float *t)
{
	float dot_product;

	dot_product = dot(ray.dir, p.normal);
	if ( dot_product > (float)(-TOLERANCE) && dot_product < (float)TOLERANCE)
	{
		return (FALSE);
	}
	*t = dot(p.normal, p.pos - ray.pos) / dot_product ;
	return (*t >= 0.0f && *t < (float)MAXDIST);
}

int						ray_cylinder_inter(t_cylinder c, t_ray ray, float *t)
{
	float3	dist;
	float	a;
	float	b;
	float	ci;
	int		result;

	dist = ray.pos - c.pos;
	c.dir = normalize(c.dir);
	a = 1.0f  - pow(dot(c.dir, ray.dir), 2);
	b = 2.0 * (dot(dist, ray.dir) - (dot(c.dir, dist) * dot(c.dir, ray.dir)));
	ci = dot(dist, dist) - pow(((float)dot(c.dir, dist)), 2) - (c.radius * c.radius);
	result = inter_solver(a, b, ci, t);
	return(result);
	if(!result);
		return (FALSE);
	if(c.is_cut);
		cut_obj(c.cut_axe, c.pos, ray, t);
	return (*t > 0.0f);
}

int						ray_cone_inter(t_cone c, t_ray ray, float *t)
{
	float3	dist;
	float	a;
	float	b;
	float	ci;
	float result;

	dist = ray.pos - c.pos;
	c.dir = normalize(c.dir);
	a = 1.0f  - (1 + pow(tan(c.radius), 2)) * pow(dot(ray.dir, c.dir), 2);
	b = 2.0 * (dot(ray.dir, dist) - (1 + pow(tan(c.radius), 2)) *
			dot(ray.dir, c.dir) * dot(dist, c.dir));
	ci = dot(dist, dist) - (1 + pow(tan(c.radius), 2)) * pow(dot(dist, c.dir), 2);
	result = inter_solver(a, b, ci, t);
	return(result);
	if(!result);
		return (FALSE);
	if(c.is_cut);
		cut_obj(c.cut_axe, c.pos, ray, t);
	return (*t > 0.0f);
}

float					intersection_obj(__global t_scene *s, t_ray ray, void **obj, int *type_obj)
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
				*obj = (void *)&s->spheres[i];
				*type_obj = SPHERE;
			}
		}
	}
	i = -1;
	while(++i < s->num_plane)
	{
		/*if(ray_plane_inter(s->planes[i], ray, &tmin))
		{
			if(tmin < dist)
			{
				dist = tmin;
				*obj = (void *)&s->planes[i];
				*type_obj = PLANE;
			}
		}*/
	}
	i = -1;
	while(++i < s->num_cylinder)
	{
		/*if(ray_cylinder_inter(s->cylinders[i], ray, &tmin))
		{
			if(tmin < dist)
			{
				dist = tmin;
				*obj = (void *)&s->cylinders[i];
				*type_obj = CYLINDER;
			}
		}*/
	}
	i = -1;
	while(++i < s->num_cone)
	{
		/*if(ray_cone_inter(s->cylinders[i], ray, &tmin))
		{
			if(tmin < dist)
			{
				dist = tmin;
				*obj = (void *)&s->cones[i];
				*type_obj = CONE;
			}
		}*/
	}
	return (dist);
}

float4						raytrace(__global t_scene *s, t_ray ray, int depth)
{
	float4					color;
	int						hit_type;
	void					*hit_obj;
	float					t;
	float3					normal;
	float3					hit_point;
	t_material				material;


	hit_obj = (void *)0;
	hit_type = -1.0f;
	t = (float)MAXDIST;

	color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	material = s->standart_material;
	t = intersection_obj(s, ray, &hit_obj, &hit_type);
	if(hit_obj)
	{
		hit_point = ray.pos + (t * ray.dir);
		if(hit_type == SPHERE)
		{
			normal = hit_point - ((t_sphere*)hit_obj)->pos;
			material = ((t_sphere*)hit_obj)->m;
		}
		else if (hit_type == PLANE)
		{
			normal = ((t_plane*)hit_obj)->normal;
			material = ((t_plane*)hit_obj)->m;
		}
		else if (hit_type == CYLINDER)
		{
			t_cylinder *cyl = (t_cylinder*)hit_obj;

			float3  dist = ray.pos - cyl->pos;
			float m = t * (float)dot(ray.dir,cyl->dir) + (float)dot(dist, cyl->dir);
			float3 left = hit_point - cyl->pos;
			float3 right = cyl->dir * m;
			normal = left - right;
			material = ((t_cylinder*)hit_obj)->m;
		}
		else if (hit_type == CONE)
		{
			t_cone *cone = (t_cone*)hit_obj;

			float3  dist = ray.pos - cone->pos;
			float m = t * (float)dot(ray.dir,cone->dir) + (float)dot(dist, cone->dir);
			float3 left = hit_point - cone->pos;
			float3 right = cone->dir * (1 + pow(tan(cone->dir), 2) * m);
			normal = left - right;
			material = ((t_cone*)hit_obj)->m;
		}
		int		i = -1;
		t_ray	shadow_r;
		float	light_dist;

		while(++i < s->num_light)
		{
			hit_obj = (void *)0;
			hit_type = -1;
			shadow_r = shadow_ray(hit_point, s->lights[i], ray.dir, &light_dist);
			t = intersection_obj(s, shadow_r, &hit_obj, &hit_type);
			if(t > light_dist)
				color += s->lights[i].color * max(0.0f, dot(normalize(normal), ray.dir));
		}
	}
	return ((float4)clamp(color, 0.0f, 1.0f));
}

__kernel void raytracing( __global float4  *color, __global t_scene *scene, __global t_cam *cam, uint width, uint height) {

	float	aspect = (float)(width) / ((float)(height));
	int  y  = get_global_id(0) / height;
	int  x = get_global_id(0) % width;
	float xindent = ((2.0f * (x + 0.5f) / ((float)width)) - 1.0f) * aspect ;
	float yindent = (1.0f  - ((2.0f * (y + 0.5f)) / ((float)height))); 
	t_ray ray;

	ray.pos = cam->pos;
	//ray.dir = normalize((float3)(yindent, xindent, -1.0f) - cam->pos);
	cam->dir = normalize(cam->lookat - cam->pos);
	cam->up = normalize(cam->up);
	cam->right = cross(cam->dir, cam->up);
	ray.dir = (float)length(cam->lookat - cam->pos) * cam->dir + yindent * cam->up + xindent * cam->right;
	ray.dir = normalize(ray.dir);
	color[get_global_id(0)] = raytrace(scene, ray, 0);
}
