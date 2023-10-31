#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "linked-list.h"

namespace base {

   Node* destroy(Node* list)
   {
      Node* p = list;
      while (p != NULL) {
         Node* next = p->next;
         free(p->reg.name);
         free(p);
         p = next;
      }
      return NULL;
   }

   Node* append(Node* list, uint32_t nmec, char *name)
   {
      Node* new_node = (Node*) malloc(sizeof(Node));
      if (new_node == NULL) {
         printf("No memory available to allocate new node.\n");
         exit(1);
      }

      char* student_name = strdup(name);
      
      new_node->reg.name = student_name;
      new_node->reg.nmec = nmec;
      new_node->next = NULL;

      if (list == NULL) {
         return new_node;
      }

      Node* last = list;

      while (last->next != NULL) {
         last = last->next;
      }

      last->next = new_node;

      return list;
   }

   void print(Node* list)
   {
      if (list == NULL) {
         printf("List is empty.");
         return;
      } 
      printf("%-6s | %-99s\n", "NMec", "Nome");
      for (Node* p = list; p != NULL; p = p->next) {
         printf("%6d | %s", p->reg.nmec, p->reg.name);
      }
   }

   int exists(Node* list, uint32_t nmec)
   {
      return 0;
   }

   Node* remove(Node* list, uint32_t nmec)
   {
      return NULL;
   }

   const char *search(Node* list, uint32_t nmec)
   {
      return NULL;
   }

   Node* sort_by_name(Node* list)
   {
      return NULL;
   }

   Node* sort_by_number(Node* list)
   {
      return NULL;
   }
}
