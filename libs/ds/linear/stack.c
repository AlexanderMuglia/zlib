#include "include/stack.h"

ZSTATUS
ZStackInitialize
(
    ZStack**     Stack
)
{
    ZSTATUS         status      =   ZSTATUS_FAILED;

    if( *Stack )
    {
        status = ZSTATUS_ALREADY_INITIALIZED;
    }
    else
    {
        *Stack = malloc( sizeof(ZStack) );
        if( *Stack )
        {
            (*Stack)->stack = malloc( sizeof(ZSinglyLinkedList) );
            if( (*Stack)->stack )
            {
                status = ZSTATUS_OK;
            }
            else
            {
                status = ZSTATUS_OUT_OF_MEMORY;
            }
        }
        else
        {
            status = ZSTATUS_OUT_OF_MEMORY;
        }
    }

    return status;
}

ZSTATUS
ZStackDestroy
(
    ZStack**     Stack
)
{
    ZSTATUS     status      =   ZSTATUS_FAILED;

    if( *Stack )
    {
        status = ZSinglyLinkedListDestroy( &((*Stack)->stack) );
        if( ZSTATUS_OK == status )
        {
            free(*Stack);
            *Stack = NULL;
        }
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}

ZSTATUS
ZStackGetSize
(
    ZStack*     Stack,
    int*        Size
)
{
    ZSTATUS         status      =   ZSTATUS_FAILED;

    if( Stack )
    {
        *Size = Stack->stack->size;
        status = ZSTATUS_OK;
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}

ZSTATUS
ZStackIsEmpty
(
    ZStack*     Stack,
    int*        IsEmpty
)
{
    ZSTATUS         status      =   ZSTATUS_FAILED;

    if( Stack )
    {
        *IsEmpty = ( Stack->stack->size == 0 );
        status = ZSTATUS_OK;
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}

ZSTATUS
ZStackPush
(
    ZStack*      Stack,
    char*        Data
)
{
    ZSTATUS         status      =   ZSTATUS_FAILED;

    if( Stack && Data )
    {
        status = ZSinglyLinkedListPrepend( Stack->stack, Data );
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;
}

ZSTATUS
ZStackPeak
(
    ZStack*     Stack,
    char**      Result
)
{
    ZSTATUS         status      =   ZSTATUS_FAILED;
    int             isEmpty     =   -1;

    if( Stack )
    {
        status = ZStackIsEmpty( Stack, &isEmpty );
        if( ZSTATUS_OK == status )
        {
            if( isEmpty )
            {
                Result = NULL;
            }
            else
            {
                *Result = Stack->stack->head->data;
            }
            // redundant but to be clear
            status = ZSTATUS_OK;
        }
    }
    else
    {
        status = ZSTATUS_INVALID_ARGS;
    }

    return status;

}


ZSTATUS
ZStackPop
(
    ZStack*     Stack,
    char**      Result
)
{
    ZSTATUS                     status      =   ZSTATUS_FAILED;
    ZSinglyLinkedListNode*      tmpResult   =   NULL;

    if( Stack && Stack->stack )
    {
        if( Stack->stack->size > 0 )
        {
            tmpResult = Stack->stack->head;

            *Result = malloc( strlen(tmpResult->data) );
            if( Result )
            {
                strcpy( *Result, tmpResult->data );
                if ( Stack->stack->size > 1 )
                {
                    Stack->stack->head = Stack->stack->head->next;
                }
                else
                {
                    Stack->stack->head = NULL;
                }
                free( tmpResult );
                Stack->stack->size -= 1;
                status = ZSTATUS_OK;
            }
            else
            {
                status = ZSTATUS_OUT_OF_MEMORY;
            }
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
    ZSTATUS                     status  =   0;
    ZStack*                     stack   =   NULL;
    char*                       result  =   NULL;

    status = ZStackInitialize( &stack );
    if( ZSTATUS_OK == status )
    {
        status = ZStackPush( stack, "bye" );
        status = ZStackPush( stack, "bye1" );
        status = ZStackPush( stack, "bye2" );
        status = ZStackPush( stack, "bye3" );
        status = ZStackPush( stack, "bye4" );
    }

    status = ZStackPop( stack, &result );
    printf("got status %d, %s\n", status, result );
    status = ZStackPop( stack, &result );
    printf("got status %d, %s\n", status, result );
    status = ZStackPop( stack, &result );
    printf("got status %d, %s\n", status, result );
    status = ZStackPop( stack, &result );
    printf("got status %d, %s\n", status, result );
    status = ZStackPop( stack, &result );
    printf("got status %d, %s\n", status, result );
    status = ZStackPop( stack, &result );
    printf("got status %d, %s\n", status, result );

    status = ZStackDestroy( &stack );
    printf("got status %d\n", status );
    status = ZStackDestroy( &stack );
    printf("got status %d\n", status );
    return 0;
}
