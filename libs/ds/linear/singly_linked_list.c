#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ZNode{
  struct  ZNode* next;
  void*          data;
} ZNode;

typedef struct {
  ZNode* head;
} ZList;

int ZAppend
(
  ZList*    List,
  void*     Value
)
{
  ZNode*	 new        =   NULL;
  ZNode*   current    =   NULL;
  int      retVal     =   -1;

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
       retVal = 0;
    }
  }
  else
  {
    new = malloc( sizeof(ZNode) );
    if( new )
    {
      new->data = Value;
      List->head = new;
      retVal = 0;
    }
  }

  return retVal;
}

int ZPrepend
(
  ZNode* Head,
  void*  Value
)
{
  return -1;
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
