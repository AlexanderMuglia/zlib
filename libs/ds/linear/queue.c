#include "include/queue.h"

ZSTATUS
ZQueueInitialize
(
    ZQueue**     Queue
)
{
    ZSTATUS     status      =   ZSTATUS_FAILED;

    if( *Queue )
    {
        status = ZSTATUS_INVALID_ARGS;
    }
    else
    {
        *Queue = malloc( sizeof(ZQueue) );
        if( *Queue )
        {
            (*Queue)->queue = malloc( sizeof(ZSinglyLinkedList) );
            if( (*Queue)->queue )
            {
                status = ZSTATUS_OK;
            }
            else
            {
                status = ZSTATUS_OUT_OF_MEMORY;
                free( *Queue );
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
ZQueueIsEmpty
(
    ZQueue*     Queue,
    int*        IsEmpty
)
{
    ZSTATUS         status      =   ZSTATUS_FAILED;

    if( Queue )
    {
        *IsEmpty = (Queue->queue->size == 0);
        status = ZSTATUS_OK;
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}


ZSTATUS
ZEnqueue
(
    ZQueue*      Queue,
    char*        data
)
{
    ZSTATUS         status      =   ZSTATUS_FAILED;

    if( Queue )
    {
        status = ZSinglyLinkedListPrepend( Queue->queue, data );
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}

ZSTATUS
ZQueuePeak
(
    ZQueue*     Queue,
    char**      result
)
{
    ZSTATUS         status      =   ZSTATUS_FAILED;
    int             isEmpty     =   -1;

    if( Queue )
    {
        status = ZQueueIsEmpty( Queue, &isEmpty );
        if( ZSTATUS_OK != status || isEmpty )
        {
            result = NULL;
        }
        else
        {
            *result = Queue->queue->head->data;
        }
        status = ZSTATUS_OK;
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
    ZQueue*                     queue   =   NULL;
    char*                       result  =   NULL;

    status = ZQueueInitialize( &queue );
    if( ZSTATUS_OK == status )
    {
        status = ZEnqueue( queue, "bye" );
        if ( ZSTATUS_OK == status )
        {
            status = ZQueuePeak( queue, &result );
        }
    }

    printf("got status %d, %s\n", status, result );

    return 0;
}
