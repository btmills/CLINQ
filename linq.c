#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "linq.h"

/*
 * Create a new linked list of nodes containing only the nodes of a first linked
 * list whose contents satisfy a certain condition.
 * Modeled after C#/LINQ's <IEnumerable>.Where(...)
 *
 * head: First node of a linked list
 * fn: Function accepting three arguments (the index of the node in the list, a
 *	   pointer to the contents of the node, and a pointer to the search term to
 *	   compare to) and returns true whenever the contents match the search term
 * term: A pointer to the search term to be passed to fn
 *
 * returns: A new linked list containing only those elements of head for which
 *			fn returned true
 */
struct node* ll_where(struct node* head, bool (*fn)(unsigned int, void*, void*), void* term)
{
	unsigned int i;
	struct node* ptr = NULL;
	struct node* result = NULL;

	// Iterate over each element of head
	for(i = 0, ptr = head;
		ptr != NULL;
		i++, ptr = ptr->next)
		if(fn(i, ptr->record, term)) // If the value satisifes the condition
			ll_add(&result, ptr->record); // Add the value to the new list

	return result;
}

/*
 * Aggregate an operation over an entire list with an initial value and an
 * accumulator.
 * Modeled after C#/LINQ's <IEnumerable>.Aggregate(...)
 *
 * head: First node of a linked list
 * fn: Linked list predicate function accepting two arguments (an accumulator
 *	   and an individual value to add to the accumulator) that modifies the
 *	   accumulated value to include the value
 * accum: Pointer to an accumulator. May contain an initial value.
 */
void ll_aggregate(struct node* head, void (*fn)(void* accum, void* record), void* accum)
{
	struct node* ptr = head;
	for(ptr = head; ptr != NULL; ptr = ptr->next)
		fn(accum, ptr->record);
}

/*
 * Get the contents of the first and only node in a linked list. Errors if the
 * list does not have exactly one node.
 *
 * head: First element of a linked list
 *
 * returns: Contents of the first and only element. NULL if length != 1.
 */
void* ll_single(struct node* head)
{
	if(ll_length(head) != 1)
		return NULL;
	return head->record;
}

/*
 * Perform an operation for each record in a linked list.
 *
 * head: First element of a linked list
 * fn: Function accepting two arguments (index of the element in the list and
 *	   a pointer to the value)
 */
void ll_each(struct node* head, void (*fn)(unsigned int, void*))
{
	unsigned int i;
	struct node* ptr = head;
	for(i = 0; ptr != NULL; ptr = ptr->next, i++)
		fn(i, ptr->record);
}