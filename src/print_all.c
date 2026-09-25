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
			minirt->sphere[i].center.x,
			minirt->sphere[i].center.y,
			minirt->sphere[i].center.z);
		printf("  Diameter: %.6f\n",
			minirt->sphere[i].d);
		printf("  rgb: %d, %d, %d\n",
			minirt->sphere[i].rgb.r,
			minirt->sphere[i].rgb.g,
			minirt->sphere[i].rgb.b);
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
			minirt->plane[i].point_in_py.x,
			minirt->plane[i].point_in_py.y,
			minirt->plane[i].point_in_py.z);
		printf("  Normal: %.6f, %.6f, %.6f\n",
			minirt->plane[i].direction.x,
			minirt->plane[i].direction.y,
			minirt->plane[i].direction.z);
		printf("  rgb: %d, %d, %d\n",
			minirt->plane[i].rgb.r,
			minirt->plane[i].rgb.g,
			minirt->plane[i].rgb.b);
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
			minirt->cylinder[i].center.x,
			minirt->cylinder[i].center.y,
			minirt->cylinder[i].center.z);
		printf("  Normal: %.6f, %.6f, %.6f\n",
			minirt->cylinder[i].axis_dir.x,
			minirt->cylinder[i].axis_dir.y,
			minirt->cylinder[i].axis_dir.z);
		printf("  Diameter: %.6f\n",
			minirt->cylinder[i].d);
		printf("  Height: %.6f\n",
			minirt->cylinder[i].h);
		printf("  rgb: %d, %d, %d\n",
			minirt->cylinder[i].rgb.r,
			minirt->cylinder[i].rgb.g,
			minirt->cylinder[i].rgb.b);
		i++;
	}
}

void	print_light(t_data *minirt)
{
	printf("\n========== LIGHT ==========\n");
	printf("Position: %.6f, %.6f, %.6f\n",
		minirt->light.lightpoint.x,
		minirt->light.lightpoint.y,
		minirt->light.lightpoint.z);
	printf("Brightness: %.6f\n",
		minirt->light.brightness);
}

void	print_camera(t_data *minirt)
{
	printf("\n========== CAMERA ==========\n");
	printf("Viewpoint: %.6f, %.6f, %.6f\n",
		minirt->camera.origin.x,
		minirt->camera.origin.y,
		minirt->camera.origin.z);
	printf("Normal: %.6f, %.6f, %.6f\n",
		minirt->camera.threed_nov.x,
		minirt->camera.threed_nov.y,
		minirt->camera.threed_nov.z);
	printf("fov: %.6f\n",
		minirt->camera.fov);
}

void	print_ambient_light(t_data *minirt)
{
	printf("\n========== AMBIENT LIGHT ==========\n");
	printf("Ratio: %.6f\n",
		minirt->ambient_light.ratio);
	printf("rgb: %d, %d, %d\n",
		minirt->ambient_light.rgb.r,
		minirt->ambient_light.rgb.g,
		minirt->ambient_light.rgb.b);
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
