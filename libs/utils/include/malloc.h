#ifndef ZMALLOC_H
#define ZMALLOC_H

// Material learned from IIT College of Science.
// https://moss.cs.iit.edu/cs351/slides/slides-malloc.pdf


#include <stddef.h>
#include <unistd.h>

//must be power of 2
#define ALIGNMENT 8

#define ALIGN( size )  (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1 ))

// header size
#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))


// Returns a pointer to the payload (of minimum length size bytes)
// of a memory block.
//
// This memory is off-limits to the DMA until released by the user.
void* ZMalloc( size_t size );

// Indicates to the DMA that the payload pointed to by ptr can be reused.
//
// Value of ptr must have been returned by a previous call to ZFree.
void  ZFree( void *ptr );

// Request to resize memory region pointed to by ptr to size size.
//
// DMA may create a new block in which case old data is copied to
// new region and old region is freed.
void* ZRealloc( void *ptr, size_t size );

#endif
