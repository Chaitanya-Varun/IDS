#include<stdio.h>
#include<stdlib.h>

////Structure of node or nucleotide cell
struct node{
	char mol;
	struct node* next;
	struct node* link;
	};
////Structure of cell for storing addresses of DNA molecule
struct list{
	struct node* id;
	struct list *next;};
	
	
////Declaration of variables used in programme
struct node* newnode=NULL;
struct list* root=NULL;   //For storing the main chain of DNAs addresses 
int s=1;                   //For keeping track of number of DNA molecules created 
struct list* m=NULL;struct list* m1=NULL;struct list* m2=NULL;//For traversing with in the lists
//Function for creating DNA molecule
struct node* createDNA(){
	struct list* tag=NULL;     //Temporary list which stores the address of the newly creating DNA molecule
	tag=(struct list*)malloc(sizeof(struct list)); //Memory allocation for tag
	int i;char n;
	printf("\nMolecule-%d:\n",s);
	printf("Enter the number of nucleotides :");
	scanf("%d",&i);
	struct node* head=NULL;
	struct node* temp=NULL;
	struct node* temp2=NULL;
	struct node*  a =NULL;        //For keeping track of nucleotides created in alpha chain
	struct node*  b =NULL;        //For keeping track of nucleotides created in beta chain
	int j=0;
		while(j< i){
			temp=(struct node*)malloc(sizeof(struct node));  //Memory for the new upper node
			temp2=(struct node*)malloc(sizeof(struct node)); //Memory for the new lower node
			printf("\nEnter the Nucleotide :");
			scanf("\n%c",&n);
			if((n!= 'A')&&(n!= 'T')&&(n!= 'G')&&(n!= 'C'))
				printf("\nInvalid Nucleotide.\n");
			else{
				 temp -> mol =n;                     //Taking the input into temp(upper node)
				 temp -> link =temp2;                //Linking the alpha and 
				 temp2 -> link =temp;                //beta chains
				 if(temp -> mol =='A')               //Giving the data into lower node based on the upper node
					temp2 ->mol = 'T';
		    	 else if(temp -> mol =='T')
					temp2 ->mol = 'A';
			     else if(temp -> mol =='G')
					temp2 ->mol = 'C';
				 else if(temp -> mol =='C')
					temp2 ->mol = 'G';
				if(head==NULL){                     //The first node/nucleotide creation
					head=temp;			            //Making the temp as the first node
					a=head;
					b= temp -> link;
					}
				else{
					a->next=temp;                   //Attaching the new node to the last list in the alpha chain
					a =a->next;                     //Traversing to the new node in alpha chain
					b-> next = temp2;               //Attaching the new node to the last list in the beta chain
					b = b->next;                    //Traversing to the new node in beta chain
					}
					j++;
					}
			 }
        printf("\nDNA molecule created as Molecule-%d.\n",s);
        tag->id=head;                              //Storing the head of the new DNA mole in the list
		if(s==1){
			root=tag;                              //For the first address in the list
			tag->next=NULL;
			m=root;
				}
		else{
			m->next=tag;                            //For adding the address in the list
			m=m->next;}
		s++;
        
        return(head);                              //Returns the head of the DNA molecule
	}
////The function for printing the given DNA molecule
void printDNA(struct node* head){
	struct node*temp=NULL;
	struct node*temp2=NULL;
	temp=head;                                     //Using the temporary node for printing the nucleotide in alpha chain
	temp2=temp->link;                              //Using the temporary node for printing the nucleotide in beta chain
	if(head==NULL){                                //Incase of empty molecule 
		printf("Empty DNA chain.\n");}
	else{
		while(temp!=NULL){                         //Until it reaches the last node in alpha chain
			printf("%c--",temp->mol);              
			temp=temp->next;
			}
		temp=head;
		printf("\n");
		while(temp!=NULL){                         //For making the links                        
			printf("|  ");
			temp=temp->next;
			}
		printf("\n");
		while(temp2!=NULL){                        //Until it reaches the last node in beta chain
			printf("%c--",temp2->mol);             //printing the character stored in it
			temp2=temp2->next;
			}
		printf("\n");		
		}
		}
////Function for finding how many nodes are there in the list	
int length(struct node*head){
	int i=0;
	struct node*temp=NULL;                        //Temporary struct node pointer used in travelling the alpha chain
	temp=head;
	while(temp!=NULL){
		temp=temp->next;
		i++;}                                     //Appending i to get catch of count
	return(i);
	}	
////Function for finding how many DNA molecules addresses are stored in the list
int lengthList(struct list*root)
{
	struct list* tag =NULL;int i=0;               //Temporary struct list pointer used in traversing in linked list
	tag =root;
	while(tag->next !=NULL){
		tag=tag->next;
		i++;                                      //Appending i to get catch of count
		}
	return(i+1);
	}
	
void insert(struct node*head,int j,char n,int pos){
	struct node*temp =NULL;                                  //For the new node in alpha chain
	struct node*temp2=NULL;                                  //For the new node in beta chain
	struct node*a=NULL;                                      //For traversing along the given DNA molecule in alpha chain
	struct node*b=NULL; 
	struct list*newroot=NULL;                                     //For traversing along the given DNA molecule in alpha chain
	a=head;
	b=head->link;
	temp =(struct node*)malloc(sizeof(struct node));          //Allocate memory for the new node in alpha chain
	temp2 =(struct node*)malloc(sizeof(struct node));         //Allocate memory for the new node in beta chain
	if(pos > length(head)+1)
		printf("\nInvalid Insertion");                        //Check for valid insertion
	temp->link=temp2;                                         //Making the link between the the new nodes
	temp2->link=temp;
	if(j==1){                                                 //Naming of nucleotides based on one input
		temp->mol = n;
		if(temp -> mol =='A')
					temp2 ->mol = 'T';
		else if(temp -> mol =='T')
					temp2 ->mol = 'A';
		else if(temp -> mol =='G')
					temp2 ->mol = 'C';
		else if(temp -> mol =='C')
					temp2 ->mol = 'G';
			
			}
	else if(j==2){
		temp2->mol=n;
		if(temp2 -> mol =='A')
				temp ->mol = 'T';
		else if(temp2 -> mol =='T')
				temp ->mol = 'A';
		else if(temp2-> mol =='G')
				temp ->mol = 'C';
		else if(temp2 -> mol =='C')
				temp ->mol = 'G';
		
		}
	if(pos==1 && head ==NULL){                                 //For the first element making the temp as head and head list is empty
			head = temp;
			newroot=(struct list*)malloc(sizeof(struct list));
			newroot->id = head;
			newroot->next=root->next;
			//printf("Working\n");
			root = newroot;
			}
	else if(pos==1 && head != NULL){                           //For the first element making the temp as head and head list is non-empty
			temp->next=head;
			head =temp;
			temp2->next= temp->next->link;
			newroot=(struct list*)malloc(sizeof(struct list));
			newroot->id = head;
			newroot->next=root->next;
			//printf("Working\n");	
			root = newroot;		
			}
	else{
		for(int i=1;i< pos-1;i++){                             //For traversing to the right position to be inserted
				a=a->next;
				b=b->next;
				}
	    temp->next = a->next;                                  //Making the links established in alpha chain
		a->next=temp;
		temp2->next = b->next;                                 //Making the links established in beta chain
		b->next=temp2;
				}
	//~ if(pos==1)
		  //~ printDNA(head);
	}

////Function for deletion of a node/nucleotide
struct node* delete(struct node*head,int pos){
	struct node*temp=NULL;                      //For traversing the alpha chain
	struct node*temp2=NULL;                     //For traversing the beta chain
	struct node*a=NULL;                         //For traversing the alpha chain but staying one node behind
	struct node*b=NULL;                         //For traversing the beta chain but staying one node behind
	if(pos>length(head))                        //Check for valid deletion
		printf("\nInvalid deletion.");
	else if(pos==1){                            //First node is to be deleted
		temp=head;
		temp2=temp->link;
		head =temp->next;                       //Making the head go to the next  node of the chain
		temp->next = NULL;                      //Making the first node in alpha chain free from all connections
		temp2->next =NULL;                       //Making the first node in alpha chain free from all connections
		temp->link=NULL;
		temp2->link=NULL;
		free(temp);                             //Making free the memory allocated to the nodes
		free(temp2);
		//printDNA(head);
		}
	else{
		temp=head;
		a=head;
		temp2 =temp->link;
		b=temp->link;
		for(int i=1;i<pos;i++){                 //Going to the position to be deleted
			temp=temp->next;
			temp2=temp2->next;
			}
		for(int i=1;i<pos-1;i++){               //Going to the position one node before to that to be deleted
			a=a->next;
			b=b->next;
			}
		a->next= temp->next;                    //Making the connection in list and removing itself between the list
		temp->next =NULL;	                    //Making the connection free from chain
		b->next = temp2->next;
		temp2->next = NULL;
		temp->link=NULL;                        //Making all links clear
		temp2->link=NULL;
		free(temp);                             //Freeing the memory allocated to them
		free(temp2);			
		}
		return(head);
		}
////Function for splitting the DNA molecule
void splitDNA(struct node*head){
	struct list* tag=NULL;                         //Temporary list which stores the address of the newly creating DNA molecule
	tag=(struct list*)malloc(sizeof(struct list)); //Memory allocation for tag
	struct node* a=NULL,*b=NULL,*c=NULL,*d=NULL;   
	a=head;b=head->link;
	while(a!=NULL){
		struct node* temp=NULL,*temp2=NULL;
		temp=(struct node*)malloc(sizeof(struct node)); //Allocating memory for the new nodes
		temp2=(struct node*)malloc(sizeof(struct node));
		temp2->link=b;                                  //Assignining the vertical links
		b->link=temp2;
		temp->link=a;            
		a->link=temp;
		if(a==head){                                    //Getting the required nucleotide based on the the given chain
			if(a->mol =='A')
					temp ->mol = 'T';
			else if(a -> mol =='T')
					temp ->mol = 'A';
			else if(a -> mol =='G')
					temp ->mol = 'C';
			else if(a -> mol =='C')
					temp ->mol = 'G';
			if(b -> mol =='A')
					temp2 ->mol = 'T';
			else if(b -> mol =='T')
					temp2 ->mol = 'A';
			else if(b -> mol =='G')
					temp2 ->mol = 'C';
			else if(b -> mol =='C')
					temp2 ->mol = 'G';
			c = temp;		
			d = temp2;
			tag->id=temp2;                              //Storing the head of the new DNA mole in the list
			if(s==1){
				root=tag;                              //For the first address in the list
				tag->next=NULL;
				m=root;
					}
			else{
				m->next=tag;                            //For adding the address in the list
				m=m->next;}
			s++;
			
			}
		else{                                          //Getting the required nucleotide based on the the given chain
			if(a -> mol =='A')
					temp ->mol = 'T';
			else if(a -> mol =='T')
					temp ->mol = 'A';
			else if(a -> mol =='G')
					temp ->mol = 'C';
			else if(a -> mol =='C')
					temp ->mol = 'G';
			if(b -> mol =='A')
					temp2 ->mol = 'T';
			else if(b -> mol =='T')
					temp2 ->mol = 'A';
			else if(b -> mol =='G')
					temp2 ->mol = 'C';
			else if(b -> mol =='C')
					temp2 ->mol = 'G';
				}
		c->next=temp;                                     //Making the horizontal links in the new chains
		d->next=temp2;
		c=temp;                                           //Traversing in new list
		d=temp2;
		a=a->next;                                        //Traversing in the given list
		b=b->next;
		}

	printf("New DNA from the split is given as Molecule-%d\n",s-1);
}	
void printallDNA(){
	struct list* chain=NULL;
	chain=root;                                                //Getting to the starting of the chain
	if(root==NULL){
		printf("No Molecule has been created yet.\n");}
	else{
		printf("Molecule-1\n");                                //Printing of the First chain
		printDNA(chain->id);
		for(int j=1;j<lengthList(root);j++){                   //Printing the rest chains
			printf("Molecule - %d\n",j+1);
			chain=chain->next;
			printDNA(chain->id);
			}
		printf("\n");
		}
		}

int main(){
	char o;int n;struct list* chain=NULL;struct node*head=NULL;int c;int pos=0;char new;
	printf("Welcome!\nPress which operation you want to do (Make sure you first create a DNA chain)\n");
	do{
	printf("(a)Create a DNA molecule\n(b)Insert a molecue in main DNA chains \n(c)Delete a Molecule in  DNA chains\n(d)Split the DNA molecule\n(e)Print DNA chain\n(f)Print all  DNA Chains\n(g)Exit \n");
	scanf(" %c",&o);
      
    if(o=='a'){
		createDNA();}
	else if(o=='b'){
		printf("Enter in which DNA molecule you want to insert :\n" );
		scanf("%d",&n);
		chain=root;
		for(int j=1;j<n;j++){
			chain=chain->next;
			}
		head= chain->id;
		printf("Enter the chain in which  has to insert (For alpha-press 1 and beta-press 2):\n");
		scanf("%d",&c);
		printf("Enter in which position you want to enter:\n");
		scanf("%d",&pos);
		printf("Enter the nucleotide you want to insert :\n");
		scanf(" %c",&new);
		insert(head,c,new,pos);
		printf("Inserted successfully\n");
		}
	else if(o=='c'){
		printf("Enter in which DNA molecule you want to delete :\n" );
		scanf("%d",&n);
		chain=root;
		for(int j=1;j<n;j++){
			chain=chain->next;
			}
		head= chain->id;
		printf("In which position of the node do you want to delete :\n");
		scanf("%d",&pos);
		chain->id=delete(head,pos);	
		printf("Deleted succesfully.\n");
		}
	else if(o=='e'){
		printf("Enter molecule number whose DNA chain has to be printed :\n");
		scanf("%d",&n);
		chain=root;
		for(int j=1;j<n;j++){
			chain=chain->next;
			}
		head= chain->id;
		printDNA(head);
		}
	else if(o=='f'){
		printallDNA();

		}
	else if(o=='d'){
		printf("Enter the DNA molecule number to be split :\n");
		scanf("%d",&n);
		chain=root;
		for(int j=1;j<n;j++){
			chain=chain->next;
			}
		head= chain->id;
		splitDNA(head);
		}

		}while(o!='g');    
	}