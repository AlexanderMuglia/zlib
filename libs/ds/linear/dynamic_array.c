#include "include/dynamic_array.h"

ZSTATUS
ZDynamicArrayInitialize
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

ZSTATUS
ZDynamicArrayPush
(
    ZDynamicArray*      Array,
    char*               Input
)
{
    ZSTATUS         status      =   ZSTATUS_FAILED;

    if( Array->used >= Array->size )
    {
        Array->size = ((3 * Array->size ) / 2) + 8;
        Array->array = realloc( Array->array, Array->size * sizeof( char* ) );

        if( Array->array )
        {
            status = ZSTATUS_OK;
        }
        else
        {
            status = ZSTATUS_OUT_OF_MEMORY;
        }
    }
    else
    {
        status = ZSTATUS_OK;
    }

    if( ZSTATUS_OK == status )
    {
        Array->array[Array->used] = Input;
        Array->used += 1;
    }

    return status;
}


int main(int argc, char** argv)
{
    ZSTATUS                     status  =   0;
    ZDynamicArray*              array   =   NULL;
    char                        example[100];

    status = ZDynamicArrayInitialize( &array, 1);
    for( int i = 0; i < 10; i++ )
    {
        strcat( example, "hi" );
        status = ZDynamicArrayPush( array, example );
        printf("%s\t%ld\t%d\n", array->array[i], array->size, status );
    }
    return 0;
}
