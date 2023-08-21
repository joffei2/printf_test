#include "main.h"

/**
 * is_printable - Evaluates character if printed
 * @chara: Character to be evaluated
 *
 * Return: 1 if chara is printable, else 0
 */
int is_printable(char chara)
{
	if (chara >= 32 && chara < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Attach ascci in hexadecimal code to the buffer
 * @buf: Array of charsacters
 * @x: Index where to start appending.
 * @ascii_code: ASSCI code
 * Return: 3
 */
int append_hexa_code(char ascii_code, char buf[], int x)
{
	char map_to[] = "0123456789ABCDEF";
	if (ascii_code < 0)
		ascii_code *= -1;

	buf[x++] = '\\';
	buf[x++] = 'x';

	buf[x++] = map_to[ascii_code / 16];
	buf[x] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies as to when a character is a digit
 * @chara: Character to be evaluated
 *
 * Return: 1 if chara is a digit, else 0
 */
int is_digit(char chara)
{
	if (chara >= '0' && chara <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a number to specific size
 * @numb: Number to be casted
 * @size: Number that indicates the type to be casted
 *
 * Return: Value casted of numb
 */
long int convert_size_number(long int numb, int size)
{
	if (size == S_LONG)
		return (numb);
	else if (size == S_SHORT)
		return ((short)numb);

	return ((int)numb);
}

/**
 * convert_size_unsigne - Casts a number to specific size
 * @numb: Number to be casted
 * @size: Number that indicates the type to be casted
 *
 * Return: value casted of numb
 */
long int convert_size_unsgnd(unsigned long int numb, int size)
{
	if (size == S_LONG)
		return (numb);
	else if (size == S_SHORT)
		return ((unsigned short)numb);

	return ((unsigned int)numb);
}
