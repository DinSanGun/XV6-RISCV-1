#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define ARRAY_SIZE (1 << 16)  // 2^16 = 65536
#define NUM_CHILDREN 4

int main(int argc, char *argv[]) {

  int i;
  int array[ARRAY_SIZE];
  int pids[NUM_CHILDREN];
  int result;
  int child_number;
  int n_finished;
  int statuses[4];
  int total_sum = 0;

  // Initialize array with consecutive numbers
  for (i = 0; i < ARRAY_SIZE; i++) {
    array[i] = i;
  }

  printf("Creating %d child processes...\n", NUM_CHILDREN);
  
  // Create NUM_CHILDREN child processes
  result = forkn(NUM_CHILDREN, pids);
  
  if (result == -1) {
    printf("Error: forkn failed\n");
    exit(-1, "");
  }
  
  // Check if this is the parent process
  if (result == 0) {
    // Parent process
    printf("Child PIDs: ");
    for (i = 0; i < NUM_CHILDREN; i++) {
      printf("%d ", pids[i]);
    }
    printf("\n");
    
    // Wait for all children to finish
    if (waitall(&n_finished, statuses) == -1) {
      printf("Error: waitall failed\n");
      exit(-1, "calculation failed");
    }
    
    // Verify all children finished
    if (n_finished != NUM_CHILDREN) {
      printf("Error: expected %d children to finish, but got %d\n", 
             NUM_CHILDREN, n_finished);
      exit(-1, "calculation failed");
    }
    
    // Sum the results from all children
    for (i = 0; i < n_finished; i++) {
      total_sum += statuses[i];
    }
    
    printf("Total sum: %d\n", total_sum);
    
    // The expected sum should be 0+1+2+...+(2^16-1) = 2147450880
    if (total_sum == 2147450880) {
      printf("Sum is correct!\n");
      exit(0, "calculation completed");
    } else {
      printf("Sum is incorrect! Expected 2147450880\n");
      exit(-1, "calculation failed");
    }
    
  } else {
    // Child process
    child_number = result;
    int start_index = (ARRAY_SIZE / NUM_CHILDREN) * (child_number - 1);
    int end_index = (child_number == NUM_CHILDREN) ? 
                    ARRAY_SIZE : 
                    (ARRAY_SIZE / NUM_CHILDREN) * child_number;
    int local_sum = 0;
    
    // Calculate sum for this quarter of the array
    for (i = start_index; i < end_index; i++) {
      local_sum += array[i];
    }
    
    printf("Child %d (PID %d): Sum of elements [%d-%d] = %d\n", 
           child_number, getpid(), start_index, end_index-1, local_sum);
    
    // Exit with the local sum as the status
    exit(local_sum, "");
  }

    return 0;
}