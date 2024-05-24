#include "mmu.h"
#include "unity.h"
#include <string.h>

#define PAGE_TABLE_ADDR_SHIFT (0x40000000000ULL) /* shift for the mirrored address */

static char message[32] = { 0 }; /* MMU test buffer */

void setUp(void)
{
    /* initialize page tables and enable MMU */
    mmu_init();
}

void tearDown(void)
{
    /* no cleanup necessary for MMU */
}

void test_address_translation(void)
{
    uint64_t* translation_table = NULL;
    uint64_t expected_pa = 0x0ULL;
    uint64_t pa = 0x0ULL;
    uint64_t va = 0x40000000ULL;

    /* Get the base address of the page table */
    translation_table = (uint64_t*)mmu_get_page_table_base();

    /* Simplified example for testing */
    pa = translation_table[va >> 30];

    /* Check that the base address of the page table is not NULL */
    TEST_ASSERT_NOT_NULL(translation_table);

    /* Check a known translation */
    TEST_ASSERT_EQUAL_UINT64(expected_pa, pa & 0xFFFFFFF000);
}

void test_memory_access(void)
{
    char* mirrored = NULL;              /* mirrored address */
    char* original = NULL;              /* original address */
    uint64_t* translation_table = NULL; /* base address of the page table */
    uint64_t old_entry = 0x0ULL;        /* original page table entry */

    /* Get the base address of the page table */
    translation_table = (uint64_t*)mmu_get_page_table_base();

    /* Store the old entry to restore it later */
    old_entry = translation_table[1];

    /* Map [0x0; 0x40000000000) and [0x40000000000; 0x80000000000) to the same physical memory */
    translation_table[1] = translation_table[0];

    original = message;
    mirrored = (char*)((uintptr_t)message + PAGE_TABLE_ADDR_SHIFT);

    /* Write data to the original address and read it from the mirrored address */
    strncpy(original, "Ping!", sizeof(message));
    TEST_ASSERT_EQUAL_STRING("Ping!", mirrored);

    /* Write data to the mirrored address and read it from the original address */
    strncpy(mirrored, "Pong!", sizeof(message));
    TEST_ASSERT_EQUAL_STRING("Pong!", original);

    /* Restore the original page table entry */
    translation_table[1] = old_entry;
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_address_translation);
    RUN_TEST(test_memory_access);

    return UNITY_END();
}
