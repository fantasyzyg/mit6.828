// Simple implementation of cprintf console output for the kernel,
// based on printfmt() and the kernel console's cputchar().

#include <inc/types.h>
#include <inc/stdio.h>
#include <inc/stdarg.h>

/*	
	printf.c 封装了一些高层函数,但是 console.c 是一些底层函数
*/

static void
putch(int ch, int *cnt)  // 显示单一字符
{
	cputchar(ch);  // output a char to console
	*cnt++;
}

int
vcprintf(const char *fmt, va_list ap)
{
	int cnt = 0;

	vprintfmt((void*)putch, &cnt, fmt, ap);
	return cnt;
}


// 格式化输出字符串到console，由于想提供可变参数，于是搞出了这些东西
int
cprintf(const char *fmt, ...)
{
	va_list ap;
	int cnt;

	va_start(ap, fmt);             // 展开是： ap = (char *)(&fmt) + align_long(fmt);  fmt在stack上占据4 bytes, fmt此时就在栈上
	cnt = vcprintf(fmt, ap);
	va_end(ap);

	return cnt;
}

