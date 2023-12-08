// list/list.c
// 
// Implementation for linked list.
//
// Myles Block

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list_t *list_alloc() {
  list_t *list = (list_t *)malloc(sizeof(list_t));
  list->head = NULL;
  list->length = 0;
  return list;
  }


void list_free(list_t *head_of_list) {
  node_t *current = head_of_list->head;
  node_t *next;
  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
}

void list_print(list_t *head_of_list) {
  node_t *current = head_of_list->head;
  printf("Current values of the linked list: \n");
  while(current != NULL && head_of_list->length != 0) {
    printf("%d->", current->value);
    current = current->next;
  }
  printf("\n"); 
}


int list_length(list_t *head_of_list) { 
  return head_of_list->length; 
}

void list_add_to_back(list_t *head_of_list, elem value) {
  node_t *newNode = (node_t *) malloc(sizeof(node_t));
  newNode->value = value;

  node_t *current = head_of_list->head;
  while (current->next != NULL){
    current = current->next;
  }
  current->next = newNode;
  newNode->next = NULL;
  head_of_list->length++;

}
void list_add_to_front(list_t *head_of_list, elem value) {
  node_t *newNode = (node_t *) malloc(sizeof(node_t));
  newNode->value = value;
  newNode->next = head_of_list->head;
  head_of_list->head = newNode;
  head_of_list->length++;
}
void list_add_at_index(list_t *head_of_list, elem value, int index) {
  if (is_index_within_list(head_of_list, index)) {
    node_t *newNode = (node_t *) malloc(sizeof(node_t));
    newNode->value = value;
    node_t *current = head_of_list->head;
    node_t *prev = NULL;
    int count = 1;

    if (index == 1) {
      list_add_to_front(head_of_list, index);
    }
    else if (!is_index_within_list(head_of_list, index)) {
      list_add_to_back(head_of_list, value);
    }
    else {
      while (count < index) {
        prev = current;
        current = current->next;
        count++;
      }
      prev->next = newNode;
      newNode->next = current;
      head_of_list->length++;
    }
  }
}

elem list_remove_from_back(list_t *head_of_list) { 
  node_t *current = head_of_list->head;
  node_t *prev = NULL;
  while (current->next != NULL) {
    prev = current;
    current = current->next;
  }
  elem value = current->value;
  if (prev != NULL){
    prev->next = NULL;
  } 
  else{
    free(prev);
  }
  head_of_list->length--;
  return value;
  free(current);
}


elem list_remove_from_front(list_t *head_of_list) {
  if(head_of_list->head == NULL){
    printf("Linked list is empty\n");
    return -1;
  }
  head_of_list->length--;
  node_t *current = head_of_list->head;
  elem value = current->value;
  head_of_list->head = current->next;
  free(current);
  return value;
}

elem list_remove_at_index(list_t *head_of_list, int index) { 
  node_t *current = head_of_list->head; //pointer to keep track of the current node
  node_t *prev = NULL;

  if (is_index_within_list(head_of_list, index)) {
    int count = 1;
    while (count < index) {
      prev = current;
      current = current->next;
      count++;
    }
    elem value = current->value;
    if (prev != NULL) {
      prev->next = current->next;
    }
    else {
      free(prev);
    }
    head_of_list->length--;
    return value;
    free(current);
  }

  return -1;
}

bool list_is_in(list_t *head_of_list, elem value) { 
  node_t *current = head_of_list->head;
  while (current != NULL) {
    if (current->value == value) {
      return true;
    }
    current = current->next;
  }
  return false;
}


elem list_get_elem_at(list_t *head_of_list, int index) {
  node_t *current = head_of_list->head;
  int count = 1;

  //checks if the index is within the list length
  if (is_index_within_list(head_of_list, index)) {
    while (count < index) {
    current = current->next;
    count++;
  }
  return current->value;
  }
  return -1;
}


int list_get_index_of(list_t *head_of_list, elem value) { 
  node_t *current = head_of_list->head;
  int count = 1;
  while (current != NULL) {
    if (current->value == value) {
      return count;
    }
    current = current->next;
    count++;
  }
  return -1;
}

bool is_index_within_list(list_t *head_of_list, int index){
  bool is_index_valid = (list_length(head_of_list) >= index && (index > 0))? true : false;
  return is_index_valid;
}

