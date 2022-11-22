#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

struct node
{
  void *data;
  struct node *next;
};
typedef struct node *llist_t;

void llist_create(llist_t **list);
void llist_destroy(llist_t *list);

void llist_add(llist_t *list, void *data);
void llist_remove(llist_t *node);

#endif /* _LINKED_LIST_H_ */