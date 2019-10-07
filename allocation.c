#include <stdio.h>
#include <stdlib.h>

#include "student.h"

void leaky() {
  int* n = malloc(sizeof(int));
  free(n);
}

int main(int argc, char** argv) {
  /*
   * malloc() is the function we use in C to dynamically allocate memory (i.e.
   * allocate memory on the heap).  malloc() takes a single argument specifying
   * the number of bytes to be allocated and returns a pointer to the allocated
   * memory (as a void pointer, which can be cast to any type of pointer).
   */
  void* v_ptr = malloc(10);

  /*
   * The sizeof operator can help us figure out how many bytes to request from
   * malloc().  It tells us the number of bytes needed to store a given data
   * type.  For example, here, we use sizeof to see how many bytes are needed
   * to store an int.
   */
  printf("== sizeof(int): %lu\n", sizeof(int));

  /*
   * Here, we use malloc() to allocate space for a single integer on the heap.
   * Note how we use sizeof() to tell us how many bytes to request to store the
   * integer.  Once the int is allocated and we have a pointer to it, we can
   * use that pointer just like any other int pointer, e.g. dereferencing it
   * to get and set the underlying value.
   */
  int* n = malloc(sizeof(int));
  // int* n = malloc(sizeof(*n));
  *n = 32;
  printf("== *n: %d\n", *n);

  /*
   * We can also use malloc() to allocate memory on the heap for an array.
   * Here, we dynamically allocate an array of 10 integers and initialize
   * the values of the elements of the array within a loop.
   */
  int* array = malloc(100 * sizeof(int));
  int i;
  for (i = 0; i < 100; i++) {
    array[i] = i;
    // *(array + i) = i;
  }

  /*
   * We can also use malloc() to dynamically allocate memory for a struct.
   * Note that to access the fields of a struct when we have a pointer to
   * that struct, we need to dereference the pointer.  The arrow operator
   * (i.e. ->) both dereferences a struct pointer and accesses one of its
   * fields.
   */
  struct student* s = malloc(sizeof(struct student));
  (*s).id = 933222222;
  s->gpa = 4.0;
  s->name = "Rey";
  printf("== %s %d %f\n", s->name, s->id, s->gpa);

  /*
   * A 2D array is actually represented as a 1D array of 1D arrays, i.e. a
   * pointer to an array of pointers, each of which points to a 1D array of
   * elements.  To allocate a 2D array, we need to allocate memory for the
   * outer 1D array of pointers, and then allocate a 1D array for each of
   * those pointers to point to.
   *
   * Here's how it would look to allocate an 5 x 4 array of ints.
   */
  int** matrix = malloc(5 * sizeof(int*));
  for (i = 0; i < 5; i++) {
    matrix[i] = malloc(4 * sizeof(int));
  }
  matrix[2][3] = 6;

  /*
   * To free memory allocated with malloc(), we use the free() function.
   */
  free(v_ptr);
  free(n);
  free(NULL);
  free(array);
  free(s);

  /*
   * In order to free the memory allocated to our 2D array, we need to reverse
   * what we did to allocate it.  Specifically, we need to free each of the
   * inner 1D arrays of ints before we free the outer 1D array of pointers.
   */
  for (i = 0; i < 5; i++) {
    free(matrix[i]);
  }
  free(matrix);

  leaky();
}
