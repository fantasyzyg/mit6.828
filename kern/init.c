/* See COPYRIGHT for copyright information. */

#include <inc/stdio.h>
#include <inc/string.h>
#include <inc/assert.h>

#include <kern/monitor.h>
#include <kern/console.h>

// Test the stack backtrace function (lab 1 only)
void
test_backtrace(int x)
{
	cprintf("entering test_backtrace %d\n", x);
	if (x > 0)
		test_backtrace(x-1);
	else
		mon_backtrace(0, 0, 0);
	cprintf("leaving test_backtrace %d\n", x);
}

// 需要先声明，下面才能使用
void test_int(int a, int b, int c, int d, int e, int f, int g, int h)
{
	cprintf("%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n", &a, &b, &c, &d, &e, &f, &g, &h);
}

void test_char(char a, char b, char c, char d, char e, char f, char g, char h)
{
	cprintf("%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n", &a, &b, &c, &d, &e, &f, &g, &h);
}

/**
 * @brief  简单测试32bit系统的栈空间
 *   
 */
void test_stack_pointer() {
	// int a = 1;
    // int b = 2;
    // int c = 3;
    // int d = 4;
    // int e = 5;
    // int f = 6;
    // int g = 7;
    // int h = 8;
	
    // test_int(a,b,c,d,e,f,g,h);

	char a = '1';
    char b = '2';
    char c = '3';
    char d = '4';
    char e = '5';
    char f = '6';
    char g = '7';
    char h = '8';

	test_char(a,b,c,d,e,f,g,h);
}


void
i386_init(void)
{
	extern char edata[], end[];

	// Before doing anything else, complete the ELF loading process.
	// Clear the uninitialized global data (BSS) section of our program.
	// This ensures that all static/global variables start out zero.
	memset(edata, 0, end - edata);

	// Initialize the console.
	// Can't call cprintf until after we do this!
	cons_init();

	cprintf("6828 decimal is %o octal!\n", 6828);

	// test_stack_pointer();

	// Test the stack backtrace function (lab 1 only)
	test_backtrace(5);

	// Drop into the kernel monitor.
	while (1)
		monitor(NULL);
}


/*
 * Variable panicstr contains argument to first call to panic; used as flag
 * to indicate that the kernel has already called panic.
 */
const char *panicstr;

/*
 * Panic is called on unresolvable fatal errors.
 * It prints "panic: mesg", and then enters the kernel monitor.
 */
void
_panic(const char *file, int line, const char *fmt,...)
{
	va_list ap;

	if (panicstr)
		goto dead;
	panicstr = fmt;

	// Be extra sure that the machine is in as reasonable state
	asm volatile("cli; cld");

	va_start(ap, fmt);
	cprintf("kernel panic at %s:%d: ", file, line);
	vcprintf(fmt, ap);
	cprintf("\n");
	va_end(ap);

dead:
	/* break into the kernel monitor */
	while (1)
		monitor(NULL);
}

/* like panic, but don't */
void
_warn(const char *file, int line, const char *fmt,...)
{
	va_list ap;

	va_start(ap, fmt);
	cprintf("kernel warning at %s:%d: ", file, line);
	vcprintf(fmt, ap);
	cprintf("\n");
	va_end(ap);
}
