/* GPLv2 (c) Airbus */
#include <debug.h>
#include <info.h>

extern info_t   *info;
extern uint32_t __kernel_start__;
extern uint32_t __kernel_end__;

/* Question 4 */
static void test_RAM_overflow(loc_t lower_bound, loc_t upper_bound)
{
	char *lb = (char*)(lower_bound.addr);
	char *ub = (char*)(upper_bound.addr);

	const int overlay = 0x50;

	if ((int)(lb - overlay) >= 0)
		debug("%c\n", *(lb - overlay));

	*(ub + overlay) = ~0x0;
}

/* Question 3 */
static void test_memory_zone(loc_t loc) 
{
	char *addr = (char*)(loc.addr);
	/* Reading test */
	char __attribute__((unused)) c  = *addr;
	/* Writing test */
	*addr = ~0x0;
}

/* Question 2 */
static void display_memory_map_entry(multiboot_memory_map_t *entry)
{
	char * const type_string[] = {
		"AVAILABLE\n",
		"RESERVED\n",
		"ACPI RECLAIMABLE\n",
		"NVS\n"
	};

	debug("+ From: @0x%x bytes\n", entry->addr);
	debug("+ (length: 0x%x bytes) | ", entry->len);

	if (entry->type > 0 && entry->type < 5)
		debug(type_string[entry->type - 1]);
	else
		debug("UNKOWN TYPE, PROBABLY RESERVED\n");

	debug("+ To  : @0x%x bytes\n", entry->addr + entry->len);

	debug("---------------------------\n");
}

#define RAM_LENGTH_THRESHOLD	0x8000000	/* 128MB */

static void check_memory_map(multiboot_uint32_t addr, multiboot_uint32_t length)
{
	multiboot_memory_map_t *entry = (multiboot_memory_map_t*) (addr);

	int entry_nb = length / sizeof(*entry);

	debug("=== MMAP ===\n");
	debug("---------------------------\n");

	while (entry_nb--) {
		loc_t entry_starting_addr	= (loc_t)((raw64_t)(entry->addr));
		loc_t entry_ending_addr		= (loc_t)((raw64_t)(entry->addr + entry->len));

		/* Question 2 */
		display_memory_map_entry(entry);

		/* Question 3 */
		test_memory_zone(entry_starting_addr);

		/* Question 4 */
		if (entry->len >= RAM_LENGTH_THRESHOLD)
			test_RAM_overflow(entry_starting_addr, entry_ending_addr);

		++entry;
	}
}


void tp() {
	debug("kernel mem [0x%x - 0x%x]\n", &__kernel_start__, &__kernel_end__);
	debug("MBI flags 0x%x\n", info->mbi->flags);

	/* Question 2, 3 & 4*/
	check_memory_map(info->mbi->mmap_addr, info->mbi->mmap_length);
}


