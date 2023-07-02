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

/*
 * Initializes a ZQueue
 */
ZSTATUS
ZQueueInitialize
(
    ZQueue**     Queue
);

/*
 * Returns the size of the queue Size.
 */
ZSTATUS
ZQueueGetSize
(
    ZQueue*     Queue,
    int*        Size
);

/*
 * Checks if the queue is empty
 */
ZSTATUS
ZQueueIsEmpty
(
    ZQueue*     Queue,
    int*        IsEmpty
);

/*
 * Uses ZSinglyLinkedListAppend to add an item to queue.
 */
ZSTATUS
ZEnqueue
(
    ZQueue*      Queue,
    char*        Data
);

/*
 * Returns a reference to the actual string that is next in queue
 * Does not edit the queue.
 */
ZSTATUS
ZQueuePeak
(
    ZQueue*     Queue,
    char**      Result
);

/*
 * Returns a copy of the string that was next in queue.
 * Removes the item from the queue.
 * Result string must be freed manually as it is a duplicate.
 */
ZSTATUS
ZDequeue
(
    ZQueue*     Queue,
    char**      Result
);
