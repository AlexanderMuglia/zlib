#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../../common/ZStatus.h"

typedef struct {
    char**      array;
    size_t      size;
    size_t      used;

} ZDynamicArray;

/*
 * Initializes a dynamic array starting at a user-defined size.
 */
ZSTATUS
ZDynamicArrayInitialize
(
    ZDynamicArray**      Array,
    size_t               InitSize
);

/*
 * Adds an item (Input) to the end of the array. Will dynamically grow the array as needed.
 */
ZSTATUS
ZDynamicArrayPush
(
    ZDynamicArray*      Array,
    char*               Input
);

/*
 * Returns a pointer to the final item in the array (placed in Output).
 * Sets last spot to NULL
 * Will not resize the array currently.
 */
ZSTATUS
ZDynamicArrayPop
(
    ZDynamicArray*      Array,
    char**              Output
);

/*
 * Overwrites an item in the array. Does not allow writing outside of range pushed to.
 */
ZSTATUS
ZDynamicArrayInsert
(
    ZDynamicArray*      Array,
    char*               Input,
    int                 Index
);
