#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../../../../common/ZStatus.h"

ZSTATUS
ZLinearSearch
(
    char**      Array,
    int         ArrayLen,
    char*       Item,
    int*        Index
);

ZSTATUS
ZBinarySearch
(
    int*        Array,
    int         ArrayLen,
    int         Item,
    int*        Index
);
