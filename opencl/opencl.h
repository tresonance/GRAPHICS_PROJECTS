#ifndef __OPENCL_H__
#define __OPENCL_H__
#include <OpenCL/opencl.h>

#define WIDTH 600
#define HEIGHT 600
const int kwidth = 600;
const int kheight = 600;
const float kMaxRenderDist = 8000.0;

#define BIAS 0.0001
//#define MAXSOURCE_SIZE 4096
#define PI 3.14159265358979323846264338327950288419716939937511

typedef struct			s_material
{
	int					color_type;
	float4				color;
	float				reflectivity;
	float				refractivity;
}						t_material;

typedef struct			s_phere
{
	float4				pos;
	float				radius;
	t_material			material;
}						t_sphere;

typedef struct			s_plane
{
	float4				pos;
	float4				normal;
	t_material			material;
}						t_plane;

typedef struct			s_cylinder
{
	float4				pos;
	float4				normal;
	t_material			material;
}						t_cylinder;

typedef struct			s_cone
{
	float4				pos;
	float4				normal;
	t_material			material;;
}						t_cone;

typedef struct			s_cube
{
	float4				pos_min;
	float4				pos_max;
	t_material			material;
}						t_cube;

typedef struct			s_light
{
	float4				pos;
	float4				color;
}						t_light;

typedef struct			s_ray
{
	float4				pos;
	float4				dir;
}						t_ray;

typedef struct			s_scene
{
	t_sphere			sphere;
	int					num_sphere;

	t_plane				plane;
	int					num_plane;

	t_cylinder			cylinder;
	int					num_cylinder;

	t_cone				cone;
	int					num_cone;

	t_cube				cube;
	int					num_cube;

	t_light				light;
	int					num_light;

	t_material			material;
}						t_scene;

typedef struct			t_camera
{
	float4				pos;
	float4				lookat;
	float4				up;
	float4				right;
	float4				forward;
}						t_camera;

typedef					s_matrix
{
	float16				m;
}						t_matrix;

/*
 * inter.cl
 */
float					ray_sphere_inter(t_sphere *s, t_ray *ray, float *t);
float					ray_plane_inter(t_plane *p, t_ray *ray, float *t);
float4					raytrace(t_scene *scene, t_ray *ray);
/*
 * matrix.cl
 */
float3					matrix_vector_multiply(float *m1, float3 vec);
#endif
