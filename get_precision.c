#include "main.h"

/**
 * get_precision - Calculate precision for printing
 * @format: Format string where to print the args
 * @x: List of args to be printed
 * @arg_ls: list of args
 *
 * Return: precision
 */
int get_precision(const char *format, int *x, va_list arg_ls)
{
	int curr_x = *x + 1;
	int precision = -1;

	if (format[curr_x] != '.')
		return (precision);

	precision = 0;

	for (curr_x += 1; format[curr_x] != '\0'; curr_x++)
	{
		if (is_digit(format[curr_x]))
		{
			precision *= 10;
			precision += format[curr_x] - '0';
		}
		else if (format[curr_x] == '*')
		{
			curr_x++;
			precision = va_arg(arg_ls, int);
			break;
		}
		else
			break;
	}

	*x = curr_x - 1;

	return (precision);
}
