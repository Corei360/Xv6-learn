// This file contains definitions for the
// x86 memory management unit (MMU).

// Control Register flags
#define CR0_PE          0x00000001      // Protection Enable
// #define CR0_MP          0x00000002      // Monitor coProcessor
// #define CR0_EM          0x00000004      // Emulation
// #define CR0_TS          0x00000008      // Task Switched
// #define CR0_ET          0x00000010      // Extension Type
// #define CR0_NE          0x00000020      // Numeric Errror
// #define CR0_WP          0x00010000      // Write Protect
// #define CR0_AM          0x00040000      // Alignment Mask
// #define CR0_NW          0x20000000      // Not Writethrough
// #define CR0_CD          0x40000000      // Cache Disable
// #define CR0_PG          0x80000000      // Paging

// #define CR4_PSE         0x00000010      // Page size extension

// various segment selectors.
#define SEG_KCODE 1  // kernel code
#define SEG_KDATA 2  // kernel data+stack
#define SEG_UCODE 3  // user code
#define SEG_UDATA 4  // user data+stack
#define SEG_TSS   5  // this process's task state

// cpu->gdt[NSEGS] holds the above segments.
// #define NSEGS     6

#ifndef __ASSEMBLER__
// Segment Descriptor
struct segdesc {
       uint lim_15_0 : 16;  // Low bits of segment limit
       uint base_15_0 : 16; // Low bits of segment base address
       uint base_23_16 : 8; // Middle bits of segment base address
       uint type : 4;       // Segment type (see STS_ constants)
       uint s : 1;          // 0 = system, 1 = application
       uint dpl : 2;        // Descriptor Privilege Level
       uint p : 1;          // Present
       uint lim_19_16 : 4;  // Hight bits of segment limit
       uint avl : 1;        // Unused (available for software use)
       uint rsv1 : 1;       // Reserved
       uint db : 1;         // 0 = 16-bit segment, 1 = 32-bit segment
       uint g : 1;          // Granularity: limit scaled by 4K when set
       uint base_31_24 : 8; // Hight bits of segment base address
};

// Normal segment
#define SEG(type, base, lim, dpl) (struct segdesc)   \
{ ((lim)>>12) & 0xffff, (uint)(base) & 0xffff,       \
  ((uint)(base)>>16) & 0xff, type, 1, dpl, 1,        \
  (uint)(lim)>>28, 0, 0, 1, 1, (uint)(base)>>24 }
#define SEG16(type, base, lim, dpl) (struct segdesc) \
{ (lim) & 0xffff, (uint)(base) & 0xffff,             \
  ((uint)(base)>>16) & 0xff, type, 1, dpl, 1,        \
  (uint)(lim)>>16, 0, 0, 1, 0, (uint)(base)>>24 }
#endif

#define SEG_NULLASM                             \
    .word 0, 0;                                 \
    .byte 0, 0, 0, 0

// The 0xC0 means the limit is in 4096-byte units and
// (for executeble segments) 32-bit mode.
#define SEG_ASM(type, base, lim)                                      \
    .word (((lim) >> 12) & 0xffff), ((base) & 0xffff);                \
    .byte (((base) >> 16) & 0xff), (0x90 | (type)),                   \
        (0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)

// #define DPL_USER           0x3    // User DPL

// Application segment type bits
#define STA_X              0x8    // Executable segment
#define STA_E              0x4    // Expand down (non-executable segments)
#define STA_C              0x4    // Conforming code segment (executable only)
#define STA_W              0x2    // Writeable (non-executable segments)
#define STA_R              0x2    // Readable (executable segments)
#define STA_A              0x1    // Accessed

// A virtual address 'la' has a three-part structure as follows:
//
// +----------10----+--------10------+--------12-----------+
// | Page Directory |   Page Table   | Offset within Page  |
// |      Index     |      Index     |                     |
// +----------------+----------------+---------------------+
//  \--- PDX(va) --/ \--- PTX(va) --/

// page directory index
#define PDX(va)            (((uint)(va) >> PDXSHIFT & 0x3FF)

// page table index
#define PTX(va)            (((uint)(va) >> PTXSHIFT & 0x3FF)

#define PGSIZE             4096   // bytes mapped by a page

#define PGSHIFT            12     // log2(PGSIZE)



#define PGROUNDUP(sz)    (((sz)+PGSIZE-1) & ~(PGSIZE-1))
#define PGROUNDDOWN(a)   (((a) & ~(PGSIZE-1))
