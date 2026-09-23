#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "math.h"

struct Task{
int first;
int second;
char operation;
int result;
int complete_status;
};

void print_help(){
printf("Using calculator rules\n");
printf("Options:\n -f integer (first number)\n -s integer (second number, do not need for factorial)\n");
printf(" -o operation (+, -, *, /, ^, !)\n -h (show help)\n");
}

int makeCalculate(struct Task* task){
int error_code = 0;

switch (task->operation){
case '+':
error_code = calcs::addition(task->first, task->second, &task->result);
break;

case '-':
error_code = calcs::subtraction(task->first, task->second, &task->result);
break;

case '*':
error_code = calcs::multiplication(task->first, task->second, &task->result);
break;

case '/':
error_code = calcs::division(task->first, task->second, &task->result);
break;

case '^':
error_code = calcs::power(task->first, task->second, &task->result);
break;

case '!':
error_code = calcs::factorial(task->first, &task->result);
break;

default:
error_code = -1;
break;
}
task->complete_status = error_code;
return error_code;
}

void printResult(const struct Task* task){
int status;
switch (task->complete_status){
case calcs::ok:
printf("Result: %d\n", task->result);
break;

case calcs::error_negative_power:
fprintf(stderr, "Error: can not raise integer to a negative power\n");
break;

case calcs::error_negative_factorial:
fprintf(stderr, "Error: factorial of negative number is not defined\n");
break;

case calcs::error_null_division:
fprintf(stderr, "Error: can not divide by 0\n");
break;

case calcs::error_overflow:
fprintf(stderr, "Error: variable overflow\n");
break;

default:
printf("Error");
break;
}
}

int makeTask(int argc, char** argv, struct Task* task){
int opt;

optind = 0;

while((opt = getopt(argc, argv, "f:s:o:h")) != -1){
switch(opt){
case 'f':
task->first = atoi(optarg);
break;

case 's':
task->second = atoi(optarg);
break;

case 'o':
if (optarg[0] == '\0'){
fprintf(stderr, "operation is not given\n");
return 1;
}
task->operation = optarg[0];
break;

case 'h':
print_help();
return 2;

case '?':
print_help();
return 1;

default:
return 1;
} 
}

return 0;
}

int applicationRun(int argc, char** argv){
struct Task task = {0, 0, '\0', 0, 0};

int status = makeTask(argc, argv, &task);

if (status != 0){
if (status == 2){
return 0;
}
return status;
}
makeCalculate(&task);
printResult(&task);

return task.complete_status;
}

int main(int argc, char** argv){
return applicationRun(argc, argv);
}
