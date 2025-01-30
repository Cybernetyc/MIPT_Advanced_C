
/**
 * @description Function to analyzer\n
 * and return total size of used\n
 * memory of linked list\n
 * @param head
 * @return size_t total_size
 */
#include "B1/main.h"

size_t totalMemoryUsage(list *head)
{
  size_t total_size = 0; ///< Var for total size


  for(list *p = head; p!=NULL; p = p->next) ///< If size in noNULL head
    total_size += p->size; ///< Summ total size

  return total_size;
}
