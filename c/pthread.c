#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct{
   int a;
   int b;
}thread_args;

static void *start_routine(void *arg){

   printf("Hello from thread\n");
   return NULL; // Explicitly return NULL
}
static void *start_routine_with_arg(void *arg){
   int *value = (int *)arg; //
   printf("Received value: %d\n", *value);
   return NULL; // No Return Value Needed
}
static void *start_routine_with_return(void *arg){
   int *result = malloc(sizeof(int));
   *result = 42;
   return (void *)result; // Return
}
static void *start_routine_exit(void *arg){
   int result = 10;
   pthread_exit((void *)(intptr_t)result); // Exit with result
}
static void *start_routine_struct_args(void *arg) {
   thread_args *args = (thread_args *)arg;
   printf("SUM: %d\n", args->a + args->b); 
   return NULL;
}

int main(){

   pthread_t t1, t2, t3, t4, t5;
   
   int value = 1;
   void *retval, *ret;
   thread_args args = {5,10};
   pthread_create(&t1, NULL, start_routine, NULL);
   pthread_create(&t2, NULL, start_routine_with_arg, &value);
   pthread_create(&t3, NULL, start_routine_with_return, NULL);
   pthread_create(&t4, NULL, start_routine_exit, NULL);
   pthread_create(&t5, NULL, start_routine_struct_args, &args);

   printf("Hello from main\n");
   pthread_join(t1, NULL);

   pthread_join(t2, NULL);

   pthread_join(t3, &retval);
   int *result  = (int *)retval;
   printf("Thread returned: %d\n", *result);
   free(retval);
   
   {
      pthread_join(t4, &ret);
      int result  = (int)(intptr_t)ret;
      printf("Thread returned: %d\n", result);
   }

   pthread_join(t5, NULL);
   return 0;
}