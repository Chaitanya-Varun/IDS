#include<stdio.h>
#include<stdlib.h>
//Structure for the node of a tree
struct node{
    int key;                                  //Stores the key value
    struct node*left_child;                   //Stores link to the left child
    struct node*right_child;                  //Stores link to the right child
    struct node*parent;                       //Stores link to the parent
};
//Function to insert node in a tree
struct node* insert(struct node*root,int key,FILE*output){           //takes the root as input and key to be inserted
    struct node*temp=NULL;                                           //Creating new node
    temp=(struct node*)malloc(sizeof(struct node));                  //Allocating memory
    temp->left_child = NULL;temp->right_child=NULL;temp->parent=NULL;//Initiating the parameters
    temp->key = key;                                                 //Loading the new key into the node
    struct node*p=NULL;                                              //For finding the parent node
    p=root;                                                          //Initializing to root
    if(root==NULL){                                                  //For the first node,new temp becomes root
        root = temp;
    }
    else{
        struct node*current=NULL;current=root;                       //For finding the right parent for the new node
        while(current){
            p = current;                                             //Updating parent each time
            if(temp->key > current->key){                            //When new key greater than the compared node key
                current = current->right_child;                      //Move to the right(greater node side)
            }
            else{
                current = current ->left_child;                      //If lesser,move to the left(lower node side)
            }
        }
        temp->parent = p;                                            //When there is node node to compare,the new node becomes leaf of the particular node
        if(temp->key > p->key){                                      //If the new key is greater than the parent key ,insert as right child
            p->right_child = temp;
        }
        else{                                                        //If the new key is less than the parent key,insert left
            p->left_child = temp;
        }
    }
    fprintf(output,"True\n");                                        //Print to the output
    return(root);
}
//Function to find the node containing the required key value
struct node* find(struct node*root,int key,int d,FILE*output){
    d=0;                                                              //To keep the count of depth
    struct node*temp=NULL;temp=root;                                  //Initializing search from the root
    while(temp!=NULL){                                                //Until we don't reach the terminals continue the search
        if(temp->key==key){                                           //If the required key matches the node,s key,return the node
            //fprintf(output,"True",d);
            return(temp);
        }
        else if(temp->key < key){                                     //If the required key is greater than nodes key,move to its right child
            temp = temp->right_child;
            d++;                                                      //When travel to next child,you increase depth by one
        }
        else{                                                         //If the required key is lesser than nodes key,move to its left child
            temp = temp->left_child;
            d++;                                                      //When travel to next child,you increase depth by one
        }
    }
    if(temp==NULL){                                                   //When there is no such key,we reach the end of tree
        //fprintf(output,"False\n");
        return(0);
    }
}
//Function to delete a required node
int delete_node(struct node*root,int key,FILE*output){
    struct node*temp=NULL;int d=0;
    temp = find(root,key,d,output);                                   //Find the required node for given key to delete
    if(temp!=NULL){                                                   //Ensure the key is present
        struct node*p=NULL;                                           //Parent for the node to be deleted
        p=temp->parent;
        if(temp->right_child==NULL && temp->left_child==NULL){        //If that node is a leaf
            if(p->right_child == temp){                               //If the node was parent's right child
                p->right_child = NULL;                                //Delete the node,make parent to point to nothing
            }
            else{                                                      //If left,repeat the same
                p->left_child=NULL;
            }
            temp->parent=NULL;temp=NULL;                               //Making the node from the links
        }
        else if((temp->right_child!=NULL && temp->left_child==NULL)||(temp->right_child==NULL && temp->left_child!=NULL)){
            struct node*child=NULL;                                    //If the node has one child
            if(temp->left_child!=NULL){                                //The child is left child
                child = temp->left_child;                              //storing its child before the parent gets deleted
                if(temp==p->right_child){                              //If the node is its parent right child
                    p->right_child=temp->left_child;                   //then update the parents child as nodes child
                }
                else{                                                   //If the node is its parent left child
                    p->left_child=temp->left_child;                     //then update the parents child as nodes child
                }
                child->parent=p;                                        //Updating the parent for the child
                temp->left_child=NULL;temp->parent=NULL;temp=NULL;
                free(temp);                                             //Freeing temp
            }
            else{                                                       //The child is right child
                child = temp->right_child;                              //storing its child before the parent gets deleted
                if(temp==p->right_child){                               //If the node is its parent right child
                    p->right_child=temp->right_child;                   //then update the parents child as nodes child
                }
                else{                                                   //If the node is its parent left child
                    p->left_child=temp->right_child;                    //then update the parents child as nodes child
                }
                child->parent=p;                                        //Updating the parent for the child
                temp->right_child=NULL;temp->parent=NULL;temp=NULL;
                free(temp);                                             //Freeing temp
            }
        }
        else{                                                           //If the node to be deleted has two children
            struct node*c=NULL;
            c=temp->left_child;                                         //Following the predecessors policy,move to the left node
            if(c->left_child==NULL && c->right_child==NULL){            //If this node is a leaf
                temp->key=c->key;                                       //Replace this node with previous node being deleted
                temp->left_child=NULL;
                c->parent==NULL;c=NULL;
                free(c);
            }
            else if(c->left_child!=NULL && c->right_child==NULL){        //If the node has only left child
                temp->key=c->key;
                temp->left_child=c->left_child;                          //Replace the node being deleted with this node
                c->left_child->parent=temp;
                c->left_child=NULL;
                c->parent==NULL;c=NULL;
                free(c);                                                 //Delete the node
            }
            else{                                                        //If this node has got right child
                struct node*g=NULL;
                g=c->right_child;
                while(g->right_child!=NULL){                             //Search for node with largest key value i.e. the right most node
                    g=g->right_child;
                }
                struct node*parent_g=NULL;
                parent_g=g->parent;                                      //Replace this node with the node being deleted
                temp->key=g->key;                                        //Updating node with new key and updating its links
                if(g->left_child==NULL){
                    parent_g->right_child=NULL;
                    g->parent=NULL;
                }
                else{
                    parent_g->right_child=g->left_child;
                    g->left_child->parent=parent_g;
                    g->parent=NULL;g->left_child=NULL;
                }
                free(g);                                                 //Delete the node
            }
        }
        //fprintf(output,"deleted %d\n",key);
        fprintf(output,"True\n");                                        //Print to console
        return(1);
    }
    else{
        fprintf(output,"False\n");
        return(0);
    }
}
//Function for printing the tree in inorder traversal
void inorder(struct node*root,FILE*output){
    //printf("Inorder Traversal :");
    if(root!=NULL){                                                    //For not reaching the empty tree
        inorder(root->left_child,output);                              //First print the nodes left child in inorder traversal
        fprintf(output,"%d ",root->key);                               //Printing the node
        inorder(root->right_child,output);                             // print the nodes right child in inorder traversal
    }
}
//Function for printing the tree in preorder traversal
void preorder(struct node*root,FILE*output){
    if(root!=NULL){
        fprintf(output,"%d ",root->key);                                //Printing the present node
        preorder(root->left_child,output);                              // print the nodes left child in preorder traversal
        preorder(root->right_child,output);                             // print the nodes right child in preorder traversal
    }
}
//Function for printing the tree in postorder traversal
void postorder(struct node*root,FILE*output){
    if(root!=NULL){
        postorder(root->left_child,output);                              // print the nodes left child in postorder traversal
        postorder(root->right_child,output);                             // print the nodes right child in postorder traversal
        fprintf(output,"%d ",root->key);                                 //Printing the present node
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
    temp=find(root,key,d,output);                                        //finding the required key
    PrintTree(temp,output);                                              //considering this as root ,printing sub tree
}
//Function for finding the number of nodes in tree
int NumberofNodes(struct node*root,FILE*output){
    //struct node*temp=NULL;
    if(root!=NULL){              //Recursive call by counting itself,then adding its right sub branch and left sub brach
        return(1+NumberofNodes(root->left_child,output)+NumberofNodes(root->right_child,output));
    }
    else{
        return(0);
    }
}
//Calculate difference between the number of nodes of its right sub branch and left sub branch
void CalculateImbalance(struct node*root,int key,FILE*output){
    struct node*temp=NULL;int d=0;
    temp=find(root,key,d,output);                      //Finding required node and calculating imbalanc
    fprintf(output,"%d,(#left child - #right child = %d-%d=%d)",NumberofNodes(temp->left_child,output)-NumberofNodes(temp->right_child,output),NumberofNodes(temp->left_child,output),NumberofNodes(temp->right_child,output),NumberofNodes(temp->left_child,output)-NumberofNodes(temp->right_child,output));
}

int main(){
    FILE*fp,*output;int c=0,n=0;int key=0;struct node*root=NULL;int d;
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
            root=insert(root,key,output);
        }
        else if(c=='2'){                                 //Deletion operation
            c=fgetc(fp);
            if(c==' ')
                fscanf(fp,"%d",&key);
            delete_node(root,key,output);
        }
        else if(c=='3'){                                  //Finding operation
            c=fgetc(fp);
            if(c==' ')
                fscanf(fp,"%d",&key);
            struct node*f=find(root,key,d,output);
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
