#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../../common/ZStatus.h"

/*
 * does a bubble sort of an array of integers.
 * O(n^2) time
 */
ZSTATUS
ZBubbleSort
(
    int*    Array,
    int     ArrayLen
);

/*
 * Performs Quicksort on an array of integers.
 * O(nlogn) time, operates in place
 */
ZSTATUS
ZQuickSort
(
    int*    Array,
    int     ArrayLen
);
