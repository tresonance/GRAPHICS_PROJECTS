#include "host.h"

int				get_box_material(t_scene *scene, char **str, int *box_num, int *index, int *i, int total_line)
{
	if(ft_isdigit(str[*index][*i]))
		scene->boxs[*box_num].m.color_type = (int)ft_atof(str[*index] , &(*i));
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
		scene->boxs[*box_num].m.color.x = (cl_float)ft_atof(str[*index], &(*i));

		scene->boxs[*box_num].m.color.y = (cl_float)ft_atof(str[*index], &(*i));
		scene->boxs[*box_num].m.color.z = (cl_float)ft_atof(str[*index], &(*i));
		scene->boxs[*box_num].m.color.w = (cl_float)ft_atof(str[*index], &(*i));
		//set_material_color(&scene->boxs[*box_num].m.color, &str[*index][*i], &(*i));
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
		scene->boxs[*box_num].m.reflective = (float)ft_atof(str[*index], i);
		scene->boxs[*box_num].m.refractive = (float)ft_atof(str[*index], i);
	}
	else
		return(error_at_line("wrong material reflective refractive  param number", *index, str, total_line));

	if(0 != ft_strcmp("}", &str[(*index)][*i]))
		return(error_at_line("wrong material en accolade", *index, str, total_line));
	return (0);
}


int					parse_box(t_scene *scene, int *box_num, char **str, int *index, int total_line)
{
	int				i;

	if(0 == ft_strcmp("box{", str[*index]))
	{
		if(0 == ft_strncmp("bottom_left:", str[++(*index)], 12))
		{
			i = 13;
			if(0 == check_param_number(&str[*index][i], *index, 3))
			{
				scene->boxs[*box_num].bottom_left.x = (cl_float)ft_atof(str[*index], &i);
				scene->boxs[*box_num].bottom_left.y = (cl_float)ft_atof(str[*index], &i);
				scene->boxs[*box_num].bottom_left.z = (cl_float)ft_atof(str[*index], &i);
				//set_vector(&scene->boxs[*box_num].bottom_left, &str[*index][i], &i);
			
			}else
				return (error_at_line("Error line:", *index, str, total_line));
		}
		else
			return (error_at_line("Error line : ", *index, str, total_line));
		if(0 == ft_strncmp("top_right:", str[++(*index)], 10))
		{
			i = 11;
			if(0 == check_param_number(&str[*index][i], *index, 3))
			{
				scene->boxs[*box_num].top_right.x = (cl_float)ft_atof(str[*index], &i);
				scene->boxs[*box_num].top_right.y = (cl_float)ft_atof(str[*index], &i);
				scene->boxs[*box_num].top_right.z = (cl_float)ft_atof(str[*index], &i);
				//set_vector(&scene->boxs[*box_num].top_right, &str[*index][i], &i);
			}
			else
				return (error_at_line("Error line:", *index, str, total_line));
		}
		else
			return (error_at_line("Error line : ", *index, str, total_line));

		if(0 == ft_strncmp("material{", str[++(*index)], 9))
		{
			i = 9;
			if(0 != get_box_material(scene, str, box_num, index, &i, total_line ))
				return (error_at_line("Error line:", *index, str, total_line));
		}
		else
			return (error_at_line("Error line:", *index, str, total_line));
		/*if(0 == ft_strncmp("color:", str[++(*index)], 6))
		{
			i = 7;
			if(0 == check_param_number(&str[*index][i], *index, 3))
			{
				scene->boxs[*box_num].top_right.x = (cl_float)ft_atof(str[*index], &i);
				scene->boxs[*box_num].top_right.y = (cl_float)ft_atof(str[*index], &i);
				scene->boxs[*box_num].top_right.z = (cl_float)ft_atof(str[*index], &i);

				//set_vector(&scene->boxs[*box_num].m.color, &str[*index][i], &i);
			}
			else
				return (error_at_line("Error line", *index, str, total_line));
		}
		else
			return (error_at_line("Error line:", *index, str, total_line));*/
		if(0 == ft_strcmp("}", str[++(*index)]))
		{
			(*box_num)++;
			*index += 2;
			return (0);
		}
		return (1);
	}
	return (0);
}
