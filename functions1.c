#include "main.h"

/************************* print unsigned number *************************/
/**
 * print_unsigned - Prints the  unsigned numbers
 * @arg_ls: List a of args
 * @buf: Buffer array that handle print
 * @flags:  Calculates flags
 * @width: width
 * @precision: Precision specs
 * @size: Size spec
 * Return: Number of chararacters to be printed.
 */
int print_unsigned(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	unsigned long int numb = va_arg(arg_ls, unsigned long int);

	numb = convert_size_unsgnd(numb, size);

	if (numb == 0)
		buf[x--] = '0';

	buf[BUFF_SIZE - 1] = '\0';

	while (numb > 0)
	{
		buf[x--] = (numb % 10) + '0';
		numb /= 10;
	}

	x++;

	return (write_unsgnd(0, x, buf, flags, width, precision, size));
}

/************* print unsigned octal numbers  ****************/
/**
 * print_octal - Prints unsigned octal numbers
 * @arg_ls: List of args
 * @buf: Buffer array that  handle print
 * @flags:  Calculates flags
 * @width: width
 * @precision: Precision specs
 * @size: Size spec
 * Return: Number of characters to be printed
 */
int print_octal(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size)
{

	int x = BUFF_SIZE - 2;
	unsigned long int numb = va_arg(arg_ls, unsigned long int);
	unsigned long int inte_numb = numb;

	UNUSED(width);

	numb = convert_size_unsgnd(numb, size);

	if (numb == 0)
		buf[x--] = '0';

	buf[BUFF_SIZE - 1] = '\0';

	while (numb > 0)
	{
		buf[x--] = (numb % 8) + '0';
		numb /= 8;
	}

	if (flags & F_HASH && inte_numb != 0)
		buf[x--] = '0';

	x++;

	return (write_unsgnd(0, x, buf, flags, width, precision, size));
}

/************** print unsigned numbers in hex **************/
/**
 * print_hexadecimal - Prints unsigned numbers in gexadecimals
 * @arg_ls: List of args
 * @buf: Buffer array that handle print
 * @flags:  Calculates flags
 * @width: width
 * @precision: Precision specs
 * @size: Size specs
 * Return: Number of character to be printed
 */
int print_hexadecimal(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(arg_ls, "0123456789abcdef", buf,
		flags, 'x', width, precision, size));
}

/************* print unsigned numbers in upper hex **************/
/**
 * print_hexa_upper - Prints unsugned numbers in upper hexadecimals
 * @arg_ls: List of args
 * @buf: Buffer array that handle print
 * @flags:  Calculates flags
 * @width: width
 * @precision: Precision specs
 * @size: Size spec
 * Return: Number of charatcter to be printed
 */
int print_hexa_upper(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(arg_ls, "0123456789ABCDEF", buf,
		flags, 'X', width, precision, size));
}

/************** print unsigned upper or lower hex numbers **************/
/**
 * print_hexa - Prints unsigned upper or lower hex numbers
 * @arg_ls: List of args
 * @map_to: Array of values to map the numb
 * @buf: Buffer array that handle print
 * @flags:  Calculates flags
 * @flag_ch: Calculates flags
 * @width: width
 * @precision: Precision specs
 * @size: Size spec
 * Return: Number of character to be printed
 */
int print_hexa(va_list arg_ls, char map_to[], char buf[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int z = BUFF_SIZE - 2;
	unsigned long int numb = va_arg(arg_ls, unsigned long int);
	unsigned long int inte_numb = numb;

	UNUSED(width);

	numb = convert_size_unsgnd(numb, size);

	if (numb == 0)
		buf[z--] = '0';

	buf[BUFF_SIZE - 1] = '\0';

	while (numb > 0)
	{
		buf[z--] = map_to[numb % 16];
		numb /= 16;
	}

	if (flags & F_HASH && inte_numb != 0)
	{
		buf[z--] = flag_ch;
		buf[z--] = '0';
	}

	z++;

	return (write_unsgnd(0, z, buf, flags, width, precision, size));
}
