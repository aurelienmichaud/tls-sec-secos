### Question 1

@0x300000 is the starting (4-byte-aligned) address of the multiboot_header (12 bytes). Then, in the next 16-byte-aligned address (@0x300010), the stack takes 0x2000 bytes of space. Eventually we reach __kernel_start__ which lies right after the stack, starting at @0x302010.

### Question 2

Answer in tp.c

### Question 3

Reading and writing seem to be authorized everywhere. A fortiori there is no Segmentation fault, the reason being this mere OS does not process any memory barrier control.

### Question 4

Nothing special happens when we try to read/write out of the RAM's bounds for the same reason as Question 3.

