#include "host.h"

int				get_cone_material(t_scene *scene, char **str, int *cone_num, int *index, int *i, int total_line)
{
	if(ft_isdigit(str[*index][*i]))
		scene->cones[*cone_num].m.color_type = (int)ft_atof(str[*index] , &(*i));
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
		scene->cones[*cone_num].m.color.x = (cl_float)ft_atof(str[*index], &(*i));

		scene->cones[*cone_num].m.color.y = (cl_float)ft_atof(str[*index], &(*i));
		scene->cones[*cone_num].m.color.z = (cl_float)ft_atof(str[*index], &(*i));
		scene->cones[*cone_num].m.color.w = (cl_float)ft_atof(str[*index], &(*i));
		//set_material_color(&scene->cones[*cone_num].m.color, &str[*index][*i], &(*i));
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
		scene->cones[*cone_num].m.reflective = (float)ft_atof(str[*index], i);
		scene->cones[*cone_num].m.refractive = (float)ft_atof(str[*index], i);
	}
	else
		return(error_at_line("wrong material reflective refractive  param number", *index, str, total_line));

	if(0 != ft_strcmp("}", &str[(*index)][*i]))
		return(error_at_line("wrong material en accolade", *index, str, total_line));
	return (0);
}


int					parse_cone(t_scene *scene, int *cone_num, char **str, int *index, int total_line)
{
	int				i;

	if(0 == ft_strcmp("cone{", str[*index]))
	{
		if(0 == ft_strncmp("pos:", str[++(*index)], 4))
		{
			i = 5;
			if(0 == check_param_number(&str[*index][i], *index, 3))
			{
				scene->cones[*cone_num].pos.x = (cl_float)ft_atof(str[*index], &i);
				scene->cones[*cone_num].pos.y = (cl_float)ft_atof(str[*index], &i);
				scene->cones[*cone_num].pos.z = (cl_float)ft_atof(str[*index], &i);
				//set_vector(&scene->cones[*cone_num].pos, &str[*index][i], &i);
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
				scene->cones[*cone_num].radius = ft_atof(str[*index], &i);
			else
				return (error_at_line("Error line:", *index, str, total_line));
		}
		else
			return (error_at_line("Error line:", *index, str,total_line));;
		if(0 == ft_strncmp("dir:", str[++(*index)], 4))
		{
			i = 5;
			if(0 == check_param_number(&str[*index][i], *index, 3))
			{
				scene->cones[*cone_num].dir.x = (cl_float)ft_atof(str[*index], &i);
				scene->cones[*cone_num].dir.y = (cl_float)ft_atof(str[*index], &i);
				scene->cones[*cone_num].dir.z = (cl_float)ft_atof(str[*index], &i);

				//set_vector(&scene->cones[*cone_num].dir, &str[*index][i], &i);
			}
			else
				return (1);
		}
		else
			return (error_at_line("Error line:", *index, str, total_line));
		if(0 == strncmp("is_cut:", str[++(*index)], 7))
		{
			i = 8;
			scene->cones[*cone_num].is_cut = (int)ft_atof(&str[*index][i], &i);
		}
		else
			return (error_at_line("Error line : ", *index, str, total_line));
		if(0 == ft_strncmp("cut_axe:", str[++(*index)], 8))
		{
			i = 9;
			if(0 == check_param_number(&str[*index][i], *index, 3))
			{
				scene->cones[*cone_num].cut_axe.x = (cl_float)ft_atof(&str[*index][i], &i);
				scene->cones[*cone_num].cut_axe.y = (cl_float)ft_atof(&str[*index][i], &i);
				scene->cones[*cone_num].cut_axe.z = (cl_float)ft_atof(&str[*index][i], &i);

				//set_vector(&scene->cones[*cone_num].cut_axe, &str[*index][i], &i);
			}
			else
				return (error_at_line("Error line:", *index, str, total_line));
		}
		else
			return (error_at_line("Error line: ", *index, str, total_line));
		if(0 == strncmp("cut_length:", str[++(*index)], 11))
		{
			i = 12;
			scene->cones[*cone_num].cut_length = (cl_float)ft_atof(str[*index], &i);
		}
		else
			return (error_at_line("Error line : ", *index, str, total_line));
		if(0 == ft_strncmp("material{", str[++(*index)], 9))
		{
			i = 9;
			if(0 != get_cone_material(scene, str, cone_num, index, &i, total_line ))
				return (error_at_line("Error line:", *index, str, total_line));
		}
		else
			return (error_at_line("Error line:", *index, str, total_line));
		/*if(0 == ft_strncmp("color:", str[++(*index)], 6))
		{
			i = 7;
			if(0 == check_param_number(&str[*index][i], *index, 3))
			{
				
				//set_vector(&scene->cones[*cone_num].m.color, &str[*index][i], &i);
			}
			else
				return (error_at_line("Error line", *index));
		}
		else
			return (error_at_line("Error line:", *index));*/
		if(0 == ft_strcmp("}", str[++(*index)]))
		{
			(*cone_num)++;
			*index += 2;
			return (0);
		}
		return (1);
	}
	return (0);
}
