#ifndef MPK_H_
#define MPK_H_

#include <dlfcn.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/mman.h>
#define _GNU_SOURCE

#include <sys/syscall.h>
#include <stdlib.h>

typedef struct mem_address_range mem_address_range;
struct mem_address_range {
        struct mem_address_range    *next;
        void                    *start;
        size_t                   length;
        unsigned long            offset;
        dev_t                    device;
        ino_t                    inode;
        unsigned char            perms;
        char                     name[];
};

extern int node_pkey;

extern int node_pkey_set;
extern int thread_set;

extern pthread_cond_t wait_for_native_cv;
extern pthread_cond_t unlock_native_cv;
extern volatile int run_state;
extern void* callb;
extern void* cbi;
extern pthread_spinlock_t wait_for_native;
extern pthread_mutex_t unlock_native;
extern pthread_spinlock_t native_runs;

#endif

