// Corey Noel
// For CS 449 
// Project 3

#include <stdlib.h>

typedef struct node {
	int isFull;
	int size;
	struct node *nxt;
	struct node *prv;
} Node;

Node *fst;
Node *lst;

void *my_bestfit_malloc(int size) {
	int fullSize;
	Node *cur;
	Node *bst;

	if (size <= 0)
		return NULL;

	fullSize = sizeof(Node) + size;					// fullsize = size of node + size of space

	if (fst == NULL) {								// if we have no nodes
		fst = (Node *)sbrk(fullSize);				// allocate more space
		if ((int)fst == -1) 						// sbrk returns -1 when there's no space
			return NULL;

		lst = fst;									// create our node
		fst->isFull = 1;
		fst->size = size;
		fst->nxt = NULL;
		fst->prv = NULL;

		return fst + sizeof(Node);					// return it
	}

	cur = fst;
	bst = NULL;

	while (cur != NULL) {							// bestfit algorithm
		if (!(cur->isFull)) {
			if (cur->size == size) {				// perfect fit
				cur->isFull = 1;
				return cur + sizeof(Node);
			} else if (cur->size > size) {	
				if (bst == NULL || bst->size > cur->size)		// new best min node
					bst = cur;
			}
		}
		cur = cur->nxt;
	}

	if (bst == NULL) {								// if no node was big enough
		Node *result = (Node *)sbrk(fullSize);		// allocate more space
		if ((int)result == -1)						// sbrk returns -1 when there's no space
			return NULL;							

		result->isFull = 1;							// create our node
		result->size = size;						
		result->nxt = NULL;
		result->prv = lst;
		lst->nxt = result;
		lst = result;

		return result + sizeof(Node);				// return it
	}

	bst->isFull = 1;								// otherwise, we found a non-perfect node

	cur = bst + fullSize;
	cur->isFull = 0;								// split and create it
	cur->size = bst->size - fullSize;				// (cur is used as an empty temp node)
	cur->nxt = bst->nxt;							// I don't check if lst needs to be updated
	cur->prv = bst;									// because if the lst is empty
	bst->nxt = cur;									// I always remove it
	bst->size = size;								// We thus know that the node we found is not lst

	return bst + sizeof(Node);						// return our node
}

void my_free(void *ptr) {
	Node *nd = (Node*) ptr - sizeof(Node);
	Node *previous = nd->prv;
	Node *next = nd->nxt;
	Node *head = nd;
	nd->isFull = 0;

	int prevEmpty = previous != NULL && !previous->isFull;		// is the previous node empty
	int nextEmpty = next != NULL && !next->isFull;				// is the next node empty

	if (prevEmpty && !nextEmpty) {								// if just previous...
		previous->nxt = next;									
		if (next != NULL)
			next->prv = previous;
		previous->size += nd->size + sizeof(Node);
		if (previous->nxt == NULL)
			lst = previous;

		head = previous;


	} else if (nextEmpty && !prevEmpty) {						// if just next...
		nd->nxt = next->nxt;
		if (next->nxt != NULL) 
			next->nxt->prv = nd;
		nd->size += next->size + sizeof(Node);
		if (nd->nxt == NULL)
			lst = nd;

		head == nd;

	} else if (nextEmpty && prevEmpty) {						// if both are empty...
		previous->nxt = next->nxt;
		if (previous->nxt != NULL)
			previous->nxt->prv = previous;
		previous->size += nd->size + next->size + 2 * sizeof(Node);

		if (previous->nxt == NULL) 
			lst = previous;

		head == previous;
	}

	if (head->nxt == NULL) 										// if we end in an empty block
		sbrk(0 - (head->size + sizeof(Node)));					// deallocate that space from the heap
}