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

ZSTATUS
ZDynamicArrayPop
(
    ZDynamicArray*      Array,
    char**              Output
)
{
    ZSTATUS         status           =   ZSTATUS_FAILED;
    size_t          strSize          =   0;

    if( Array && Output )
    {
        if( Array->used > 0 )
        {
            strSize = strlen( Array->array[Array->used - 1 ] );
            *Output = malloc( strSize );
            if( Output )
            {
                strcpy( *Output, Array->array[Array->used - 1] );
                Array->array[Array->used - 1] = NULL;
                Array->used -= 1;
                status = ZSTATUS_OK;
            }
            else
            {
                status = ZSTATUS_OUT_OF_MEMORY;
            }
        }
        else
        {
            status = ZSTATUS_INDEX_OUT_OF_RANGE;
        }
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}

ZSTATUS
ZDynamicArrayInsert
(
    ZDynamicArray*      Array,
    char*               Input,
    uint64_t            Index
)
{
    ZSTATUS         status      =   ZSTATUS_FAILED;

    if( Array )
    {
        if( Array->used > Index )
        {
            Array->array[Index] = Input;
            status = ZSTATUS_OK;
        }
        else
        {
            status = ZSTATUS_INDEX_OUT_OF_RANGE;
        }
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}

ZSTATUS
ZDynamicArrayDestroy
(
    ZDynamicArray*      Array
)
{
    ZSTATUS         status      =   ZSTATUS_FAILED;

    for( uint64_t i = 0; i < Array->size; i++ )
    {
        Array->array[i] = NULL;
    }
    Array->size = 0;
    Array->used = 0;
    free(Array->array);
    free(Array);
    status = ZSTATUS_OK;

    return status;
}
