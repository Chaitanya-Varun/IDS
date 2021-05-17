#include<stdio.h>
#include<stdlib.h>
#include<time.h>
////Creating the structure of node used in the stack
struct node{
	int l;
	int h;
	int ln;
	struct node* link;
	};

struct node*top=NULL;  //This is the pointer pointing to the topmost node
////Function to push the new node into the stack
void push(int l,int h,int ln){
	struct node* temp=NULL;
	temp=(struct node*)malloc(sizeof(struct node));   //Assigning the new node 
	temp->l=l;                                        //Assigning the parameters
	temp->h=h;
	temp->ln=ln;
	temp->link=top;                                   //Creating the link in the stack
	top=temp;                                         //Updating the top
	}
////Function to pop the top most node 	
struct node* pop(){
	struct node*temp=NULL;                            //Storing the data of the top into a temporary node
	temp=top;                                         
	if(top==NULL)                                     //Check for the empty stack
		printf("Stack is empty,nothing to pop\n");
	else{
		top=temp->link;                               //Updating the top to descend 
		}
	return(top);
	}
////Function to the swap values in array between positions i and j	
void swap(int*a,int i,int j){
	int temp=0;
	temp=a[i];                                        //Noting the the value of first element
	a[i]=a[j];                                        //Change it to new position in array
	a[j]=temp;                                        //Replacing the old value with new value
	}
////Function to put the selected pivot in the right position taking the pivot from last position
int partition(int*a,int l,int h){                     //here a is array,l is low index of array ,h is high index of array
	int i=l-1,j=l;                                    //initiating the varibles used in traversing the array
	int pivot=a[h];                                   //Selecting the pivot to be last element of the array
	while(j<h){
		if(a[j]<=pivot){                              //Making the elements smaller than the pivot move to left of pivot
			i++;
			swap(a,i,j);
			}
		j++;
		}
	swap(a,h,i+1);                                   //Making pivot into the right place
	return(i+1);                                     //Returning the position of the pivot
	}
////Function to do partition using random pivot by actually changing it to the last position
int ran_partition(int*a,int l,int h){
	int num = l+(rand()%(h-l));                      //Selecting the random pivot
	swap(a,num,h);                                   //Swapping the last position value with selected pivot
	return(partition(a,l,h));                        //Following the partition function to do the rest
	}
////Function to print the available contents in the stack	
void printStack(struct node*top){
	struct node* temp =top;                         //Creating a temporary pointer to traverse the stack
	if(temp==NULL)                                  //Check for the empty stack
		printf("The stack is empty.\n");
	else{
		printf("{");                                //Printing the stack in the required format
		while(temp !=NULL){
			printf("(%d,%d,%d)",temp->l,temp->h,temp->ln);
			if(temp->link!=NULL){
				printf(", ");
				}
			temp=temp->link;                        //Moving to the next node of the stack
			}
		printf("}\n");                              //Reaching the end of stack
		}
	}
	
int indentation=0;                                  //For proper spacing to specify in which call operation happens
////Function for the quick sort algorithm
void quicksort(int*a,int l,int h){
	indentation++;
	if(l<h){                                        //Making sure the array is not single element and terminate if so
		int piv = ran_partition(a,l,h);             //Pivot declaration
		push(l,piv-1,89);                           //Pushing the poarameters into the stack
		for(int i=0;i<indentation;i++)              //Indentation purpose
			printf("\t");
		printStack(top);
		quicksort(a,l,piv-1);                      //Recursive right sort
		pop();
		push(piv+1,h,95);
		for(int i=0;i<indentation;i++)
			printf("\t");
		printStack(top);
		quicksort(a,piv+1,h);                      //Recursive left sort
		pop();
		}
	indentation--;
	}

////Function for printing the elements in the array	
void printArray(int*a,int n){
	int t=0;                                       //Temporary variable to traverse the array
	while(t<n){
		printf(" %d,",a[t]);
		t++;
		}
	printf("\n");
	}
	
int main(){
	srand(time(0));                                //Seeding the random values
	int a[]={6,5,4,3,2,1};                         //Array declaration
	printf("Original Array:\n");
	printArray(a,6);
	int n= sizeof(a)/sizeof(a[0]);
	push(0,n-1,119);                               //The first call of the quick sort function
	printStack(top);
	quicksort(a,0,n-1);
	pop();
	
	printf("Sorted Array :\n");                    //Array is sorted
	printArray(a,6);
	}