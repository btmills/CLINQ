#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct node;

struct node* new_node();
struct node* node_ctor(struct node* this, void* contents);
void node_dtor(struct node* this);
void ll_clear(struct node* head, void (*fn)(void*));
struct node* ll_tail(struct node* head);
struct node* ll_prev(struct node* head, void* contents);
struct node* ll_remove(struct node* head, void* contents);
void ll_add(struct node* *head, void* contents);
unsigned int ll_length(struct node* head);

#endif /* LINKED_LIST_H */