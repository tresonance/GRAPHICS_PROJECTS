#include "host.h"

void			display_camera_data(t_cam  *cam)
{
	printf("\nCAMERA: pos(%f, %f, %f), lookat(%f,%f,%f)\n", cam->pos.x, cam->pos.y, cam->pos.z, cam->lookat.x, cam->lookat.y, cam->lookat.z);
	printf("------------------------------------------------\n");
}


void			display_object_data(t_scene *s)
{
	int			i;

	i = -1;
	while(++i < s->num_light && s->num_light <= LIGHT_NUMBER_MAXI)
		printf("LIGHT: pos(%f, %f, %f), type(%d), dir(%f,%f,%f), color(%f %f %f %f)\n", s->lights[i].pos.x, s->lights[i].pos.y, s->lights[i].pos.z, s->lights[i].light_type,s->lights[i].dir.x, s->lights[i].dir.y, s->lights[i].dir.z, s->lights[i].color.x, s->lights[i].color.y, s->lights[i].color.z, s->lights[i].color.w);
	printf("-------------------------------------------------\n");

	i = -1;
	while(++i < s->num_plane && s->num_plane <= PLANE_NUMBER_MAXI)
		printf("PLANE: pos(%f, %f, %f), normal(%f,%f,%f), material{%d, {%f, %f, %f, %f}, %f, %f} }\n", s->planes[i].pos.x, s->planes[i].pos.y, s->planes[i].pos.z,  s->planes[i].normal.x, s->planes[i].normal.y, s->planes[i].normal.z, s->planes[i].m.color_type, s->planes[i].m.color.x,s->planes[i].m.color.y,s->planes[i].m.color.z,s->planes[i].m.color.w,s->planes[i].m.reflective,s->planes[i].m.refractive);
	printf("-------------------------------------------------\n");


	i = -1;
	while(++i < s->num_sphere && s->num_sphere <= SPHERE_NUMBER_MAXI)
		printf("SPHERE: pos(%f, %f, %f), radius(%f), material{%d, {%f, %f, %f %f}, %f, %f} }\n", s->spheres[i].pos.x, s->spheres[i].pos.y, s->spheres[i].pos.z, s->spheres[i].radius,s->planes[i].m.color_type, s->planes[i].m.color.x,s->planes[i].m.color.y,s->planes[i].m.color.z,s->planes[i].m.color.w,s->planes[i].m.reflective,s->planes[i].m.refractive);
	printf("-------------------------------------------------\n");

	i = -1;
	while(++i < s->num_cylinder && s->num_cylinder <= CYLINDER_NUMBER_MAXI)
		printf("CYLINDER: pos(%f, %f, %f), radius(%f), dir(%f,%f,%f), material{%d, {%f, %f, %f, %f}, %f, %f} }\n", s->cylinders[i].pos.x, s->cylinders[i].pos.y, s->cylinders[i].pos.z,  s->cylinders[i].radius, s->cylinders[i].dir.x, s->cylinders[i].dir.y, s->cylinders[i].dir.z,s->planes[i].m.color_type, s->planes[i].m.color.x,s->planes[i].m.color.y,s->planes[i].m.color.z,s->planes[i].m.color.w,s->planes[i].m.reflective,s->planes[i].m.refractive);
	printf("-------------------------------------------------\n");

	i = -1;
	while(++i < s->num_cone && s->num_cone <= CONE_NUMBER_MAXI)
		printf("CONE: pos(%f, %f, %f), radius(%f), dir(%f,%f,%f), material{%d, {%f, %f, %f, %f}, %f, %f} }\n", s->cones[i].pos.x, s->cones[i].pos.y, s->cones[i].pos.z,  s->cones[i].radius, s->cones[i].dir.x, s->cones[i].dir.y, s->cones[i].dir.z,s->planes[i].m.color_type, s->planes[i].m.color.x,s->planes[i].m.color.y,s->planes[i].m.color.z,s->planes[i].m.color.w,s->planes[i].m.reflective,s->planes[i].m.refractive);
	printf("-------------------------------------------------\n");

	i = -1;
	while(++i < s->num_box && s->num_box <= BOX_NUMBER_MAXI)
		printf("BOX: bottom_left(%f, %f, %f), top_right(%f,%f,%f), material{%d, {%f, %f, %f, %f}, %f, %f} }\n", s->boxs[i].bottom_left.x, s->boxs[i].bottom_left.y, s->boxs[i].bottom_left.z, s->boxs[i].top_right.x, s->boxs[i].top_right.y, s->boxs[i].top_right.z,s->boxs[i].m.color_type, s->boxs[i].m.color.x,s->boxs[i].m.color.y,s->boxs[i].m.color.z,s->boxs[i].m.color.w,s->boxs[i].m.reflective,s->boxs[i].m.refractive);
	printf("-------------------------------------------------\n");

	printf("SCENE STANDART: color(%f %f %f %f)\n", s->standart_material.color.x,s->standart_material.color.y,s->standart_material.color.z,s->standart_material.color.w );
}


void				display_scene_data(t_scene *scene, t_cam *cam)
{
	printf("----------- HOST DATA BEFORE COPYING __________ \n");
	display_camera_data(cam);
	display_object_data(scene);
}

void				display_scene_data_on_device(t_scene *scene, t_cam *cam)
{
	printf("----------- DEVICE  DATA AFTER COPYING __________ \n");
	display_camera_data(cam);
	display_object_data(scene);
}
