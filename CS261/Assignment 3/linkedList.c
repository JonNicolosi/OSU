#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	// FIXME: you must write this
	assert(list != 0);

	list->frontSentinel = malloc(sizeof(struct Link));
	list->backSentinel = malloc(sizeof(struct Link));
	list->frontSentinel->next = list->backSentinel;
	list->frontSentinel->prev = 0;
	list->backSentinel->prev = list->frontSentinel;
	list->backSentinel->next = 0;

	list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE v)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(link != 0);

	struct Link *newLink = malloc(sizeof(struct Link));

	newLink->value = v;

	newLink->next = link;
	newLink->prev = link->prev;

	link->prev->next = newLink;
	link->prev = newLink;

	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(link != 0);

	link->prev->next = link->next;
	link->next->prev = link->prev;

	free(link);

	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE e)
{
	// FIXME: you must write this
	assert(list != 0);

	addLinkBefore(list, list->frontSentinel->next, e);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE e)
{
	// FIXME: you must write this
	assert(list != 0);

	addLinkBefore(list, list->backSentinel, e);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(list->size > 0);

	return(list->frontSentinel->next->value);
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(list->size > 0);

	return(list->backSentinel->prev->value);
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(list->size > 0);

	removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(list->size > 0);

	removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);

	if (list->size > 0)
		return 0;
	else
		return 1;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != 0);

	struct Link *curLink = list->frontSentinel;

	while(curLink != list->backSentinel)
	{
		curLink = curLink->next;
		printf("%d", curLink->value);
	}
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE v)
{
	// FIXME: you must write this
	assert(list != 0);

	linkedListAddFront(list, v);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE e)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(list->size > 0);


	struct Link *tmp = list->frontSentinel->next;
    int i;
	for (i = 0; i < list->size; i++)
	{
		if (tmp->value == e)
			return 1;

		else
			tmp = tmp->next;
	}

	return(0);
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE e)
{
	// FIXME: you must write this
	assert(list != 0);
	assert(list->size > 0);

	struct Link *tmp = list->frontSentinel->next;
    int i;
	for (i = 0; i < list->size; i++)
	{
		if (tmp->value == e)
			removeLink(list, tmp);

		else
			tmp = tmp->next;
	}
}

