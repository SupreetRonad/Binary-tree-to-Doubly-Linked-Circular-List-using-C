#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};
typedef struct node* Node;

Node Clhead=NULL,prev=NULL,tail=NULL;

Node newNode(int data) {
    Node node = (Node) malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

void getDLL(Node r){
	if(r==NULL)
		return;
	
	getDLL(r->left);
	
	if(prev==NULL)
		Clhead=r;
	else{
		r->left=prev;
		prev->right=r;
	}
	
	prev=r;
	getDLL(r->right);
}

//Insertion for Binary search tree
void insert(Node* rootRef, int data) {
    Node root = *rootRef;
    if (root == NULL) 
		*rootRef = newNode(data);
    else
        if (data < root->data) 
			insert( &(root->left), data);
        else if(data > root->data)
			insert( &(root->right), data);
}

void printList() {
    Node current = Clhead;  
	if(Clhead==NULL)
		return;
    do{
        printf(" %d ", current->data);
        current = current->right;
    }while(current != Clhead);
    printf("\n");
}

void getTail(Node r){
	if(r==NULL)
		return;
	if(r->right==NULL){
		tail=r;
		return;
	}
	getTail(r->right);
}

void insertCL(int data){
	Node new=newNode(data);
	if(Clhead==NULL){										//for empty cll
		Clhead=tail=new;
		new->right=new->left=new;
		return;
	}
	if(Clhead->data > data || tail->data < data){			//if new data to be inserted before head
		tail->right=new;
		Clhead->left=new;
		new->right=Clhead;
		new->left=tail;
		if(Clhead->data > data)
			Clhead=new;
		else
			tail=new;
		return;
	}
	Node temp=Clhead;
	do{											//If the new data is nor tail neither the head. In between.
		if(temp->right->data > data)
			break;
		temp=temp->right;
	}while(temp!=Clhead);
	temp->right->left=new;
	new->left=temp;
	new->right=temp->right;
	temp->right=new;
}

int deleteNode(int key) 
{ 
    if (Clhead == NULL) 
        return 0; 
   
    Node curr = Clhead, prev; 
    while (curr->data != key) { 
        if (curr->right == Clhead) { 
            return 0;
        }   
        prev = curr; 
        curr = curr->right; 
    } 
	
    if (curr->right == Clhead) { 
		prev->right=Clhead;
		tail=prev;
        free(curr); 
        return 1; 
    } 
  
    if (curr == Clhead) { 
        prev = Clhead; 
        while (prev->right != Clhead) 
            prev = prev->right; 
        Clhead = curr->right; 
        prev->right = Clhead; 
        free(curr); 
    } 
   
    else if (curr->right == Clhead) { 
        prev->right = Clhead; 
        free(curr); 
    } 
    else { 
        prev->right = curr->right; 
        free(curr); 
    }
	return 1;	
} 

//Insertion for Binary tree
Node create(){
	Node p;
	int x;
	scanf("%d",&x);
	
	if(x==-1)
		return NULL;
	
	p=newNode(x);  	
	printf("Left child of %d : ",x);
	p->left=create(); 
	printf("Right child of %d : ",x);
	p->right=create();	
	return p;
}

int main() {
    Node root = NULL;
	int ch=1,data=1;
	
	//For binary tree
	printf("(Enter -1 if No Node)\n");
	printf("\nEnter Root node : ");
	
	root=create();
	getTail(root);
	getDLL(root);
	Clhead->left=tail;
	tail->right=Clhead;
	printList(Clhead);
	int  f=1;
	printf("\n Press 1 to continue : ");
	scanf("%d",&f);
	
	Clhead=NULL;		//Make all pointers Null to use the same pointers for Application
	tail=NULL;
	prev=NULL;
	root=NULL;
	
	
	//For binary Search tree application	
	printf("\n\n---- Application -----\n\n Enter all the base data (-1 to stop) : ");
	scanf("%d",&data);
	while(data!=-1){
		insert(&root,data);
		scanf("%d",&data);
	}
	getTail(root);
	getDLL(root);
	Clhead->left=tail;
	tail->right=Clhead;
	printList(Clhead);
	printf("\n Press 1 to continue : ");
	scanf("%d",&f);
	ch=1;
	while(ch!=0){
		printf("\n1.Deletion\n2.Insertion\n3.Display\n Enter your Choice : ");
		scanf("%d",&ch);
		switch(ch){
			case 2:
				printf("\n Enter Data to be inserted: ");
				scanf("%d",&data);
				insertCL(data);
				printList(Clhead);
				break;
			case 1:
				printf("\n Enter data to be deleted : ");
				scanf("%d",&data);
				f=deleteNode(data);
				if(f){
					printList(Clhead);
					break;
				}
				printf("\nKey not found\n");
				break;
			case 3:
				printList(Clhead);
				break;
		}
	}
}
