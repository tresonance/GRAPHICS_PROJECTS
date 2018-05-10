#include "host.h"

int					radius_checker(char *str)
{
	int				i;
	int				dot;
	int				digit;

	dot = 0;
	i = -1;
	while(str[++i])
	{
		if(!ft_isdigit(str[i]))
		{
			if(str[i] == '.' && ++dot)
			{
				if(i == 0)
					return (1);
				if(dot > 1)
					return (1);
			}
		}
	}
	return (0);
}

int				get_sphere_material(t_scene *scene, char **str, int *sphere_num, int *index, int *i, int total_line)
{
	if(ft_isdigit(str[*index][*i]))
		scene->spheres[*sphere_num].m.color_type = (int)ft_atof(str[*index] , &(*i));
	else
		return (error("color_type error line:", *index, *i, str, total_line));
	if(str[*index][*i] != ',')
		return (error("error virgule line:", *index, *i, str, total_line));
	if(str[*index][++(*i)] != ' ')
		return (error("error ewpace line:", *index, *i, str, total_line));
	if(str[*index][++(*i)] != '{')
		return (error("error accolade ouvrante line:", *index, *i, str, total_line));

	if(0 == check_material_color_param(&str[*index][++(*i)], *index, 4))
	{
		scene->spheres[*sphere_num].m.color.x = (cl_float)ft_atof(str[*index], &(*i));

		scene->spheres[*sphere_num].m.color.y = (cl_float)ft_atof(str[*index], &(*i));
		scene->spheres[*sphere_num].m.color.z = (cl_float)ft_atof(str[*index], &(*i));
		scene->spheres[*sphere_num].m.color.w = (cl_float)ft_atof(str[*index], &(*i));
		//set_material_color(&scene->spheres[*sphere_num].m.color, &str[*index][*i], &(*i));
	}
	else
		return(error_at_line("wrong material color param number", *index, str, total_line));
	//*i = ft_strchr(str[*index], '}') - str[*index];
//printf("AFTER------>%c<----\n", str[*index][(*i)] != '}'	);
	if(str[*index][(*i)] != '}')
		return (error("error accolade fermante line:", *index, *i, str, total_line));
	if(str[*index][++(*i)] != ',')
		return 	error_at_line("error virgule derrire acc fermanante line:", *index, str, total_line);
	if(str[*index][++(*i)] != ' ')
		error("error espace derrie acc fermante line:", *index, *i, str, total_line);
	if(0 == check_material_color_param(&str[*index][++(*i)], *index, 2))
	{
		scene->spheres[*sphere_num].m.reflective = (float)ft_atof(str[*index], i);
		scene->spheres[*sphere_num].m.refractive = (float)ft_atof(str[*index], i);
	}
	else
		return(error_at_line("wrong material reflective refractive  param number", *index, str, total_line));

	if(0 != ft_strcmp("}", &str[(*index)][*i]))
		return(error_at_line("wrong material en accolade", *index, str, total_line));
	return (0);
}


int					parse_sphere(t_scene *scene, int *sphere_num, char **str, int *index, int total_line)
{
	int				i;

	if(0 == ft_strcmp("sphere{", str[*index]))
	{
		if(0 == ft_strncmp("pos:", str[++(*index)], 4))
		{
			i = 5;
			if(0 == check_param_number(&str[*index][i], *index, 3))
			{
				scene->spheres[*sphere_num].pos.x = (cl_float)ft_atof(str[*index], &i);
				scene->spheres[*sphere_num].pos.y = (cl_float)ft_atof(str[*index], &i);
				scene->spheres[*sphere_num].pos.z = (cl_float)ft_atof(str[*index], &i);
				//set_vector(&scene->spheres[*sphere_num].pos, &str[*index][i], &i);
			}
			else
				return (error_at_line("Error line:", *index, str, total_line));
		}
		else
			return (error_at_line("Error line: ", *index, str, total_line));
		if(0 == ft_strncmp("radius:", str[++(*index)], 7))
		{
			i = 8;
			if(0 == radius_checker(&str[*index][i]))
				scene->spheres[*sphere_num].radius = ft_atof(str[*index], &i);
			else
				return (error_at_line("Error line:", *index, str, total_line));
		}
		else
			return (error_at_line("Error line:", *index, str, total_line));;
		if(0 == ft_strncmp("material{:", str[++(*index)], 9))
		{
			i = 9;
			if(0 != get_sphere_material(scene, str, sphere_num, index, &i, total_line ))
				return (error_at_line("Error line:", *index, str, total_line));
		}
		else
			return (error_at_line("Error line:", *index, str, total_line));
		/*if(0 == ft_strncmp("color:", str[++(*index)], 6))
		{
			i = 7;
			if(0 == check_param_number(&str[*index][i], *index, 3))
			{
				scene->spheres[*sphere_num].m.color.x = (cl_float)ft_atof(str[*index], &i);
				scene->spheres[*sphere_num].m.color.y = (cl_float)ft_atof(str[*index], &i);
				scene->spheres[*sphere_num].m.color.z = (cl_float)ft_atof(str[*index], &i);
				scene->spheres[*sphere_num].m.color.w = (cl_float)ft_atof(str[*index], &i);
				//set_vector(&scene->spheres[*sphere_num].m.color, &str[*index][i], &i);
			}
			else
				return (error_at_line("Error line", *index));
		}
		else
			return (error_at_line("Error line:", *index));*/
		if(0 == ft_strcmp("}", str[++(*index)]))
		{
			(*sphere_num)++;
			*index += 2;
			return (0);
		}
		return (error_at_line("Wrong Camera data", *index, str, total_line));
	}
	return (0);
}
