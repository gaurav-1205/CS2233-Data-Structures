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

//Binary search tree with parent, left child and right child
struct tree
{
	struct number* list;	
	struct tree* parent;	
	struct tree* left;
	struct tree* right;
	int color;		//0 for Red and 1 for Black 2 for double black/black token
};

unsigned long long int c1=0, c2=0, i=0;

int getnum(char a);		//converts char to int
void insert(int digit);		//inserts number to linked list
void display(struct number* n);		//print the linked list
void display_col(struct tree* n);	//print the preorder along with colors of the nodes
void displayPath(struct number* n);		//prints the path along with the color of the node	
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
struct tree* get_uncle(struct tree* node);	//returns the pointer to the uncle of the node
void fixInsert(struct tree* node);	//assigns appropriate colors to the nodes
void fixToken(struct tree* node);	//fixes the token of the node while deletion
void leftRotate(struct tree* node);	//left rotate a node
void rightRotate(struct tree* node);	//right rotate a node
void getChild();	//printfs the values of left and right child along with the colors
char get_color(int num);	//returns R for Red and B for Black
int isOnLeft(struct tree* node);	//returns 1 is node is left child else returns 0;
void detailedTraversal(struct tree* Z);

struct number* head1=NULL,*prevhead1=NULL, *head2=NULL;
struct tree* root=NULL, *ptr=NULL, *NIL, *NILDB;
int S_flag=0;

int main()
{
	char digit;
	while((digit=fgetc(stdin))!=EOF)
	{
		if(digit=='N')
		{
			if(root!=NULL)
			{
				deleteBST(root);
				free(NIL);
				free(NILDB);
				head1=NULL;
				root=NULL;
			}
			newLL();
		}
		else if(digit=='S')
			search();
		else if(digit=='P')
		{
			if (head1==NULL)
				head1=prevhead1;
			preorder(root);
			printf("\n");
		}
		else if(digit=='C')
			getChild();

		else if(digit=='+')
			addElem();
		
		else if(digit=='>')
		{
			getSucc();
			printf("\n");
		}
		else if(digit=='-')
		{
			deleteNode();
			head1=NULL;
		}
	}
	return 0;
}

void newLL()	//This function is called when the user enters 'N'
{
	char digit;
	int num;
	NIL=(struct tree*)malloc(sizeof(struct tree));
	NIL->list=NULL;
	NIL->color=1;	//The sentinel node with black color

	NILDB=(struct tree*)malloc(sizeof(struct tree));
	NILDB->list=NULL;
	NILDB->color=2;	//The sentinel node with black color and black token

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
	S_flag=0;
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
	if(node==NIL||node==NULL)
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
		struct tree* d = traverse(p);
		if (d!=NULL)
			del(d);
		deleteList(head1);
		head1=NULL;
		//q=NULL;
	}
}

void getChild()	//printfs the values of left and right child along with the colors
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
		if(q==NULL)
		{
			printf("-1\n");
			return;
		}
		if(q->left->list==NULL)
			printf("L ");
		else
			display(q->left->list);
		printf("%c ", get_color(q->left->color));
		if(q->right->list==NULL)
			printf("L ");
		else
			display(q->right->list);
		printf("%c\n", get_color(q->right->color));
		deleteList(head1);
		head1=NULL;
	}
}

void fixInsert(struct tree* Z)	//assigns appropriate colors to the nodes
{
	if(Z->parent==NULL)
	{
		Z->color=1;	//black for root
		return;
	}	
	struct tree *U, *par, *gpar;
	par=Z->parent;
	gpar=Z->parent->parent;
	//U = get_uncle(Z);
	//printf("working\n");
	if((Z->parent->color==1)&&(root->color==1))
		return;

	if(Z->color==0)
	{
		if(par==gpar->left)
		{
			U=gpar->right;
			if(U->color==0)
			{
				par->color = 1;
				gpar->color = 0;
				U->color = 1;
				Z = gpar;
				fixInsert(Z);
			}
			else if(U->color==1)
			{
				if(par->left==Z)
				{
					rightRotate(gpar);
					int temp;
					temp=par->color;
					par->color=gpar->color;
					gpar->color=temp;
					Z=par;
					fixInsert(Z);
				}
				else if(par->right==Z)
				{
					leftRotate(par);
					Z=par;
					par=Z->parent;
					fixInsert(Z);
				}
			}
		}
		else if(Z->parent==Z->parent->parent->right)
		{
			U=gpar->left;
			if(U->color==0)
			{
				par->color = 1;
				gpar->color = 0;
				U->color = 1;
				Z = gpar;
				fixInsert(Z);
			}
			else if(U->color==1)
			{
				if(par->right==Z)
				{
					leftRotate(gpar);
					int temp;
					temp=par->color;
					par->color=gpar->color;
					gpar->color=temp;
					Z=par;
					fixInsert(Z);
				}
				else if(Z->parent->left==Z)
				{
					rightRotate(par);
					Z=par;
					par=Z->parent;
					fixInsert(Z);
				}
			}
		}
	
	}
	root->color=1;
}

void leftRotate(struct tree* node)		//This function is used for left rotating the node if possible. If left rotation is not possible, it does nothing
{
	if(node!=NULL)
	{
		if(node->right!=NULL)
		{
			struct tree* temp1 = node->parent;
			struct tree* temp2 = node->right;
			if(node->parent!=NULL)
			{
				if(node==temp1->left)
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
			node->right=temp2->left;
			temp2->left=node;
			node->parent=temp2;
			node->right->parent=node;
		}
	}
}

void rightRotate(struct tree* node)		//This function is used for right rotating the node if possible. If right rotation is not possible, it does nothing
{
	if(node!=NULL)
	{
		if(node->left!=NULL)
		{
			struct tree* temp1 = node->parent;
			struct tree* temp2 = node->left;
			if(node->parent!=NULL)
			{
				if(node==temp1->left)
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

			node->left=temp2->right;
			temp2->right=node;
			node->parent=temp2;
			node->left->parent=node;
		}
	}
}

void fixToken(struct tree* node)	//fixes the token for deletion
{
	struct tree *par, *sibling;
	if(node->color==1)
		return;
	if(node==root)
	{
		root->color=1;
		return;
	}
	par=node->parent;
	if(node==par->left)
		sibling=par->right;
	else
		sibling=par->left;
	
	if(sibling->color==0)
	{
		sibling->color=1;	//sibling black
		par->color=0;	//parent red
		if(node==par->left)
			leftRotate(par);
		
		else if(node==par->right)
			rightRotate(par);

		fixToken(node);
	}
	else if((sibling->color==1)&&(sibling->left->color==1)&&(sibling->right->color==1))
	{
		node->color--;
		sibling->color--;
		par->color++;
		if(par->color==2)
			fixToken(par);
	}
	else if((sibling->color==1)&&(sibling->left->color==0)&&(sibling->right->color==1))
	{
		int temp;
		temp=sibling->left->color;
		sibling->left->color=sibling->color;
		sibling->color=temp;
		rightRotate(sibling);
		fixToken(node);
	}
	else if(node==par->right && sibling->left->color==0)
	{
		rightRotate(par);
		//display(sibling->list);
		par->color=1;
		sibling->color=0;
		sibling->left->color=1;
	}

	else if((sibling->color==1)&&(sibling->right->color==0))
	{
		
		if(isOnLeft(node)==1)
		{
			sibling->right->color=sibling->color;
			sibling->color=par->color;
			par->color=1;
			leftRotate(par);
		}
		else if(isOnLeft(node)==0)
		{
			sibling->right->color=par->color;
			leftRotate(sibling);
			rightRotate(par);
		}
		node->color=1;
		root->color=1;
	}
}

void del(struct tree* q)	//frees all the pointers and deletes the nodes
{
	if(q!=NULL)
		{
			struct tree *par, *sibling, *child, *temp;
			if((q->right==NIL) && (q->left==NIL))		//If node does not have a child
			{
				par=q->parent;
				deleteList(q->list);
				if(par!=NULL)
				{
					if(q==par->left)
					{
						par->left = NILDB;
						NILDB->color=2;
						NILDB->parent=par;
					}
					else if(q==par->right)
					{
						par->right = NILDB;
						NILDB->color=2;
						NILDB->parent=par;
					}
					q->parent=NULL;
				}
				
				if(q->color==1)
				{
					fixToken(NILDB);
					//display(par->list);
					if(par->left==NILDB)
						par->left=NIL;
					else if(par->right==NILDB)
						par->right=NIL;
					free(q);
				}
				else if(q==root)
					free(q);
				
				NILDB->parent=NULL;
				NILDB->color=2;

			}

			else if((q->right!=NIL) && (q->left==NIL))	//if node has only right child
			{
				
				child = q->right;
				if (q->parent!=NULL)
				{
					par=q->parent;
					if(q==par->left)
					{
						par->left = child;
						child->parent = par;
						sibling = par->right;
					}
					else if(q==par->right)
					{
						par->right = child;
						child->parent = par;
						sibling = par->left;
					}
					child->color++;
					if(child->color==1)
						child->color=1;
					else if(child->color==2)
					{
						fixToken(child);
					}
					deleteList(q->list);
					free(q);
				}
				else
				{
					root=q->right;
					root->color=1;
					q->right=NULL;
					deleteList(q->list);
					free(q);
					root->parent=NULL;
				}
			}

			else if((q->right==NIL) && (q->left!=NIL))	//if node has only left child
			{
				child = q->left;
				if (q->parent!=NULL)
				{
					par = q->parent;
					if(q==par->left)
					{
						par->left = child;
						child->parent = par;
						sibling = par->right;
					}
					else if(q==par->right)
					{
						par->right = child;
						child->parent = par;
						sibling = par->left;
					}
					child->color++;
					if(child->color==1)
						child->color=1;
					else if(child->color==2)
					{
						fixToken(child);
					}
					deleteList(q->list);
					free(q);
				}
				else
				{
					root=q->left;
					root->color=1;
					q->left=NULL;
					deleteList(q->list);
					free(q);
					root->parent=NULL;
				}
			}

			else if((q->right!=NIL) && (q->left!=NIL))	//node has both the children
			{
				struct tree* temp=q->left;
				
				//for (temp;temp->right!=NIL;temp=temp->right);		//we go once right and continuously left to get the predecessor
				while(temp->right!=NIL)
					temp=temp->right;
		
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
		printf("-1\n");
		return;
	}
	
	int p = compare(head2, n->list);
	if((p==2)&&(S_flag==0))		//if S is the root, we need to print only the color of root
	{
		//printf(" %d\n", root->color);
		if(root->color==0)
			printf(" R\n");
		else
			printf(" B\n");
		return;
	}
	S_flag=1;
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
		displayPath(head1);
		printf(" %c\n", get_color(n->color));
		/*if(n->color==0)
				printf(" R\n");
			else
				printf(" B\n");*/
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
		root->left=NIL;	//making nil nodes of black color
		root->right=NIL;	//making nil nodes of black color
		root->list=n;
		root->color=1;	//color of root is black
		return;
	}
	if (node->list!=NULL)
	{
		if(compare(n, node->list)==1)
		{
			if (node->right->list==NULL)
			{
				struct tree* p = (struct tree*)malloc(sizeof(struct tree));
				p->parent=node;
				node->right=p;
				p->list = n;
				p->left=NIL;
				p->right=NIL;
				p->color=0;	//color of newnode will be Red
				fixInsert(p);
			}
			else
				insertToBST(node->right,n);
		}
		else if(compare(n, node->list)==0)
		{
			if (node->left->list==NULL)
			{
				struct tree* p = (struct tree*)malloc(sizeof(struct tree));
				p->parent=node;
				node->left=p;
				p->list = n;
				p->left=NIL;
				p->right=NIL;
				p->color=0;
				fixInsert(p);
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
	if(n==NULL||n==NIL)
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

void insertPath(int digit)		//inserts data into linked list for displaying the path
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

void display_col(struct tree* dis)
{
	if(dis->list==NULL)
		return;
	struct tree* n = dis;
	while(1)
	{
		if (n->list!=NULL)
			{printf("%d", n->list->num);}	//displays the answer digit by digit
		if(n->list->next==NULL)
			{break;}
		else
			n->list=n->list->next;
	}
	printf(" %d\n", n->color);
}

void displayPath(struct number* n)
{
	if(n==NULL)
		return;
	while(1)
	{
		if (n!=NULL)
		{
			printf("%d", n->num);		//displays the answer digit by digit
		}	
		if(n->next==NULL)
			{break;}
		else
			n=n->next;
	}
}

int getnum(char a)	//fgetc takes input as character. So we subtract 48 to convert to integer
{
	return (a-48);
}

char get_color(int num)	//returns R for Red and B for Black
{
	if(num==0)
		return 'R';
	else if(num==1||num==2)
		return 'B';
}

int isOnLeft(struct tree* node)	//returns 1 is node is left child else returns 0;
{
	if(node==node->parent->left)
		return 1;
	else if(node==node->parent->right)
		return 0;
	else return -1;
}


void detailedTraversal(struct tree* Z) {
	if(Z == NULL || Z == NIL) return;
	if(Z->left == NIL) printf("NIL(%c) <- ", NIL->color == 1 ? 'B':'R');
	else {
		display(Z->left->list);
		printf("(%c) <- ", Z->left->color == 1 ? 'B':'R');
	}
	display(Z->list);
	printf("(%c) -> ", Z->color == 1 ? 'B':'R');
    if(Z->right == NIL) printf("NIL\n");
	else {
		display(Z->right->list);
		printf("(%c)\n", Z->right->color == 1 ? 'B':'R');
	}
	detailedTraversal(Z->left);
	detailedTraversal(Z->right);
}
