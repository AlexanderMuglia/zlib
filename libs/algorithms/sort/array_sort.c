#include "include/array_sort.h"

ZSTATUS
ZBubbleSort
(
    int*    Array,
    int     ArrayLen
)
{
    ZSTATUS         status      =  ZSTATUS_OK;
    int             i           =  0;
    int             j           =  0;

    if( Array )
    {
        for( i = 0; i < ArrayLen - 1; i++ )
        {
            for( j = 0; j < ArrayLen - i - 1; j++ )
            {
                if( Array[j] > Array[j + 1] )
                {
                    Array[j] = Array[j] ^ Array[j + 1];
                    Array[j + 1 ] = Array[j] ^ Array[j + 1];
                    Array[j] = Array[j] ^ Array[j + 1];
                }
            }
        }
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}
