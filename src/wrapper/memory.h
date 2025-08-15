#ifndef WRAPPER_MEMORY_H_
#define WRAPPER_MEMORY_H_

#include <stddef.h>
#include <stdint.h>

uintptr_t* myMalloc(size_t size);
void myFree(void* adress);

#endif // WRAPPER_MEMORY_H_
