#include "include/array_sort.h"

static
ZSTATUS
iPartition
(
    int*    Array,
    int     Lo,
    int     Hi,
    int*    PivotIndex
)
{
    ZSTATUS         status       =  ZSTATUS_OK;
    int             p            =  0;
    int             i            =  0;
    int             tmp          =  0;

    *PivotIndex = Lo - 1;

    if( Array )
    {
        p = Array[Hi];

        for( i = Lo; i < Hi; i++ )
        {
            if( Array[i] <= p )
            {
                *PivotIndex += 1;
                tmp = Array[i];
                Array[i] = Array[*PivotIndex];
                Array[*PivotIndex] = tmp;
            }
        }

        *PivotIndex += 1;
        Array[Hi] = Array[*PivotIndex];
        Array[*PivotIndex] = p;
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}

static
ZSTATUS
iQuickSort
(
    int*    Array,
    int     Lo,
    int     Hi
)
{
    ZSTATUS         status                =  ZSTATUS_OK;
    int             pivotIndex            =  0;

    if( Array )
    {
        if( Lo >= Hi )
        {
           //base case
           return status;
        }
        else
        {
            status = iPartition( Array, Lo, Hi, &pivotIndex );
            if( ZSTATUS_OK == status )
            {
                status = iQuickSort( Array, Lo, pivotIndex - 1 );
                if( ZSTATUS_OK == status )
                {
                    status = iQuickSort( Array, pivotIndex + 1, Hi );
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

ZSTATUS
ZQuickSort
(
    int*    Array,
    int     ArrayLen
)
{
    ZSTATUS         status       =  ZSTATUS_OK;

    if( Array )
    {
        iQuickSort( Array, 0, ArrayLen - 1 );
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}
