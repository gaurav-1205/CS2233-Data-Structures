//This program can handle input of arbitrary size number

#include <stdio.h>
#include <stdlib.h>

//Linked list to store arbitrary size numbers
struct number
{
	int num;
	struct number* prev;
	struct number* next;
};

//Binary search tree with parent, left child and roght child
struct tree
{
	struct number* list;	
	struct tree* parent;	
	struct tree* left;
	struct tree* right;
};

unsigned long long int c1=0, c2=0, i=0;

int getnum(char a);		//converts char to int
void insert(int digit);		//inserts number to linked list
void display(struct number* n);		//print the linked list
void newLL();	//This function is called when the user enters 'N'
void deleteList(struct number* n);		//This function empties the linked list
int compare(struct number* n1, struct number* n2);		//compare the two given numbers
int eqDigit(struct number* n1, struct number* n2);		//returns 0, 1, 2 for less than, greater than and equal to respectively
void insertToBST(struct tree* node, struct number* n);		//assign the linked list to the node of BST
void preorder(struct tree* node);	//prints the set in preorder
void deleteBST(struct tree* n);		//deletes the BST
void search();		//used for searching the BST
void traverseBST(struct tree* n);	//used for traversing the BST
void insertPath(int digit);		//insert into linked list for printing the path
void addElem();		//Add digit to the BST
void getSucc();		//function to get the succesor of the number
struct tree* traverse(struct tree* n);		//used to traverse the BST
struct tree* inorder(struct tree* node);	//inorder traversal gives the tree in sorted order which is useful to find the succesor
void deleteNode();	//function to delete the node of the binary search tree
void del(struct tree* q);	//recursive function for deletion of a node
void printChild();		//functon to print the children of the node
void printUncle();		//functon to print the uncle of the node
void leftRotate();	//left rotate a node
void rightRotate();	//right rotate a node


struct number* head1=NULL,*prevhead1=NULL, *head2=NULL;
struct tree* root=NULL, *ptr=NULL;

//struct tree* ptr = NULL;


int main()
{
	char digit;
	while((digit=fgetc(stdin))!=EOF)
	{
		if((digit=='N') || (digit=='B'))
		{
			if(root!=NULL)
			{
				deleteBST(root);
				head1=NULL;
				root=NULL;
			}
			newLL();
		}
		else if(digit=='S')
		{
			search();
			printf("\n");
		}
		else if(digit=='P')
		{
			if (head1==NULL)
				head1=prevhead1;
			preorder(root);
			printf("\n");
		}
		else if(digit=='+')
		{
			addElem();
		}
		else if(digit=='>')
		{
			getSucc();
			printf("\n");
		}
		else if(digit=='-')
		{
			deleteNode();
			head1=NULL;
			//printf("\n");
		}
		else if(digit=='C')
		{
			printChild();
			printf("\n");
		}
		else if(digit=='U')
		{
			printUncle();
			printf("\n");
		}
		else if(digit=='L')
		{
			leftRotate();;
		}
		else if(digit=='R')
		{
			rightRotate();
		}
	}
	return 0;
}

void newLL()	//This function is called when the user enters 'N'
{
	char digit;
	int num;
	
	while((digit=fgetc(stdin)) != '\n')
	{
		if(digit==' ')
		{
			if(head1!=NULL)
			{
				insertToBST(root, head1);
				prevhead1=head1;
				head1=NULL;
			}
		}	
		else 
		{
			num = getnum(digit);
			insert(num);
		}
		
	}
	if (head1!=NULL)
	insertToBST(root, head1);
}

void search() 	//used for searching the BST
{
	char digit;
	int num;
	head1=NULL;
	while((digit=fgetc(stdin)) != '\n')
	{
		if(digit!=' ')
		{
			num = getnum(digit);
			insert(num);
		}
	}
	if (head1!=NULL)
	{
		head2=head1;
		head1=NULL; 
		struct tree* p = root;
		traverseBST(p);		//adds 1 and 0 to the linked list as per path traversed
		deleteList(head1);
		head1=NULL;
	}
}

void preorder(struct tree* node)		//prints the preorder traversal of the BST
{
	if(node==NULL)
	{return;}

	display(node->list);
	preorder(node->left);
	preorder(node->right);
}

void addElem() 	//Insert element in the BST
{
	char digit;
	int num;
	head1=NULL;
	while((digit=fgetc(stdin)) != '\n')
	{
		if(digit!=' ')
		{
			num = getnum(digit);
			insert(num);
		}
	}
	if(head1!=NULL)
	{
		insertToBST(root, head1);
		head1=NULL;
	}
}

void getSucc()	//This function enters the data in linked list and calls the inorder function to get the succesor
{
	char digit;
	int num;
	head1=NULL;
	while((digit=fgetc(stdin)) != '\n')
	{
		if(digit!=' ')
		{
			num = getnum(digit);
			insert(num);
		}
	}
	if(head1!=NULL)
	{
		struct tree* p = root;
		struct tree* q = inorder(p);
		if((q==NULL) && (i==0))
			printf("-1");
		i=0;
		deleteList(head1);
		head1=NULL;
	}	
}

void deleteNode()		//This function enters the data in linked list and calls the del function to delete it
{
	char digit;
	int num;
	head1=NULL;
	while((digit=fgetc(stdin)) != '\n')
	{
		if(digit!=' ')
		{
			num = getnum(digit);
			insert(num);
		}
	}
	if(head1!=NULL)
	{
		struct tree* p = root;
		struct tree* q = traverse(p);
		if (q!=NULL)
			del(q);
		deleteList(head1);
		head1=NULL;
	}
}

void printChild()		//This functon prints the children of the node. If any of the children is NULL it prints as 'Nil'
{
	char digit;
	int num;
	head1=NULL;
	while((digit=fgetc(stdin)) != '\n')
	{
		if(digit!=' ')
		{
			num = getnum(digit);
			insert(num);
		}
	}
	if(head1!=NULL)
	{
		struct tree* p = root;
		struct tree* q = traverse(p);
		if(q!=NULL)
		{
			if (q->left!=NULL)
				display(q->left->list);
			else
				printf("Nil ");
			
			if (q->right!=NULL)
				display(q->right->list);
			else
				printf("Nil");
		}
		else
			printf("-1");
		deleteList(head1);
		head1=NULL;
	}
}

void printUncle()		//This function prints the Uncle of the node. If the uncle does not exist it prints '-1'
{
	char digit;
	int num;
	head1=NULL;
	while((digit=fgetc(stdin)) != '\n')
	{
		if(digit!=' ')
		{
			num = getnum(digit);
			insert(num);
		}
	}
	if(head1!=NULL)
	{
		struct tree* p = root;
		struct tree* q = traverse(p);
		if (q!=NULL)
		{
			if((q->parent!=NULL)&&(q->parent->parent!=NULL))
			{
				if(q->parent==q->parent->parent->left)
				{
					if(q->parent->parent->right!=NULL)
						display(q->parent->parent->right->list);
					else
						printf("-1");
				}
				else
				{
					if(q->parent->parent->left!=NULL)
						display(q->parent->parent->left->list);
					else
						printf("-1");
				}
			}
			else{
				printf("-1");
			}
		}
		else
			printf("-1");
		deleteList(head1);
		head1=NULL;
	}
}

void leftRotate()		//This function is used for left rotating the node if possible. If left rotation is not possible, it does nothing
{
	char digit;
	int num;
	head1=NULL;
	while((digit=fgetc(stdin)) != '\n')
	{
		if(digit!=' ')
		{
			num = getnum(digit);
			insert(num);
		}
	}
	if(head1!=NULL)
	{
		struct tree* p = root;
		struct tree* q = traverse(p);
		if(q!=NULL)
		{
			if(q->right!=NULL)
			{
				struct tree* temp1 = q->parent;
				struct tree* temp2 = q->right;
				if(q->parent!=NULL)
				{
					if(q==temp1->left)
						temp1->left=temp2;
					else
						temp1->right=temp2;
					temp2->parent=temp1;
				}
				else
				{
					temp2->parent=NULL;
					root=temp2;
				}
				q->right=temp2->left;
				temp2->left=q;
				q->parent=temp2;
			}
		}
		
		deleteList(head1);
		head1=NULL;
	}
}

void rightRotate()		//This function is used for right rotating the node if possible. If right rotation is not possible, it does nothing
{
	char digit;
	int num;
	head1=NULL;
	while((digit=fgetc(stdin)) != '\n')
	{
		if(digit!=' ')
		{
			num = getnum(digit);
			insert(num);
		}
	}
	if(head1!=NULL)
	{
		struct tree* p = root;
		struct tree* q = traverse(p);
		if(q!=NULL)
		{
			if(q->left!=NULL)
			{
				struct tree* temp1 = q->parent;
				struct tree* temp2 = q->left;
				if(q->parent!=NULL)
				{
					if(q==temp1->left)
						temp1->left=temp2;
					else
						temp1->right=temp2;
					temp2->parent=temp1;
				}
				else
				{
					temp2->parent=NULL;
					root=temp2;
				}

				q->left=temp2->right;
				temp2->right=q;
				q->parent=temp2;
			}
		}
		
		deleteList(head1);
		head1=NULL;
	}
}

void del(struct tree* q)	//frees all the pointers and deletes the node
{
	if(q!=NULL)
		{
			if((q->right==NULL) && (q->left==NULL))		//If node does not have a child
			{
				deleteList(q->list);
				q->list=NULL;
				if(q->parent!=NULL)
				{
					if(q==q->parent->left)
						q->parent->left = NULL;
					else if(q==q->parent->right)
						q->parent->right = NULL;
					q->parent=NULL;
				}
				free(q);
			}

			else if((q->right!=NULL) && (q->left==NULL))	//if node has only right child
			{
				struct tree* temp;
				if (q->parent!=NULL)
				{
					temp= q->parent;
					if(q==temp->left)
					{
						temp->left = q->right;
						q->right->parent = temp;
					}
					else if(q==temp->right)
					{
						temp->right = q->right;
						q->right->parent = temp;
					}
					deleteList(q->list);
					q->list = NULL;
					free(q);
				}
				else
				{
					root=q->right;
					q->right=NULL;
					deleteList(q->list);
					free(q);
					root->parent=NULL;
				}
				
				
			}

			else if((q->right==NULL) && (q->left!=NULL))	//if node has only left child
			{
				struct tree* temp;
				if (q->parent!=NULL)
				{
					temp = q->parent;
					if(q==temp->left)
					{
						temp->left = q->left;
						q->left->parent = temp;
					}
					else if(q==temp->right)
					{
						temp->right = q->left;
						q->left->parent = temp;
					}
					deleteList(q->list);
					q->list = NULL;
					free(q);
				}
				else
				{
					root=q->left;
					q->left=NULL;
					deleteList(q->list);
					free(q);
					root->parent=NULL;
				}
			}

			else if((q->right!=NULL) && (q->left!=NULL))	//node has both the children
			{

				struct tree* temp;
				for (temp=q->right;temp->left!=NULL;temp=temp->left);		//we go once right and continuously left to get the successor

				struct number * data_succ = temp->list;
				temp->list= q->list;
				q->list=data_succ;
				
				del(temp);
			}
		}
}

struct tree* traverse(struct tree* n)		//returns the pointer to the node containing the entered data
{
	if(n==NULL)
	{
		return n;
	}
	int p = compare(head1, n->list);
	if(p==0)
	{		
		traverse(n->left);
	}
	else if(p==1)
	{		
		traverse(n->right);
	}
	
	if(p==2)
	{
		return n;
	}
}

void traverseBST(struct tree* n)	//used for traversing the BST and entering path traversals to the list
{
	if(n==NULL)
	{
		printf("-1");
		return;
	}
	int p = compare(head2, n->list);
	if(p==0)
	{		
		insertPath(p);		
		traverseBST(n->left);
	}
	else if(p==1)
	{		
		insertPath(p);		
		traverseBST(n->right);
	}
	
	if(p==2)
	{
		display(head1);
		return;
	}
}


int compare(struct number* n1, struct number* n2)		//compare the two given numbers. returns 0, 1, 2 for less than, greater than and equal to respectively
{
	c1=0;c2=0;
	for(struct number* ptr1=n1;ptr1!=NULL;ptr1=ptr1->next)
		c1++;
	for(struct number* ptr2=n2;ptr2!=NULL;ptr2=ptr2->next)
		c2++;
	if(c1>c2)	//If the digits are of unequal length, then it can easily be compared with the longest number being the greater
		return 1;
	else if(c1<c2)
		return 0;
	else if(c1==c2)
	{
		return eqDigit(n1, n2);		
	}
}

int eqDigit(struct number* n1, struct number* n2)	//for equal number of digits, we compare one by one each digit and return two if all the digits are equal
{
	unsigned long long int c=c1;

	while(c!=1)
	{
		if(n1->num > n2->num)
		{
			return 1;
		}
		else if(n1->num < n2->num)
		{
			return 0;
		}

		n1=n1->next;
		n2=n2->next;
		c--;
		
	}

	if(c == 1 && n1->num == n2->num)
	{
		return 2;
	}
	else if(c==1 && n1->num > n2->num)
	{
		return 1;
	}
	else if(c == 1 && n1->num < n2->num)
	{
		return 0;
	}	
}

void insertToBST(struct tree* node, struct number* n)	//insert data to the binary search tree
{
	if (root==NULL)
	{
		root = (struct tree*)malloc(sizeof(struct tree));
		root->parent=NULL;
		root->left=NULL;
		root->right=NULL;
		root->list=n;
		return;
	}


	if(node==NULL)
	{
		struct tree* node = (struct tree*)malloc(sizeof(struct tree));
		node->parent=NULL;
		node->list = n;
		node->left=NULL;
		node->right=NULL;
		//return;
	}
	if (node->list!=NULL)
	{
		if(compare(n, node->list)==1)
		{
			if (node->right==NULL)
			{
				struct tree* p = (struct tree*)malloc(sizeof(struct tree));
				p->parent=node;
				node->right=p;
				p->list = n;
				p->left=NULL;
				p->right=NULL;
			}
			else
				insertToBST(node->right,n);
		}
		else if(compare(n, node->list)==0)
		{
			if (node->left==NULL)
			{
				struct tree* p = (struct tree*)malloc(sizeof(struct tree));
				p->parent=node;
				node->left=p;
				p->list = n;
				p->left=NULL;
				p->right=NULL;
			}
			else
				insertToBST(node->left,n);
		}
	}
}

struct tree* inorder(struct tree* node)		//inorder always returns elements in sorted order. This is useful for finding the successor
{

	if(node==NULL)
	{
		return node;
	}

	inorder(node->left);

	if(i==0)
	{
		if(compare(head1, node->list)==0)
		{	
			display(node->list);
			i=1;
			return node;
		}
	}
		
	inorder(node->right);
}

void deleteList(struct number* n)	//deletes the linked list
{
	struct number* current = (struct number*)malloc(sizeof(struct number));
	current = n;
	struct number* next; 

	while (current != NULL)  
	{ 
		next = current->next; 
		free(current); 
		current = next; 
	}
}

void deleteBST(struct tree* n)//Deleting by post order traversal
{
	if(n==NULL)
		return;
	
	deleteBST(n->left);
	deleteBST(n->right);

	deleteList(n->list);
	free(n);
	n=NULL;
}
//PS we need the second insert function as we do not need to sanitize the linked list by removing leading zeros

void insert(int digit)		//inserts data in the linked list
{
	if(head1==NULL)
	{
		if(digit==0)
			return;
		head1 = (struct number*)malloc(sizeof(struct number));
		head1 ->num = digit;
		head1 ->next = NULL;
		head1 ->prev = NULL;
		return;
	}
	struct number* p = (struct number*)malloc(sizeof(struct number));
	struct number* ptr1 = head1;
	p->num = digit;
	p->next = NULL;
	
	for(ptr1 = head1; ptr1->next != NULL; ptr1 = ptr1->next);

	ptr1->next = p;
	p->prev = ptr1;
}

void insertPath(int digit)		//inserts data into linked list for displaying the path. It does not sanitize inputs
{
	if(head1==NULL)
	{
		head1 = (struct number*)malloc(sizeof(struct number));
		head1 ->num = digit;
		head1 ->next = NULL;
		head1 ->prev = NULL;
		return;
	}
	struct number* p = (struct number*)malloc(sizeof(struct number));
	struct number* ptr1 = head1;
	p->num = digit;
	p->next = NULL;
	
	for(ptr1 = head1; ptr1->next != NULL; ptr1 = ptr1->next);

	ptr1->next = p;
	p->prev = ptr1;
}

void display(struct number* n)	//prints the linked list
{
	if(n==NULL)
		return;
	while(1)
	{
		if (n!=NULL)
			{printf("%d", n->num);}	//displays the answer digit by digit
		if(n->next==NULL)
			{break;}
		else
			n=n->next;
	}
	printf(" ");
}

int getnum(char a)	//fgetc takes input as character. So we subtract 48 to convert to integer
{
	return (a-48);
}
