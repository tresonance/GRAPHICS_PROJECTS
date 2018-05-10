#include "host.h"

void			err_exit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

int				error_at_line(char *str, int line, char **scene_tab, int file_num_line)
{
	fprintf(stderr, "%s : %d\n", str, line + 1);
	free_scene_string(scene_tab, file_num_line);
	return (1);
}


char			*kernel_src(char *file)
{
	FILE		*fp;
	char		*src;
	long int	src_size;

	fp = fopen(file, "r");
	if(fp)
	{
		fseek(fp, 0,SEEK_END);
		src_size = ftell(fp);
		rewind(fp);
		if(NULL == (src = (char*)malloc(src_size + 1)))
			err_exit("Cannot allocate kernel");
		src[src_size] = '\0';
		fread(src, 1, src_size, fp);
		fclose(fp);
		return (src);
	}
	else
		return(NULL);

	return (src);
}

int					load_data_from_file(char *scene_file, t_scene *scene, t_cam *cam , int display_flag)
{
	char			**tab;
	int				num_line;
	int				index;

	index = 0;
	scene->num_light = 0;
	scene->num_sphere = 0;
	scene->num_cone = 0;
	scene->num_plane = 0;
	scene->num_cylinder = 0;
	scene->num_box = 0;
	tab = get_scene(scene_file, &num_line);
	if(tab == NULL)
		err_exit("Cannot read scene file");
	if(parse_camera(cam, tab, &index, num_line ))
	{
		free_scene_string(tab, num_line);
		return (1);
	}

	while(index < num_line)
	{
		if(parse_light(scene, &scene->num_light, tab, &index, num_line)
		|| parse_sphere(scene, &scene->num_sphere, tab, &index, num_line)
		|| parse_cylinder(scene, &scene->num_cylinder, tab, &index, num_line)
		|| parse_cone(scene, &scene->num_cone, tab, &index, num_line)
		|| parse_plane(scene, &scene->num_plane, tab, &index, num_line)
		|| parse_box(scene, &scene->num_box, tab, &index, num_line))
		{
			free_scene_string(tab, num_line);
			err_exit("---[STOP:]--> Pasring Error");

		}
	}
	if(display_flag)
		display_scene_data(scene, cam);
	free_scene_string(tab, num_line);
	return (0);
}
