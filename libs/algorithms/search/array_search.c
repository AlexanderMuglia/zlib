#include "include/array_search.h"

ZSTATUS
ZArrayLinearSearch
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
            else
            {
                if( !Array[i] && !Item ) break;
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


#define ARRAY_SIZE    4
int main ()
{
    ZSTATUS     status      =  ZSTATUS_OK;
    char*       array[ARRAY_SIZE];
    int         result      =  -1;

    array[0] = "hello";
    array[1] = "hi";
    array[3] = "bye";

    status = ZArrayLinearSearch( array, ARRAY_SIZE, "bye", &result);

    printf("'bye' is at %d in the array 0x%x\n", result, status);
    return 0;
}
