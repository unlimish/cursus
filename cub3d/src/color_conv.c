int	get_r(int rgb)
{
	return (rgb & (0xFF << 16));
}

int	get_g(int rgb)
{
	return (rgb & (0xFF << 8));
}

int	get_b(int rgb)
{
	return (rgb & 0xFF);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
