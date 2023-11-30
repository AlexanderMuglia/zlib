#include "include/malloc.h"
#include <stdio.h>

static int                  is_initialized      = 0;
static pthread_mutex_t      init_mutex          = PTHREAD_MUTEX_INITIALIZER;
static void*                g_heap_start        = 0;


static
ZSTATUS
ZMallocInitialize()
{
    ZSTATUS     status      = ZSTATUS_FAILED;

    pthread_mutex_lock( &init_mutex );

    if( !is_initialized )
    {
        is_initialized = 1;
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
    header   = sbrk( blk_size );

    // mark allocated bit
    *header = blk_size | 1;

    *ret = (char*)header + SIZE_T_SIZE; status = ZSTATUS_OK;

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

ZSTATUS
ZRealloc( void *ptr, size_t size, void** ret )
{
    return ZSTATUS_FAILED;
}

int main()
{
    ZSTATUS     status  = ZSTATUS_OK;
    char*       myptr   = NULL;

    status = ZMallocInitialize();

    if( ZSTATUS_OK == status )
    {
        printf( "%p\n", HEAP_START );
        status = ZMalloc( 64 * sizeof(char), (void**)&myptr );
        myptr = (char*)myptr;

        if( ZSTATUS_OK == status )
        {
            myptr[0] = 'H';
            myptr[1] = 'I';
            myptr[2] = '\0';
            printf( "%s\n", myptr );
            status = ZFree( myptr );
        }

        printf( "Free worked? %x\n", status );
    }
}
