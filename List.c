
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct NodeObj
{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
}
NodeObj;

typedef NodeObj* Node;

typedef struct ListObj
{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
}
ListObj;


Node newNode(int data)
{
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

void freeNode(Node* pN)
{
   if( pN!=NULL && *pN!=NULL )
   {
      free(*pN);
      *pN = NULL;
   }
}

List newList(void)
{
   List L;
   L = malloc(sizeof(ListObj));
   //printf("L = %p\n", (void*)L);
   L->front = L->back = L->cursor = NULL;
   L->index = -1;
   L->length = 0;
   return(L);
}


void freeList(List* pL)
{
   if(pL!=NULL && *pL!=NULL)
   { 
      while( !(length(*pL) == 0))
      { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}

int length(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

int index(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->index);
}


int front(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length == 0 )
   {
      printf("List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);
}


int back(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length == 0 )
   {
      printf("List Error: calling back() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->back->data);
}

int get(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->cursor == NULL )
   {
      printf("List Error: calling get() with a NULL cursor\n");
      exit(EXIT_FAILURE);
   }
   return(L->cursor->data);
}

int equals(List A, List B)
{
   Node N = NULL;
   Node M = NULL;
   if( A==NULL || B==NULL)
   {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( A->length != B->length)
      return (0);
   N = A->front;
   M = B->front;
   while (N != NULL)
   {
      if(N->data != M->data)
         return (0);
      N = N->next;
      M = M->next;
   }
   return (1);
}


void clear(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling clear() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   while( length(L) != 0)
   { 
      deleteFront(L); 
   }
   L->cursor = NULL;
   L->index = -1;
}

void set(List L, int x) {
   if (length(L) > 0 && index(L) >= 0)
   {
	L->cursor->data = x;
   }
}
void moveFront(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   L->cursor = L->front;
   if(L->length !=0)
      L->index = 0;
}

void moveBack(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   L->cursor = L->back;
   L->index = L->length - 1;
}

void movePrev(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->cursor != NULL)
   {
      L->cursor = L->cursor->prev;
      L->index--;
   }
}

void moveNext(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->cursor != NULL)
   {
      L->cursor = L->cursor->next;
      if(L->cursor != NULL)
         L->index++;
      else
         L->index = -1;
   }
}

void prepend(List L, int data)
{
   Node N = newNode(data);
   if( L==NULL )
   {
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->length == 0)
   {
      L->front = L->back = N;
      L->length++;
   }
   else
   {
      N->next = L->front;
      L->front->prev = N;
      L->front = N;
      if(L->cursor != NULL)
         L->index++;
      L->length++;
   }
}

void append(List L, int data)
{
   Node N = newNode(data);
   if( L==NULL )
   {
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->length == 0)
   {
      L->front = L->back = N;
      L->length++;
   }
   else
   {
      N->prev = L->back;
      L->back->next = N;
      L->back = N;
      L->length++;
   }
}


void insertBefore(List L, int data)
{
   Node N = newNode(data);
   if( L==NULL )
   {
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->cursor == NULL)
   {
      printf("List Error: calling insertBefore() with a NULL cursor\n");
      exit(EXIT_FAILURE);
   }
   if(L->cursor == L->front)
   {
      N->next = L->front;
      L->front->prev = N;
      L->front = N;
      L->index++;
      L->length++;
   }
   else
   {
      N->prev = L->cursor->prev;
      N->next = L->cursor;
      L->cursor->prev->next = N;
      L->cursor->prev = N;
      L->index++;
      L->length++;
   }
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data)
{
   Node N = newNode(data);
   if( L==NULL )
   {
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->cursor == NULL)
   {
      printf("List Error: calling insertAfter() with a NULL cursor\n");
      exit(EXIT_FAILURE);
   }
   if(L->cursor == L->back)
   {
      N->prev = L->back;
      L->back->next = N;
      L->back = N;
      L->length++;
   }
   else
   {
      N->next = L->cursor->next;
      N->prev = L->cursor;
      L->cursor->next->prev = N;
      L->cursor->next = N;
      L->length++;
   }
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L)
{
   Node N = NULL;
   if( L==NULL )
   {
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->front == NULL)
   {
      printf("List Error: calling deleteFront() with an empty List\n");
      exit(EXIT_FAILURE);
   }
   if(L->length == 1)
   {
      freeNode(&L->front);
      L->front = L->back = L->cursor = NULL;
      L->index = -1;
      L->length = 0;
   }
   if(L->length > 1)
   {
      N = L->front;
      L->front = L->front->next;
      if(L->cursor == N) {
      L->cursor = L->front;
      }
      freeNode(&N);
      L->front->prev = NULL;
      if(L->index == 0) {
         L->cursor = NULL;
      }
      L->index--;
      L->length--;
   }
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L)
{
   Node N = NULL;
   if( L==NULL )
   {
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->back == NULL)
   {
      printf("List Error: calling deleteBack() with an empty List\n");
      exit(EXIT_FAILURE);
   }
   if(L->length == 1)
   {
      freeNode(&L->front);
      L->front = L->back = L->cursor = NULL;
      L->index = -1;
      L->length = 0;
   }
   else
   {
      N = L->back;
      if(L->cursor == N)
      {
         L->cursor = NULL;
         L->index = -1;
      }
      L->back = L->back->prev;
      freeNode(&N);
      L->back->next = NULL;
      L->length--;
   }
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L)
{
   Node N = NULL;
   if( L==NULL )
   {
      printf("List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->cursor == NULL)
   {
      printf("List Error: calling delete() with a NULL cursor\n");
      exit(EXIT_FAILURE);
   }
   N = L->cursor;
   L->cursor = NULL;
   if(L->length == 1)
   {
      freeNode(&L->front);
      L->front = L->back = NULL;
   }
   else if(L->front == N)
   {
      N = L->front;
      L->front = L->front->next;
      freeNode(&N);
      L->front->prev = NULL;
   }
   else if(L->back == N)
   {
      N = L->back;
      L->back = L->back->prev;
      freeNode(&N);
      L->back->next = NULL;
   }
   else
   {
      N->prev->next = N->next;
      N->next->prev = N->prev;
      freeNode(&N);
   }
   L->length--;
   L->index = -1;
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L
// consisting of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L)
{
   Node N = NULL;
   if( L==NULL )
   {
      printf("List is null");
      printf("List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   for(N = L->front; N != NULL; N = N->next)
   {
      fprintf(out, "%d ", N->data);
   }
}

// copyList()
// Returns a new List representing the same integer sequence as L.
// The cursor in the new list is undefined, regardless of the state of
// the cursor in L. The state of L is unchanged.
List copyList(List L)
{
   List Copy = newList();
   Node N = NULL;
   if( L==NULL )
   {
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   N = L->front;
   while(N != NULL)
   {
      append(Copy, N->data);
      N = N->next;
   }
   return(Copy);
}


