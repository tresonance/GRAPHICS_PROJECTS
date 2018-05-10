#include "host.h"

int				error(char *str, int line, int position, char **file_tab, int total_line)
{
	fprintf(stderr, "%s: line: %d, position: %d", str, line + 1, position);
	error_at_line("", line, file_tab, total_line);
	return (1);
}



int					check_material_color_param(char *str, int line, int param_number)
{
	int				i;
	int				num_space;
	int				continu;

	i = -1;
	num_space = 0;
	continu = TRUE;
	while(str[++i] && continu)
	{
		if(!ft_isdigit(str[i]))
		{
			if(str[i] == ' ')
				num_space++;
			else if (str[i] == '.')
				;
			else
				continu = FALSE;
		}
	}
	return (!(num_space + 1  == param_number));
}

/*void				set_material_color(cl_float4 *color, char *str, int *i)
{
	color->s[0] = (float)ft_atof(str, &(*i));
	color->s[1] = (float)ft_atof(str, &(*i));
	color->s[2] = (float)ft_atof(str, &(*i));
	color->s[3] = (float)ft_atof(str, &(*i));
}*/


int				get_plane_material(t_scene *scene, char **str, int *plane_num, int *index, int *i, int total_line)
{
	if(ft_isdigit(str[*index][*i]))
		scene->planes[*plane_num].m.color_type = (int)ft_atof(str[*index] , &(*i)); 
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
		scene->planes[*plane_num].m.color.x = (cl_float)ft_atof(str[*index], &(*i));

		scene->planes[*plane_num].m.color.y = (cl_float)ft_atof(str[*index], &(*i));
		scene->planes[*plane_num].m.color.z = (cl_float)ft_atof(str[*index], &(*i));
		scene->planes[*plane_num].m.color.w = (cl_float)ft_atof(str[*index], &(*i));
		//set_material_color(&scene->planes[*plane_num].m.color, &str[*index][*i], &(*i));
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
		scene->planes[*plane_num].m.reflective = (float)ft_atof(str[*index], i);
		scene->planes[*plane_num].m.refractive = (float)ft_atof(str[*index], i);
	}
	else
		return(error_at_line("wrong material reflective refractive  param number", *index, str, total_line));
	
	if(0 != ft_strcmp("}", &str[(*index)][*i]))
		return(error_at_line("wrong material en accolade", *index, str, total_line));
	return (0);
}

int					parse_plane(t_scene *scene, int *plane_num, char **str, int *index, int total_line)
{
	int				i;

	if(0 == ft_strcmp("plane{", str[*index]))
	{
		if(0 == ft_strncmp("pos:", str[++(*index)], 4))
		{
			i = 5;
			if(0 == check_param_number(&str[*index][i], *index, 3))
			{
				scene->planes[*plane_num].pos.x = (cl_float)ft_atof(str[*index], &i);
				scene->planes[*plane_num].pos.y = (cl_float)ft_atof(str[*index], &i);
				scene->planes[*plane_num].pos.z = (cl_float)ft_atof(str[*index], &i);
				//set_vector(&scene->planes[*plane_num].pos, &str[*index][i], &i);

			}
			else
				return (error_at_line("Error pos pram number line:", *index, str, total_line));
		}
		else
			return (error_at_line("Error wrong pos writing line: ", *index, str, total_line));
		if(0 == ft_strncmp("normal:", str[++(*index)], 7))
		{
			i = 8;
			if(0 == check_param_number(&str[*index][i], *index, 3))
			{
				scene->planes[*plane_num].normal.x = (cl_float)ft_atof(str[*index], &i);
				scene->planes[*plane_num].normal.y = (cl_float)ft_atof(str[*index], &i);
				scene->planes[*plane_num].normal.z = (cl_float)ft_atof(str[*index], &i);

				//set_vector(&scene->planes[*plane_num].normal, &str[*index][i], &i);
			}
			else
				return (error_at_line("Error normal param number line:", *index, str, total_line));
		}
		else
			return (error_at_line("Error wrong normal writing line:", *index, str, total_line));;
		if(0 == ft_strncmp("material{", str[++(*index)], 9))
		{
			i = 9;
			if(0 != get_plane_material(scene, str, plane_num, index, &i, total_line ))
				return (error_at_line("Error material line:", *index, str, total_line));
		}
		else
			return (error("Error material line:", *index, i, str, total_line));
		/*if(0 == ft_strncmp("color:", str[++(*index)], 6))
		{
			i = 7;
			if(0 == check_param_number(&str[*index][i], *index, 4))
				set_material_color(&scene->planes[*plane_num].m.color, &str[*index][i], &i);
			else
				return (error_at_line("Error material line", *index));
		}
		else
			return (error_at_line("Error wrong color writing line:", *index));*/
		if(0 == ft_strcmp("}", str[++(*index)]))
		{
			(*plane_num)++;
			*index += 2;
			return (0);
		}
		return (error("error: Miss \'}\' at the end ", *index, i, str, total_line));
	}
	return (0);
}
