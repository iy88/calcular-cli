#ifndef MAP_H
#define MAP_H
#include <stdio.h>
#include <stdlib.h>
#define MAX_TABLE_LENGTH 50
#include <string.h>
typedef struct m_n {
	char* key;
	void* value;
	struct m_n* next;
} map_node;

typedef struct {
	unsigned long long size;
	map_node** buckets;
} hashMap;

typedef map_node* map_node_ptr;

typedef hashMap* hashMapPtr;

int hash(char* key);

hashMapPtr createHashMap();

int mapSet(hashMapPtr map, char* key, void* value, int size);

void* mapGet(hashMapPtr map, char* key);

int mapDelete(hashMapPtr map, char* key);

void mapClean(hashMapPtr map);

int mapHas(hashMapPtr map, char* key);

void mapDestory(hashMapPtr);

#endif