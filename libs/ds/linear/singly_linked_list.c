#include "include/singly_linked_list.h"

ZSTATUS
ZSinglyLinkedListAppend
(
    ZSinglyLinkedList*      List,
    char*                   Value
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
    char*                   Value
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
            printf( "%s->", current->data);
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
    uint32_t                Index
)
{
    ZSTATUS                                 status          =  ZSTATUS_FAILED;
    ZSinglyLinkedListNode*                  prev            =  NULL;
    ZSinglyLinkedListNode*                  current         =  NULL;
    int                                     i               =  0;

    if( List )
    {
        if( Index < List->size )
        {
            prev = List->head;

            if( 0 == Index )
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

                for( i = 1; i < Index; i++ );
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

ZSTATUS
ZSinglyLinkedListSearch
(
    ZSinglyLinkedList*      List,
    char*                   Item,
    int*                    Index
)
{
    ZSTATUS                 status     =  ZSTATUS_FAILED;
    int                     i          =  0;
    int                     found      =  0;
    ZSinglyLinkedListNode*  cur        =  NULL;

    if( List )
    {
        if( List->head )
        {
            cur = List->head;
            for( i = 0; i < List->size; i++ )
            {
                if( strcmp(cur->data, Item) == 0 )
                {
                    found = 1;
                    break;
                }
                else
                {
                    cur = cur->next;
                }
            }
            if( found )
            {
                *Index = i;
            }
            else
            {
                *Index = -1;
            }
            status = ZSTATUS_OK;
        }
        else
        {
            *Index = -1;
            status = ZSTATUS_OK;
        }
    }
    else
    {
        *Index = -1;
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

    status = ZSinglyLinkedListSearch( list, "hi2", &i);
    printf("got status %d, and we (maybe) found the string at index %d\n", status, i);
    list = malloc( sizeof(ZSinglyLinkedList) );
    node = malloc( sizeof(ZSinglyLinkedListNode) );

    status = ZSinglyLinkedListSearch( list, "hi2", &i);
    printf("got status %d, and we (maybe) found the string at index %d\n", status, i);
    status = ZSinglyLinkedListPrepend( list, hi );
    status = ZSinglyLinkedListSearch( list, "hi", &i);
    printf("got status %d, and we (maybe) found the string at index %d\n", status, i);
    status = ZSinglyLinkedListPrepend( list, hi2 );
    status = ZSinglyLinkedListPrepend( list, hi3 );
    status = ZSinglyLinkedListPrepend( list, hi3 );

    status = ZSinglyLinkedListSearch( list, "hi2", &i);
    printf("got status %d, and we (maybe) found the string at index %d\n", status, i);
    status = ZSinglyLinkedListSearch( list, "bye", &i);
    printf("got status %d, and we (maybe) found the string at index %d\n", status, i);
    node = list->head;
    printf( "List size = %d\n", list->size );

    status = ZSinglyLinkedListPrint( list );

    return 0;
}
