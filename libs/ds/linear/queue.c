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

int main(int argc, char** argv)
{
    ZSTATUS                     status  =   0;
    ZQueue*                     queue   =   NULL;

    status = ZQueueInitialize( &queue );
    if( ZSTATUS_OK == status )
    {
        status = ZEnqueue( queue, "bye" );
    }

    printf("got status %d, %s\n", status, queue->queue->head->data );

    return 0;
}
