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


ZSTATUS
ZSinglyLinkedListRemoveAtIndex
(
    ZSinglyLinkedList*      List,
    uint32_t                index
)
{
    ZSTATUS                                 status          =  ZSTATUS_FAILED;
    ZSinglyLinkedListNode*                  prev            =  NULL;
    ZSinglyLinkedListNode*                  current         =  NULL;
    int                                     i               =  0;

    if( List )
    {
        if( index < List->size )
        {
            prev = List->head;

            if( 0 == index )
            {
                if ( List->size > 1 )
                {
                    List->head = List->head->next;
                }
                else
                {
                    List->head = NULL;
                }
                free( prev );
            }
            else
            {
                current = prev->next;

                for( i = 1; i < index; i++ );
                {
                    prev = current;
                    current = current->next;
                }
                prev->next = current->next;

                free ( current );
            }

            List->size -= 1;
            status = ZSTATUS_OK;
        }
        else
        {
            status = ZSTATUS_INDEX_OUT_OF_RANGE;
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
    status = ZSinglyLinkedListPrepend( list, (void*) hi2 );
    status = ZSinglyLinkedListPrepend( list, (void*) hi3 );
    status = ZSinglyLinkedListPrepend( list, (void*) hi3 );
    printf("%d\n", list->size);
    status = ZSinglyLinkedListRemoveAtIndex( list, 3 );
    printf("%x\n", status);
    status = ZSinglyLinkedListRemoveAtIndex( list, 1 );
    printf("%x\n", status);

    node = list->head;
    printf( "List size = %d\n", list->size );

    //status = ZSinglyLinkedListPrint( list );

    return 0;
}
