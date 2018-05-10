#include "host.h"

int					parse_light(t_scene *scene, int *light_num, char **str, int *index, int total_line)
{
	int				i;

	if(0 == ft_strcmp("light{", str[*index]))
	{
		if(0 == ft_strncmp("pos:", str[++(*index)], 4))
		{
			i = 5;
			if(0 == check_param_number(&str[*index][i], *index, 3))
			{
				scene->lights[*light_num].pos.x = (cl_float)ft_atof(str[*index], &i);
				scene->lights[*light_num].pos.y= (cl_float)ft_atof(str[*index], &i);
				scene->lights[*light_num].pos.z = (cl_float)ft_atof(str[*index], &i);
				//set_vector(&scene->lights[*light_num].pos, str[*index], &i);
			}
			else
				return (error_at_line("Error line:", *index, str, total_line));
		}
		else
			return (error_at_line("Error line: ", *index, str, total_line));
		if(0 == ft_strncmp("light_type:", str[++(*index)], 11))
		{
			i = 12;
			if(ft_isdigit(str[*index][i]) && (ft_strlen(&str[*index][i]) == 1))
				scene->lights[*light_num].light_type = (int)ft_atof(str[*index], &i);
			else
				return (error_at_line("Error line: ", *index, str, total_line));
		}
		else
			return (error_at_line("Error line: ", *index, str, total_line));
		if(0 == ft_strncmp("dir:", str[++(*index)], 4))
		{
			i = 5;
			if(0 == check_param_number(&str[*index][i], *index, 3))
			{
				scene->lights[*light_num].dir.x = (cl_float)ft_atof(str[*index], &i);
				scene->lights[*light_num].dir.y = (cl_float)ft_atof(str[*index], &i);
				scene->lights[*light_num].dir.w = (cl_float)ft_atof(str[*index], &i);

				//set_vector(&scene->lights[*light_num].dir, str[*index], &i);
			}
			else
				return (error_at_line("Error line: ", *index, str, total_line));;
		}
		else
			return (error_at_line("Error line:", *index, str, total_line));
		if(0 == ft_strncmp("color:", str[++(*index)], 6))
		{
			i = 7;
			if(0 == check_param_number(&str[*index][i], *index, 4))
			{
				scene->lights[*light_num].color.x = (cl_float)ft_atof(str[*index], &i);
				scene->lights[*light_num].color.y = (cl_float)ft_atof(str[*index], &i);
				scene->lights[*light_num].color.z = (cl_float)ft_atof(str[*index], &i);
				scene->lights[*light_num].color.w = (cl_float)ft_atof(str[*index], &i);
				//set_color(&scene->lights[*light_num].color, str[*index], &i);
			}
			else
				return (error_at_line("Error line", *index, str, total_line));
		}
		else
			return (error_at_line("Error line:", *index, str, total_line));
		if(0 == ft_strcmp("}", str[++(*index)]))
		{
			(*light_num)++;
			*index += 2;
			scene->standart_material.color_type = 0;
			scene->standart_material.color.x = 1.0f;
			scene->standart_material.color.y = 1.0f;
			scene->standart_material.color.z = 1.0f;
			scene->standart_material.color.w = 1.0f;
			scene->standart_material.reflective = 0.0f;
			scene->standart_material.refractive = 0.0f;
			return (0);
		}
		return (error_at_line("Error line:", *index, str, total_line));
	}
	scene->standart_material.color_type = 1;
	scene->standart_material.color.x = 0.0f;
	scene->standart_material.color.y = 0.0f;
	scene->standart_material.color.z = 0.0f;
	scene->standart_material.color.w = 1.0f;
	scene->standart_material.reflective = 0.0f;
	scene->standart_material.refractive = 0.0f;
	return (0);
}
