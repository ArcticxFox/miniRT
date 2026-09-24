#include "parsing.h"

void	print_spheres(t_data *minirt)
{
	int	i;

	printf("\n========== SPHERES ==========\n");
	printf("Count: %d / Capacity: %d\n",
		minirt->sph_count, minirt->sph_cap);

	i = 0;
	while (i < minirt->sph_count)
	{
		printf("\nSphere %d\n", i);
		printf("  Coordinates: %.6f, %.6f, %.6f\n",
			minirt->sphere[i].coords[0],
			minirt->sphere[i].coords[1],
			minirt->sphere[i].coords[2]);
		printf("  Diameter: %.6f\n",
			minirt->sphere[i].diameter);
		printf("  rgb: %d, %d, %d\n",
			minirt->sphere[i].rgb[0],
			minirt->sphere[i].rgb[1],
			minirt->sphere[i].rgb[2]);
		i++;
	}
}

void	print_planes(t_data *minirt)
{
	int	i;

	printf("\n========== PLANES ==========\n");
	printf("Count: %d / Capacity: %d\n",
		minirt->pl_count, minirt->pl_cap);

	i = 0;
	while (i < minirt->pl_count)
	{
		printf("\nPlane %d\n", i);
		printf("  Coordinates: %.6f, %.6f, %.6f\n",
			minirt->plane[i].coords[0],
			minirt->plane[i].coords[1],
			minirt->plane[i].coords[2]);
		printf("  Normal: %.6f, %.6f, %.6f\n",
			minirt->plane[i].threed_nov[0],
			minirt->plane[i].threed_nov[1],
			minirt->plane[i].threed_nov[2]);
		printf("  rgb: %d, %d, %d\n",
			minirt->plane[i].rgb[0],
			minirt->plane[i].rgb[1],
			minirt->plane[i].rgb[2]);
		i++;
	}
}

void	print_cylinders(t_data *minirt)
{
	int	i;

	printf("\n========== CYLINDERS ==========\n");
	printf("Count: %d / Capacity: %d\n",
		minirt->cyl_count, minirt->cyl_cap);

	i = 0;
	while (i < minirt->cyl_count)
	{
		printf("\nCylinder %d\n", i);
		printf("  Coordinates: %.6f, %.6f, %.6f\n",
			minirt->cylinder[i].coords[0],
			minirt->cylinder[i].coords[1],
			minirt->cylinder[i].coords[2]);
		printf("  Normal: %.6f, %.6f, %.6f\n",
			minirt->cylinder[i].threed_nov[0],
			minirt->cylinder[i].threed_nov[1],
			minirt->cylinder[i].threed_nov[2]);
		printf("  Diameter: %.6f\n",
			minirt->cylinder[i].diameter);
		printf("  Height: %.6f\n",
			minirt->cylinder[i].height);
		printf("  rgb: %d, %d, %d\n",
			minirt->cylinder[i].rgb[0],
			minirt->cylinder[i].rgb[1],
			minirt->cylinder[i].rgb[2]);
		i++;
	}
}

void	print_light(t_data *minirt)
{
	printf("\n========== LIGHT ==========\n");
	printf("Position: %.6f, %.6f, %.6f\n",
		minirt->light.lightpoint[0],
		minirt->light.lightpoint[1],
		minirt->light.lightpoint[2]);
	printf("Brightness: %.6f\n",
		minirt->light.brightness);
}

void	print_camera(t_data *minirt)
{
	printf("\n========== CAMERA ==========\n");
	printf("Viewpoint: %.6f, %.6f, %.6f\n",
		minirt->camera.viewpoint[0],
		minirt->camera.viewpoint[1],
		minirt->camera.viewpoint[2]);
	printf("Normal: %.6f, %.6f, %.6f\n",
		minirt->camera.threed_nov[0],
		minirt->camera.threed_nov[1],
		minirt->camera.threed_nov[2]);
	printf("fov: %.6f\n",
		minirt->camera.fov);
}

void	print_ambient_light(t_data *minirt)
{
	printf("\n========== AMBIENT LIGHT ==========\n");
	printf("Ratio: %.6f\n",
		minirt->ambient_light.ratio);
	printf("rgb: %d, %d, %d\n",
		minirt->ambient_light.rgb[0],
		minirt->ambient_light.rgb[1],
		minirt->ambient_light.rgb[2]);
}

void	print_everything(t_data *minirt)
{
	print_ambient_light(minirt);
	print_camera(minirt);
	print_light(minirt);
	print_spheres(minirt);
	print_planes(minirt);
	print_cylinders(minirt);
}
