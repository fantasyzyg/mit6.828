### MIT 6.828

#### Lab1
课程地址：https://pdos.csail.mit.edu/6.828/2018/labs/lab1/

分为3个Part
### Part1：熟悉PC启动流程
- 熟悉 x86 汇编
  - Intel syntax & AT&T syntax
- 熟悉模拟器 QEMU 以及 GDB 调试工具
- 理解PC的物理地址空间
- 理解BIOS的作用

### Part2：熟悉Boot Loader
- 熟悉引导扇区地作用 `boot sector` (磁盘第一个扇区)
- 理解实模式以及保护模式，以及不同模式下的寻址方式
- 理解引导扇区是如何加载内核的
- 理解 ELF （Executable and Linkable Format）
- 熟悉C语言
- 理解 编译 以及 链接 

### Part3：内核
- 理解加载地址以及链接地址
- 理解 cprint 函数底层实现
- 理解程序执行调用栈的底层机制


#### Lab2
课程地址：https://pdos.csail.mit.edu/6.828/2018/labs/lab2/

同样分为3个Part，目的是实现内存管理，包含两个组件
1. Physical Memory Allocator
   1. 以Page作为最小粒度进行管理
   2. 包含allocte和free
2. Virtual Memory Management
   1. Maps the virtual addresses used by kernel and user software to addresses in physical memory. 
   2. x86的硬件内存管理单元（MMU）通过查询页表（Page Table）可以帮助我们完成这种映射


借助`CR3`寄存器，以及MMU的翻译能力，页面组织是一个两层索引树结构

```java
// virtual addresse
10bits|10bits|12bits
Dir|Table|Offset
```


### Part 1: Physical Page Management
实现一个 `Physical page allocator`，主要是对裸机物理内存进行管理，用链表串联起来，基本单位是4K

### Part 2: Virtual Memory
首先需要熟悉X86模式下的内存管理架构：段翻译以及页翻译

- 虚拟地址：A virtual address consists of a segment selector and an offset within the segment
- 线性地址：A linear address is what you get after segment translation but before page translation
- 物理地址：A physical address is what you finally get after both segment and page translation and what ultimately goes out on the hardware bus to your RAM.

在JOS中，在boot阶段设立的GDT中已经设置了所有段的访问范围是  0 and limits to 0xffffffff, 所以虚拟地址是相等于线性地址，所以我们只需要考虑 Page Translation