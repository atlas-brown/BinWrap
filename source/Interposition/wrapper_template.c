#include <string.h>
#include <stdio.h>
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sys/mman.h>
#include <dlfcn.h>
#include <link.h>



static void* main_handle;
static void* preloads[128];


//The first function executed by a node module
__attribute__ ((aligned(4096), pure)) void wrap_node_module_register()
{
         asm ("movq $0xdeadcafe, %rax; jmpq *%rax" );
}


//put output from script "wrap_functions.sh" here



//We use align 4096 in order to ensure that wrappers reside in
//another page (convenient for mprotect).
__attribute__ ((aligned(4096))) void setup_plt(){
    
    preloads[0] = dlsym(main_handle, "node_module_register");

    //put output from script "create_dlsym_table.sh" here

}

static __attribute__((constructor)) void init_method(void)
{

    main_handle = dlopen(NULL, RTLD_LAZY);

    struct link_map *map, *iter;

    dlinfo(main_handle, RTLD_DI_LINKMAP, &map);

    iter = map;
    
    uint8_t* got_address;
    long unsigned jit, jit_address;
    while(iter){
        if (strstr(iter->l_name, MODULE_NAME_STR)){  //change MODULE_NAME to native module name
            
            setup_plt();

            mprotect((void*) wrap_node_module_register, 4096, PROT_WRITE);

            jit_address = (unsigned long) wrap_node_module_register;
            jit = (long unsigned) preloads[0]<<16 | 0xb848;
            *((long unsigned*) jit_address) = jit;


            //put the output of script "wrapper_code_overwrite.sh" here
            
            //make wrapper functions executable again
            mprotect((void*) wrap_node_module_register, 4096, PROT_EXEC);
	    // Manually set the got entry for node_module_register
            //put the output of script "./plt_overwrite.sh" here
	    break;
        }
	iter = iter->l_next;
    }
}

            











