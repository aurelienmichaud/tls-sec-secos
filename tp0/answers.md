### Question 1

@0x300000 is the starting (4-byte-aligned) address of the multiboot_header (12 bytes). Then, in the next 16-byte-aligned address (@0x300010), the stack takes 0x2000 bytes of space. Eventually we reach __kernel_start__ which lies right after the stack, starting at @0x302010.

### Question 2

