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

### Each

	void ll_each(struct node* head, void (*fn)(unsigned int, void*));

Perform an operation for each record in a linked list.

### Single

	void* ll_single(struct node* head);

Get the record stored in the first and only node of a linked list. Errors (returns NULL) if the list does not have exactly one node.

### Where

	struct node* ll_where(struct node* head, bool (*fn)(unsigned int, void*, void*), void* term);

Create a new linked list of nodes containing only the nodes of a first linked list whose contents satisfy a certain condition.