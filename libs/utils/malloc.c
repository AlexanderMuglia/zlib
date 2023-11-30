#include "include/malloc.h"
#include <stdio.h>

void* ZMalloc( size_t size )
{
    size_t      blk_size    = 0;
    size_t*     header      = NULL;

    blk_size = ALIGN( size + SIZE_T_SIZE );
    header   = sbrk( blk_size );

    // mark allocated bit
    *header = blk_size | 1;

    return (char*)header + SIZE_T_SIZE;

}

void  ZFree( void *ptr )
{
    size_t*     header      = NULL;

    header = (size_t*)((char*)ptr - SIZE_T_SIZE);

    // unmark allocated bit
    *header = *header & ~1L;
}

void* ZRealloc( void *ptr, size_t size )
{
    return NULL;
}

int main()
{
    char*   myptr   = NULL;

    myptr = (char*)ZMalloc( 64 * sizeof(char) );

    if( myptr )
    {
        myptr[0] = 'H';
        myptr[1] = 'I';
        myptr[2] = '\0';
        printf( "%s\n", myptr );
        ZFree( myptr );
    }

    printf( "Free worked? %p\n", myptr );


}
