#include <stdarg.h>
#include <unistd.h>

int	len;
va_list	ap;

void	ft_putnbr(long long n, int base)
{
	char	*radix = "0123456789abcdef";
	int		tab[21], i = 0;

	if (n < 0)
	{
		n = -n;
		write(1, "-", 1);
		len++;
	}
	if (!n)
	{
		write(1, "0", 1);
		len++;
	}
	while (n)
	{
		tab[i]=n % base;
		n /= base;
		i++;
	}
	while (i)
	{
		i--;
		write(1, &radix[tab[i]], 1);
		len++;
	}
}

void	ft_conv(char spec)
{
	char			*s;
	int				d;
	unsigned int	x;

	if(spec == '%')
	{
		write(1, "%", 1);
		len++;
	}
	else if (spec == 's')
	{
		s = va_arg(ap, char *);
		if (!s)
			s = "(null)";
		while (*s)
		{
			write(1,s,1);
			len++;
			s++;
		}
	}
	else if (spec == 'd')
	{
		d = va_arg(ap, int);
		ft_putnbr(d, 10);
	}
	else if (spec == 'x')
	{
		x = va_arg(ap, unsigned int);
		ft_putnbr(x, 16);
	}
}

int	ft_printf(const char *format, ...)
{
	len = 0;
	va_start(ap, format);

	while(*format)
	{
		if (*format == '%')
		{
			format++;
			ft_conv(*format);
		}
		else
		{
			write(1, format, 1);
			len++;
		}
		format++;
	}
	va_end(ap);
	return len;
}
