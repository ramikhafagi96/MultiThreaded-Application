# MultiThreaded-Application
Implemented Matrix Multiplication and Merge Sort using multi threading
# Description
* The project has two multi-threaded programs implemented by using POSIX threads library in C++ to create and join threads.
* The first program is Matrix Multiplication and used to algorithms for the implememntation
  1. The computation of each element of the output matrix happens in a thread.
  2. The computation of each row of the output matrix happens in a thread.
* Execution time for each algorithm is calculated, and the second algorithm was found to be faster on large matrices
* The second program is Merge Sort and implemented as follows
  1. Divide the unsorted list into two sub-lists of about half the size.
  2. Sort each sub-list in a thread recursively by re-applying the merge sort.
  3. Merge the two sub-lists back into one sorted list.
