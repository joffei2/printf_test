#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf: Printf function
 * @format: format
 * Return: Printed characters
 */
int _printf(const char *format, ...)
{
	int x, prnt = 0, charct_print = 0;
	int flags, width, precision, size, buf_ind = 0;
	va_list arg_ls;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(arg_ls, format);

	for (x = 0; format && format[x] != '\0'; x++)
	{
		if (format[x] != '%')
		{
			buffer[buf_ind++] = format[x];
			if (buf_ind == BUFF_SIZE)
				print_buffer(buffer, &buf_ind);
			charct_print++;
		}
		else
		{
			print_buffer(buffer, &buf_ind);
			flags = get_flags(format, &x);
			width = get_width(format, &x, arg_ls);
			precision = get_precision(format, &x, arg_ls);
			size = get_size(format, &x);
			++x;
			prnt = handle_print(format, &x, arg_ls, buffer,
				flags, width, precision, size);
			if (prnt == -1)
				return (-1);
			charct_print += prnt;
		}
	}

	print_buffer(buffer, &buf_ind);

	va_end(arg_ls);

	return (charct_print);
}

/**
 * print_buffer - Prints content of the buffer existing
 * @buffer: array of characters
 * @buf_ind: Index at which to add following character, represent length.
 */
void print_buffer(char buffer[], int *buf_ind)
{
	if (*buf_ind > 0)
		write(1, &buffer[0], *buf_ind);

	*buf_ind = 0;
}
