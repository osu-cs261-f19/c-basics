#include <stdio.h>

/*
 * We can use pointers to accomplish the same effect as pass-py-reference in
 * C++.  If we pass a pointer to a value (i.e. the memory address where that
 * value is stored), we can update the underlying value from within a function
 * (using a pointer), and the update will affect that value in the calling
 * function.
 */
void make_it_32(int* it) {
  *it = 32;
}

int main(int argc, char** argv) {
  /*
   * Declare an integer variable and a pointer to an integer.  Initialize
   * the pointer to point to the memory location occupied by the original
   * integer.
   */
  int n = 16;
  int* n_ptr = &n;

  /*
   * Print the value of our integer, the value of our pointer, and the
   * memory address of the integer, the latter two of which will be the same.
   * Also, dereference n_ptr (i.e. *n_ptr) to see the value stored at the
   * memory address held in i_ptr.
   */
  printf("== n: %d\n", n);
  printf("== n_ptr: %p\n", n_ptr);
  printf("== &n: %p\n", &n);
  printf("== *n_ptr: %d\n", *n_ptr);

  /*
   * Dereference n_ptr (i.e. *n_ptr) to update the value stored at the memory
   * address held in n_ptr.  Note that this updates the value of i itself.
   * However, the memory addresses where n lives (and thus also the address
   * stored in n_ptr) doesnt change/
   */
  *n_ptr = 8;
  printf("\n== n: %d\n", n);
  printf("== n_ptr: %p\n", n_ptr);
  printf("== &n: %p\n", &n);
  printf("== *n_ptr: %d\n", *n_ptr);

  /*
   * Demonstrate how we can simulate pass-by-reference by passing the address
   * of n into our make_it_32() function.  When this function returns, the
   * value of n will be changed to 32.  Note that we could also pass n_ptr as
   * the argument to make_it_32() here and it would have the same effect.
   */
  make_it_32(&n);
  // make_it_32(n_ptr);
  printf("\n== n: %d\n", n);
  printf("== n_ptr: %p\n", n_ptr);
  printf("== &n: %p\n", &n);
  printf("== *n_ptr: %d\n", *n_ptr);

  /*
   * A void pointer (void*) is a generic pointer that can point to data of any
   * type.  Here, we create a void pointer that points to our integer n.  Note
   * that when we print the value of v_ptr, it is the same as the address of
   * n (and thus also the same as the value of n_ptr).
   *
   * Because there is no type information associated with a void pointer, we
   * can't dereference it.  Doing so would be a compile-time error.
   */
  void* v_ptr = &n;
  printf("\n== v_ptr: %p\n", v_ptr);
  // printf("== *v_ptr: %d\n", *v_ptr);

  /*
   * In order to get the value stored at the memory address pointed to by a
   * void pointer, we must cast back to the original type, either by assignment
   * or through an explicit cast, both of which we demonstrate below.
   */
  int* n_ptr2 = v_ptr;
  printf("== *n_ptr2: %d\n", *n_ptr2);
  printf("== *((int*)v_ptr): %d\n", *((int*)v_ptr));
}
