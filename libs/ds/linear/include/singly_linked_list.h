#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../../common/ZStatus.h"


/*
 * A node of a a singly linked list that stores a string as data
 */
typedef struct ZSinglyLinkedListNode
{
    struct          ZSinglyLinkedListNode*           next;
    char*                                            data;

} ZSinglyLinkedListNode;

/*
 * A singly linked list type that holds strings for data
 */
typedef struct
{
    ZSinglyLinkedListNode*      head;
    uint32_t                    size;

} ZSinglyLinkedList;

/*
 * Appends a new node to the end of the list
 */
ZSTATUS
ZSinglyLinkedListAppend
(
    ZSinglyLinkedList*      List,
    char*                   Value
);

/*
 * Appends a new node to the start of the list
 */
ZSTATUS
ZSinglyLinkedListPrepend
(
    ZSinglyLinkedList*      List,
    char*                   Value
);

/*
 * Prints a singly linked list. Shows NULL at last link but is not a node
 */
ZSTATUS
ZSinglyLinkedListPrint
(
    ZSinglyLinkedList*      List
);

/*
 * Removes a node at a given index
 */
ZSTATUS
ZSinglyLinkedListRemoveAtIndex
(
    ZSinglyLinkedList*      List,
    uint32_t                index
);

/*
 * Searches the list for a given value.
 * If found, return ZSTATUS_OK and place index in Index
 * If not found, still return ZSTATUS_OK but index will be -1
 */
ZSTATUS
ZSinglyLinkedListSearch
(
    ZSinglyLinkedList*      List,
    char*                   Item,
    int*                    Index
);

ZSTATUS
ZSinglyLinkedListDestroy
(
    ZSinglyLinkedList*      List
);
