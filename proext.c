#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_VERTICES 10000
#define MAX_EDGES 3000
#define MAX_TIME 300

typedef unsigned int vertex; //Represents the vertex or a person
//structure for the event i.e transmission or recovery in the priority queue
struct event{
    int prior_time;//Time of happening of the event
    char task;//Action to be done: 't' for transmit,'r' for recovery
    int person;//The individual the task is assigned to
    struct event*next;//Link for the next event
};
//The structure for node representing a person in the SIR list
struct dot{
    int index;//Individuals identity
    char status;//Whether susceptible,infected or recovered
    struct dot*next;//Link for the next dot
};
//Structure of the of the node for identification of list(S,I,R)
struct list{
    struct dot*head;//The head of the list
};
//Structure for a node in adjancy matrix
struct node{
    int individual;//Individuals identity
    struct node*right;//Connection for the row
    struct node*down;//Connection for the column
};


//Utility functions used in creation of adjancy matrix
//Function used for creating a new node in the matrix
struct node*new_node(int individual){
    struct node*temp = NULL;//Allocation of required memory
    temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL){
        printf("Could not allocate memory for nodes\n");
        exit(1);
    }
    temp->individual=individual;//Initiating the parameters
    temp->right=NULL;temp->down=NULL;
    return(temp);//Returns the address
}
//Function for creating the matrix of size of given rows and columns
struct node*create_matrix(int rows,int columns){
    int m=0,n=0;//Variables to keep track of rows and columns
    struct node*head=new_node(0);//Creation of the head node
    struct node*prow=NULL,*row=head,*counter=NULL;//Variable pointers used in linking of the matrix
    for(m=0;m<rows;m++){//For creating rows
        for(n=1;n<columns;n++){//for creating columns
            row->right=new_node(0);
            if(prow!=NULL){//keeping track of previous row for linking
                prow->down = row->right;//linking between consecutive rows
                prow = prow->right;//Updating to next column
            }
            row = row->right;//moving towards right for columns
        }
        if(m==0){//For the first row
            prow = head->right;//Previous row tracker
            counter = new_node(0);//New node i.e. first node in a new row
            head->down =counter;//Linking with in the first column
            row = counter;//for the new row
        }
        else{
            prow = counter;//Previous row tracker
            counter = new_node(0);//First node of the next node
            if(m!=rows-1){
                prow->down = counter;//Linking with in the column
                row = counter;
                prow = prow->right;
            }
        }
    }
    return(head);//returning the head node address
}
//Function for printing the matrix
void printMatrix(struct node*head){
    struct node*r=NULL,*c=NULL;//pointers keeping track of rows and columns
    r=head;c=head;
    while(r!=NULL){//print all rows
        while(c!=NULL){//print all columns
           printf("%d ",c->individual);
           c = c->right;
        }
        printf("\n");
        r = r->down;
        c = r;
    }
    printf("\n");
}
//Function to indicate the link between two individuals
void activate(struct node*head,int r,int c){//the r and c persons are connected
    struct node* temp = NULL,*temp1=NULL;temp=head;temp1=head;//pointers for navigation of a node
    for(int i=0;i<c;i++){//Reaching the correct row
        temp = temp->right;
    }
    for(int j=0;j<r;j++){//Reaching the correct column
        temp = temp->down;
    }
    temp->individual=1;//Making the link active
    for(int i=0;i<r;i++){//Similarly connecting c and r
        temp1 = temp1->right;
    }
    for(int j=0;j<c;j++){
        temp1 = temp1->down;
    }
    temp1->individual=1;//Results in a symmetric matrix
}
//Function to navigate to the required node
struct node*navigate(struct node*head,int p){
    struct node*temp=NULL;temp=head;
    for(int i=0;i<p;i++){//Move to the required node
        temp = temp->down;
    }
    return(temp);//returning the required node
}

//Function to tell how many links does a node have
int edgesOfNode(struct node*head,int index){
    struct node*temp = head;int b=0;
    for(int i=0;i<index;i++){//Reaching the required individual
        temp = temp->down;
    }
    while(temp!=NULL){//Counting the edges its connected
        if(temp->individual!=0)//If theres an edge increment the counter
            b++;
        temp = temp->right;//Travel through the row
    }
    //printf("%d\n",b);
    return(b);//Returns the number of links for the particular node
}


//Utility functions used in maintaining the SIR lists
//Creation of individual in the list
struct dot*new_dot(int index,char s){//Creating the new dot .i.e individual
    struct dot*temp=NULL;//Allocation of required memory
    temp = (struct dot*)malloc(sizeof(struct dot));
    temp->index = index;//Initiating the parameters
    temp->status = s;
    return(temp);//Returning the dots address
}
//Adding l new elements to the list
struct dot*enqueList(int l,char stat){
    int i=0;struct dot*head=NULL,*temp=NULL;
    while(i<l){
        if(i==0){//For the first node
            head = new_dot(i,stat);//Assigning the head
            temp = head;//for continuing the queue
        }
        else{
            temp->next=new_dot(i,stat);//Adding the new elements to the queue
            temp = temp->next;
        }
        i++;
    }
    return(head);//Returning the head of the list
}
//Function used find the address of the given individual
struct dot*find_dot(struct dot*head,int i){
    struct dot*temp=head;
    while(temp!=NULL){
        if(temp->index!=i)
            temp = temp->next;
        else{
            break;
        }
    }
    if(temp!=NULL){
        //printf("F\n");
        return(temp);
    }
    else{
       // printf("N\n");
        return(NULL);
    }
}
//Function to find the address of the parent of required node
struct dot*find_dotParent(struct dot*head,int i){
    if(head->index==i){//for the case where the head is required node
        return(0);
    }
    else{
        struct dot*temp=head;
        while(temp->next!=NULL){//searching for the parent in the list
            if(temp->next->index!=i){
                temp = temp->next;
            }
            else{
                return(temp);
            }
        }
        if(temp->next==NULL){//if the required node is not present
            return(0);
        }
    }
}
//function to remove the require node from the list
struct dot*removeFromList(struct dot*head,int i){
    struct dot* temp=NULL,*parent=NULL;//Required node and its parent pointers
    if(head->index==i){//For the case where the head node has to be deleted
        temp=head;
        if(head->next==NULL){//Empty queue
            free(temp);
            return(0);
        }
        else{//Updating the head
            head = head->next;
            temp->next=NULL;
            free(temp);//Deleting the node
            return(head);//Returning the address of the new head
        }
    }
    else{//For node in the queue but is not the head
        parent = find_dotParent(head,i);//Finding the parent of node required
        temp = parent->next;//Required node
        parent->next = temp->next;//Connecting the parent to the temps next
        temp->next=NULL;
        free(temp);//deleting the node
        return(head);//returning the new node
    }
}
//Function for removing the node from one list to other
void move(struct dot**head1,struct dot**head2,int i,char updated_stat){
    *head1 = removeFromList(*head1,i);//Deleting the node from the list
    struct dot*temp = new_dot(i,updated_stat);//Creating a new node that has same params as the deleted one with updated status
    struct dot*t= *head2;//Joining the node in the new list
    if(t==NULL){
        *head2=temp;
    }
    else{
        while(t->next!=NULL){//Travel to end of the list
            t = t->next;
        }
        t->next = temp;//attached
    }
}

//Function used in printing the list
void printList(struct dot*head){
    struct dot*temp=head;
    if(head==NULL){
        printf("Empty");
    }
    while(temp!=NULL){//print the entire list
        printf("%d,",temp->index);
        temp = temp->next;//traversing the list
    }
    printf("\n");
}
//Function for finding the length of the list
int length(struct dot*head){
    if(head==NULL){//Empty list
        return(0);
    }
    else{
        struct dot*temp=head;int l=0;
        while(temp!=NULL){//Traversing the entire list
            l++;
            temp = temp->next;
        }
        return(l);
    }
}

//Utility functions used in the priority queue
//Function for creating a new event
struct event*new_event(int time,char task,int person){
    struct event*temp=NULL;//Allocating the memory
    temp=(struct event*)malloc(sizeof(struct event));
    temp->prior_time = time;//Initiating the parameters
    temp->task = task;
    temp->person = person;
    temp->next=NULL;
}
//Functions used to know the the prior task
int peek(struct event*head){
    if(head!=NULL){
        return(head->prior_time);//returns the time of occurrence of the event
    }
    else{
        return(-1);
    }
}
char peek_task(struct event*head){
    if(head!=NULL){
        return(head->task);//returns the task of the event earliest
    }
    else{
        return('.');
    }
}
int peek_person(struct event*head){
    if(head!=NULL){
        return(head->person);//returns the person affected of the event earliest
    }
    else{
        return(-1);
    }
}
//Function used in popping the topmost event
struct event*pop(struct event*head){
    if(head!=NULL){
        struct event*temp =head;//Finding the top most task
        head = head->next;//updating the task
        temp->next=NULL;
        free(temp);//deleting the event
        if(head!=NULL)
            return(head);
        else{
            //printf("Queue is empty after one event left\n");
            return(NULL);
        }
    }
    else{
        printf("Queue is empty\n");
        return(NULL);
    }
}
//Function to insert the new task in the priority list
struct event*push(struct event*head,int time,char task,int person){
    struct event*start = head;
    struct event*temp=new_event(time,task,person);//New event
    if(head==NULL){//IMPLEMENT THE PRIORITY QUEUE
        head = temp;//First node
        return(head);
    }
    else{
        if(head->prior_time > temp->prior_time){//If the new event is of more priority
            temp->next = head;
            head = temp;
        }
        else{//Searching appropriate place for the task according to the priority of task
            while (start->next != NULL) {
                if(start->next->prior_time < temp->prior_time)
                    start = start->next;
                else
                    break;
            }
            temp->next = start->next;//Connecting the queue
            start->next = temp;
        }
        return(head);//Returning the head
    }
}
//Function for prediction of time of recovery
int pred_time_recovery(){
    int d = 1;// gamma = 0.2
    srand(time(NULL));
    while(rand()%5!=0){//it will be divisible with probability of 0.2=1/5
        d++;
    }
    return(d);
}
//Function for prediction of time of transmission
int pred_time_transmission(){
    int d=1;// tau = 0.5
    srand(time(NULL));
    while(rand()%2!=0){//it will be divisible by two with probability oh 0.5=1/2
        d++;
    }
    return(d);
}
//Process of transmission
void process_trans_SIR(int n,struct dot**S,struct dot**I,struct node*head,struct event**PQ,int time){
    struct dot*s=*S;struct dot*i=*I;//The pointers of the S(susceptible) and I(infected) list
    struct dot*v = find_dot(s,n);//Finding the dot in the S list
    if(v!=NULL){//If the person is susceptible
        move(S,I,n,'i');//Move the node from the S list to I list
        int rd = pred_time_recovery();//Probabilistic time of recovery
        *PQ = push(*PQ,time+rd,'r',n);//Pushing the recovery event for the node
        //printf("Event to recover created at %d for %d\n",time+rd,n);
        struct node*t=navigate(head,n);//Pointers for referring the adjancy matrix
        int p=0;//keep track of neighbors
        while(t!=NULL){//Checking all the neighbors of the dots
            if(t->individual==1){//It is a neighbor
                //printf("neighbor-%d\n",p);
                struct dot*dot=NULL;
                dot=find_dot(*S,p);//Finding whether that dot is susceptible
                if(dot!=NULL){//It is susceptible
                    //printf("In the susceptible list\n");
                    int ntime = 0;
                    //ntime=pred_time_transmission();//Predicting the time it gets infected
                    int d=1;// tau = 0.5
                    while(rand()%2!=0){//it will be divisible by two with probability oh 0.5=1/2
                        d++;
                    }
                    ntime=d;
                    ntime += time;
                    *PQ = push(*PQ,ntime,'t',p);//Pushing the event of it get infected
                    //printf("Event to transmit created at %d for %d\n",ntime,p);
                }
                else{
                    //printf("hi\n");
                }
            }
            p++;//traversing the complete graph
            t = t->right;
        }
    }
}
//Process of recovery
void process_rec_SIR(int n,struct dot**I,struct dot**R){
    struct dot*i=*I;struct dot*r=*R;
    struct dot*v=find_dot(i,n);//The dot is infected
    if(v!=NULL){
        move(I,R,n,'r');//Move the dot to recovered list
    }
}


int main(){
    FILE*fp;fp=fopen("data.txt","w");
    struct node*adj_mat=NULL;int e=0,f=0;
    /*number of nodes in a graph*/
    srand ( time(NULL) );
    int numberOfVertices = rand() % MAX_VERTICES;

    /*number of maximum edges a vertex can have*/
    srand ( time(NULL) );
    int maxNumberOfEdges = rand() % MAX_EDGES;
    /*graphs is 2 dimensional array of pointers*/
    if( numberOfVertices == 0)
        numberOfVertices++;
    vertex ***graph;
    printf("Total Vertices = %d, Max # of Edges = %d\n",numberOfVertices, maxNumberOfEdges);
    adj_mat=create_matrix(numberOfVertices,numberOfVertices);//Creating matrix of proper size

    /*generate a dynamic array of random size*/
    if ((graph = (vertex ***) malloc(sizeof(vertex **) * numberOfVertices)) == NULL){
        printf("Could not allocate memory for graph\n");
        exit(1);
    }

    /*generate space for edges*/
    int vertexCounter = 0;
    /*generate space for vertices*/
    int edgeCounter = 0;

    for (vertexCounter = 0; vertexCounter < numberOfVertices; vertexCounter++){
        if ((graph[vertexCounter] = (vertex **) malloc(sizeof(vertex *) * maxNumberOfEdges)) == NULL){
            printf("Could not allocate memory for edges\n");
            exit(1);
        }
        for (edgeCounter = 0; edgeCounter < maxNumberOfEdges; edgeCounter++){
            if ((graph[vertexCounter][edgeCounter] = (vertex *) malloc(sizeof(vertex))) == NULL){
                printf("Could not allocate memory for vertex\n");
                exit(1);
            }
        }
    }

    /*start linking the graph. All vetrices need not have same number of links*/
    vertexCounter = 0;edgeCounter = 0;
    for (vertexCounter = 0; vertexCounter < numberOfVertices; vertexCounter++){
        printf("%d:\t",vertexCounter);
        for (edgeCounter=0; edgeCounter < maxNumberOfEdges; edgeCounter++){
            if (rand()%2 == 1){ /*link the vertices*/
                int linkedVertex = rand() % numberOfVertices;
                int b=0;//Ensuring that the link is not already made before
                for(int i=0;i<maxNumberOfEdges;i++){
                    if(graph[vertexCounter][i]!=linkedVertex)
                        b++;
                }
                //Ensuring the links for a node does not exceed the max number of edges
                e = edgesOfNode(adj_mat,vertexCounter);f = edgesOfNode(adj_mat,linkedVertex);
                if(linkedVertex!=vertexCounter && b==maxNumberOfEdges && e<maxNumberOfEdges && f<maxNumberOfEdges){
                    graph[vertexCounter][edgeCounter] = linkedVertex;
                    activate(adj_mat,vertexCounter,linkedVertex);
                    printf("%d, ", linkedVertex);
                }
                else{ /*make the link NULL*/
                    graph[vertexCounter][edgeCounter] = NULL;
                }

            }
            else{ /*make the link NULL*/
                graph[vertexCounter][edgeCounter] = NULL;
            }
        }
        printf("\n");
    }
    printf("\n\n");
    printMatrix(adj_mat);
    //The process of simulation
    struct event*Q=NULL;//Priority queue
    struct dot*S=NULL,*I=NULL,*R=NULL;//S,I,R lists
    S = enqueList(numberOfVertices,'s');//Making all persons susceptible
    int t=1;Q=push(Q,2,'t',0);
    while(t<=MAX_TIME){//Simulation lasts until Q ends or Time max has reached
        while(Q!=NULL){
            int p = peek(Q);//Priority time of the earliest event
            if(t==p){
                char e = Q->task;//Event task
                int p = Q->person;//Affected person
                if(e=='t'){//Event is transmission
                    srand(time(0));
                    process_trans_SIR(p,&S,&I,adj_mat,&Q,t);
                }
                else if(e=='r'){//Event is recovery
                    process_rec_SIR(p,&I,&R);
                }
                else{
                    printf("Unidentified event.\n");
                }
                Q=pop(Q);//Event popped out
            }
            else{
                break;
            }
        }
	//Print the SIR list
        printf("At time : %d\n",t);
        printf("S-List : ");printList(S);
        printf("I-List : ");printList(I);
        printf("R-List : ");printList(R);
        int ns=0,ni=0,nr=0;
        ns=length(S);ni=length(I);nr=length(R);
        fprintf(fp,"%d,%d,%d,%d\n",t,ns,ni,nr);
        t++;
    }
    /*printf("At time : %d\n",t);
    printf("S-List : ");printList(S);
    printf("I-List : ");printList(I);
    printf("R-List : ");printList(R);
    Q=pop(Q);*/
    return 0;
}
