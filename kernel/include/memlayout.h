
#define KERNBASE  0x80000000          // First kernel virtual address

#define V2P_WO(x) ((x) - KERNBASE)    // same as V2P, but without casts
