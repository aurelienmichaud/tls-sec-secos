/* GPLv2 (c) Airbus */
#include <debug.h>
#include <info.h>

extern info_t   *info;
extern uint32_t __kernel_start__;
extern uint32_t __kernel_end__;

static void display_mmap(multiboot_uint32_t addr, multiboot_uint32_t length)
{
	multiboot_memory_map_t *entry = (multiboot_memory_map_t*) (addr);

	int entry_nb = length / sizeof(*entry);

	char * const type_string[] = {
		"AVAILABLE\n",
		"RESERVED\n",
		"ACPI RECLAIMABLE\n",
		"NVS\n"
	};

	debug("=== MMAP ===\n");

	debug("---------------------------\n");
	while (entry_nb--) {

		debug("+ From: @0x%x bytes\n", entry->addr);
		debug("+ (length: 0x%x bytes) | ", entry->len);

		if (entry->type > 0 && entry->type < 5)
			debug(type_string[entry->type - 1]);
		else
			debug("UNKOWN TYPE, PROBABLY RESERVED\n");

		debug("+ To  : @0x%x bytes\n", entry->addr + entry->len);

		debug("---------------------------\n");

		++entry;
	}
}


void tp() {
	debug("kernel mem [0x%x - 0x%x]\n", &__kernel_start__, &__kernel_end__);
	debug("MBI flags 0x%x\n", info->mbi->flags);

	/* Question 2 */
	display_mmap(info->mbi->mmap_addr, info->mbi->mmap_length);
}


