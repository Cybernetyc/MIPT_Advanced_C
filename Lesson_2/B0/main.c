/**
 * @description Function to find\n
 * the maximum block in a singly\n
 * linked list
 * @param head
 * @return uint64_t max_adress
 *
 */
uint64_t findMaxBlock(list *head)
{
  uint64_t max_address = 0;
  size_t max_size = 0;

  for(list *p = head; p!=NULL; p = p->next){
    if (max_size < p->size){
      max_size = p->size;
      max_address = p->address;
    }
  }

  return max_address;
}