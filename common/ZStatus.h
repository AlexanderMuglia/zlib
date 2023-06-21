#include <stdint.h>

typedef     uint32_t          ZSTATUS;

#define             ZSTATUS_OK                        (ZSTATUS)  0x00000000
#define             ZSTATUS_FAILED                    (ZSTATUS)  0x00000001
#define             ZSTATUS_INVALID_ARGS              (ZSTATUS)  0x00000002
#define             ZSTATUS_OUT_OF_MEMORY             (ZSTATUS)  0x00000003
#define             ZSTATUS_ERR_INTERNAL              (ZSTATUS)  0x00000004
#define             ZSTATUS_INDEX_OUT_OF_RANGE        (ZSTATUS)  0x00000005

