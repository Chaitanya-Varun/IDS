#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//Structure of node for the BST
struct node{
    struct node* parent;             //Parent for the node
    struct node* right;              //Right_child link
    struct node* left;               //Left_child link
    int key;                         //Data to handle
    int size;                        //Size of the tree sub-rooted at this node
};
//Function for creating a new node
struct node *newNode(int key){
    struct node *temp =(struct node *)malloc(sizeof(struct node));   //Allocating memory
    temp->key = key;                             //Initiating the parameters
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    temp->size = 1;
    return temp;                                 //Returning allocated address
}
//Function for normal recursive sort
struct node* normal_insert(struct node*root,int key,int* d){
    if(root==NULL){                              //For the first node of BST
        root= newNode(key);
        *d=1;
        return(root);
    }                                            //If the key value is less than the root's key
    else if(key < root->key){                    //If the left child's place is empty,join it
        if(root->left==NULL){
            root->left = newNode(key);
            root->left->parent = root;
        }
        else{
            normal_insert(root->left,key,d);     //Else continue insertion to left branch
        }
    }
    else if(key > root->key){                    //If the key value is greater than the root's key
        if(root->right==NULL){                   //If the left child's place is empty,join it
            root->right = newNode(key);
            root->right->parent = root;
        }
        else{
            normal_insert(root->right,key,d);    //Else continue insertion to left branch
        }
    }
    *d=1;
    return(root);                                //Return the present root
}
//Function for inserting the new node as root
struct node*root_insert(struct node*root,struct node*new_root,int* d){
    if(root==NULL)                                //For the first node
        return new_root;
    while(root!=NULL){
        normal_insert(new_root,root->key,d);      //Building the new BST from the old BST with new root
        root_insert(root->left,new_root,d);
        root_insert(root->right,new_root,d);
        *d=1;
        return(new_root);
    }
    *d=1;
   return(new_root);                              //Return the present root
}
//The actual probabilistic insert function
struct node* insert(struct node*root,int key,int* d){
    int r=0,n=0;
    if(root!=NULL){                      //Counting the size of BST
        n=root->size;
        srand(time(NULL));
        r =(rand()%(n))+1;               //Generating random number in [1,n-1]
        }
    if(r!=n||n==0){                      //For the first insertion of root
        //printf("normal\n");            //Implementing the normal insert with probability n-1/n
        root = normal_insert(root,key,d);
        *d=1;
        return(root);
    }
    else{                                 //Implementing the normal insert with probability 1/n
        //printf("root insertion\n");
        struct node* new_root = NULL,*temp = NULL;
        new_root = newNode(key);
        root_insert(root,new_root,d);
        *d=1;
        return(new_root);
    }
}
//Function for counting the size of a tree at given node
int NumberofNodes(struct node*root){
    //struct node*temp=NULL;
    if(root!=NULL){              //Recursive call by counting itself,then adding its right sub branch and left sub brach
        return(1+NumberofNodes(root->left)+NumberofNodes(root->right));
    }
    else{
        return(0);
    }
}
//Function for updating the size parameter for all nodes in BST
struct node*update(struct node*root){
    if(root==NULL){
        return root;
    }
    else{
        root->size = NumberofNodes(root);
        update(root->left);
        update(root->right);
    }
}

//Function for printing the tree in inorder traversal
void inorder(struct node*root,FILE*output){
    //printf("Inorder Traversal :");
    if(root!=NULL){                                                    //For not reaching the empty tree
        inorder(root->left,output);                              //First print the nodes left child in inorder traversal
        fprintf(output,"%d ",root->key);                               //Printing the node
        inorder(root->right,output);                             // print the nodes right child in inorder traversal
    }
}
//Function for printing the tree in preorder traversal
void preorder(struct node*root,FILE*output){
    if(root!=NULL){
        fprintf(output,"%d ",root->key);                                //Printing the present node
        preorder(root->left,output);                              // print the nodes left child in preorder traversal
        preorder(root->right,output);                             // print the nodes right child in preorder traversal
    }
}
//Function for printing the tree in postorder traversal
void postorder(struct node*root,FILE*output){
    if(root!=NULL){
        postorder(root->left,output);                              // print the nodes left child in postorder traversal
        postorder(root->right,output);                             // print the nodes right child in postorder traversal
        fprintf(output,"%d ",root->key);                                 //Printing the present node
    }
}

//Function to find the node containing the required key value
struct node* find(struct node*root,int key,int d){
    d=0;                                                              //To keep the count of depth
    struct node*temp=NULL;temp=root;                                  //Initializing search from the root
    while(temp!=NULL){                                                //Until we don't reach the terminals continue the search
        if(temp->key==key){                                           //If the required key matches the node,s key,return the node
            //fprintf(output,"True",d);
            return(temp);
        }
        else if(temp->key < key){                                     //If the required key is greater than nodes key,move to its right child
            temp = temp->right;
            d++;                                                      //When travel to next child,you increase depth by one
        }
        else{                                                         //If the required key is lesser than nodes key,move to its left child
            temp = temp->left;
            d++;                                                      //When travel to next child,you increase depth by one
        }
    }
    if(temp==NULL){                                                   //When there is no such key,we reach the end of tree
        //fprintf(output,"False\n");
        return(0);
    }
}

//Function to print the tree in all traversals
void PrintTree(struct node*root,FILE*output){
    fprintf(output,"Inorder Traversal : ");
    inorder(root,output);fprintf(output,"\n");                           //printing in inorder traversal
    fprintf(output,"Pre-order Traversal : ");
    preorder(root,output);fprintf(output,"\n");                          //printing in preorder traversal
    fprintf(output,"Post-order Traversal : ");
    postorder(root,output);fprintf(output,"\n");                         //printing in postorder traversal
}
//Function for printing the sub tree considering the node with given key as root
void PrintSubTree(struct node*root,int key,FILE*output){
    struct node*temp=NULL;int d=0;
    temp=find(root,key,d);                                        //finding the required key
    PrintTree(temp,output);                                       //considering this as root ,printing sub tree
}
//Function used to implement the insertion function
struct node* insert_update(struct node*root,int key,int* b){
    struct node* troot = insert(root,key,b);           //calling the insert function
    update(troot);                                     //updating the size parameter
    //preorder(troot);printf("\n");
    return(troot);
}

//Function for joining the trees
struct node* join(struct node*L,struct node*R){
    int m=0,n=0,r,total=0;
    if(L!=NULL){
        m = L->size;
    }
    if(R!=NULL){
        n = R->size;
    }
    total = m+n;
    if(total==0){
        return(NULL);
    }
    srand(time(NULL));r =(rand()%(m+n));
    if(r<m){                                            //When left sub-branch takes the head,right branch joins with probability m/m+n
        L->right = join(L->right,R);
        return(L);
    }
    else{                                               //When right sub-branch takes the head,left branch joins with probability n/m+n
        R->left = join(L,R->left);
        return(R);
    }
}

//Function used to delete a node in probabilistic way
struct node*delete_fn(struct node*root,int key,int* b){
struct node*temp=NULL;int d=0;
    temp = find(root,key,d);
    if(temp==NULL){                                                   //When there is no such key,we reach the end of tree
        //fprintf(output,"False\n");
        *b=0;
        return(0);
    }
    struct node* left_branch = temp->left;temp->left=NULL;            //Assigning the right and left sub-branches
    struct node* right_branch = temp->right;temp->right=NULL;
    struct node*new_root = join(left_branch,right_branch);
    new_root->parent = temp->parent;
    temp->parent = NULL;
    free(temp);*b=1;
    update(new_root);
    return(new_root);
}

//Function used to delete a node in probabilistic way
struct node* delete_node(struct node* root,int key,int* b){
    struct node*temp=NULL;int d=0;
    temp = find(root,key,d);
    if(temp==NULL){                                                   //When there is no such key,we reach the end of tree
        //fprintf(output,"False\n");
        *b=0;
        return(0);
    }
    struct node* left_branch = temp->left;temp->left=NULL;            //Assigning the right and left sub-branches
    struct node* right_branch = temp->right;temp->right=NULL;
    int m = NumberofNodes(left_branch);                               //Finding the number of nodes in right and left branches
    int n = NumberofNodes(right_branch);
    if(m==0 && n==0){                                                 //Either leaf or root with no children
        if(temp->parent != NULL){                                     //For leaf node
            if(temp->parent->left==temp){                             //Updating the parents node and deleting the current node
                temp->parent->left=NULL;
                temp->parent=NULL;temp=NULL;
                free(temp);
            }
            else{
                temp->parent->right=NULL;
                temp->parent=NULL;temp=NULL;
                free(temp);
            }
        }
        else{                                                    //If the root is only present and is now deleted
            root=NULL;
        }
        update(root);                                            //Updating the size parameter in the BST
        //preorder(root);printf("\n");
        *b=1;
        return(root);                                            //Returning the new root
    }
    else if(m==0&&n!=0){                                         //When the node has only right child
        if(temp->parent==NULL){                                  //In case of root
            root = right_branch;
            right_branch->parent=NULL;
        }
        else{                                                    //Updating the link with parent and child of the current node
            if(temp->parent->right=temp){
                temp->parent->right=right_branch;
                right_branch->parent=temp->parent;
            }
            else{
                temp->parent->left=right_branch;
                right_branch->parent=temp->parent;
            }
            temp->parent=NULL;
        }
        free(temp);                                           //Deleting node
        update(root);                                         //updating the size parameter
        //preorder(root);printf("\n");
        *b=1;
        return(root);
    }
    else if(m=!0 && n==0){                                   //In case of only left child
        if(temp->parent==NULL){                              //Similarly handled as when node only has left child
            root = left_branch;
            left_branch->parent=NULL;
        }
        else{
            if(temp->parent->right=temp){
                temp->parent->right=left_branch;
                left_branch->parent=temp->parent;
            }
            else{
                temp->parent->left=left_branch;
                left_branch->parent=temp->parent;
            }
            temp->parent=NULL;
        }
        free(temp);
        update(root);
        //preorder(root);printf("\n");
        *b=1;
        return(root);
    }
    else{                                                   //For the case where the both children are present
        srand(time(NULL));
        int r =(rand()%(m+n));                              //generating random number in [0,m+n-1]
        if(r<m){                                            //When left sub-branch takes the head,right branch joins with probability m/m+n
            //printf("del-left heads\n");
            if(temp==root){                                 //In case of root is being deleted
                root = left_branch;
            }
            left_branch->parent = temp->parent;             //Eliminating the links for the node to be deleted
            if(temp->parent!=NULL && temp->parent->left==temp){
                temp->parent->left = left_branch;
                temp->parent=NULL;
            }
            else if(temp->parent!=NULL && temp->parent->right==temp){
                temp->parent->right = left_branch;
                temp->parent=NULL;
            }
            else{
                temp->parent=NULL;
            }
            free(temp);                                   //Deleting the node
            struct node* ltemp = left_branch;             //Joining the right sub-branch with left one
            while(ltemp->right != NULL){
                ltemp = ltemp->right;
            }
            ltemp->right = right_branch;
            right_branch->parent = ltemp;
        }
        else{
            //printf("del-right heads\n");              //When the right branch heads,left branch joins with probability of n/m+n ;
            if(temp==root){                             //Implementing similar procedure as done for left sub-branch case
                root = right_branch;
            }
            right_branch->parent = temp->parent;
            if(temp->parent!=NULL && temp->parent->left==temp){
                temp->parent->left = right_branch;
                temp->parent=NULL;
            }
            else if(temp->parent!=NULL && temp->parent->right==temp){
                temp->parent->right = right_branch;
                temp->parent=NULL;
            }
            else{
                temp->parent=NULL;
            }
            struct node* rtemp = right_branch;
            while(rtemp->left != NULL){
                rtemp = rtemp->left;
            }
            rtemp->left = left_branch;
            left_branch->parent = rtemp;
        }
        update(root);                          //Update the size parameter
        //preorder(root);printf("\n");
        *b=1;
        return(root);                          //Return the current node
    }
}

//Calculate difference between the number of nodes of its right sub branch and left sub branch
void CalculateImbalance(struct node*root,int key,FILE*output){
    struct node*temp=NULL;int d=0;
    temp=find(root,key,d);                      //Finding required node and calculating imbalance
    fprintf(output,"%d,(#left child - #right child = %d-%d=%d)",NumberofNodes(temp->left)-NumberofNodes(temp->right),NumberofNodes(temp->left),NumberofNodes(temp->right),NumberofNodes(temp->left)-NumberofNodes(temp->right));
}

int main(){
    FILE*fp,*output;int c=0,n=0;int key=0;struct node*root=NULL;int d;int b;
    fp=fopen("input.txt","r");                           //Opening input file
	output=fopen("ouput.txt","w");                       //For writing the output
	fscanf(fp,"%d",&n);                                  //Counts the number of operations
	//fprintf(output,"Number of operations:%d\n",n);
	while(c!=-1){                                        //Until reach end of file
        c=fgetc(fp);
        if(c=='1'){                                      //Insertion operation
            c=fgetc(fp);
            if(c==' ')
                fscanf(fp,"%d",&key);
            b=0;
            root=insert_update(root,key,&b);
            /*if(key==24||key==20){
                b=0;
                root=delete_node(root,root->key,&b);
                fprintf(output,"From deletion at node\n");
                PrintTree(root,output);
            }*/
            if(b!=0){
                fprintf(output,"True\n");
            }
            else{
                fprintf(output,"False\n");
            }

        }
        else if(c=='2'){                                 //Deletion operation
            c=fgetc(fp);
            if(c==' ')
                fscanf(fp,"%d",&key);
            b=0;
            root=delete_fn(root,key,&b);
            if(b!=0){
                fprintf(output,"True\n");
            }
            else{
                fprintf(output,"False\n");
            }
        }
        else if(c=='3'){                                  //Finding operation
            c=fgetc(fp);
            if(c==' ')
                fscanf(fp,"%d",&key);
            struct node*f=find(root,key,d);
            if(f!=NULL)
                fprintf(output,"True,depth=%d\n",d);
            else{
                fprintf(output,"False\n");
            }
        }
        else if(c=='4'){                                //Printing the entire tree operation
            PrintTree(root,output);
        }
        else if(c=='5'){                                //Printing the right sub tree operation
            c=fgetc(fp);
            if(c==' ')
                fscanf(fp,"%d",&key);
            PrintSubTree(root,key,output);
        }
        else if(c=='6'){                                //Calculate the imbalance for given node operation
            c=fgetc(fp);
            if(c==' ')
                fscanf(fp,"%d",&key);
            CalculateImbalance(root,key,output);
        }
        else{
            continue;
        }
	}
	fclose(fp);fclose(output);                         //Closing the files
	return(0);

}
