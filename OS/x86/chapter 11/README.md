# Chapter 11 进入保护模式

## 全局描述符表

在保护模式下，对内存的访问仍然使用段地址和偏移地址，但是，在每个段能够被访问之前，必须先进行登记。

和每个段有关的信息需要8个字节进行描述，成为段描述符，每个段都需要一个描述符。为了存放这些描述符，需要在内存中开辟出一段空间。最主要的描述符表是全局描述符表。在进入保护模式之前，必须定义全局描述符表。

为了跟踪全局描述符表，处理器内部有一个48位的寄存器，称为全局描述符表寄存器。该寄存器分为两个部分，分别是32位的线性地址和16位的边界。32位的线性基地址部分保存的是全局描述符表在内存中起始的线性地址，16位边界地址部分保存的是全局描述符表的边界。GDT的界限是16位的，所以改变最大是$2^16$字节，最多可定义8192个描述符。

## 存储器的段描述符

在本章中，我们定义GDT的位置为主引导扇区程序之后即`0x00007e00`处。一旦确定了GDT在内存中的起始位置，下一步的工作就是要确定访问的段，并在GDT中位这些段创建各自的描述符。

如下图所示，每个描述符在GDT中占8字节。图中，下面是低32位，上面是高32位。

![存储器的段描述符格式](https://s2.loli.net/2022/03/19/3qLBk5lOYrXVty2.png)

描述符中指定了32位的段起始地址，以及20位的段边界地址。`G`是粒度位，用于解释段界限的含义。当`G`位是0时，段界限以字节为单位。若该位是1,则段界限以4KB为单位。`S`位用于描述符的类型，当该位是0时，表示一个系统段，为1时，表示是一个代码段或者数据段。

`DPL`表示描述符的特权级。这两位用于指定段的特权级。共有4中处理器支持的特权级别，分别是0、1、2、3，其中0是最高特权级别。`P`是段存在位。`D/B`位是默认的操作数大小。

## 保护模式下的内存访问

`CR0`是处理器内部的控制寄存器，它的第一位是保护模式允许位，为1则处理器进入保护模式。

保护模式下的中断机制和实模式不同，因此，原有的中断向量表不再适用，而且在保护模式下，BIOS中断都不能再用。在重新设置保护模式下的中断环境之前，必须关中断。

在32位处理器上，内存的访问方式发生了变化。首先，当引用一个段时，处理器自动将段地址左移4位，并传送到描述符高速缓存器。此后，就一直适用描述符高速缓存器的内容作为段地址。

在保护模式下，尽管访问内存时也需要指定一个段，但传送到段选择器的内容不是逻辑段地址，而是段描述符在描述符标中的索引号。
