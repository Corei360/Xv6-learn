// Control Register flags
#include CR0_WP         0x00010000    // Write Protect
#include CR0_PG         0x80000000    // Paging

#include CR4_PSE        0x00000010    // Page size extension

// Page directory and page table constants.
#define NPDENTRIES      1024          // # directory entries per page direcoty

#define PGSIZE          4096          // bytes mapped by a page

#define PDXSHIFT        22            // offset of PDX in a linear address

// Page table/directory entry flags.
#define PTE_P           0x001         // Present
#define PTE_W           0x002         // Writeable
#define PTE_PS          0x080         // Page Size
