//-----------------------------------------------------------------------------
// Jerry Liu
// jelliu
// CMPS101
// pa5
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

//Private NodeObj Type
typedef struct NodeObj
{
    int data;
    struct NodeObj* next;
    struct NodeObj* previous;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj
{
    Node front;
    Node back;
    Node cursor;
    Node previous;
    Node next;
    int length;
    int index;
} ListObj;

typedef ListObj* List;

// Constructors-Destructors ---------------------------------------------------
// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data)
{
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->previous = NULL;
    return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
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
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
}
void freeList(List* pL)
{
    if(pL!=NULL && *pL!=NULL)
    {
        while( length(*pL) != 0 )
        {

            deleteFront(*pL);

        }

    }
    free(*pL);
    *pL = NULL;
}

// Access functions -----------------------------------------------------------
// Access functions -----------------------------------------------------------
// Returns the number of elements in this List.
int length(List L)
{
    return (L->length);
}
// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
int index(List L)
{
    return (L->index);
}
// Returns front element. Pre: length()>0
int front(List L)
{
    if( L==NULL )
    {
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
    }
    if( length(L) <= 0)
    {
        printf("List Error: calling front() on an empty List\n");
        exit(1);
    }
    return(L->front->data);
}
// Returns back element. Pre: length()>0
int back(List L)
{
    if( L==NULL )
    {
        printf("List Error: calling back() on NULL List reference\n");
        exit(1);
    }
    if( length(L) == 0)
    {
        printf("List Error: calling back() on an empty List\n");
        exit(1);
    }
    return(L->back->data);


}
// Returns cursor element. Pre: length()>0, index()>=0
int get(List L)
{
    if( L==NULL )
    {
        printf("List Error: calling get() on NULL List reference\n");
        exit(1);
    }
    if( length(L) <= 0 || index(L) < 0)
    {
        printf("List Error: calling get() on an empty List\n");
        exit(1);
    }
    return(L->cursor->data);
}
// Returns equal if this List and L are the same integer
// sequence. The cursor is ignored in both lists.
int equals(List A, List B)
{
    int eq = 0;
    Node N = NULL;
    Node M = NULL;

    if( A==NULL || B==NULL )
    {
        printf("List Error: calling equals() on NULL List reference\n");
        exit(1);
    }

    eq = ( A->length == B->length );
    N = A->front;
    M = B->front;
    while( eq && N!=NULL)
    {
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}
// Manipulation procedures ----------------------------------------------------
// Manipulation procedures ----------------------------------------------------
// Resets this List to its original empty state.
void clear(List L)
{

    if( L==NULL )
    {
        printf("List Error: calling clear() on NULL List reference\n");
        exit(1);
    }

    if(length(L)==0)
    {
        printf("List Error: calling clear on an empty L\n");
        exit(1);
    }
    while(length(L) > 0)
    {
        deleteFront(L);
    }
}
// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L)
{
    if(L->length > 0)
    {
        L->cursor = L->front;
        L->index = 0;
    }
}
// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L)
{
    if(L->length > 0)
    {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L)
{
    if(L->cursor != NULL)
    {
        if(L->cursor != L->front)
        {
            L->cursor = L->cursor->previous;
        }
        else
        {
            L->cursor = NULL;
            L->index = -1;
        }
    }
}
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L)
{
    if (L->cursor != NULL)
    {
        if (L->cursor != L->back)
        {
            L->cursor = L->cursor->next;
            L->index++;
        }
        else
        {
            L->cursor = NULL;
            L->index = -1;
        }
    }
}
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data)
{
    Node N = newNode(data);
    if(length(L) == 0)
    {
        L->front = L->back = L->cursor = N;
        L->length = 1;
        L->index = 0;
    }
    else
    {
        N->next = L->front;
        L->front->previous = N;
        L->front = L->cursor = N;
        L->length++;
        L->index = 0;
    }
}
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data)
{
    Node N = newNode(data);
    if (length(L) == 0)
    {
        L->front = L->back = L->cursor = N;
        L->length = 1;
        L->index = 0;
    }
    else
    {
        L->back->next = N;
        N->previous = L->back;
        L->back = L->cursor = N;
        L->length++;
        L->index = L->length - 1;
    }

}
// Insert new element before cursor.
// Pre: length()>0,index()>=0
void insertBefore(List L, int data)
{
    if (length(L) > 0 && index(L) >= 0)
    {
        Node N = newNode(data);
        if (index(L) != 0)
        {
            L->cursor->previous->next = N;
            N->previous = L->cursor->previous;
            N->next = L->cursor;
            L->cursor->previous = N;
        }
        else
        {
            N->next = L->front;
            L->front->previous = N;
            L->front = N;
        }

        L->cursor = N;
        L->length++;
    }
    else
    {
        printf("List Error: calling insertBefore() on an empty Queue\n");
        exit(1);
    }
}
// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data)
{
    if (length > 0 && index >= 0)
    {
        Node N = newNode(data);
        if (index(L) != L->length - 1)
        {
            L->cursor->next->previous = N;
            N->previous = L->cursor;
            N->next = L->cursor->next;
            L->cursor->next = N;
        }
        else
        {
            L->back->next = N;
            N->previous = L->back;
            L->back = N;
        }

        L->cursor = N;
        L->length++;
        L->index++;
    }
    else
    {
        printf("List Error: calling insertAfter() on an empty List\n");
        exit(1);
    }
}

// Deletes the front element. Pre: length()>0
void deleteFront(List L)
{
    Node N = NULL;

    if( L==NULL )
    {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(1);
    }
    if( length(L) ==0 )
    {
        printf("List Error: calling Dequeue on an empty List\n");
        exit(1);
    }
    N = L->front;
    if( length(L)>1 )
    {
        L->front = L->front->next;
        L->front->previous = NULL;
    }
    else
    {
        L->front = L->back = L->cursor = NULL;
    }
    L->length--;
    freeNode(&N);
}
// Deletes the back element. Pre: length()>0
void deleteBack(List L)
{
    Node N = NULL;

    if( L == NULL )
    {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }
    if( length(L) == 0)
    {
        printf("List Error: calling deleteBack on an empty List\n");
        exit(1);
    }
    N = L->back;
    if( length(L)>1 )
    {
        L->back = L->back->previous;
        L->back->next = NULL;
    }
    else
    {
        L->front = L->back = L->cursor = NULL;
    }
    L->length--;
    freeNode(&N);
}
// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L)
{
    if (length(L) > 0 && index(L) >= 0)
    {
        Node cursor = L->cursor;
        L->cursor->previous->next = L->cursor->next;
        L->cursor->next->previous = L->cursor->previous;
        freeNode(&cursor);
        L->length--;
        L->cursor = NULL;
        L->index = -1;
    }
    else
    {
        printf("List Error: calling delete on an empty List\n");
        exit(1);
    }
}

// Other operations -----------------------------------------------------------
//Recieves inputs from List L and output it into a different file
void printList(FILE* out, List L)
{
    Node N = NULL;

    if( L==NULL )
    {
        printf("Queue Error: calling printList() on NULL List reference\n");
        exit(1);
    }

    for(N = L->front; N != NULL; N = N->next)
    {
        fprintf(out,"%d ", N->data );
    }
}
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L)
{
    List l = newList();
    L->cursor = L->front;
    while (L->cursor != NULL)
    {
        append(l, L->cursor->data);
        L->cursor = L->cursor->next;
    }
    return l;
}



