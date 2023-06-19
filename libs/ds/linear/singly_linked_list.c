#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../common/ZStatus.h"

typedef struct ZNode{
    struct  ZNode* next;
    void*          data;
} ZNode;

typedef struct {
    ZNode* head;
} ZList;

ZSTATUS
ZAppend
(
    ZList*    List,
    void*     Value
)
{
    ZSTATUS     status     =   ZSTATUS_FAILED;
    ZNode*	    new        =   NULL;
    ZNode*      current    =   NULL;

    if( List )
    {
        // we have at least one item in the list
        if( List->head )
        {
            current = List->head;
            while( current->next )
            {
                current = (ZNode*) current->next;
            }
            new = malloc( sizeof(ZNode) );

            if( new )
            {
                new->data = Value;
                current->next = new;
                status = ZSTATUS_OK;
            }
            else
            {
                status = ZSTATUS_OUT_OF_MEMORY;
            }
        }
        else
        {
             // the list is empty
            new = malloc( sizeof(ZNode) );
            if( new )
            {
                new->data = Value;
                List->head = new;
                status = ZSTATUS_OK;
            }
            else
            {
                status = ZSTATUS_OUT_OF_MEMORY;
            }
        }
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}

ZSTATUS
ZPrepend
(
    ZList* List,
    void*  Value
)
{
    ZSTATUS     status    =  ZSTATUS_FAILED;
    ZNode*      new       =  NULL;

    if( List )
    {
        if ( List->head )
        {

        }
        else
        {
            // list currently empty
            new = malloc( sizeof(ZNode) );
            if ( new )
            {
                new->data = Value;
                List->head = new;
                status = ZSTATUS_OK;
            }
            else
            {
                status = ZSTATUS_OUT_OF_MEMORY;
            }
        }
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}

int main(int argc, char** argv)
{
  int     status   =  0;
  char*   hi       =  "hi";
  char*   hi2      =  "hi2";
  ZList*  list     =  NULL;

  list = malloc( sizeof(ZList) );

  status = ZAppend( list, (void*) hi );
  status = ZAppend( list, (void*) hi2 );

  printf("%s\n%s\n", (char*) list->head->data, (char*) list->head->next->data);

  return 0;
}
