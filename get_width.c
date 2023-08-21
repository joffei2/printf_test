#include "main.h"

/**
 * get_width - Calculates width for printing
 * @format: Format string where to print the args
 * @x: List of args to be printed.
 * @arg_ls: list of args.
 *
 * Return: width.
 */
int get_width(const char *format, int *x, va_list arg_ls)
{
	int curr_x;
	int width = 0;

	for (curr_x = *x + 1; format[curr_x] != '\0'; curr_x++)
	{
		if (is_digit(format[curr_x]))
		{
			width *= 10;
			width += format[curr_x] - '0';
		}
		else if (format[curr_x] == '*')
		{
			curr_x++;
			width = va_arg(arg_ls, int);
			break;
		}
		else
			break;
	}

	*x = curr_x - 1;

	return (width);
}
