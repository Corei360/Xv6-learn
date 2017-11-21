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
    uint lim_19_16 : 4;  // High bits of segment limit
    uint avl : 1;        // Unused (available for software use)
    uint rsv1 : 1;       // Reserved
    uint db : 1;         // 0 = 16-bit segment, 1 = 32-bit segment
    uint g : 1;          // Granularity: limit scaled by 4K when set
    uint base_31_24 : 8; // High bits of segment base address
};
// PAGEBREAK: 12
// Gate descriptors for interrupts and traps
struct gatedesc {
    uint off_15_0 : 16;   // low 16 bits of offset in segment
    uint cs : 16;         // code segment selector
    uint args : 5;        // # args, 0 for interrupt/trap gates
    uint rsv1 : 3;        // reserved(should be zero I guess)
    uint type : 4;        // type(STS_{TG,IG32,TG32})
    uint s : 1;           // must be 0 (system)
    uint dpl : 2;         // descriptor(meaning new) privilege level
    uint p : 1;           // Present
    uint off_31_16 : 16;  // high bits of offset in segment
};

#endif
