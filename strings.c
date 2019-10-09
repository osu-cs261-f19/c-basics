#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

int main(int argc, char** argv) {
  /*
   * In C, strings are represented as arrays of characters.  Here, we allocate
   * space for a string with 64 total characters.  Note that one character of
   * this space must be reserved for a terminating null character ('\0'), so
   * the string we're allocating here really only has space for 63 "regular"
   * characters.
   */
  char* str = malloc(64 * sizeof(char));

  /*
   * Note that when initializing a string with a constant (i.e. with a string
   * "inside double quotes"), that string points to a location in read-only
   * memory and can't be modified.  The string should thus be declared as
   * const.  By doing this, trying to modify it, as in the commented-out line
   * below, becomes a compile-time error instead of a runtime error.
   */
  const char* name = "Leia Organa";
  // name[0] = 'l';

  /*
   * strlen() is a useful string function that returns the number of
   * printable characters in a string.  Note that this *does not* include the
   * terminating null character ('\0').
   */
  printf("== strlen(name): %lu\n", strlen(name));

  /*
   * strncpy() is a good function to use to copy the contents of one string
   * into another array.  Note that this is a better option than strcpy(),
   * since the latter doesn't allow us to limit the number of characters
   * copied like strncpy() does.  By limiting the number of characters copied
   * to only as many as we have allocated space for, we can protect ourselves
   * against buffer overflow attacks.
   */
  int n = strlen(name);
  char* copy = malloc((n + 1) * sizeof(char));
  strncpy(copy, name, n + 1);
  printf("== copy: %s\n", copy);
  copy[0] = 'l';
  printf("== copy: %s\n", copy);

  /*
   * snprintf() is another function that's useful for initializing strings.
   * This function allows us to "print" content to a string in a manner similar
   * to the way we print to the console using printf().  snprintf() also limits
   * the number of characters "printed", similar to strncpy().
   */
  struct student s = {.gpa = 3.75, .name = "Luke Skywalker", .id = 933111111};
  snprintf(str, 64, "%s %d %f", s.name, s.id, s.gpa);
  printf("== str: %s\n", str);

  /*
   * Just like any memory allocated with malloc(), we must free strings using
   * free().
   */
  free(str);
}
