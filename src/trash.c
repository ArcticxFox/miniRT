void	render_loop(void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;

	if (!mlx->needs_redraw)
		return ;
	printf("rendering\n");
	printf(
	"render: camera = %f %f %f\n",
	mlx->camera.origin.x,
	mlx->camera.origin.y,
	mlx->camera.origin.z
);
	mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){ {255, 255, 255, 255} });

	render_scene(mlx, mlx->camera);

	mlx_put_image_to_window(
		mlx->mlx,
		mlx->win,
		mlx->img,
		0,
		0
	);

	char	str[15];
	mlx_set_font(mlx->mlx, "default");
	mlx_set_font_scale(mlx->mlx, "default", 12.f);
	sprintf(str, "%.4f", mlx->camera.origin.x);
	mlx_string_put(mlx->mlx, mlx->win, 20, 20, (mlx_color){ .rgba = 0x0020FFFF }, "x:");
	mlx_string_put(mlx->mlx, mlx->win, 50, 20, (mlx_color){ .rgba = 0x0020FFFF }, str);

	sprintf(str, "%.4f", mlx->camera.origin.y);
	printf("\n\nhello str == %s\n\n", str);
	mlx_string_put(mlx->mlx, mlx->win, 20, 40, (mlx_color){ .rgba = 0x0020FFFF }, "y:");
	mlx_string_put(mlx->mlx, mlx->win, 50, 40, (mlx_color){ .rgba = 0x0020FFFF }, str);

	sprintf(str, "%.4f", mlx->camera.origin.z);
	mlx_string_put(mlx->mlx, mlx->win, 20, 60, (mlx_color){ .rgba = 0x0020FFFF }, "z:");
	mlx_string_put(mlx->mlx, mlx->win, 50, 60, (mlx_color){ .rgba = 0x0020FFFF }, str);


	mlx->needs_redraw = 0;
}


void	render_movind_scene(mlx_t *mlx, t_camera camera)
{
	int			x;
	int			y;
	double		viewport_x;
	double		viewport_y;
	t_ray		ray;
	mlx_color	*color = NULL;

	y = 0;
	while (y < mlx->info.height)
	{
		x = 0;
		while (x < mlx->info.width)
		{
			viewport_x = (2.0 * (x + 0.5) / mlx->info.width - 1.0) * mlx->info.width / mlx->info.height;
			viewport_y = 1.0 - 2.0 * (y + 0.5) / mlx->info.height;
			ray = camera_ray(mlx, camera, x, y);
			*color = ray_color(mlx, ray);
			mlx_set_image_region(mlx->mlx, mlx->img, x, y, x+5, y+5, color);
			x += 5;
		}
		y +=5;
	}
}
