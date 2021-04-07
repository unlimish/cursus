int main()
{
	char search = 'D';
	char	tmp[32] = "ABCDEF";
	printf("%s (search: %c)\n", tmp, search);
	printf("%p\n", ft_strchr(tmp,(int)search));
	printf("%p\n", strchr(tmp,(int)search));

	search = 'Z';
	printf("%s (search: %c)\n", tmp, search);
	printf("%p\n", ft_strchr(tmp,(int)search));
	printf("%p\n", strchr(tmp,(int)search));
}
