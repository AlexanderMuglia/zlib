#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../../common/ZStatus.h"
#include "singly_linked_list.h"

/*
 * A queue type that holds strings for data
 * ZSinglyLinkedList under the hood
 */
typedef struct
{
    // ZQueue->queue(->head->data) is a bit gross, but user shouldn't have to know
    // Just hide behind methods like ZEnqueue and ZQueuePeak :)
    ZSinglyLinkedList*      queue;

} ZQueue;

ZSTATUS
ZQueueInitialize
(
    ZQueue**     Queue
);

ZSTATUS
ZQueueIsEmpty
(
    ZQueue*     Queue,
    int*        IsEmpty
);

ZSTATUS
ZEnqueue
(
    ZQueue*      Queue,
    char*        data
);

ZSTATUS
ZQueuePeak
(
    ZQueue*     Queue,
    char**      result
);

ZSTATUS
ZDequeue
(
    ZQueue*     Queue,
    char**      Result
);
