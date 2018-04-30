#ifndef __HEADER_H__
#define __HEADER_H__

#include <Opencl/cl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAXSOURCE_SIZE (0x100000)
#define WIDTH 600
#define HEIGHT 600
#define BIAS 0.0001
//#define MAXSOURCE_SIZE 4096
#define PI 3.14159265358979323846264338327950288419716939937511

typedef struct			s_material
{
	int					color_type;
	cl_float4			color;
	float				reflectivity;
	float				refractivity;
}						t_material;

typedef struct			s_phere
{
	cl_float4			pos;
	float				radius;
	t_material			material;
}						t_sphere;

typedef struct			s_plane
{
	cl_float4			pos;
	cl_float4			normal;
	t_material			material;
}						t_plane;

typedef struct			s_cylinder
{
	cl_float4			pos;
	cl_float4			normal;
	t_material			material;
}						t_cylinder;

typedef struct			s_cone
{
	cl_float4			pos;
	cl_float4			normal;
	t_material			material;;
}						t_cone;

typedef struct			s_cube
{
	cl_float4			pos_min;
	cl_float4			pos_max;
	t_material			material;
}						t_cube;

typedef struct			s_light
{
	cl_float4			pos;
	cl_float4			color;
}						t_light;

typedef struct			s_ray
{
	cl_float4			pos;
	cl_float4			dir;
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

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data;
	int					end;
	int					bpp;
	int					size_line;
}						t_env;

typedef struct			t_camera
{
	cl_float4			pos;
	cl_float4			lookat;
	cl_float4			up;
	cl_float4			right;
	cl_float4			forward;
}						t_camera;

typedef struct			s_opencl
{
	cl_platform_id		platform;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				device_scene;
	cl_mem				device_camera;
	cl_mem				device_ortho;
	cl_mem				device_perspective;
	cl_int				err;
	char				*kernel_src;
}						t_opencl;

/*
 * init_scene.c
 */
t_scene					init_scene(void);
t_camera				init_camera(void);

/*
 * host.c
 */
void					init_opencl(t_opencl *p);
void					compile_opencl_program(t_opencl *p);
void					release_opencl(t_opencl *p);

/*
 * projection_matrix.c
 */
//float			*init_ortho(float l, float r, float t, float b, float n, float f);
void		init_ortho(float l, float r, float t, float b, float n, float f, float m[16]);
//float			*init_perspective(float fov, float aspect_ratio, float f, float n);
void		init_perspective(float fov, float aspect_ratio, float f, float n, float m[16]);
#endif
