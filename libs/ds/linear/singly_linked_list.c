#include "include/singly_linked_list.h"

ZSTATUS
ZSinglyLinkedListAppend
(
    ZSinglyLinkedList*      List,
    void*                   Value
)
{
    ZSTATUS                     status     =   ZSTATUS_FAILED;
    ZSinglyLinkedListNode*	    new        =   NULL;
    ZSinglyLinkedListNode*      current    =   NULL;

    if( List )
    {
        // we have at least one item in the list
        if( List->head )
        {
            current = List->head;
            while( current->next )
            {
                current = (ZSinglyLinkedListNode*) current->next;
            }
            new = malloc( sizeof(ZSinglyLinkedListNode) );

            if( new )
            {
                new->data = Value;
                current->next = new;
                List->size += 1;
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
            new = malloc( sizeof(ZSinglyLinkedListNode) );
            if( new )
            {
                new->data = Value;
                List->head = new;
                status = ZSTATUS_OK;
                List->size += 1;
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
ZSinglyLinkedListPrepend
(
    ZSinglyLinkedList*      List,
    void*                   Value
)
{
    ZSTATUS                     status    =  ZSTATUS_FAILED;
    ZSinglyLinkedListNode*      new       =  NULL;

    if( List )
    {
        new = malloc( sizeof(ZSinglyLinkedListNode) );
        if ( new )
        {
            new->data = Value;

            if ( List->head )
            {
                new->next = List->head;
            }

            List->head = new;
            List->size += 1;
            status = ZSTATUS_OK;
        }
        else
        {
            status = ZSTATUS_OUT_OF_MEMORY;
        }
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}

ZSTATUS
ZSinglyLinkedListPrint
(
    ZSinglyLinkedList*      List
)
{
    ZSTATUS                      status      =  ZSTATUS_FAILED;
    ZSinglyLinkedListNode*       current     =  NULL;

    if( List )
    {
        current = List->head;

        while ( current )
        {
            // assuming string for now, but this can be better
            printf( "%s->", (char*) current->data);
            current = current->next;
        }
        printf("NULL\n");
        status = ZSTATUS_OK;
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }
}
int main(int argc, char** argv)
{
    ZSTATUS                     status   =  0;
    char*                       hi       =  "hi";
    char*                       hi2      =  "hi2";
    char*                       hi3      =  "hi3";
    ZSinglyLinkedList*          list     =  NULL;
    ZSinglyLinkedListNode*      node     =  NULL;
    int                         i        =  0;

    list = malloc( sizeof(ZSinglyLinkedList) );
    node = malloc( sizeof(ZSinglyLinkedListNode) );

    status = ZSinglyLinkedListPrepend( list, (void*) hi );
    status = ZSinglyLinkedListAppend( list, (void*) hi2 );
    status = ZSinglyLinkedListPrepend( list, (void*) hi3 );

    node = list->head;
    printf( "List size = %d\n", list->size );
    while ( node )
    {
        printf( "list item %d: %s\n", i, (char*) node->data );
        node = node->next;
        i++;
    }

    status = ZSinglyLinkedListPrint( list );

    return 0;
}
