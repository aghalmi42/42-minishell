
#include "../../include/minishell.h"

char	*gc_strtrim(char const *s1, char const *set, t_list **gc_head)
{
	size_t	start;
	size_t	end;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	result = gc_malloc(sizeof(char) * (end - start + 1), gc_head);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1 + start, end - start + 1);
	return (result);
}

char	*gc_itoa(int n, t_list **gc_head)
{
	char	*result;
	int		len;

	len = len_number(n);
	result = gc_malloc(sizeof(char) * (len + 1), gc_head);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (n < 0)
		result[0] = '-';
	else if (n == 0)
		result[0] = '0';
	while (n != 0)
	{
		len--;
		result[len] = value_negatif(n % 10) + '0';
		n = n / 10;
	}
	return (result);
}
