#include "include/malloc.h"
#include <stdio.h>

static int                  is_initialized      = 0;
static pthread_mutex_t      init_mutex          = PTHREAD_MUTEX_INITIALIZER;
static void*                g_heap_start        = 0;


// Initializes the ZMalloc lib. Currently only needed to find the start of the heap.
//
// Must be called before using the library.
//
// Once we initialize, we are very restricted. Nothing that allocates memory can be used
// other than ZMalloc or ZRealloc. This even includes things like printf, so we include a
// printf in initialization.
ZSTATUS
ZMallocInitialize()
{
    ZSTATUS     status      = ZSTATUS_FAILED;

    pthread_mutex_lock( &init_mutex );

    if( !is_initialized )
    {
        is_initialized = 1;

        // This print statement is more important than just alerting the user to
        // the lib being initialized. More importantly, it ensures printf has
        // been called (with a non-zero length string), which allocates the FILE*
        // for the printf buffer. This has to be called before we set our heap start
        // to allow more printf-ing without allocating memory outside of the lib.
        printf("ZMalloc Initialized!\n");
        g_heap_start = sbrk(0);

        status = ZSTATUS_OK;
    }
    else
    {
        status = ZSTATUS_ALREADY_INITIALIZED;
    }

    pthread_mutex_unlock( &init_mutex );

    return status;

}

// Tries to find available memory in the heap that was used but is now freed.
//
// Returns NULL if it there are no gaps of sufficient size.
static
ZSTATUS
ZFindFit( size_t size, void** ptr )
{
    size_t*     header      = NULL;
    void*       heap_end    = NULL;

    header = HEAP_START;
    heap_end = sbrk( 0 );

    while( (void*)header < heap_end )
    {
        if( !(*header)&1 && *header >= size )
        {
            *ptr = header;
            return ZSTATUS_OK;
        }

        header = (size_t*)((char*)header + ( *header & ~1L ));
    }

    ptr = NULL;
    return ZSTATUS_NOT_FOUND;
}

ZSTATUS
ZMalloc( size_t size, void** ret )
{
    ZSTATUS     status      = ZSTATUS_FAILED;
    size_t      blk_size    = 0;
    size_t*     header      = NULL;

    blk_size = ALIGN( size + SIZE_T_SIZE );

    status = ZFindFit( blk_size, (void**)&header );

    if( ZSTATUS_OK == status && header )
    {
        if( blk_size < *header )
        {
            // cut down block and use only what we need
            // need to check for min block size
            *(size_t*)((char*)header + blk_size) = *header - blk_size;

        }
        else
        {
            // use full block
            *header = *header | 1;
        }
    }
    else
    {
        header  = sbrk( blk_size );
        *header = blk_size | 1;
        status = ZSTATUS_OK;
    }

    *ret = (char*)header + SIZE_T_SIZE;

    return status;
}


ZSTATUS
ZFree( void *ptr )
{
    ZSTATUS     status      = ZSTATUS_FAILED;
    size_t*     header      = NULL;

    if( ptr )
    {
        header = (size_t*)((char*)ptr - SIZE_T_SIZE);

        // unmark allocated bit
        *header = *header & ~1L;

        status = ZSTATUS_OK;
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}

//ZSTATUS
//ZRealloc( void *ptr, size_t size, void** ret )
//{
//    return ZSTATUS_FAILED;
//}
