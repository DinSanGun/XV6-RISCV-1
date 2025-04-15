#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {

  int arr_size = 1 << 16; // 2^16
  int children_num = 4;

  int pids[children_num]; // array to store pids of child processes
  int identifier; 
  int child_number;
  int n_finished; // Number of processes that have finished after waitall call
  int statuses[NPROC];
  int total_sum = 0;


  int* num_array = malloc(sizeof(int) * arr_size);
  if (num_array == 0) {
    printf("malloc failed!\n");
    exit(1, "malloc failed");
  }

  // Initialize an array with consecutive numbers
  for (int i = 0; i < arr_size; i++)
    num_array[i] = i;

  printf("Creating %d child processes\n", children_num);
  
  // Create child processes
  identifier = forkn(children_num, pids);
  
  if (identifier == -1) {
    printf("Error: forkn failed\n");
    exit(1, "forkn error");
  }
  
  // Parent process case
  if (identifier == 0) {

    printf("Child processes PIDs: ");
    for (int i = 0; i < children_num; i++) 
      printf("%d ", pids[i]);
    printf("\n");

    
    // Wait for all children to finish
    if (waitall(&n_finished, statuses) == -1) {
      printf("Error: waitall failed!\n");
      exit(1, "Calculation failed");
    }
    
    // Verify all children finished
    if (n_finished != children_num) {
      printf("Error: expected %d children to finish, but got %d\n", children_num, n_finished);
      exit(1, "Calculation failed");
    }
    
    // Sum the results from all children
    for (int i = 0; i < n_finished; i++)
      total_sum += statuses[i];
    
    printf("Total sum is: %d\n", total_sum);

    exit(0, "Calculation succeeded\n");
  } 
  else {
    // Child process
    child_number = identifier;
    int start_index = (arr_size / children_num) * (child_number - 1);
    int end_index;

    if(child_number == children_num)
      end_index = arr_size;
    else
      end_index = (arr_size / children_num) * child_number;

    int partial_sum = 0;
    
    // Calculate sum for this quarter of the array
    for (int i = start_index; i < end_index; i++)
      partial_sum += num_array[i];
    
  
    //printf("Child process %d sum: %d\n",child_number, partial_sum);

    // Exit with the local sum as the status
    exit(partial_sum, "");

    exit(0, "");
  }

    return 0;
}