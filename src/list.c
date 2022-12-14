#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>

#include "list.h"

struct SList *slist_append(struct SList **head, void *val) {
	if (!head)
		return NULL;

	struct SList *i, *l;

	i = calloc(1, sizeof(struct SList));
	i->val = val;

	if (*head) {
		for (l = *head; l->nex; l = l->nex);
		l->nex = i;
	} else {
		*head = i;
	}

	return i;
}

struct SList *slist_find(struct SList *head, bool (*test)(const void *val)) {
	struct SList *i;

	if (!test)
		return NULL;

	for (i = head; i; i = i->nex) {
		if (test(i->val)) {
			return i;
		}
	}

	return NULL;
}

void *slist_find_val(struct SList *head, bool (*test)(const void *val)) {
	struct SList *f = slist_find(head, test);
	if (f)
		return f->val;
	else
		return NULL;
}

struct SList *slist_find_equal(struct SList *head, bool (*equal)(const void *val, const void *data), const void *data) {
	struct SList *i;

	for (i = head; i; i = i->nex) {
		if (equal) {
			if (equal(i->val, data)) {
				return i;
			}
		} else if (i->val == data) {
			return i;
		}
	}

	return NULL;
}

void *slist_find_equal_val(struct SList *head, bool (*equal)(const void *val, const void *data), const void *data) {
	struct SList *f = slist_find_equal(head, equal, data);
	if (f)
		return f->val;
	else
		return NULL;
}

bool slist_equal(struct SList *a, struct SList *b, bool (*equal)(const void *a, const void *b)) {
	struct SList *ai, *bi;

	for (ai = a, bi = b; ai && bi; ai = ai->nex, bi = bi->nex) {
		if (equal) {
			if (!equal(ai->val, bi->val)) {
				return false;
			}
		} else if (ai->val != bi->val) {
			return false;
		}
	}

	if (ai || bi) {
		return false;
	}

	return true;
}

void *slist_remove(struct SList **head, struct SList **item) {
	if (!head || !item)
		return NULL;

	struct SList *i, *f, *p;
	void *removed = NULL;

	i = *head;
	p = NULL;
	f = NULL;

	for (i = *head; i; i = i->nex) {
		if (i == *item) {
			f = *item;
			break;
		}
		p = i;
	}

	if (f) {
		if (p) {
			p->nex = f->nex;
		} else {
			*head = f->nex;
		}
		removed = f->val;
		free(f);
		*item = NULL;
	}

	return removed;
}

unsigned long slist_remove_all(struct SList **head, bool (*equal)(const void *val, const void *data), const void *data) {
	if (!head)
		return 0;

	struct SList *i;
	unsigned long removed = 0;

	while ((i = slist_find_equal(*head, equal, data))) {
		slist_remove(head, &i);
		removed++;
	}

	return removed;
}

unsigned long slist_remove_all_free(struct SList **head, bool (*equal)(const void *val, const void *data), const void *data, void (*free_val)(void *val)) {
	if (!head)
		return 0;

	struct SList *i;
	unsigned long removed = 0;

	while ((i = slist_find_equal(*head, equal, data))) {
		if (free_val) {
			free_val(i->val);
		} else {
			free(i->val);
		}
		slist_remove(head, &i);
		removed++;
	}

	return removed;
}

struct SList *slist_shallow_clone(struct SList *head) {
	struct SList *c, *i;

	c = NULL;
	for (i = head; i; i = i->nex) {
		slist_append(&c, i->val);
	}

	return c;
}

void *slist_val(struct SList *head, unsigned long index) {
	unsigned long n = 0;

	for (struct SList *i = head; i; i = i->nex) {
		if (index == n++)
			return i->val;
	}

	return NULL;
}

unsigned long slist_length(struct SList *head) {
	unsigned long length = 0;

	for (struct SList *i = head; i; i = i->nex) {
		length++;
	}

	return length;
}

struct SList *slist_sort(struct SList *head, bool (*before)(const void *a, const void *b)) {
	struct SList *sorted = NULL;

	if (!head || !before) {
		return sorted;
	}

	if (!head->nex) {
		slist_append(&sorted, head->val);
		return sorted;
	}

	struct SList *sorting = slist_shallow_clone(head);

	struct SList *sorting_head  = sorting;
	struct SList **sorted_trail = &sorted;

	while (sorting != NULL) {
		sorting_head = sorting;
		sorted_trail = &sorted;

		sorting = sorting->nex;

		while (!(*sorted_trail == NULL || before(sorting_head->val, (*sorted_trail)->val))) {
			sorted_trail = &(*sorted_trail)->nex;
		}

		sorting_head->nex = *sorted_trail;
		*sorted_trail = sorting_head;
	}

	slist_free(&sorting);
	return sorted;
}

void slist_free(struct SList **head) {
	if (!head)
		return;

	struct SList *i, *f;

	i = *head;
	while (i) {
		f = i;
		i = i->nex;
		free(f);
	}

	*head = NULL;
}

void slist_free_vals(struct SList **head, void (*free_val)(void *val)) {
	if (!head)
		return;

	struct SList *i;

	for (i = *head; i; i = i->nex) {
		if (free_val) {
			free_val(i->val);
		} else {
			free(i->val);
		}
	}

	slist_free(head);
}

bool slist_equal_strcasecmp(const void *val, const void *data) {
	if (!val || !data) {
		return false;
	}
	return strcasecmp(val, data) == 0;
}

