#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <common.h>

typedef struct {
    uint64_t fun_addr;
    uint64_t fun_size;
    char *fun_name;
} elf_data;
elf_data elf_func[1000];
int elf_cnt = 0;
int ftrace_cnt = 0;
char ftrace_buf[100][100];
int fun_dep = 0;

void ELF_Read(char *elf_name) {
    if(elf_name == NULL)
        Log("No ELF is found");

    // fopen();
    FILE *elf_stream = fopen(elf_name, "rb");
    Assert(elf_stream, "Cannot read '%s'", elf_name);       // If the ELF cannot be detected...
    
    // fread();
    unsigned char *buffer;
    buffer = (unsigned char *)malloc(100500 * sizeof(unsigned char));
    int ret = fread(buffer, sizeof(unsigned char), 100500, elf_stream);
    Assert(ret != 0, "Can not open '%s'", elf_name);        // If the ELF is empty...

    // The required database
    Elf64_Ehdr *Ehdr = (Elf64_Ehdr *) buffer;
    Elf64_Shdr *Shdr = (Elf64_Shdr *) (buffer + Ehdr->e_shoff);
    Elf64_Shdr *Shdr_strtab = NULL;
    Elf64_Shdr *Shdr_symtab = NULL;

    // Find the location of symbol table and string table
    for (int i = 0; Shdr_strtab == NULL || Shdr_symtab == NULL; i++)
    {
        if (Shdr[i].sh_type == SHT_SYMTAB)
        {
            Shdr_symtab = &Shdr[i];
        }
        else if (Shdr[i].sh_type == SHT_STRTAB)
        {
            Shdr_strtab = &Shdr[i];
            break;
        }
    }

    // Find functions
    Elf64_Sym *Sym_table = (Elf64_Sym *)(buffer + Shdr_symtab->sh_offset);

    for (int i = 0; i <= Shdr_symtab->sh_size / Shdr_symtab->sh_entsize; i++)
    {
        if (ELF64_ST_TYPE(Sym_table[i].st_info) == STT_FUNC)
        {
            elf_func[elf_cnt].fun_addr = Sym_table[i].st_value;
            elf_func[elf_cnt].fun_size = Sym_table[i].st_size;
            elf_func[elf_cnt].fun_name = (char *)(buffer + Shdr_strtab->sh_offset + Sym_table[i].st_name);
            elf_cnt++;
        }
    }
}

void Ftrace_Write(uint64_t pc, uint64_t dnpc, int is_call) {
    int pc_fun = -1, dnpc_fun = -1;
    for (int i = 0; i < elf_cnt; i++)
    {
        if (elf_func[i].fun_addr <= pc && pc < elf_func[i].fun_addr + elf_func[i].fun_size)
            pc_fun = i;
        if (elf_func[i].fun_addr <= dnpc && dnpc < elf_func[i].fun_addr + elf_func[i].fun_size)
            dnpc_fun = i;
    }
    if (pc_fun == dnpc_fun)
        return;
    char empty[100] = {0};
    for (int i = 0; i < fun_dep; i++)
        empty[i] = ' ';
    if (elf_func[dnpc_fun].fun_addr == dnpc)
    {
        if (is_call)
        {
            sprintf(ftrace_buf[ftrace_cnt], "%lx: %scall [%s@%lx]", pc, empty, elf_func[dnpc_fun].fun_name, elf_func[dnpc_fun].fun_addr);
            ftrace_cnt++;
            fun_dep++;
        }
    }
    else
    {
        sprintf(ftrace_buf[ftrace_cnt], "%lx: %sret [%s]", pc, empty, elf_func[pc_fun].fun_name);
        ftrace_cnt++;
        fun_dep--;
    }
    ftrace_cnt %= 100;
}

void Ftrace_Print() {
    for (int i = 0; i < ftrace_cnt; i++)
    {
        if ((i + 1) % 100 == ftrace_cnt)
            printf("-->%s\n", ftrace_buf[i]);
        else
            printf("   %s\n", ftrace_buf[i]);
    }
}
