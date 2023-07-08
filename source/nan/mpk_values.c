#include "mpk_values.h"

int node_pkey = 0;

int node_pkey_set = 0;
int thread_set = 0;

pthread_cond_t wait_for_native_cv;
pthread_cond_t unlock_native_cv;
volatile int run_state = 0;
void *callb = NULL;
void *cbi = NULL;
pthread_spinlock_t wait_for_native;
pthread_mutex_t unlock_native;
pthread_spinlock_t native_runs;

