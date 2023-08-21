#include "main.h"
/**
 * handle_print - Prints an argument depending on it's type
 * @fmt: Format string where to print the args
 * @arg_ls: List of args
 * @ind:
 * @buf: Buffer array that handle print.
 * @flags: Calculates flags
 * @width: get width.
 * @precision: Precision specs
 * @size: Size spec
 * Return: 1/2
 */
int handle_print(const char *fmt, int *ind, va_list arg_ls, char buf[],
	int flags, int width, int precision, int size)
{
	int z, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_stg}, {'%', print_perc},
		{'i', print_int}, {'d', print_int}, {'b', print_bin},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13strng}, {'\0', NULL}
	};
	for (z = 0; fmt_types[z].fmt != '\0'; z++)
		if (fmt[*ind] == fmt_types[z].fmt)
			return (fmt_types[z].fn(arg_ls, buf, flags, width, precision, size));

	if (fmt_types[z].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
