#include "include/array_search.h"
#include "../sort/include/array_sort.h"

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
            mid = (high + low)/2;

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

#define ARRAY_SIZE   100
int main ()
{
    ZSTATUS     status      =  ZSTATUS_OK;
    char*       array[ARRAY_SIZE];
    int         result      =  -1;
    int         item        =  0;
    int         numArray[ARRAY_SIZE];

    for( int j = 0; j < ARRAY_SIZE; j++ )
    {
        numArray[j] = rand();
    }

    item = numArray[0];
    status = ZBubbleSort( numArray, ARRAY_SIZE );
    status = ZBinarySearch( numArray, ARRAY_SIZE, item, &result);
    printf("BinarySearch on %d gave index %d, status 0x%x\n", item, result, status);
    return 0;
}
