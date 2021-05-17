#include<stdio.h>
#include<stdlib.h>
//Structure of a element in the matrix
struct node{
	int val;                                             //value of the element
	struct node* right;                                  //Address of the next element in row
	struct node* down;                                   //Address of the next element in column
	};


//Reading matrix from the given file
struct node* ReadMatrix(FILE*fp){
	int c=0,data=0;struct node*head=NULL;struct node*temp=NULL;struct node*row=NULL,*column=NULL,*pcolumn=NULL,*prow=NULL;  //Variables used in the function
	
	while((c!=-1)&&(c!='\n')){                            //checking the end of file
		c=fgetc(fp);                                      //reads the character
		if(c==-1||c=='\n')                                //when the end of matrix reading is done , returns the matrix head
			return(head);
		else if(c!=';'&&c!=','){                          //When the character read is integer
			ungetc(c,fp);                                 //goes back putting the read integer back and making the pointer to point to it
			fscanf(fp,"%d",&data);                        //storing the data temporarily
			if(head!=NULL){                               
				temp->val=data;                           //Assigning the stored data to the new node created
				if(prow!=NULL){                           //To link between the rows
					prow->down=row;}
				}
			}
		else if(c==','){                                    //When the character is in comma the next integer goes to the next row
			temp=(struct node*)malloc(sizeof(struct node)); //creating a new node
			temp->down=NULL;
			temp->right=NULL;
			row->right=temp;                                 //linking along the row
			row=row->right;
			if(prow!=NULL){                                  //for corresponding linking between rows 
				prow=prow->right;}
			}
			
		else if(c==';'){                                   //when this character occurs the matrix has got new row
			temp=(struct node*)malloc(sizeof(struct node));//Creating the node 
			temp->down=NULL;
			temp->right=NULL;
			pcolumn=column;                                //to keep track the previous column
			prow=pcolumn;                                  //to keep track of the node in previous row to be linked with present row
			column->down=temp;
			column=column->down;
			row=column;                                    //travelling in the new row
			
			}
			
		if(head==NULL){                                     //for the creation of first node
			temp=(struct node*)malloc(sizeof(struct node)); //create node
			temp->down=NULL;
			temp->right=NULL;
			temp->val=data;                                 //Assigning the data stored into the node    
			head=temp;
			row=head;column=head;                           //Initialising the row and column variables to travel
			}
			
		}
		return(head);                                       //gives back the head
	}
//Function for printing a selected matrix	
void printMatrix(struct node*head){                         
	struct node*row=NULL,*column=NULL;
	column=head;
	while(column!=NULL){                                     //For covering all the rows
		row=column;                                        
		while(row!=NULL){                                    //for covering all the columns
			printf("%d \t",row->val);
			row=row->right;
			}
		printf("\n");
		column=column->down;
			}
	}
//Function to find the number of columns in a matrix	
int ColumnsinMatrix(struct node*head){                       
	struct node*temp=NULL;int i=0;
	temp=head;
	while(temp!=NULL){                                       //Count of i tells the number of nodes in the row which is number of columns
		i++;
		temp=temp->right;}                                   //traversing the row
	//printf("Columns=%d\n",i);
	return(i);
	}
//Function to find the number of rows in a matrix	
int RowsinMatrix(struct node*head){
	struct node*temp=NULL;int i=0;
	temp=head;
	while(temp!=NULL){
		i++;                                                  //Count of i tells the number of nodes in the column which is number of rows
		temp=temp->down;}
	//printf("Rows=%d\n",i);
	return(i);
	}
//Function to check whether the matrix is square or not	
int Squaritycheck(struct node* head){
	int r=0,c=0,s=0;
	r=RowsinMatrix(head);
	c=ColumnsinMatrix(head);
	if(r==c){                                                //In square matrix number of rows and columns are equal
		printf("The matrix is square matrix.\n");
		s=1;}
	else if(r<c){
		printf("The matrix is fat rectangular matrix.\n");
		s=0;}
	else if(r>c){
		printf("The matrix is tall rectangular matrix.\n");
		s=0;}
	return(s);
		}
//Function to check whether the given matrix is symmetric		
void Symmetrycheck(struct node* head){    
	int i=0,j=0;struct node*row=NULL,*column=NULL,*prow=NULL,*pcolumn=NULL;
	i =Squaritycheck(head);                                 //For matrix to be symmetric it has to be square
	if(i!=1){
		printf("As the matrix is not square matrix it cannot be symmetric.\n");
		}
	else{
		row=head;column=head;prow=head;pcolumn=head;
		while(prow!=NULL){                                   //For keeping the track of rows in matrix and travel all columns
			row=prow;column=pcolumn;
			while(row!=NULL){                                //traversing in a row
				if(row->val==column->val){
					j=0;                                     //if the values of the ith row and ith column are equal
					//printf("%d=%d\n",row->val,column->val);
					row=row->right;
					column=column->down;
					}
				else if(row->val!=column->val){              //if the values of the ith row and ith column are equal       
					printf("Matrix is not symmetric.\n");
					//printf("%d not equal to %d",row->val,column->val);
					j=1;
					break;}
					}
		if(j==0){                                           //Going to verify the next row and next column
				prow=prow->down;
				pcolumn=pcolumn->right;
						}
		else
			break;
		}
		if(j==0)
			printf("Matrix is symmetric.\n");
		
	}
 }
//Function which tells the inner product of two vectors namely row and column 
int InnerProduct(struct node*row,struct node*column){
	struct node*temp1=NULL,*temp2=NULL;int i=0;
	temp1=row;temp2=column;
	while(temp1!=NULL){
		i += (temp1->val)*(temp2->val);                      //Defining the dot product of vectors
		temp1=temp1->right;
		temp2=temp2->down;}
	//printf("%d\n",i);
	return(i);
		}
//Function which does multiplication of two matrices 
struct node* Matrixmultiplication(struct node*head1,struct node*head2){
	 struct node*a=NULL,*b=NULL,*temp1=NULL,*temp2=NULL,*newnode=NULL,*row=NULL,*column=NULL,*head=NULL,*prow=NULL,*pcolumn=NULL;
	 a=head1;b=head2;
	 if(ColumnsinMatrix(head1)!=RowsinMatrix(head2))
		printf("Invalid multiplication of matrices.\n");            //matrix multiplication possible only between mxn and nxp
	else{
		while(a!=NULL){                                             //Traversing the rows in the first matrix
			b=head2;                                                //comig back to the starting of columns
			while(b!=NULL){                                         //travelling all columns in the second matrix
				temp1=a;temp2=b;
				newnode=(struct node*)malloc(sizeof(struct node));  //creating new node which is the inner product ith row and jth column
				newnode->down=NULL;newnode->right=NULL;          
				if(b==head2&&head!=NULL){                           //For the linking between the new nodes
					pcolumn=column;
					prow=pcolumn;
					column->down=newnode;
					column=column->down;
					row=column;
					}
				newnode->val=InnerProduct(temp1,temp2);
				if(head==NULL){                                      //For the first node in the Multiplicated matrix
					head=newnode;					
					row=head;column=head;
					}
				else{
					row->right=newnode;                             //linking the rows of the node
					row=row->right;
					if(prow!=NULL){
						prow->down=row;                             //linking between the previous rows and present row
						prow=prow->right;}
					}
				b=b->right;                                        //traversing all columns
				}
			a=a->down;                                             //traversing the rows
			}
		 }
		 return(head);
	
	}
//Function to write the given matrix into the given file	
void WriteMatrix(FILE*out,struct node*head){          
	struct node*row=NULL,*column=NULL;             
	row=head;column=head;                                           
	while(column!=NULL){                                          //traversing the columns
		row=column;
		while(row!=NULL){                                         //traversing the rows
			fprintf(out,"%d",row->val);
			if(row->right!=NULL)
				fprintf(out,",");
			else if(row->right==NULL&&column->down!=NULL)
				fprintf(out,";");
			row=row->right;
			}
		column=column->down;
		}
	fprintf(out,"\n");
	printf("Successfully written matrix to the file.\n");
	
	}	

	
int main(){
	FILE*fp,*out;struct node*a=NULL,*b=NULL,*c=NULL;
	fp=fopen("Inputtext.txt","r");
	out=fopen("Ouputtext.txt","w");
	a=ReadMatrix(fp);
	b=ReadMatrix(fp);
	c=Matrixmultiplication(a,b);
	//printMatrix(a);
	//printMatrix(b);
	printMatrix(c);
	//RowsinMatrix(a);
	//ColumnsinMatrix(a);
	//Squaritycheck(a);
	//Symmetrycheck(a);
	//InnerProduct(a,b);
	WriteMatrix(out,c);
	fclose(fp);fclose(out);
	return(0);
	}
	
