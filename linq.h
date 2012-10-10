#ifndef LINQ_H
#define LINQ_H

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

struct node* ll_where(struct node* head, bool (*fn)(unsigned int, void*, void*), void* term);
void ll_aggregate(struct node* head, void (*fn)(void* accum, void* record), void* accum);
void* ll_single(struct node* head);
void ll_each(struct node* head, void (*fn)(unsigned int, void*));

#endif /* LINQ_H */