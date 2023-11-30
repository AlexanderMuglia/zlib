#ifndef ZMALLOC_H
#define ZMALLOC_H

// Material learned from IIT College of Science.
// https://moss.cs.iit.edu/cs351/slides/slides-malloc.pdf

#include "../../../common/ZStatus.h"
#include <stddef.h>
#include <pthread.h>
#include <unistd.h>

//must be power of 2
#define ALIGNMENT           8

#define ALIGN( size )       (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1 ))

// header size
#define SIZE_T_SIZE         (ALIGN(sizeof(size_t)))

// start of the heap at initialization time
#define HEAP_START          g_heap_start


// Initializes the ZMalloc lib. Currently only needed to find the start of the heap.
//
// Must be called before using the library.
static ZSTATUS ZMallocInitialize();

// Tries to find available memory in the heap that was used but is now freed.
//
// Returns NULL if it there are no gaps of sufficient size.
static ZSTATUS ZFindFit( size_t size, void** ptr );

// Returns a pointer to the payload (of minimum length size bytes)
// of a memory block.
//
// This memory is off-limits to the DMA until released by the user.
ZSTATUS ZMalloc( size_t size, void** ret );

// Indicates to the DMA that the payload pointed to by ptr can be reused.
//
// Value of ptr must have been returned by a previous call to ZFree.
ZSTATUS ZFree( void* ptr );

// Request to resize memory region pointed to by ptr to size size.
//
// DMA may create a new block in which case old data is copied to
// new region and old region is freed.
ZSTATUS ZRealloc( void* ptr, size_t size, void** ret );

#endif
