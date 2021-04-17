#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*result;
	size_t		len;
	size_t		i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		len = ft_strlen(s2);
	else if (s2 == NULL)
		len = ft_strlen(s1);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	if (!(result = (char *)malloc(len + 1)))
		return (NULL);
	i = 0;
	while (s1 != NULL && *s1 != '\0')
		result[i++] = *s1++;
	while (s2 != NULL && *s2 != '\0')
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}

char	*ft_strdup(const char *s)
{
	char				*result;
	size_t				size;
	unsigned char		*result_ptr;
	const unsigned char	*s_ptr;

	size = ft_strlen(s) + 1;
	if (!(result = malloc(size)))
		return (NULL);
	result_ptr = (unsigned char *)result;
	s_ptr = (const unsigned char *)s;
	while (size != 0)
	{
		*result_ptr++ = *s_ptr++;
		size--;
	}
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	const char	*ptr_s;
	char		str_c;
	size_t		len_s;

	ptr_s = (const char *)s;
	str_c = (char)c;
	len_s = ft_strlen(s) + 1;
	while (len_s != 0)
	{
		if (*ptr_s == str_c)
			return ((char *)ptr_s);
		ptr_s++;
		len_s--;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	char	*ptr_result;

	if (s == NULL)
		return (NULL);
	(len > ft_strlen(s + start)) ? (result = malloc(ft_strlen(s + start) + 1)) :
		(result = malloc(len + 1));
	if (result == NULL || (start >= ft_strlen(s) && len != 0))
		return (result);
	ptr_result = result;
	while (start != 0 && len != 0)
	{
		s++;
		start--;
	}
	while (len != 0 && *s != '\0')
	{
		*result = *s + start;
		result++;
		s++;
		len--;
	}
	*result = '\0';
	return (ptr_result);
}
