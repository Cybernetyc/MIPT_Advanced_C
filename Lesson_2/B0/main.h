//
// Created by Dmitry on 30.01.2025.
//

#ifndef B0_MAIN_H
#define B0_MAIN_H

#include <stdlib.h>
#include <stdint.h>

typedef struct list{
  uint64_t address;
  size_t size;
  char comment[64];
  struct list* next;
} list;

#endif //B0_MAIN_H
