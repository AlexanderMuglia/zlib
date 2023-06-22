#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../../common/ZStatus.h"



typedef struct ZSinglyLinkedListNode
{
    struct          ZSinglyLinkedListNode*           next;
    void*                                            data;

} ZSinglyLinkedListNode;

typedef struct
{
    ZSinglyLinkedListNode*      head;
    uint32_t                    size;

} ZSinglyLinkedList;


ZSTATUS
ZSinglyLinkedListAppend
(
    ZSinglyLinkedList*      List,
    void*                   Value
);


ZSTATUS
ZSinglyLinkedListPrepend
(
    ZSinglyLinkedList*      List,
    void*                   Value
);

ZSTATUS
ZSinglyLinkedListPrint
(
    ZSinglyLinkedList*      List
);

ZSTATUS
ZSinglyLinkedListRemoveAtIndex
(
    ZSinglyLinkedList*      List,
    uint32_t                index
);
