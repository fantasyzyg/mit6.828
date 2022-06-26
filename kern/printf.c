// Simple implementation of cprintf console output for the kernel,
// based on printfmt() and the kernel console's cputchar().

#include <inc/types.h>
#include <inc/stdio.h>
#include <inc/stdarg.h>

/*	
	printf.c 封装了一些高层函数,但是 console.c 是一些底层函数
*/

static void
putch(int ch, int *cnt)
{
	cputchar(ch);
	*cnt++;
}

int
vcprintf(const char *fmt, va_list ap)
{
	int cnt = 0;

	vprintfmt((void*)putch, &cnt, fmt, ap);
	return cnt;
}

int
cprintf(const char *fmt, ...)
{
	va_list ap;
	int cnt;

	va_start(ap, fmt);             // 展开是： ap = (char *)(&fmt) + align_long(fmt);
	cnt = vcprintf(fmt, ap);
	va_end(ap);

	return cnt;
}

