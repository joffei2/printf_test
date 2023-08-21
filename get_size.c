#include "main.h"

/**
 * get_size - Calculates the size for cast the args
 * @format: Format string where to print the args
 * @x: List of args to be printed.
 *
 * Return: size.
 */
int get_size(const char *format, int *x)
{
	int curr_x = *x + 1;
	int size = 0;

	if (format[curr_x] == 'l')
		size = S_LONG;
	else if (format[curr_x] == 'h')
		size = S_SHORT;

	if (size == 0)
		*x = curr_x - 1;
	else
		*x = curr_x;

	return (size);
}
