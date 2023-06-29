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


/*
 * 2 Crystal Ball general case problem.
 * Given 2 crystal balls that will break at a certain height,
 * efficiently find the height at which the balls will break.
 * Array is an int array consisting of 0s (won't break) and 1s (will break)
 * representing heights.
 * Index is the first index that the balls will break.
 * Runs in sqrt(n) time :)
 */
ZSTATUS
ZTwoCrystalBalls
(
    int*        Array,
    int         ArrayLen,
    int*        Index
);
