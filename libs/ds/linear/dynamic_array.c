
#include "include/dynamic_array.h"

ZSTATUS
ZInitializeDynamicArray
(
    ZDynamicArray**      Array,
    size_t               InitSize
)
{
    ZSTATUS         status      =   ZSTATUS_FAILED;

    if( *Array )
    {
        status = ZSTATUS_ALREADY_INITIALIZED;
    }
    else
    {
        *Array = malloc( sizeof(ZDynamicArray) );
        if( *Array )
        {
            (*Array)->array = malloc( sizeof(char*) * InitSize );
            if ( (*Array)->array )
            {
                (*Array)->size = InitSize;
                (*Array)->used = 0;
                status = ZSTATUS_OK;
            }
            else
            {
                free( *Array );
                status = ZSTATUS_OUT_OF_MEMORY;
            }
        }
        else
        {
            status = ZSTATUS_OUT_OF_MEMORY;
        }
    }

    return status;
}


int main(int argc, char** argv)
{
    ZSTATUS                     status  =   0;
    ZDynamicArray*              array   =   NULL;

    printf("%d\n", (array == NULL));
    status = ZInitializeDynamicArray( &array, 23);
    printf("%d\t%d\n", (array == NULL), status );

    return 0;
}
