#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include <limits.h>
# include <float.h>

typedef struct s_cylinder
{
	double	coords[3];
	double	threed_NOV[3];
	double	diameter;
	double	height;
	int		RGB[3];
}	t_cylinder;

typedef struct s_plane
{
	double	coords[3];
	double	threed_NOV[3];
	int		RGB[3];
}	t_plane;

typedef struct s_sphere
{
	double	coords[3];
	double	diameter;
	int		RGB[3];
}	t_sphere;

typedef struct s_light
{
	double	lightpoint[3];
	double	brightness;
}	t_light;

typedef struct s_camera
{
	double	viewpoint[3];
	double	threed_NOV[3];
	double	FOV;
}	t_camera;

typedef struct s_amb_light
{
	double	ratio;
	int		RGB[3];
}	t_amb_light;

typedef struct s_data
{
	t_amb_light ambient_light;
	t_camera	camera;
	t_light		light;
	t_sphere	*sphere;
	int			sph_cap;
	int			sph_count;
	t_plane		*plane;
	int			pl_cap;
	int			pl_count;
	t_cylinder	*cylinder;
	int			cyl_cap;
	int			cyl_count;
}	t_data;

typedef int	(*t_parse_func)(char **split, t_data *minirt);

typedef struct s_parser
{
	char			*string;
	t_parse_func	func;
}	t_parser;

int		program_setup(int ac, char **av, t_data *minirt);

//============== PARSING ==============

int 	parse_line(char *line, t_data *minirt);

// int		check_alpha(char *string);
char	**split_multi_comma(char *str);
int		parse_colours(char *str, int *colour_tab);
int		valid_number(char *str);
int		valid_float_number(char *str);
int		parse_float_array(char **input, double *table, double lower, double upper);
int		parse_coords(char *str, double *table, double lower, double upper);
void	*ft_realloc(void *ptr, int old_size, int new_size);

int		amb_parse(char **split, t_data *minirt);
int		cam_parse(char **split, t_data *minirt);
int		light_parse(char **split, t_data *minirt);
int		sphere_parse(char **split, t_data *minirt);
int		plane_parse(char **split, t_data *minirt);
int		cylinder_parse(char **split, t_data *minirt);

void	print_everything(t_data *minirt);

#endif
