/*	$NetBSD: stdarg.h,v 1.12 1995/12/25 23:15:31 mycroft Exp $	*/

#ifndef JOS_INC_STDARG_H
#define	JOS_INC_STDARG_H

typedef __builtin_va_list va_list;   // (char *) 可以指向任何地址

#define va_start(ap, last) __builtin_va_start(ap, last)   // last 代表最后一个参数，因为栈是向下生长的，所以是一个栈底的地址

#define va_arg(ap, type) __builtin_va_arg(ap, type)   // 等价于 (*(type*)ap), 向上移动一个参数

#define va_end(ap) __builtin_va_end(ap)

#endif	/* !JOS_INC_STDARG_H */
