#ifndef JOS_INC_ELF_H
#define JOS_INC_ELF_H

#define ELF_MAGIC 0x464C457FU	/* "\x7FELF" in little endian */


/*
	For purposes of 6.828, you can consider an ELF executable to be a header with loading information, 
	followed by several program sections, each of which is a contiguous chunk of code or data intended to be loaded into memory at a specified address. 
*/

struct Elf {
	uint32_t e_magic;	// must equal ELF_MAGIC 4 bytes
	uint8_t e_elf[12];  // 12 bytes
	uint16_t e_type;    // 2 bytes
	uint16_t e_machine; // 2 bytes
	uint32_t e_version; // 4 bytes
	uint32_t e_entry;         // 程序入口：Load Address  offset: 0x10018
	uint32_t e_phoff;         // Program Header Table 的偏移位置
	uint32_t e_shoff;         // Section Header Table 的偏移位置
	uint32_t e_flags;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;            // Program Header的数量
	uint16_t e_shentsize;
	uint16_t e_shnum;            // Section Header的数量
	uint16_t e_shstrndx;
};

struct Proghdr {
	uint32_t p_type;
	uint32_t p_offset;
	uint32_t p_va;
	uint32_t p_pa;
	uint32_t p_filesz;
	uint32_t p_memsz;
	uint32_t p_flags;
	uint32_t p_align;
};

struct Secthdr {
	uint32_t sh_name;
	uint32_t sh_type;
	uint32_t sh_flags;
	uint32_t sh_addr;
	uint32_t sh_offset;
	uint32_t sh_size;
	uint32_t sh_link;
	uint32_t sh_info;
	uint32_t sh_addralign;
	uint32_t sh_entsize;
};

// Values for Proghdr::p_type
#define ELF_PROG_LOAD		1

// Flag bits for Proghdr::p_flags
#define ELF_PROG_FLAG_EXEC	1
#define ELF_PROG_FLAG_WRITE	2
#define ELF_PROG_FLAG_READ	4

// Values for Secthdr::sh_type
#define ELF_SHT_NULL		0
#define ELF_SHT_PROGBITS	1
#define ELF_SHT_SYMTAB		2
#define ELF_SHT_STRTAB		3

// Values for Secthdr::sh_name
#define ELF_SHN_UNDEF		0

#endif /* !JOS_INC_ELF_H */
