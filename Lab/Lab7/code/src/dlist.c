#include <stdlib.h>
#include <stdio.h>

#include "dnode.h"
#include "dlist.h"

struct dlist *
dlist_create() {
	return calloc(1, sizeof(struct dlist));
}

void 
dlist_destroy(struct dlist *l) {
	struct dnode *p = l->front;

	do {
		l->front = l->front->next;
		free(p->data);
		free(p);
		p = l->front;
	} while (l->front != NULL);

	l->front = l->back = NULL;
	l->counter = 0;
}


void 
dlist_obliterate(struct dlist *l) {
	dlist_destroy(l);
	free(l);
}

void 
dlist_add_front(struct dlist *l, void *ptr) {
	struct dnode *n = dnode_create();
	n->data = ptr;

	if (0 == l->counter) {
		l->front = l->back = n;	
		l->counter = 1;
	} else {
		n->next = l->front;
		l->front->prev = n;
		l->front = n;
		(l->counter)++;
	}

#ifdef DEBUG
	printf("counter= %d, %s\n", l->counter, (char *) ptr);
	printf("front= %s\n", (char *) l->front->data);
	printf("back= %s\n\n", (char *) l->back->data);
#endif /* DEBUG */
}

void 
dlist_add_back(struct dlist *l, struct dnode *n) {
  //struct dnode *n = dnode_create();
  //n->data = ptr;

	if (0 == l->counter) {
		l->front = l->back = n;	
		l->counter = 1;
	} else {
		n->prev = l->back;
		l->back->next = n;
		l->back = n;
		(l->counter)++;
	}

#ifdef DEBUG
	printf("counter= %d, %s\n", l->counter, (char *) ptr);
	printf("front= %s\n", (char *) l->front->data);
	printf("back= %s\n\n", (char *) l->back->data);
#endif /* DEBUG */
}

void *
dlist_remove_front(struct dlist *l) {
	struct dnode *n = l->front;
	void* ptr = n->data;

	if (1 == l->counter) {
		l->front = l->back = NULL;
	} else {
		l->front = l->front->next;
		l->front->prev = NULL;
	}

	(l->counter)--;
	free(n);
	return ptr;
}

void *
dlist_remove_back(struct dlist *l) {
	struct dnode *n = l->back;
	void *ptr = n->data;

	if (1 == l->counter) {
		l->front = l->back = NULL;
	} else {
		l->back = l->back->prev;
		l->back->next = NULL;
	}

	(l->counter)--;
	free(n);
	return ptr;
}

void *
dlist_find_remove(struct dlist *l, void *ptr) {
	struct dnode *n = l->front;
	void *ret_ptr = NULL;

	while ((n != NULL) && (n->data != ptr)) {
	  n = n->next;
	}

	if (n != NULL) {
	  if (l->front == n) {
	    return dlist_remove_front(l);
	  } else if (l->back == n) {
	    return dlist_remove_back(l);
	  } else {
	    if (1 == l->counter) {
	      l->front = l->back = NULL;
	    } else {
	      n->prev->next = n->next;
	      n->next->prev = n->prev;
	    }
	    (l->counter)--;
	  }
	  
	  ret_ptr = n->data;
	  free(n);
	}
	
	return ret_ptr;
}

uint32_t 
dlist_num_elems(struct dlist *l) {
	return l->counter;
}

struct dnode
*dlist_iter_begin(struct dlist *l) {
  struct dnode *ret_val = dnode_create();

	l->iter = l->front;
	if (l->iter != NULL) {
		ret_val = l->iter; 
	}

	return ret_val;
}

struct dnode
*dlist_iter_next(struct dlist *l) {
  struct dnode *ret_val = dnode_create();

	if (l->iter != NULL) {
		l->iter = l->iter->next;
		if (l->iter != NULL) {
		  ret_val = l->iter;//return whole node instead
		}
	}

	return ret_val;
}

bool 
dlist_iter_has_next(struct dlist *l) {
	bool ret_val = false;

	if (l->iter != NULL) {
		ret_val = (l->iter->next != NULL);
	}

#ifdef DEBUG
	if (ret_val) {
		printf("dlist_has_next: current is %s\n", (char *) l->iter->data);
		printf("dlist_has_next: returning %d\n\n", ret_val);
	}
#endif /* DEBUG */

	return ret_val;
}


void *
dlist_iter_end(struct dlist *l) {
	void *ret_val = NULL;

	l->iter = l->back;
	if (l->iter != NULL) {
		ret_val = l->iter->data;
	}

	return ret_val;
}

void *
dlist_iter_prev(struct dlist *l) {
	void *ret_val = NULL;

	if (l->iter != NULL) {
		l->iter = l->iter->prev;
		if (l->iter != NULL) {
			ret_val = l->iter->data;
		}
	}

	return ret_val;
}

bool 
dlist_iter_has_prev(struct dlist *l) {
	bool ret_val = false;

	if (l->iter != NULL) {
		ret_val = (l->iter->prev != NULL);
	}

	return ret_val;
}

