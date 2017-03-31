/*
 * CS 261 Data Structures
 * Assignment 6
 * Name: Jonathan Nicolosi
 * Date: 05/29/2016
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#if HASH_FUNCTION == 1
    #define HASH hashFunction1
#else
    #define HASH hashFunction2
#endif

int hashFunction1(const char* key)
{
    int r = 0;
    int i;
    for (i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    int i;
    for (i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    int i;
    for (i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIXME: implement
    struct HashLink *curLink;
    struct HashLink *prevLink;
    int i;

    assert (map != NULL);

    /* traverse the buckets */
    for (i = 0; i < map->capacity; ++i) {
        /* get the link in the bucket */
        curLink = map->table[i];

        /* delete each link */
        while (curLink != NULL) {
            prevLink = curLink;
            curLink = curLink->next;
            free(prevLink);
        }
    }

    /* delete the array */
    free(map->table);

}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key. Returns NULL
 * if no link with that key is in the table.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIXME: implement
    int hashIndex;
    struct HashLink *curLink;
    assert (map != NULL);

    hashIndex = HASH(key) % map->capacity;
    if (hashIndex < 0)
        hashIndex += map->capacity;

    curLink = map->table[hashIndex];
    while (curLink) {
        if (strcmp(curLink->key, key) == 0)
            return &(curLink->value);

        curLink = curLink->next;
    }
    return NULL;


}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 *
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 *
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    // FIXME: implement
    struct HashMap *newHt;
    struct HashLink *curLink;
    int i;

    assert (map != NULL);
    assert(capacity > map->capacity);
    newHt = hashMapNew(capacity);
    assert (newHt != NULL);

    for (i = 0; i < map->capacity; ++i) {
        curLink = map->table[i];

        while (curLink != NULL) {
            hashMapPut(newHt, curLink->key, curLink->value);
            curLink = curLink->next;
        }
    }


    hashMapCleanUp(map);
    map->table = newHt->table;
    map->capacity = newHt->capacity;

}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // FIXME: implement


    int hashIndex;
    struct HashLink *newLink;

    assert(map != NULL);

    if (hashMapContainsKey(map, key))
        *hashMapGet(map, key) = value;
    else {
        hashIndex = HASH(key) % map->capacity;


        if (hashIndex < 0)
            hashIndex += map->capacity;

        newLink = malloc(sizeof(struct HashLink));
        assert(newLink);

        newLink->key = key;
        newLink->value = value;
        newLink->next = map->table[hashIndex];
        map->table[hashIndex] = newLink; /* add to bucket */
        ++(map->size);

        if ((map->size / (double) map->capacity) > 8.0)
            resizeTable(map, map->capacity * 2);
    }



}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
    int hashIndex;
    struct HashLink * LastLink;
    struct HashLink * CurrentLink;

    if(HASH_FUNCTION == 1)
        hashIndex = hashFunction1(key) % map->capacity;
    else
        hashIndex = hashFunction2(key) % map->capacity;


    /* Set pointer to head of linked list at hash index of table */
    CurrentLink = map->table[hashIndex];
    LastLink = CurrentLink;

    /* Set pointer to head of linked list at hash index of table */
    while(CurrentLink != 0){
        if(strcmp(key, CurrentLink->key) == 0){
            if(LastLink == CurrentLink){
                LastLink = CurrentLink->next;
                map->table[hashIndex] = LastLink;
            }
            else
                LastLink->next = CurrentLink->next;


            /* "Free"-ing the memory occupied by key and value before freeing hashLink */
            //free(currLink->key);    //Free char*
            CurrentLink->value = 0;

            /* Free hashLink and decrement hashLink counter */
            free(CurrentLink);

            /* Decrement hashLink counter */
            map->size--;

            /* Break from while loop */
            break;
        }
        CurrentLink = CurrentLink->next;
    }





}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIXME: implement
    assert(map != NULL);

    return hashMapGet(map, key) != NULL;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // FIXME: implement
    assert (map != NULL);
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // FIXME: implement
    assert (map != NULL);
    return map->capacity;

}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement
	int emptyCounter = 0;
	int i;

    for(i = 0; i < map->capacity; i++)
        if(map->table[i] == 0)
            emptyCounter++;

    return emptyCounter;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
	float loadRatio = 0.0;

    loadRatio = (float)map->size / (float)map->capacity;

	return loadRatio;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{   int i;
    for (i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}
