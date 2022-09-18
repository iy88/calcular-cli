#include "anyTypeHashMap.h"

int hash(char* key) {
	int hash = 0;
	int i = 0;
	while (key[i] != 0) {
		hash += key[i];
		i++;
	}
	return hash % MAX_TABLE_LENGTH;
}

void copy(void* des, void* src, unsigned long long size) {
	char* d = des;
	char* s = src;
	while (size-- > 0) {
		*d++ = *s++;
	}
}

unsigned long long lenStr(char* s) {
	unsigned long long len = 0;
	while (s[len] != '\0') {
		len++;
	}
	return len;
}

int isEqual(char* s1, char* s2) {
	int i = 0;
	while (s1[i] != '\0') {
		if (s1[i] != s2[i]) {
			return 0;
		}
		i++;
	}
	if (s1[i] != s2[i]) {
		return 0;
	}
	else {
		return 1;
	}
}

hashMapPtr createHashMap() {
	hashMapPtr map = (hashMapPtr)malloc(sizeof(hashMap));
	if (map == NULL) {
		return NULL;
	}
	map->size = 0;
	map->buckets = (map_node**)calloc(MAX_TABLE_LENGTH, sizeof(map_node_ptr));
	return map;
}

int mapSet(hashMapPtr map, char* key, void* value, int size) {
	int idx = hash(key);
	if (map->buckets[idx] == 0) {
		map_node_ptr node = (map_node_ptr)malloc(sizeof(map_node));
		if (node != NULL) {
			node->key = (char*)malloc((lenStr(key) + 1) * sizeof(char));
			if (node->key != NULL) {
				copy(node->key, key, (lenStr(key) + 1) * sizeof(char));
				node->value = malloc(size);
				if (node->value != NULL) {
					copy(node->value, value, size);
				}
				else {
					printf("no more memory for use!\n");
					exit(1);
				}
				node->next = NULL;
				map->buckets[idx] = node;
				map->size++;
				return 1;
			}
			else {
				printf("no more memory for use!\n");
				exit(1);
			}
		}
		else {
			printf("no more memory for use!\n");
			exit(1);
		}
	}
	else {
		map_node_ptr current = map->buckets[idx];
		if (isEqual(current->key, key) == 1) {
			free(current->value);
			current->value = malloc(size);
			if (current->value != NULL) {
				copy(current->value, value, size);
			}
			else {
				printf("no more memory for use!\n");
				exit(1);
			}
			return 2;
		}
		else {
			while (current->next != NULL) {
				current = current->next;
				if (isEqual(current->key, key) == 1) {
					free(current->value);
					current->value = malloc(size);
					if (current->value != NULL) {
						copy(current->value, value, size);
					}
					else {
						printf("no more memory for use!\n");
						exit(1);
					}
					return 2;
				}
			}
		}
		map_node_ptr node = (map_node_ptr)malloc(sizeof(map_node));
		if (node != NULL) {
			node->key = (char*)malloc((lenStr(key) + 1) * sizeof(char));
			if (node->key != NULL) {
				copy(node->key, key, (lenStr(key) + 1) * sizeof(char));
				node->value = malloc(size);
				if (node->value != NULL) {
					copy(node->value, value, size);
				}
				else {
					printf("no more memory for use!\n");
					exit(1);
				}
				node->next = NULL;
				current->next = node;
				return 1;
			}
			else {
				printf("no more memory for use!\n");
				exit(1);
			}
		}
		else {
			printf("no more memory for use!\n");
			exit(1);
		}

	}
}


void* mapGet(hashMapPtr map, char* key) {
	int idx = hash(key);
	if (map->buckets[idx] != 0) {
		map_node_ptr current = map->buckets[idx];
		while (isEqual(current->key, key) != 1) {
			if (current->next == NULL) {
				return NULL;
			}
			else {
				current = current->next;
			}
		}
		return current->value;
	}
	else {
		return NULL;
	}
}

int mapDelete(hashMapPtr map, char* key) {
	int idx = hash(key);
	if (map->buckets[idx] != 0) {
		map_node_ptr current = map->buckets[idx];
		if (isEqual(current->key, key) == 1) {
			if (current->next == NULL) {
				free(current->value);
				free(current->key);
				free(current);
				map->buckets[idx] = NULL;
				map->size--;
				return 1;
			}
			else {
				map_node_ptr tmp = current;
				map->buckets[idx] = current->next;
				free(tmp->value);
				free(tmp->key);
				free(tmp);
				map->size--;
				return 1;
			}
		}
		while (isEqual(current->next->key, key) != 1) {
			if (current->next->next == NULL) {
				return 0;
			}
			else {
				current = current->next;
			}
		}
		if (current->next->next) {
			map_node_ptr tmp = current->next;
			current->next = current->next->next;
			free(tmp->value);
			free(tmp->key);
			free(tmp);
			map->size--;
			return 1;
		}
		else {
			free(current->next->key);
			free(current->next->value);
			free(current->next);
			current->next = NULL;
			map->size--;
			return 1;
		}
	}
	else {
		return 0;
	}
}

void __map_cleanItem(map_node_ptr node) {
	if (node->next != NULL) {
		__map_cleanItem(node->next);
	}
	free(node->key);
	free(node->value);
	free(node);
}

void mapClean(hashMapPtr map) {
	for (int i = 0; i < MAX_TABLE_LENGTH; i++) {
		if (map->buckets[i] != NULL) {
			map_node_ptr current = map->buckets[i];
			__map_cleanItem(current);
			map->buckets[i] = NULL;
		}
	}
	map->size = 0;
}

int mapHas(hashMapPtr map, char* key) {
	int idx = hash(key);
	if (map->buckets[idx] != NULL) {
		map_node_ptr current = map->buckets[idx];
		if (isEqual(current->key, key) == 1) {
			return 1;
		}
		else {
			while (isEqual(current->key, key) != 1) {
				if (current->next == NULL) {
					return 0;
				}
				else {
					current = current->next;
				}
			}
			return 1;
		}
	}
	else {
		return 0;
	}
}

void mapDestory(hashMapPtr map) {
	free(map->buckets);
	free(map);
}

