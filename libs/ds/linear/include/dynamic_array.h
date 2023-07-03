#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../../common/ZStatus.h"

typedef struct {
    char**      array;
    size_t      size;
    size_t      used;

} ZDynamicArray;

ZSTATUS
ZInitializeDynamicArray
(
    ZDynamicArray**      Array,
    size_t               InitSize
);
