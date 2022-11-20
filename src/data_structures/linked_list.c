#include "linked_list.h"
#include <stddef.h>

llist_t *llist_create(void)
{
  llist_t *list = malloc(sizeof(llist_t));
  *list         = malloc(sizeof(struct node));

  struct node *new_node = list;
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
void llist_remove(llist_t *list, struct node *node)
{
  if (node->next != NULL)
    {
      node->data = node->next->data;
      node->next = node->next->next;
    }
  else
    {
      free(node);
    }
}
