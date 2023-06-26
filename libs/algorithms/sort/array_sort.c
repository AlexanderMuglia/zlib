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

#define ARRAY_SIZE    10
int main ()
{
    ZSTATUS     status      =  ZSTATUS_OK;
    int         array[ARRAY_SIZE];

    srand(5);
    for( int i = 0; i < ARRAY_SIZE; i++ )
    {
        array[i] = rand() % 1000;
        if (i % 2) array[i] *= -1;
    }

    printf("Before sort: \n");
    for( int i = 0; i < ARRAY_SIZE; i++ )
    {
        printf("%d\n", array[i]);
    }

    status = ZBubbleSort( array, ARRAY_SIZE );

    printf("After sort: \n");
    for( int i = 0; i < ARRAY_SIZE; i++ )
    {
        printf("%d\n", array[i]);
    }

    return 0;
}
