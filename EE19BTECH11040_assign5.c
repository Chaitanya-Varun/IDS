#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include <string.h>
#include<math.h>
////////////////////////////////////////////////////////////////////////////////////////////////
//Function for parenthesis check
struct bnode{                                                         //Node for storing braces
    char data;                                                        //Brace is recorded
    struct bnode *link;                                               //Links the brackets order
};
struct bstack{                                                        //Stack for Brackets
    struct bnode*btop;
};
//Function for pushing a node into the stack
void bpush(struct bstack* b,char c){
    struct bnode* t = b ->btop;                                        //For storing the top node of stack
    struct bnode*temp = NULL;
    temp =(struct bnode*)malloc(sizeof(struct bnode));
    temp->data=c;                                                      //Registering the new data
    temp->link = t;
    t = temp;
    b->btop=t;                                                         //Updating Top
    //printf("bpushed %c\n",c);
}
//Function to pop the bracket in the top most node
char bpop(struct bstack* b){
    struct bnode* t = b ->btop;char c;                                  //Temporary storing of top
    if(t==NULL){                                                        //Ensuring the stack is not empty
        //printf("bstack is empty\n");
        exit(0);
    }
    else{
        c = t->data;                                                    //Giving out the bracket in the top
        b->btop = t->link;                                              //Updating top
        t->link =NULL;t=NULL;
        free(t);                                                        //Freeing the popped node
        //printf("Popped %c\n",c);
        return(c);
    }
}
//Function to check given pair of characters are Matching Parenthesis
int MatchingParenthesis(char character1,char character2){
    if((character1=='('&&character2==')')||(character1=='['&&character2==']')||(character1=='{'&&character2=='}')){
        return 1;
    }
    else{
        return 0;
    }
}
//Function to check whether the parenthesis is balanced
int BalancedParenthesis(char*exp){
    int i=0;char c;struct bstack* b =NULL;                               //Creating a stack for the braces
    b = (struct bstack*)malloc(sizeof(struct bstack));
    b->btop=NULL;
    while(exp[i]){                                                       //Traversing through the expression
        if(exp[i]=='{'||exp[i]=='['||exp[i]=='('){                       //If encounters an opening bracket,push it stack
            bpush(b,exp[i]);
           }
        else if(exp[i]=='}'||exp[i]==']'||exp[i]==')'){                  //If encounters a closing bracket ,pop and see the bracket matches
            if(b->btop==NULL){                                           //When opening brace is not there
                printf("No Opening brace is Found for %c at position %d\n",exp[i],i);
                return 0;
                break;
            }
            else{
                c = bpop(b);
                if(!MatchingParenthesis(c,exp[i])){                      //When the opening bracket does not match the closing one
                    printf("%c is Not matching braces for %c at position %d \n ",c,exp[i],i);
                    return 0;
                    break;
                }
            }
        }
        i++;
    }
    if(b->btop==NULL){                                                   //After traversing the expression,if stack is empty ,its balanced
        return 1;
    }
    else{                                                                //There are no enough closing brackets
        printf("Open Braces left\n ");
        struct bnode*temp =NULL;temp=b->btop;
        while(temp!=NULL){
			printf("%c,",temp->data);
			temp=temp->link;
        }
        printf("\n");
        return 0;
    }
}
/////////////////////////////////////////////////////////////////////////////////////
//Function for converting the infix expression to the post fix expression
struct cnode{                                                      //Node for storing the operator
    char operator;
    struct cnode* link;
};

struct cstack{                                                     //Stack for operators
    struct cnode*top ;
};
//Function for pushing the nodes into the stack
void push(struct cstack*s,char op){
    struct cnode*temp=NULL;                                        //Creating a new node
    temp = (struct cnode*)malloc(sizeof(struct cnode));
    temp->operator=op;                                              //Fetching the data
    temp->link=s->top;                                             //Making the link
    s->top = temp;                                                 //Updating the top
}
//Function to pop the elements in the stack
char pop(struct cstack*s){
    struct cnode*temp=NULL;char op;                                 //Creating a temporary pointer pointing to the top
    temp = s->top;
    if(temp==NULL){                                                 //Checking if the stack is empty
        printf("Stack is empty,nothing to pop.\n");
        exit(0);
    }
    else{
        op= temp->operator;                                          //Popping the operator in top of stack
        s->top=temp->link;                                          //Updating the top
        temp->link=NULL;temp=NULL;
        free(temp);                                                 //Freeing the popped node
        return(op);
    }
}
//Function to see the top most character in the stack
char peek(struct cstack*s){
    char op;
    if(s->top==NULL){                                                //Checking the stack is not empty
        //printf("Stack is empty.\n");
        return(0);
    }
    else{
        op = s->top->operator;                                        //Storing the topmost character and returning it
        return op;
    }
}
//Function to tell the precedence order
int Prec(char op){
     if(op=='^'){
        return(1);
    }
    else if(op=='/'||op=='*'){
        return(2);
    }
    else if(op=='+'||op=='-'){
        return(3);
    }
    else if(op=='('||op=='['||op=='{'){
        return(4);
    }
    else{
        return(0);
    }
}
//Checking the character is an operand variable
int isOperand(char ch){
    if((ch >= 'a' && ch <= 'z')|| (ch >= 'A' && ch <= 'Z'))
        return 1;
    else
        return 0;
}
//Checking the character is an operator
int isOperator(char ch){
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^')
        return(1);
    else
        return(0);
}
//Checking all the operators got their required operands
int ValidOperators(char*exp){
    int i=0,v=1;int c=strlen(exp);
    while(i<c-1){                                                                     //Checking that no two operators are side by side
        if((isOperator(exp[i])==1)&&(isOperator(exp[i+1])==1)){
            v=0;
            printf("Invalid operations of %c,%c at positions %d,%d.\n",exp[i],exp[i+1],i,i+1);
            break;
        }
    i++;
    }
    if(isOperator(exp[0])){                                                          //Checking that the opening character is not operator
        v=0;
        printf("First operator %c at position 1 has not got enough operands.\n",exp[0]);
    }
    if(isOperator(exp[c])){                                                          //Checking that the closing character is not operator
        v=0;
        printf("Last operator %c at position %d has not got enough operands.\n",exp[c],c);
    }
    return(v);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function for evaluating the postfix expression
struct enode{                                                    //Node for keeping track of the operands
    int num;
    struct enode*link;
};

struct estack{                                                    //Stack of operands
    struct enode* etop;
};
//Function to push the operands into the stack
void epush(struct estack*e,int num){
    struct enode*temp = NULL;                                    //Creating a node
    temp = (struct enode*)malloc(sizeof(struct enode));
    temp->num=num;                                               //Fetching data to the node
    temp->link = e->etop;                                        //Making the link
    e->etop=temp;                                                //Updating the top
    //printf("push:%d\n",num);
}
//Function to pop the operands from the stack
int epop(struct estack*e){
    int num =0;
    struct enode*temp=NULL;                                      //Temporary pointer to the node
    temp = e->etop;
    if(temp==NULL){                                              //Ensuring the stack is not empty
        printf("Stack is Empty.\n");
        exit(0);
    }
    else{
        num = e->etop->num;                                      //Popping the topmost operands
        e->etop=temp->link;                                      //Updating the top
        temp->link=NULL;temp=NULL;                               //Freeing the popped node
        free(temp);
        //printf("pop:%d\n",num);
        return(num);
    }
}
//Function to evaluate the postfix expression
int evaluatePostfix(char*pfix,int k){
    struct estack*e = NULL;                                      //Creating a stack
    e =(struct estack*)malloc(sizeof(struct estack));
    e->etop=NULL;
    for(int i=0;i<k-2;i++){                                      //Traversing the expression
        if(pfix[i]==' '){                                        //If scanned character is a space bar then scan next
            continue;
        }
        else if (isdigit(pfix[i]))                               //If digit is scanned ,identify it's multi-digit number
		{
			int num=0;
			while(isdigit(pfix[i]))                              //If the next character is also digit ,then append to the unit place
			{
			num=num*10 + (int)(pfix[i]-'0');
				i++;
			}
			i--;
			epush(e,num);                                        //Push the number as operand into the stack
		}
		else{                                                    //Operator is encountered
            int num1=epop(e);int num=0;                          //Pop the top 2 elements and operate on them ,push back the result
            int num2=epop(e);
            if(pfix[i]=='^'){
                num = (int)(pow(num2, num1)+0.5);
            }
            else if(pfix[i]=='/'){
                num = num2/num1;
            }
            else if(pfix[i]=='*'){
                num = num2*num1;
            }
            else if(pfix[i]=='+'){
                num = num2+num1;
            }
            else if(pfix[i]=='-'){
                num = num2-num1;
            }
            epush(e,num);
		}
    }
    return(epop(e));
}
//Function to convert infix to post fix
void infixToPostfix(char*exp){
    int i=0,k=0,p=0;size_t c=2*strlen(exp);                     //Creating an array for storing the postfix expression
    char pfix[c];
    struct cstack* s =NULL;                                     //Creating stack for keeping track of operator and braces
    s=(struct cstack*)malloc(sizeof(struct cstack));
    while(exp[i]){                                              //Traversing the expression
        //Checking if the scanned operator is an operand
        if((isOperand(exp[i])||!isOperator(exp[i]))&&((exp[i]!='(')&&(exp[i]!=')')&&(exp[i]!='[')&&(exp[i]!=']')&&(exp[i]!='{')&&(exp[i]!='}'))){
            pfix[k]=exp[i];                                     //Directly sending it to output
            k++;
            if(isOperator(exp[i+1])||exp[i+1]==')'||exp[i+1]==']'||exp[i+1]=='}'||Prec(exp[i+1])==4){
                pfix[k] = ' ';k++;                               //For multi digit cases ,prints a space if next character is an operator or bracket
            }
        }
        else if(isOperator(exp[i])){                             //If it is an operator
            if(s->top!=NULL){                                    //Checking the stack is not empty
                char t = peek(s);                                //Looking at the top most operator in stack
                if(Prec(t)!=4){                                  //if preceded by opening brace
                    if(Prec(exp[i])<Prec(t)){                    //if scanned character is more prior than the top most character in stack,add it to the stack
                        push(s,exp[i]);
                    }
                    else{                                        //if top most character in the stack is of higher priority
                        while ((s->top!=NULL) && Prec(exp[i]) >= Prec(peek(s))){
                            pfix[k] = pop(s);                    //pop and output the character till the scanned character is of higher priority
                            k++;
                            pfix[k] = ' ';k++;
                        }
                        push(s,exp[i]);                          //Push the scanned operator
                    }
                }
                else{                                            //If it is preceded by opening brace,just add it to the stack
                    push(s,exp[i]);
                }
            }
            else{                                               //If it was the first character of the stack
                push(s,exp[i]);
            }
        }
        else if(exp[i]=='('||exp[i]=='['||exp[i]=='{'){        //If it is a opening brace add it to the stack
            push(s,exp[i]);
        }
        else if(exp[i]==')'){                                  //If closing brace is found then pop all the operators until its matching opening brace is found
            while ((s->top !=NULL) && peek(s) != '('){
                pfix[k] = pop(s);
                k++;
                pfix[k] = ' ';k++;
            }
		    if(s->top==NULL){
			    printf("Opening braces are missing\n");
			    exit(0);
			}
			else
				pop(s);
        }
        else if(exp[i]==']'){
            while ((s->top !=NULL) && peek(s) != '['){
                pfix[k] = pop(s);
                k++;
                pfix[k] = ' ';k++;
            }
            if(s->top==NULL){
			    printf("Opening Square braces are missing\n");
			    exit(0);
			}
			else
				pop(s);
        }
        else if(exp[i]=='}'){
            while ((s->top !=NULL) && peek(s) != '{'){
                pfix[k] = pop(s);
                k++;
                pfix[k] = ' ';k++;
            }
			if(s->top==NULL){
			    printf("Opening Curly braces are missing\n");
			    exit(0);
			}
			else
				pop(s);
        }
        else{                                               //If unexpected character is found
            printf("Unexpected character found.\n");
        }
    i++;
    }

    while(s->top!=NULL){                                    //Popping the remaining operators in the stack to output
        pfix[k]=pop(s);
        k++;
        pfix[k] = ' ';k++;
    }
    printf("Postfix expression : ");
    while(p<k){                                            //Printing the post fix expression
        printf("%c",pfix[p]);
        p++;
    }
    printf("\n");
    printf ("Output:%d\n", evaluatePostfix(pfix,k));       //Evaluating the postfix expression
   // return(pfix);
}
/////////////////////////////////////////////////////////////////////////

int main(){
    char exp[] = "[(30+43*24)-17]*(23*32)";                //Infix expression
    int q=0;
    printf("Infix Expression : ");
    while(exp[q]){                                         //Printing the infix expression
        printf("%c",exp[q]);
        q++;
    }
    printf("\n");
    if(ValidOperators(exp)==1){                            //Checking the operators validity
        printf("Operations are valid.\n");
        if(BalancedParenthesis(exp)==1){                   //Parenthesis check
            printf("Balanced Parenthesis\n");
            infixToPostfix(exp);                           //Converting into postfix expression and output the result
        }
        else {
            printf("Unbalanced Parenthesis\n");            //If braces are unbalanced
        }
    }
    return 0;
}

