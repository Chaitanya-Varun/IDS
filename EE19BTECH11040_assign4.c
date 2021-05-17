
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int j = 1;                                              //Variable for keeping count of job index
int total_time = 0;                                     //Variable to track the total time taken for whole process
//Structure of node in the queue
struct node{
    int j_ind;                                          //Job index
    int p_time;                                         //Process Time
    struct node* link;                                  //Link to the next node
};
//Structure of Queue
struct queue{
    struct node *front,*rear;                           //Holds the front and rear positions of a queue
};
//Function to create a new node
struct node* new_node(){
    int l = 1;int h = 300;                              //Bounds of the time for Process:l=>low,h=>high
    int num = l + (rand()%(h-l));                       //Choosing a random number
    struct node* temp = NULL;                           //Creating a new node
    temp = (struct node*)malloc(sizeof(struct node));   //Allocating memory
    temp -> j_ind = j;j++;                              //Assigning the variables
    temp -> p_time = num ;
    total_time += num;
    return(temp);                                       //Returns the address of the created node
};
//Function to create a queue
struct queue* create_queue(){
    struct queue* q =NULL;                              //Creating a queue
    q = (struct queue*)malloc(sizeof(struct queue));
    q->front = q->rear =NULL;                           //Initiating the elements
    return(q);                                          //Returns address of the queue
};
//Function to add the elements in a given queue
struct node* enqueue(struct queue*q){
    struct node*temp=NULL;                              //Creating a new node with proper variables set
    temp = new_node();
    if(q->rear == NULL){                                //For the first node in the queue
        q->front = q->rear =temp;
    }
    else{                                               //For extending the queue at the end
        q->rear->link = temp;                           //Making the link
        q->rear = temp;                                 //Updating the rear
    }
    return(q->front);                                   //Returning the front element address
}
//Function to remove the element from the queue from starting
struct node* dequeue(struct queue*q){
	struct node*temp=q->front;                          //A temporary node pointer storing the address of the present front
	if(temp==NULL){                                     //Check for empty queue
		printf("Invalid operation,.\n");
		return(0);}
	else{                                               //Updating the front and removing the before element
		q->front = temp->link;
		temp->link=NULL;
		return(temp);}
	return(temp);                                        //Returning the address of the removed node
	}
//Function for removing and adding the front node at the end
struct node* denenqueue(struct queue*q){
	struct node*temp = NULL;
    if(q->rear==q->front);                                //If that is only element in the queue ,do nothing
    else{
        temp = dequeue(q);                                //Dequeue at the start
        q->rear->link = temp;                             //Appending in the end
        q->rear = temp;
        }
    return(q->front);                                     //Returns the new front's address
	}
//Function to print the queue
void print_queue(struct queue*q){
	struct node * temp=NULL;                               //Temporary variable to traverse through the nodes
	temp = q->front;                                       //Initiating the Variable
	if(temp==NULL){                                        //Checking the queue is empty
		printf("Queue is empty.\n");
		}
	while(temp!=NULL){                                     //Until it reaches the end
		printf("J%d :%d ,",temp->j_ind,temp->p_time);      //Printing the elements
		temp = temp->link;                                 //Updating the temp
		}
	printf("\n");
	}
//Function to append elements at the end
void extend_queue(struct queue*q,int len){                 //len is the number of elements to be added in the queue
	for(int i=0;i<len;i++){
		enqueue(q);                                        //Repeating the engueue function for len times;
		}
	printf("Queue is extended by length of %d\n",len);
	}

int main(){
	int quantum = 50;int t = 0;int stime=0;int ltime=0;    //Time constraints and other time variables
	srand(time(NULL));                                     //Seeding a new value
	struct queue* q = create_queue();                      //Creating a queue named q
	extend_queue(q,100);                                    //Adding elements in queue
	struct node* temp=NULL;                                //Temporary node to travel through the queue and operate
	temp = q->front;                                       //Assigning the front to it
	//print_queue(q);
	printf("The queue at t=%d :\n",t);                     //Printing the initial Queue
    print_queue(q);
	while(temp!=NULL && t<total_time+100){                 //Condition to exit the loop till the queue gets empty
		quantum=50;stime=0;                                //stime is the service time for a quantum
		while(quantum != 0&&temp!=NULL){                   //Condition check for completing the time quantum and ending the queue
            if(ltime==0){                                  //To keep track of time the task already used last time
                if(temp->p_time > quantum){                //If required time is more than what can be served, deque and enlist at the end
                    stime=0;
                    temp->p_time = temp->p_time - quantum;
                    stime = quantum;
                    if(stime==50){                          //Making sure the node had the service time of 50us
                        temp = denenqueue(q);
                        ltime=0;
                    }
                    else{                                  //If the task already used some time before
                        ltime=50-quantum;
                    }
                    quantum = 0;t += 50;
                    if(t%200==0){                          //Loop to add appropriate number of tasks at respected time
                        int num = 64;
                        int m = t/200;
                        for(int i=1;i<m;i++){
                            num = num/2;
                        }
                        if(num>0){
                            extend_queue(q,num);
                        }
                    }
                    printf("The queue at t=%d :\n",t);    //Prints the queue after the time quantum
                    print_queue(q);
                    }
                else if(temp->p_time==quantum){            //Process time is as required as time quantum
                    stime=0;
                    temp->p_time = temp->p_time - quantum;
                    stime = quantum;
                    temp = temp->link;                    //Dequeueing the element
                    if(stime==50||ltime==50){
                        ltime=0;
                    }
                   else{
                        ltime = 50-quantum;                //Last time, used time
                    }
                    dequeue(q);
                    quantum = 0;t += 50;
                    if(t%200==0){                           //Loop to add appropriate number of tasks at respected time
                        int num = 64;
                        int m = t/200;
                        for(int i=1;i<m;i++){
                            num = num/2;
                        }
                        if(num>0){
                            extend_queue(q,num);
                        }
                    }
                    printf("The queue at t=%d :\n",t);
                    print_queue(q);
                    }
                else{                                               //When the quantum is larger than the time required
                    quantum = quantum - temp->p_time;               //Deducting the quantum size as required
                    temp = temp->link;                              //Dequeueing the element
                    dequeue(q);
                    }
                if(temp==NULL){
                    printf("The queue at t=%d :\n",t+50);
                    printf("The queue is empty now.\n");
                    }
                }
            else{                                                    //When the task already has used time before
                if(temp->p_time > ltime){                            //Time required is still greater than the time available
                    temp->p_time = temp->p_time - ltime;
                    quantum = quantum-ltime;                         //Updating the quantum size after use
                    temp = denenqueue(q);                            //De-list and En-list
                    ltime=0;
                    }
                else if(temp->p_time==ltime){                        //When the task required is equal to the time available
                    temp->p_time = temp->p_time - ltime;
                    temp = temp->link;
                    dequeue(q);                                      //Dequeue it
                    quantum=quantum-ltime;                           //Updating the quantum size after use
                    ltime = 0;
                    }
                else{                                                //When the task required is less than the time available
                    quantum = quantum - temp->p_time;                //Updating the quantum size after use
                    temp = temp->link;
                    dequeue(q);                                      //Dequeue it
                    ltime=0;
                    }
                if(temp==NULL){                                       //When  the queue has reached the end
                    printf("The queue at t=%d :\n",t+50);
                    printf("The queue is empty now.\n");
                    }
            }

			}
		}
    printf("Total time taken in the process : %d\n",total_time);    //Total process time "which matches"
	}
