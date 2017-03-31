/*
 * CS 261 Assignment 5
 * Name: Jonathan Nicolosi
 * Date: 05/24/2016
 */

#include "dynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define TESTING

#ifndef TESTING
static void adjustHeap(DynamicArray* heap, int last, int position, compareFunction compare);
static void buildHeap(DynamicArray* heap, compareFunction compare);
#endif

struct DynamicArray
{
    TYPE* data;
    int size;
    int capacity;
};

// --- Dynamic array ---

static void setCapacity(DynamicArray* array, int capacity)
{
    TYPE* data = malloc(sizeof(TYPE) * capacity);
    int i;
    for (i = 0; i < array->size; i++)
    {
        data[i] = array->data[i];
    }
    free(array->data);
    array->data = data;
    array->capacity = capacity;
}

static void init(DynamicArray* array, int capacity)
{
    assert(capacity > 0);
    array->data = NULL;
    array->size = 0;
    setCapacity(array, capacity);
}

DynamicArray* dyNew(int capacity)
{
    DynamicArray* array = malloc(sizeof(DynamicArray));
    init(array, capacity);
    return array;
}

void dyDelete(DynamicArray* array)
{
    free(array->data);
    free(array);
}

void dyAdd(DynamicArray* array, TYPE value)
{
    if (array->size >= array->capacity)
    {
        setCapacity(array, 2 * array->capacity);
    }
    array->data[array->size] = value;
    array->size++;
}

void dyAddAt(DynamicArray* array, TYPE value, int position)
{
    assert(position <= array->size);
    dyAdd(array, value);
    int i;
    for (i = array->size - 1; i > position; i--)
    {
        dySwap(array, i, i - 1);
    }
}

void dyPut(DynamicArray* array, TYPE value, int position)
{
    assert(position < array->size);
    array->data[position] = value;
}

void dyRemoveAt(DynamicArray* array, int position)
{
    assert(position < array->size);
    int i;
    for (i = position; i < array->size - 1; i++)
    {
        array->data[i] = array->data[i + 1];
    }
    array->size--;
}

TYPE dyGet(DynamicArray* array, int position)
{
    assert(position < array->size);
    return array->data[position];
}

int dySize(DynamicArray* array)
{
    return array->size;
}

void dySwap(DynamicArray* array, int position1, int position2)
{
    assert(position1 < array->size);
    assert(position2 < array->size);
    TYPE temp = array->data[position1];
    array->data[position1] = array->data[position2];
    array->data[position2] = temp;
}

// --- Stack ---

void dyStackPush(DynamicArray* stack, TYPE value)
{
    dyAdd(stack, value);
}

void dyStackPop(DynamicArray* stack)
{
    dyRemoveAt(stack, stack->size - 1);
}

TYPE dyStackTop(DynamicArray* stack)
{
    return dyGet(stack, stack->size - 1);
}

int dyStackIsEmpty(DynamicArray* stack)
{
    return stack->size == 0;
}

// --- Bag ---

static int findFirst(DynamicArray* array, TYPE value, compareFunction taskCompare)
{
    int i;
    for (i = 0; i < array->size; i++)
    {
        if (taskCompare(value, array->data[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

void dyBagAdd(DynamicArray* bag, TYPE value)
{
    dyAdd(bag, value);
}

void dyBagRemove(DynamicArray* bag, TYPE value, compareFunction taskCompare)
{
    int position = findFirst(bag, value, taskCompare);
    if (position != -1)
    {
        dyRemoveAt(bag, position);
    }
}

int dyBagContains(DynamicArray* bag, TYPE value, compareFunction taskCompare)
{
    return findFirst(bag, value, taskCompare) != -1;
}

// --- Ordered bag ---

static int binarySearch(DynamicArray* array, TYPE value, compareFunction taskCompare)
{
    int low = 0;
    int high = array->size - 1;
    while (low <= high)
    {
        int middle = (low + high) / 2;
        if (taskCompare(value, array->data[middle]) < 0)
        {
            high = middle - 1;
        }
        else if (taskCompare(value, array->data[middle]) > 0)
        {
            low = middle + 1;
        }
        else
        {
            return middle;
        }
    }
    return low;
}

void dyOrderedAdd(DynamicArray* bag, TYPE value, compareFunction taskCompare)
{
    int position = binarySearch(bag, value, taskCompare);
    dyAddAt(bag,value, position);
}

void dyOrderedRemove(DynamicArray* bag, TYPE value, compareFunction taskCompare)
{
    int position = binarySearch(bag, value, taskCompare);
    if (taskCompare(value, bag->data[position]) == 0)
    {
        dyRemoveAt(bag, position);
    }
}

int dyOrderedContains(DynamicArray* bag, TYPE value, compareFunction taskCompare)
{
    int position = binarySearch(bag, value, taskCompare);
    return taskCompare(value, dyGet(bag, position)) == 0;
}

// --- Heap ---

/**
 * Adjusts heap to maintain the heap property.
 * @param heap
 * @param last  index to adjust up to.
 * @param position  index where adjustment starts.
 * @param compare  pointer to compare function.
 */



int _smallerIndexHeap(DynamicArray *heap, int i, int j, compareFunction taskCompare)
{
	if(i < heap->size && j < heap->size) {
		if(taskCompare(heap->data[i], heap->data[j]) == -1) {
			return(i);
		}
		else {
			return(j);
		}
	}
	else{
		printf("Error in size of parameters i and j\nReturning 0\n");
		return 0;
	}
}

void adjustHeap(DynamicArray* heap, int last, int position, compareFunction taskCompare)
{
    // FIXME: implement
    int leftChild = 2 * position + 1;
	int rightChild = 2 * position + 2;
	int index;

	if (rightChild < last){
		index = _smallerIndexHeap(heap, leftChild, rightChild, taskCompare);

//		printf("\n***2 Children***\n");
//		printf("pos: 		%d\n", position);
//		printf("leftChild: 	%d\n", leftChild);
//		printf("rightChild: %d\n", rightChild);
//		printf("index: 		%d\n", index);

		if( _smallerIndexHeap(heap, index, position, taskCompare) == index){
			//printf("Child at index is smaller than pos\n");
			dySwap(heap, index, position);
			adjustHeap(heap, last, index, taskCompare);
		}
	}

	else if(leftChild < last){
/*
		printf("\n***1 Child***\n");
		printf("pos: 		%d\n", pos);
		printf("leftChild: 	%d\n", leftChild);
*/
		if( _smallerIndexHeap(heap, leftChild, position, taskCompare) == leftChild){
			printf("Left Child is smaller than pos\n");
			dySwap(heap, leftChild, position);
			adjustHeap(heap, last, leftChild, taskCompare);
		}
	}
	else{
		return;
	}

}

/**
 * Builds a valid heap from an arbitrary array.
 * @param heap  array with elements in any order.
 * @param compare  pointer to compare function.
 */
void buildHeap(DynamicArray* heap, compareFunction taskCompare)
{
    // FIXME: implement
    int firstLeaf = (heap->size / 2) - 1;
    int i;
	for (i = firstLeaf; i >= 0; i--)
		adjustHeap(heap, heap->size, i, taskCompare);
}

/**
 * Adds an element to the heap.
 * @param heap
 * @param value  value to be added to heap.
 * @param compare  pointer to compare function.
 */
void dyHeapAdd(DynamicArray* heap, TYPE value, compareFunction taskCompare)
{
    // FIXME: implement

    int index;
	int parent;
	if(heap != NULL) {
		if(heap->size == heap->capacity) {
			setCapacity(heap, 2 * heap->capacity);
		}
		heap->data[heap->size] = value;
		heap->size++;
		index = dySize(heap) - 1;

		while(index != 0){
			parent = (index-1)/2;
			printf("index: %d || parent: %d || size: %d\n", index, parent, heap->size);
			if( _smallerIndexHeap(heap, index, parent, taskCompare) == index){
				dySwap(heap, parent, index);
				index = parent; //update index
			}
			else{
				return;
			}
		}
	}
}

/**
 * Removes the first element, which has the min priority, form the heap.
 * @param heap
 * @param compare  pointer to the compare function.
 */
void dyHeapRemoveMin(DynamicArray* heap, compareFunction taskCompare)
{
    // FIXME: implement
    int last = heap->size - 1;
	heap->data[0] = heap->data[last];
	dyRemoveAt(heap, last);
	adjustHeap(heap, heap->size, 0, taskCompare);


}

/**
 * Returns the first element, which has the min priority, from the heap.
 * @param heap
 * @return  Element at the top of the heap.
 */
TYPE dyHeapGetMin(DynamicArray* heap)
{
    // FIXME: implement
    return dyGet(heap, 0);
}

/**
 * Sorts arbitrary array in-place.
 * @param heap  array with elements in arbitrary order.
 * @param compare  pointer to the compare function.
 */
void dyHeapSort(DynamicArray* heap, compareFunction taskCompare)
{
    // FIXME: implement
    buildHeap(heap, taskCompare);

	int last = heap->size - 1;

	while (last > 0)
	{
		dySwap(heap, 0, last);
		adjustHeap(heap, last, 0, taskCompare);
		last--;
	}
}

// --- Iterator ---

DynamicArrayIterator* dyIteratorNew(DynamicArray* array)
{
    DynamicArrayIterator* iterator = malloc(sizeof(DynamicArrayIterator));
    iterator->array = array;
    iterator->current = 0;
    return iterator;
}

void dyIteratorDelete(DynamicArrayIterator* iterator)
{
    free(iterator);
}

int dyIteratorHasNext(DynamicArrayIterator* iterator)
{
    return iterator->current < iterator->array->size;
}

TYPE dyIteratorNext(DynamicArrayIterator* iterator)
{
    TYPE value = dyGet(iterator->array, iterator->current);
    iterator->current++;
    return value;
}

void dyIteratorRemove(DynamicArrayIterator* iterator)
{
    iterator->current--;
    dyRemoveAt(iterator->array, iterator->current);
}

// --- Utility ---

void dyPrint(DynamicArray* array, printFunction print)
{
    printf("\nsize: %d\ncapacity: %d\n[\n", array->size, array->capacity);
    int i;
    for (i = 0; i < array->size; i++)
    {
        printf("%d : ", i);
        print(array->data[i]);
        printf("\n");
    }
    printf("]\n");
}

void dyCopy(DynamicArray* source, DynamicArray* destination)
{
    free(destination->data);
    init(destination, source->capacity);
    int i;
    for (i = 0; i < source->size; i++)
    {
        destination->data[i] = source->data[i];
    }
    destination->size = source->size;
}
