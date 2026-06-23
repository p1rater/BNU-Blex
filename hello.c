void _start() {
    const char *msg = "Hello BlexOS!";

    asm volatile (
        "mov $1, %%eax;"    // Registerlar için ÇİFT yüzde (%%)
        "mov %0, %%ebx;"    // %0, alttaki "r"(msg) kısmını temsil eder
        "mov $17, %%ecx;"
        "int $0x80;"
        :                   // Output listesi (boş)
        : "r"(msg)          // Input listesi
        : "eax", "ebx", "ecx" // Clobber listesi (değişen registerları belirtmelisin)
    );

    asm volatile (
        "mov $2, %%eax;"
        "int $0x80;"
        : : : "eax"
    );
}
