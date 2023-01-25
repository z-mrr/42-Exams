#include <stdarg.h>
#include <unistd.h>

int	len;
va_list	ap;

void	ft_putnbr(long long n, int base)
{
	if (n < 0){
		n = -n;
		write(1, "-", 1);
		len++;
	}
	if (!n){
		write(1, "0", 1);
		len++;
	}
	int	tab[21], i = 0;
	while (n){
		tab[i]=n % base;
		n /= base;
		i++;
	}
	char	*radix = "0123456789abcdef";
	while (i){
		i--;
		write(1, &radix[tab[i]], 1);
		len++;
	}
}

void	ft_conv(char spec)
{
	if(spec == '%'){
		write(1, "%", 1);
		len++;
	}
	else if (spec == 's'){
		char	*s = va_arg(ap, char *);
		if (!s)
			s = "(null)";
		while (*s){
			write(1,s,1);
			len++;
			s++;
		}
	}
	else if (spec == 'd'){
		int	d = va_arg(ap, int);
		ft_putnbr(d, 10);
	}
	else if (spec == 'x'){
		unsigned int	x = va_arg(ap, unsigned int);
		ft_putnbr(x, 16);
	}
}

int	ft_printf(const char *format, ...)
{
	len = 0;
	va_start(ap, format);

	while(*format){
		if (*format == '%'){
			format++;
			ft_conv(*format);
		}
		else{
			write(1, format, 1);
			len++;
		}
		format++;
	}
	va_end(ap);
	return len;
}
