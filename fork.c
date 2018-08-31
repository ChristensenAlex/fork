#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void bubblesort(int size, int array[]);
void selectionsort(int size, int array[]);
int cmpfunc (const void * a, const void * b) {
	return (*(int*)a - *(int*)b);//this was taken from tutorialspoint.com
}
int is_sorted(int size, int array[]){//checks is the array is sorted
	for(int i = 0; i < size+1; i++){
		if(array[i] > array[i+1]) return 0;
	}
	return 1;
}

int main(int argc, char *argv[]) {
	printf("Welcome to the sorting races (pid:%d)\n", (int) getpid());
	//get user input on how many numbers to sort
	printf("How many numbers should I sort (pid:%d)\n", (int) getpid());
	int num = 0;
	scanf("%d", &num);
	int to_sort[num];
	for(int i = 0; i < num; i++){
		to_sort[i] = rand();	
	}
	int bubble_rc = fork();
	if(bubble_rc < 0){
		fprintf(stderr, "fork failed\n");
		exit(1);//exit with a warning
	} else if(bubble_rc == 0){
		printf("Bubblesort has started (pid:%d)(ppid:%d)\n", (int) getpid(),(int) getppid());
		bubblesort(num, to_sort);
		
		exit(0);
	}	
	int selection_rc = fork();
	if(selection_rc < 0){
		fprintf(stderr, "fork failed\n");
		exit(1);//exit with a warning
	} else if(selection_rc == 0){
		printf("Selectionsort has started (pid:%d)\n", (int) getpid());
		selectionsort(num, to_sort);
		exit(0);
	}
	int quick_rc = fork();
	if(quick_rc < 0){
		fprintf(stderr, "fork failed\n");
		exit(1);//exit with a warning
	} else if(quick_rc == 0){
		printf("Qsort in library has started (pid:%d)\n", (int) getpid());
		qsort(to_sort, num, sizeof(int), cmpfunc);	
		if(is_sorted == 0){
			fprintf(stderr, "Qsort failed\n");
		}
		exit(0);
	}
	int rc = wait(NULL);
	rc = wait(NULL); // Do I need to remember these pids maybe changing to pidID is better
	rc = wait(NULL);
	sleep(2);
	//flush stuff goes here learn what it does
	printf("The race has finished\n");
	return 0;

}

void bubblesort(int size, int array[]){
	for(int g = 0; g < size; g++){
		for(int i = 0; i < size-1-g; i++){
			if(array[i] > array[i+1]){
				int temp = array[i];
				array[i] = array[i+1];
				array[i+1] = temp;
			}	
		}
	}
	return;
}

void selectionsort(int size, int array[]){
	for(int i = 0; i < size; i++){
		int smallest = array[i];
		int smallest_pointer = i;
		for(int g = i+1; g < size; g++){
			if(array[g] < smallest){
				smallest = array[g];
				smallest_pointer = g;
			}
		int temp = array[i];//swap
		array[i] = array[smallest_pointer];
		array[smallest_pointer] = temp;
		}
	}

}

