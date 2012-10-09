# CLINQ

This is a very basic proof-of-concept for adding LINQ-like list features to C. It started as part of another project, and I don't even know if it's practical for use elsewhere, but it's kind of cool.

## Operations

All of these are modeled after the equivalent C#/LINQ operation and operate on a linked list:

	struct node {
		struct node* next;
		void* record;
	};

### Aggregate

	void ll_aggregate(struct node* head, void (*fn)(void* accum, void* val), void* accum);

Aggregate an operation over an entire list with an initial value and an accumulator.

* head: Pointer to the first node in a linked list
* fn: Pointer to a function accepting two arguments (an accumulator and a record) that modifies the accumulated value to include the record's information
* accum: Pointer to an accumulator. May optionally be initialized with an initial value. Result is stored at accum.

### Each

	void ll_each(struct node* head, void (*fn)(unsigned int, void*));

Perform an operation for each record in a linked list.

* head: Pointer to the first node in a linked list
* fn: Pointer to a function accepting two arguments (index of the element in the list and a pointer to the record stored there)

### Single

	void* ll_single(struct node* head);

Get the record stored in the first and only node of a linked list. Errors (returns NULL) if the list does not have exactly one node.

* head: Pointer to the first node in a linked list
* returns: Pointer to the record stored in the first and only element of the list, or NULL if length is not exactly 1.

### Where

	struct node* ll_where(struct node* head, bool (*fn)(unsigned int, void*, void*), void* term);

Create a new linked list of nodes containing only the nodes of a first linked list whose contents satisfy a certain condition.

* head: Pointer to the first node in a linked list
* fn: Pointer to a function accepting three arguments (this index of the node in the list, a pointer to the record in the node, and a pointer to the search term to test against) that returns true whenever the record matches the search term
* term: Pointer to the search term to pass to fn
* returns: New linked list containing only those elements in the original for which fn returned true