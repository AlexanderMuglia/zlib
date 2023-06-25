#include "include/bubble_sort.h"

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
                if( Array[i] > Array[i + 1] )
                {
                    Array[i] = Array[i] ^ Array[i + 1];
                    Array[i + 1 ] = Array[i] ^ Array[i + 1];
                    Array[i] = Array[i] ^ Array[i + 1];
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

int main ()
{
    ZSTATUS     status      =  ZSTATUS_OK;
    int         array[4];

    array[0] = 3;
    array[1] = -4;
    array[2] = 0;
    array[3] = 1;

    printf("Before sort: \n");
    for( int i = 0; i < 4; i++ )
    {
        printf("%d\n", array[i]);
    }

    status = ZBubbleSort( array, 4 );

    printf("After sort: \n");
    for( int i = 0; i < 4; i++ )
    {
        printf("%d\n", array[i]);
    }

    return 0;
}
