#include "main.h"

/****************** print pointer ******************/
/**
 * print_pointer - Prints value of a pointer variable
 * @arg_ls: List of args
 * @buf: Buffer array that handle print
 * @flags:  Calculates flags
 * @width: width
 * @precision: Precision specs
 * @size: Size spec
 * Return: Number of chars to be printed.
 */
int print_pointer(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, pad = ' ';
	int inte = BUFF_SIZE - 2, length = 2, pad_strt = 1;
	unsigned long numb_adrs;
	char map_to[] = "0123456789abcdef";
	void *adrs = va_arg(arg_ls, void *);

	UNUSED(width);
	UNUSED(size);

	if (adrs == NULL)
		return (write(1, "(nil)", 5));

	buf[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	numb_adrs = (unsigned long)adrs;

	while (numb_adrs > 0)
	{
		buf[inte--] = map_to[numb_adrs % 16];
		numb_adrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	inte++;

	return (write_pointer(buf, inte, length,
		width, flags, pad, extra_c, pad_strt));
}

/************************* non printables *************************/
/**
 * print_non_printable - Print the ascii codes in hexa of non printable chars
 * @arg_ls: List of args
 * @buf: Buffer array that handles print
 * @flags:  Calculates flags
 * @width: width
 * @precision: Precision specs
 * @size: Size spec
 * Return: Number of chars to be printed
 */
int print_non_printable(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size)
{
	int x = 0, ofset = 0;
	char *str = va_arg(arg_ls, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[x] != '\0')
	{
		if (is_printable(str[x]))
			buf[x + ofset] = str[x];
		else
			ofset += append_hexa_code(str[x], buf, x + ofset);

		x++;
	}

	buf[x + ofset] = '\0';

	return (write(1, buf, x + ofset));
}

/************************* print reverse *************************/
/**
 * print_reverse - Print reverse string.
 * @arg_ls: List of args
 * @buf: Buffer aray that handle print
 * @flags:  Calculates flags
 * @width: width
 * @precision: Precision specs
 * @size: Size spec
 * Return: Numbers of chars to be printed
 */

int print_reverse(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size)
{
	char *str;
	int z, count = 0;

	UNUSED(buf);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(arg_ls, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (z = 0; str[z]; z++)
		;

	for (z = z - 1; z >= 0; z--)
	{
		char x = str[z];

		write(1, &x, 1);
		count++;
	}
	return (count);
}
/************************* prints strings in rot13 *************************/
/**
 * print_rot13strng - Print string in rot13.
 * @arg_ls: List of args
 * @buf: Buffer array that will handle print
 * @flags:  Calculates flags
 * @width: width
 * @precision: Precision specs
 * @size: Size spec
 * Return: Numbers of charsto be printed
 */
int print_rot13strng(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size)
{
	char z;
	char *str;
	unsigned int x, y;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(arg_ls, char *);
	UNUSED(buf);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(GHY)";
	for (x = 0; str[x]; x++)
	{
		for (y = 0; in[y]; y++)
		{
			if (in[y] == str[x])
			{
				z = out[y];
				write(1, &z, 1);
				count++;
				break;
			}
		}
		if (!in[y])
		{
			z = str[x];
			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
