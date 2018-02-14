#ifndef __ASM_GENERIC_H
#define __ASM_GENERIC_H

#include <types.h>

static inline uchar_t
inb(ushort_t port)
{
    uchar_t res;

    asm volatile(
        "inb %1, %0"
        :"=a"(res)
        :"r"(port)
    );

    return res;
}

static inline void
outb(ushort_t port, uchar_t cnt)
{
    asm volatile(
        "outb %1, %0"
        :
        : "r"(port), "a"(cnt)
    );
}

static inline ushort_t
inw(ushort_t port)
{
    uchar_t res;

    asm volatile(
        "inw %1, %0"
        :"=a"(res)
        :"r"(port)
    );

    return res;
}

static inline void
outw(ushort_t port, ushort_t cnt)
{
    asm volatile(
        "outw %1, %0"
        :
        : "r"(port), "a"(cnt)
    );
}

static inline uint_t
inl(ushort_t port)
{
    uint_t res;

    asm volatile(
        "inl %1, %0"
        :"=a"(res)
        :"r"(port)
    );

    return res;
}

static inline void 
outl(ushort_t port, uint_t cnt)
{
    asm volatile(
        "outl %1, %0"
        :
        : "r"(port), "a"(cnt)
    );
}

static inline void 
insb(ushort_t port, void* dst, int count)
{
    asm volatile(
        "cld;rep insl"
        :
        :"D"(dst), "c"(count), "d"(port)
        :"memory", "cc"
    );
}

static inline void 
insw(ushort_t port, void* dst, int count)
{
    asm volatile(
        "cld;rep insl"
        :
        :"D"(dst), "c"(count), "d"(port)
        :"memory", "cc"
    );
}

static inline void 
insl(ushort_t port, void* dst, int count)
{
    asm volatile(
        "cld;rep insl"
        :
        :"D"(dst), "c"(count), "d"(port)
        :"memory", "cc"
    );
}z

static inline void 
outsb(ushort_t port, void* src, int count)
{
    asm volatile(
        "cld; rep outsb"
        :
        :"d"(port), "S"(src), "c"(count)
        :"memory", "cc"
    );
}

static inline void 
outsw(ushort_t port, void* src, int count)
{
    asm volatile(
        "cld; rep outsw"
        :
        :"d"(port), "S"(src), "c"(count)
        :"memory", "cc"
    );
}

static inline void 
outsl(ushort_t port, void* src, int count)
{
    asm volatile(
        "cld; rep outsl"
        :
        :"d"(port), "S"(src), "c"(count)
        :"memory", "cc"
    );
}

static inline void 
movsb(void* src, void* dst, int count)
{
    asm volatile(
        "cld; rep movsb"
        :
        :"s"(src), "D"(dst), "c"(count)
        :"memory", "cc"
    );
}

static inline void 
movsw(void* src, void* dst, int count)
{
    asm volatile(
        "cld; rep movsw"
        :
        :"s"(src), "D"(dst), "c"(count)
        :"memory", "cc"
    );
}

static inline void 
movsl(void* src, void* dst, int count)
{
    asm volatile(
        "cld; rep movsl"
        :
        :"s"(src), "D"(dst), "c"(count)
        :"memory", "cc"
    );
}

static inline void 
stosb(void* dst, uchar_t cnt, int count)
{
    asm volatile(
        "cld;rep stosb"
        :
        :"D"(dst), "c"(count), "a"(cnt)
        :"memory", "cc"
    );
}

static inline void 
stosw(void* dst, ushort_t cnt, int count)
{
    asm volatile(
        "cld;rep stosw"
        :
        :"D"(dst), "c"(count), "a"(cnt)
        :"memory", "cc"
    );
}

static inline void 
stosl(void* dst, uint_t cnt, int count)
{
    asm volatile(
        "cld;rep stosl"
        :
        :"D"(dst), "c"(count), "a"(cnt)
        :"memory", "cc"
    );
}

static inline void
sti()
{
    asm volatile ("sti");
}

static inline void
cli()
{
    asm volatile ("cli");
}

static inline void
__attribute__((always_inline))
pdtbl_load(void* pdtbl, uint_t attr)
{
    attr &= (uint_t)(1<<3 | 1<<4);

    asm volatile(
        "movl %0, %%cr3"
        :
        :"r"(((uint_t)pdtbl & 0xFFFFF000) | attr)
    );
}

static inline void 
__attribute__((always_inline))
pg_enable()
{
    uint_t cr0;
    asm volatile(
        "movl %%cr0, %0"
        :"=r"(cr0)
    );
    
    cr0 |= 0x80000000;
    asm volatile(
        "movl %0, %%cr0"
        : 
        :"r"(cr0)
    );
}


#endif