#include <stdlib.h>
#include "include/array_search.h"

ZSTATUS
ZLinearSearch
(
    char**      Array,
    int         ArrayLen,
    char*       Item,
    int*        Index
)
{
    ZSTATUS         status      =  ZSTATUS_FAILED;
    int             i           =  0;

    if( Array )
    {
        while( i < ArrayLen )
        {
            if( Array[i] && Item )
            {
                if( strcmp(Array[i], Item) == 0 ) break;
            }
            else if( !Array[i] && !Item )
            {
                break;
            }


            i++;
        }

        status = ZSTATUS_OK;
        if( i >= ArrayLen )
        {
            *Index = -1;
        }
        else
        {
            *Index = i;
        }
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
        *Index = -1;
    }

    return status;
}

ZSTATUS
ZBinarySearch
(
    int*        Array,
    int         ArrayLen,
    int         Item,
    int*        Index
)
{
    ZSTATUS         status      =  ZSTATUS_FAILED;
    int             high        =  ArrayLen - 1;
    int             low         =  0;
    int             mid         =  ArrayLen/2;
    bool            found       =  0;

    if( Array )
    {
        while( high >= low )
        {
            mid = low + ((high - low)/2);

            if( Array[mid] == Item )
            {
                found = 1;
                break;
            }
            else if( Array[mid] > Item )
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }

        if( found )
        {
            *Index = mid;
        }
        else
        {
            *Index = -1;
        }

        status = ZSTATUS_OK;
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
        *Index = -1;
    }

    return status;
}

ZSTATUS
ZTwoCrystalBalls
(
    int*        Array,
    int         ArrayLen,
    int*        Index
)
{
    ZSTATUS         status      =  ZSTATUS_FAILED;
    int             step        =  0;
    int             i           =  0;
    int             j           =  0;

    if( Array && ArrayLen > 0 )
    {
        step = sqrt( ArrayLen );

        for( i = 0; i < ArrayLen; i += step )
        {
            if( Array[i] ) break;
        }

        i -= step;

        for( j = 0; j <= step && i < ArrayLen; j++, i++ )
        {
            if( Array[i] ) break;
        }

        status = ZSTATUS_OK;
        *Index = i;
    }
    else
    {
        *Index = -1;
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}
