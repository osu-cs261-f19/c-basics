#include <stdio.h>
#include <stdlib.h>

#include "student.h"

/*
 * Here, we have a simple function to "sort" an array of two things.  This
 * function is set up to be able to sort *any* type of things.  Specifically,
 * the array is passed as an array of void pointers (i.e. void**), so the
 * array can contain any kind of pointer.  In addition, this function takes
 * a function pointer argument, which is used to allow the caller to provide
 * a function for comparing whatever kind of data they pass in the array.
 */
void sort_two_things(void** two_things, int (*cmp)(void* a, void* b)) {
  if (cmp(two_things[0], two_things[1]) != 0) {
    void* tmp = two_things[0];
    two_things[0] = two_things[1];
    two_things[1] = tmp;
  }
}

/*
 * Here, we have a function for comparing two integers, whose addresses are
 * passed as void pointers.  To compare, we first cast the void pointers back
 * to int pointers.  Then, we can dereference and make the comparison.  We
 * return 0 if `a` represents an int whose value is less than or equal to the
 * int represented by `b`, and we return 1 otherwise.
 *
 * Importantly, note that the prototype of this function matches the prototype
 * specified for the comparison function pointer argument to sort_two_things()
 * above.
 */
int compare_ints(void* a, void* b) {
  int* ia = a;
  int* ib = b;
  if (*ia <= *ib) {
    return 0;
  } else {
    return 1;
  }
}

/*
 * Here, we have a function for comparing two student structs, whose addresses
 * are passed as void pointers.  To compare, we first cast the void pointers
 * back to student pointers.  Then, we can dereference and make the comparison.
 * We return 0 if `a` represents an student whose id field is less than or
 * equal to the id field of the student represented by `b`, and we return 1
 * otherwise.
 *
 * Again, note that the prototype of this function matches the prototype
 * specified for the comparison function pointer argument to sort_two_things()
 * above.
 */
int compare_students(void* a, void* b) {
  struct student* sa = a;
  struct student* sb = b;
  if (sa->id <= sb->id) {
    return 0;
  } else {
    return 1;
  }
}

int main(int argc, char** argv) {
  /*
   * Here, we set up an example to demonstrate how we can use function pointers
   * in conjunction with the sort_two_things() function.  Specifically, we set
   * up an array that contains pointers to two integer values.
   */
  int i, i1 = 16, i2 = 8;
  int** int_ptrs = malloc(2 * sizeof(int*));
  int_ptrs[0] = &i1;
  int_ptrs[1] = &i2;

  printf("== int_ptrs before sort:\n");
  for (i = 0; i < 2; i++) {
    printf("  -- %d: %d\n", i, *int_ptrs[i]);
  }

  /*
   * Here, we "sort" our integer array using the compare_ints() function to
   * make comparisons.
   */
  sort_two_things((void**)int_ptrs, compare_ints);

  printf("\n== int_ptrs after sort:\n");
  for (i = 0; i < 2; i++) {
    printf("  -- %d: %d\n", i, *int_ptrs[i]);
  }

  /*
   * Here, we set up a second example to demonstrate how we can use function
   * pointers in conjunction with the sort_two_things() function.  In this
   * example, we set up an array that contains pointers to two student structs.
   */
  struct student s1 = {.name = "Luke Skywalker", .id = 933222222, .gpa = 3.5};
  struct student s2 = {.name = "Leia Organa", .id = 933111111, .gpa = 4.0};
  struct student** student_ptrs = malloc(2 * sizeof(struct student*));
  student_ptrs[0] = &s1;
  student_ptrs[1] = &s2;

  printf("\n== student_ptrs before sort:\n");
  for (i = 0; i < 2; i++) {
    printf("  -- %d: %s\t%d\t%f\n", i, student_ptrs[i]->name,
      student_ptrs[i]->id, student_ptrs[i]->gpa);
  }

  /*
   * Like above, here we "sort" our array of student pointers using our
   * compare_students() function to make the comparisons.
   */
  sort_two_things((void**)student_ptrs, compare_students);

  printf("\n== student_ptrs after sort:\n");
  for (i = 0; i < 2; i++) {
    printf("  -- %d: %s\t%d\t%f\n", i, student_ptrs[i]->name,
      student_ptrs[i]->id, student_ptrs[i]->gpa);
  }
}
