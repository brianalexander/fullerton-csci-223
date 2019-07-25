// ============================================================================
// File: sortedll.h (Spring 2019)
// ============================================================================

#ifndef     SORTEDLL_H
#define     SORTEDLL_H

// defined constants
#define BUFLEN                  256
#define FALSE                   0
#define TRUE                    1


// structure declarations
typedef struct  LNode
{
    int                 value;
    struct  LNode      *next;

} LNode;


// function prototypes
LNode*  AddItem(LNode  *headPtr, int  newItem);
int     DisplayList(LNode  *nodePtr);
void    DisplayMenu(void);
int     ReleaseMemory(LNode  *nodePtr);
LNode*  RemoveItem(LNode  *headPtr, int  target);

#endif  // SORTEDLL_H
