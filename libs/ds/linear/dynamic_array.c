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
    ZSTATUS         status      =   ZSTATUS_OK;
    size_t          strSize        =   0;

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

int main(int argc, char** argv)
{
    ZSTATUS                     status  =   0;
    ZDynamicArray*              array   =   NULL;
    char*                       res     =   "";
    char*                       str1    =   "str1";
    char*                       str2    =   "str2";

    status = ZDynamicArrayInitialize( &array, 0);
    status = ZDynamicArrayPush( array, str1 );
    printf("%s\t%ld\t%d\n", array->array[0], array->size, status );
    status = ZDynamicArrayPush( array, str2 );
    printf("%s\t%ld\t%d\n", array->array[1], array->size, status );
    for( int i = 0; i < 5; i++ )
    {
        res = "";
        status = ZDynamicArrayPop( array, &res );
        printf("%s\t%ld\t%ld\t%d\n", res, array->size, array->used, status );
    }
    return 0;
}
