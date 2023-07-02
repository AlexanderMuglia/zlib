#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../../common/ZStatus.h"
#include "singly_linked_list.h"

/*
 * A stack type that holds strings for data
 * ZSinglyLinkedList under the hood
 */
typedef struct
{
    ZSinglyLinkedList*    stack;

} ZStack;

/*
 * Initializes the stack and the list that it uses.
 */
ZSTATUS
ZStackInitialize
(
    ZStack**     Stack
);

/*
 * Checks if the stack is empty.
 */
ZSTATUS
ZStackGetSize
(
    ZStack*     Stack,
    int*        Size
);

/*
 * Checks if the stack is empty.
 */
ZSTATUS
ZStackIsEmpty
(
    ZStack*     Stack,
    int*        IsEmpty
);

/*
 * Adds an item to the top of the stack.
 */
ZSTATUS
ZStackPush
(
    ZStack*      Stack,
    char*        data
);

/*
 * Returns a reference to the actual string that is at the top of the stack.
 * Does not edit the stack.
 */
ZSTATUS
ZStackPeak
(
    ZStack*     Stack,
    char**      result
);

/*
 * Returns a copy of the string that was at the top of the stack.
 * Removes the item from the stack.
 * Result string must be freed manually as it is a duplicate.
 */
ZSTATUS
ZStackPop
(
    ZStack*     Stack,
    char**      Result
);
