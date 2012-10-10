#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

/* *************************************
 * LINKED LIST
 * ************************************/

/*
 * Structure representing a node in a linked list
 * next: Pointer to the next node in the list
 * record: Contents of this node
 */
struct node {
	struct node* next;
	void* record;
};

/*
 * Allocate memory for a new node
 */
struct node* new_node()
{
	return malloc(sizeof(struct node));
}

/*
 * Construct a new node, given its contents
 *
 * this: The new node, already allocated
 * contents: The new value of the node
 */
struct node* node_ctor(struct node* this, void* contents)
{
	this->next = NULL;
	this->record = contents;
	return this; // Facilitate chaining
}

/*
 * Destruct a node by freeing its memory
 * NOTE: Does not destruct or free the node's contents
 */
void node_dtor(struct node* this)
{
	free(this);
}

/*
 * Clear a linked list and free all of its memory
 *
 * head: First element in a linked list
 * fn: Function accepting one argument (pointer to the value of a node) that
 *	   frees the memory used by the value
 */
void ll_clear(struct node* head, void (*fn)(void*))
{
	while(head != NULL) // While there are still nodes
	{
		struct node* removed = head;
		head = removed->next;
		fn(removed->record); // Get rid of the contents
		node_dtor(removed); // Destruct the node
	}
}

/*
 * Get the last node in a linked list
 *
 * head: The first element of the linked list
 *
 * returns: Last node in the linked list
 */
struct node* ll_tail(struct node* head)
{
	struct node* ptr = head;
	while(ptr->next)
		ptr = ptr->next;
	return ptr;
}

/*
 * Given the contents of a node, get the previous node
 * Contents cannot be in the first node of the list
 *
 * head: Linked list to search
 * contents: Contents of a node in the list
 */
struct node* ll_prev(struct node* head, void* contents)
{
	struct node* ptr = head;
	while(ptr->next != NULL &&
		!(ptr->next->record == contents))
		ptr = ptr->next;
	return ptr;
}

/*
 * Given the contents of a node in a linked list, remove that node
 *
 * head: First element of the linked list
 * contents: Value of the node to delete
 *
 * returns: New head of the linked list. Usually unmonified, but can change if
 * the head of the list is removed
 */
struct node* ll_remove(struct node* head, void* contents)
{
	struct node* removed;

	if(head->record == contents) // Check first if head matches
	{
		removed = head;
		head = removed->next; // Move head to new first node
		node_dtor(removed); // Destruct removed node
	}
	else
	{
		struct node* prev = ll_prev(head, contents); // Get the previous node
		if(prev != NULL) // Found contents in list
		{
			removed = prev->next;
			prev->next = (removed != NULL ? removed->next : NULL);
			node_dtor(removed); // Destruct removed node
		}
	}
	return head;
}

/*
 * Add an element to the end of a linked list.
 * A new node is automatically created to contain the value.
 *
 * head: The first element of the linked list
 * contents: The value to be stored in the new node
 */
void ll_add(struct node* *head, void* contents)
{
	struct node* next = node_ctor(new_node(), contents);
	if(*head == NULL) // Adding first
		*head = next;
	else
		ll_tail(*head)->next = next;
}

/*
 * Get the number of nodes in a linked list
 *
 * head: The first element of the linked list
 *
 * returns: The number of nodes in the list
 */
unsigned int ll_length(struct node* head)
{
	unsigned int result;
	struct node* ptr;
	for(result = 0, ptr = head;
		ptr != NULL;
		result++, ptr = ptr->next);
	return result;
}