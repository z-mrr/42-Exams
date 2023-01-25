#include <stdlib.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

int	ft_pos(char *s)
{
	int	i = 1;

	while (s[i - 1]){
		if(s[i - 1] == '\n')
			return i;
		i++;
	}
	return 0;
}

int	ft_len(char *s)
{
	int	i = 0;

	while (s[i])
		i++;
	return i;
}

char	*ft_sub(char *s, int start, int len)
{
	if (!s || len < 1 || start >= ft_len(s))
		return 0;
	char	*str = malloc(sizeof(char) * (len + 1));
	int		i = -1;
	while (++i < len)
		str[i] = s[i + start];
	str[i] = '\0';
	return str;
}

char	*ft_join(char *s1, char *s2)
{
	if (!s1 || !s2)
		return 0;
	int		i = -1, j = -1;
	char	*s = malloc(sizeof(char) * (ft_len(s1) + 1 + ft_len(s2)));
	while (s1[++i])
		s[i] = s1[i];
	while (s2[++j])
		s[i + j] = s2[j];
	s[i + j] = '\0';
	return s;
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*buf = malloc((BUFFER_SIZE + 1));

	if (!buf || fd < 0 || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0){
		free(buf);
		return 0;
	}
	if (!s || !ft_pos(s)){
		int	r = read(fd, buf, BUFFER_SIZE);
		while (r){
			buf[r]='\0';
			if (!s)
				s = ft_sub(buf, 0, r);
			else{
				char	*t = s;
				s = ft_join(s, buf);
				free (t);
			}
			if (ft_pos(buf))
				break;
			r = read(fd, buf, BUFFER_SIZE);
		}
	}
	free(buf);
	if (!s)
		return 0;
	if (!ft_pos(s)){
		char	*ret = ft_sub(s, 0, ft_len(s));
		free(s);
		s = 0;
		return ret;
	}
	char	*ret = ft_sub(s, 0, ft_pos(s));
	char	*t = s;
	if (ft_len(s) == ft_pos(s))
		s = 0;
	else
		s = ft_sub(s, ft_pos(s), ft_len(s) - ft_pos(s));
	free(t);
	return ret;
}
