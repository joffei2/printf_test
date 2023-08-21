#ifndef MAIN_H
#define MAIN_H

#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16
#define S_LONG 2
#define S_SHORT 1



//typedef struct fmt {
    //char fmt;
   // int (*fn)(va_list, char[], int, int, int, int);
//} fmt_t;

//typedef struct fmt
//{
    //char fmt;
   // int (*fn)(va_list, char *, int, int, int, int);
//} fmt_t;

/**
 * struct fmt - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;




//typedef struct fmt fmt_t;

/*********** functions.c ******************/

int print_char(va_list argt_ls, char buf[],
	int flags, int width, int precision, int size);
int print_stg(va_list argt_ls, char buf[],
	int flags, int width, int precision, int size);
int print_perc(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size);
int print_int(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size);
int print_bin(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size);


/****************** functions1.c ******************/

int print_unsigned(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size);
int print_octal(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size);
int print_hexadecimal(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size);
int print_hexa_upper(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size);
int print_hexa(va_list arg_ls, char map_to[], char buf[],
	int flags, char flag_ch, int width, int precision, int size);




/****************** functions2.c ******************/


int print_pointer(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size);
int print_non_printable(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size);
int print_reverse(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size);
int print_rot13strng(va_list arg_ls, char buf[],
	int flags, int width, int precision, int size);


int get_flags(const char *format, int *x);
int get_width(const char *format, int *x, va_list arg_ls);
int get_precision(const char *format, int *x, va_list arg_ls);
int get_size(const char *format, int *x);

int handle_write_char(char chara, char buf[],
	int flags, int width, int precision, int size);
int write_number(int is_positive, int idx, char buf[],
	int flags, int width, int precision, int size);
int write_num(int idx, char buf[], int flags, int width, int prec,
	int length, char pad, char extra_c);
int write_pointer(char buf[], int idx, int length,
	int width, int flags, char pad, char extra_c, int pad_start);

int write_unsgnd(int is_negative, int idx, char buf[],
	int flags, int width, int precision, int size);

int handle_print(const char *fmt, int *idx, va_list arg_ls, char buf[], 
	int flags, int width, int precision, int size);

int is_printable(char chara);
int append_hexa_code(char ascii_code, char buf[], int x);
int is_digit(char chara);

long int convert_size_number(long int numb, int size);
long int convert_size_unsgnd(unsigned long int numb, int size);

int _printf(const char *format, ...);
#endif
