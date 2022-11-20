#include "linked_list.h"
#include <stdlib.h>
#include <stddef.h>

llist_t *llist_create(void)
{
  llist_t *list = malloc(sizeof(llist_t));
  *list         = malloc(sizeof(struct node));

  struct node *new_node = (struct node *)list;
  new_node->data        = NULL;
  new_node->next        = NULL;

  return list;
}

void llist_destroy(llist_t *list)
{
  struct node *curr = *list;
  struct node *next;

  while (curr != NULL)
    {
      next = curr->next;
      free(curr);
      curr = next;
    }

  free(list);
}

void llist_add(llist_t *list, void *data)
{
  struct node *node = (struct node *)list;
  while (node != NULL)
    {
      node = node->next;
    }

  struct node *new_node = malloc(sizeof(struct node));
  new_node->data        = data;
  new_node->next        = NULL;

  node->next = new_node;
}
void llist_remove(llist_t *node_)
{
  struct node *node = (struct node *)*node_;
  if (node->next != NULL)
    {
      struct node *next_node = node->next;
      node->data = next_node->data;
      node->next = next_node->next;
      free(next_node);
      next_node = NULL;
    }
  else
    {
      free(node);
      node = NULL;
    }
}
