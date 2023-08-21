#include "main.h"

/**
 * handle_write_char - Print string
 * @chara: character type
 * @buf: Buffer array that handles print
 * @flags:  Calculates flags.
 * @width: width
 * @precision: precision specs
 * @size: Size spec
 *
 * Return: Number of character to be printed.
 */
int handle_write_char(char chara, char buf[],
	int flags, int width, int precision, int size)
{
	int x = 0;
	char pad = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		pad = '0';

	buf[x++] = chara;
	buf[x] = '\0';

	if (width > 1)
	{
		buf[BUFF_SIZE - 1] = '\0';
		for (x = 0; x < width - 1; x++)
			buf[BUFF_SIZE - x - 2] = pad;

		if (flags & F_MINUS)
			return (write(1, &buf[0], 1) +
					write(1, &buf[BUFF_SIZE - x - 1], width - 1));
		else
			return (write(1, &buf[BUFF_SIZE - x - 1], width - 1) +
					write(1, &buf[0], 1));
	}

	return (write(1, &buf[0], 1));
}

/**
 * write_number - Prints strings
 * @is_negative: List of args
 * @idx: character types.
 * @buf: Buffer array that handle print
 * @flags:  Calculates flags
 * @width: width
 * @precision: precision spec
 * @size: Size spec
 *
 * Return: Number of character to be printed.
 */
int write_number(int is_negative, int idx, char buf[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - idx - 1;
	char pad = ' ', extra_c = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (is_negative)
		extra_c = '-';
	else if (flags & F_PLUS)
		extra_c = '+';
	else if (flags & F_SPACE)
		extra_c = ' ';

	return (write_num(idx, buf, flags, width, precision,
		length, pad, extra_c));
}

/**
 * write_num - Write numbers that uses a bufffer
 * @idx: Index where the number starts on the buffer
 * @buf: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision spec
 * @length: Number length
 * @pad: Pading character
 * @extra_c: Extra character
 *
 * Return: Number of printed characters
 */
int write_num(int idx, char buf[],
	int flags, int width, int prec,
	int length, char pad, char extra_c)
{
	int x, pad_start = 1;

	if (prec == 0 && idx == BUFF_SIZE - 2 && buf[idx] == '0' && width == 0)
		return (0);
	if (prec == 0 && idx == BUFF_SIZE - 2 && buf[idx] == '0')
		buf[idx] = pad = ' ';
	if (prec > 0 && prec < length)
		pad = ' ';
	while (prec > length)
		buf[--idx] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (x = 1; x < width - length + 1; x++)
			buf[x] = pad;
		buf[x] = '\0';
		if (flags & F_MINUS && pad == ' ')
		{
			if (extra_c)
				buf[--idx] = extra_c;
			return (write(1, &buf[idx], length) + write(1, &buf[1], x - 1));
		}
		else if (!(flags & F_MINUS) && pad == ' ')
		{
			if (extra_c)
				buf[--idx] = extra_c;
			return (write(1, &buf[1], x - 1) + write(1, &buf[idx], length));
		}
		else if (!(flags & F_MINUS) && pad == '0')
		{
			if (extra_c)
				buf[--pad_start] = extra_c;
			return (write(1, &buf[pad_start], x - pad_start) +
				write(1, &buf[idx], length - (1 - pad_start)));
		}
	}
	if (extra_c)
		buf[--idx] = extra_c;
	return (write(1, &buf[idx], length));
}

/**
 * write_unsigned - Writes an unsigned digit
 * @is_negative: Number indicating if the number is a negative
 * @idx: Index where the number starts in the buffer
 * @buf: Character array
 * @flags: Flags spec
 * @width: Width spec
 * @precision: Precision spec
 * @size: Size specifier
 *
 * Return: Number of written characters
 */
int write_unsgnd(int is_negative, int idx,
	char buf[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - idx - 1, x = 0;
	char pad = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && idx == BUFF_SIZE - 2 && buf[idx] == '0')
		return (0);

	if (precision > 0 && precision < length)
		pad = ' ';

	while (precision > length)
	{
		buf[--idx] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';

	if (width > length)
	{
		for (x = 0; x < width - length; x++)
			buf[x] = pad;

		buf[x] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buf[idx], length) + write(1, &buf[0], x));
		}
		else
		{
			return (write(1, &buf[0], x) + write(1, &buf[idx], length));
		}
	}

	return (write(1, &buf[idx], length));
}

/**
 * write_pointer - Write memory address
 * @buf: Arrays of characters
 * @idx: Index where the number starts in the buffer
 * @length: Length of a number
 * @width: Width spec
 * @flags: Flags spec
 * @pad: Character that represents the pading
 * @extra_c: Character representing extra characters
 * @pad_start: Index where pading should start
 *
 * Return: Number of written character
 */
int write_pointer(char buf[], int idx, int length,
	int width, int flags, char pad, char extra_c, int pad_start)
{
	int x;

	if (width > length)
	{
		for (x = 3; x < width - length + 3; x++)
			buf[x] = pad;
		buf[x] = '\0';
		if (flags & F_MINUS && pad == ' ')
		{
			buf[--idx] = 'x';
			buf[--idx] = '0';
			if (extra_c)
				buf[--idx] = extra_c;
			return (write(1, &buf[idx], length) + write(1, &buf[3], x - 3));
		}
		else if (!(flags & F_MINUS) && pad == ' ')
		{
			buf[--idx] = 'x';
			buf[--idx] = '0';
			if (extra_c)
				buf[--idx] = extra_c;
			return (write(1, &buf[3], x - 3) + write(1, &buf[idx], length));
		}
		else if (!(flags & F_MINUS) && pad == '0')
		{
			if (extra_c)
				buf[--pad_start] = extra_c;
			buf[1] = '0';
			buf[2] = 'x';
			return (write(1, &buf[pad_start], x - pad_start) +
				write(1, &buf[idx], length - (1 - pad_start) - 2));
		}
	}
	buf[--idx] = 'x';
	buf[--idx] = '0';
	if (extra_c)
		buf[--idx] = extra_c;
	return (write(1, &buf[idx], BUFF_SIZE - idx - 1));
}
