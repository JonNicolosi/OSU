#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != NULL && list != 0);
	list->size = 0;
	list->sentinel = (struct Link *)malloc(sizeof(struct Link));
	assert(list->sentinel != 0);
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE val)
{
	struct Link* newLink = (struct Link *)(malloc(sizeof(struct Link)));
	assert(newLink != 0);
	newLink->value = val;
	return(newLink);
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE v)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(link != 0);

	struct Link* newLink = createLink(v);

	newLink->prev = link;
	newLink->next = link->next;

	link->next->prev = newLink;
	link->next = newLink;

	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// FIXME: you must write this
	assert(list != NULL && list != 0);
	assert(link != 0);
	assert(list->size != 0);
	link->prev->next = link->next;
	link->next->prev = link->prev;
	printf("\n\n");
	free(link);
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != NULL && !circularListIsEmpty(list));
	assert(list->size != 0);
	while(list->size > 0)
		circularListRemoveFront(list);
	free(list->sentinel);
	list->sentinel = 0;
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE val)
{
	// FIXME: you must write this
	assert(list != 0);

	addLinkAfter(list, list->sentinel, val);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE val)
{
	// FIXME: you must write this
	assert(list != 0);

	addLinkAfter(list, list->sentinel->prev, val);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(list->size > 0);
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(list->size > 0);
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(list->size > 0);

	removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(list->size > 0);

  	removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);

	if(list->size == 0)
		return 1;
	else
		return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(list->size > 0);

	struct Link* curSent = list->sentinel->next;

	while(curSent != list->sentinel)
	{
		printf("%g ", curSent->value);
		curSent = curSent->next;
	}

	printf("\n");
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != NULL && list != 0);
	assert(!circularListIsEmpty(list));
	struct Link* idx = list->sentinel->next;
	struct Link* temp;
	list->sentinel->prev = idx;
	printf("reversing deque\n");
	do{
		temp = idx->next;
		if(temp->next == list->sentinel){
			list->sentinel->next = temp;
		}
		idx->next = idx->prev;
		idx->prev = temp;
		idx = temp;
	} while(idx != list->sentinel);

}
