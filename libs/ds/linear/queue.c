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
        status = ZSinglyLinkedListAppend( Queue->queue, data );
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
    char**      Result
)
{
    ZSTATUS         status      =   ZSTATUS_FAILED;
    int             isEmpty     =   -1;

    if( Queue )
    {
        status = ZQueueIsEmpty( Queue, &isEmpty );
        if( ZSTATUS_OK != status || isEmpty )
        {
            Result = NULL;
        }
        else
        {
            *Result = Queue->queue->head->data;
        }
        status = ZSTATUS_OK;
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;

}

ZSTATUS
ZDequeue
(
    ZQueue*     Queue,
    char**      Result
)
{
    ZSTATUS                     status      =   ZSTATUS_FAILED;
    ZSinglyLinkedListNode*      tmpResult   =   NULL;

    if( Queue && Queue->queue )
    {
        if( Queue->queue->size > 0 )
        {
            tmpResult = Queue->queue->head;

            *Result = malloc( strlen(tmpResult->data) );
            if( Result )
            {
                strcpy( *Result, tmpResult->data );
                if ( Queue->queue->size > 1 )
                {
                    Queue->queue->head = Queue->queue->head->next;
                }
                else
                {
                    Queue->queue->head = NULL;
                }
                free( tmpResult );
                Queue->queue->size -= 1;
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
    ZQueue*                     queue   =   NULL;
    char*                       result  =   NULL;

    status = ZQueueInitialize( &queue );
    if( ZSTATUS_OK == status )
    {
        status = ZEnqueue( queue, "bye" );
        status = ZEnqueue( queue, "bye1" );
        status = ZEnqueue( queue, "bye2" );
        status = ZEnqueue( queue, "bye3" );
        status = ZEnqueue( queue, "bye4" );
    }

    status = ZDequeue( queue, &result );
    printf("got status %d, %s\n", status, result );
    status = ZDequeue( queue, &result );
    printf("got status %d, %s\n", status, result );
    status = ZDequeue( queue, &result );
    printf("got status %d, %s\n", status, result );
    status = ZDequeue( queue, &result );
    printf("got status %d, %s\n", status, result );
    status = ZDequeue( queue, &result );
    printf("got status %d, %s\n", status, result );
    status = ZDequeue( queue, &result );
    printf("got status %d, %s\n", status, result );

    return 0;
}
