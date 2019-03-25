#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define inf 214748647		//inf for int

int n;		//input size 
int size, len;	//These vairables are used to get the minimum element of the priority queue
int constraint=0;	//This variable is used to change the key value to extract min from the priority queue
struct number *head1=NULL;
char prev_digit='p';

struct graphLL	//this is used to access the adjacency list
{
	int data;
	int weight;
	struct graphLL* next;
};

struct number	//This struct is used for linked list which displays path
{
	int num;
	struct number* left;
	struct number* right;
};

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int parent(int x)
{
	return floor(x/2);
}

int left(int x)
{
	return 2*x + 1;
}

int right(int x)
{
	return 2*x + 2;
}

void minHeapify(int a[], int i)	//This function forms the min-Heap
{
	int s;
	int l = left(i);
	int r = right(i);
	if(l<size && a[l]>a[i])
		s = l;
	else
		s = i;
	if(r<size && a[r]>a[s])
		s = r;
	if(s!=i)
	{
		swap(&a[s], &a[i]);
		minHeapify(a, s);
	}
}

void buildMinHeap(int a[])
{
	int i;
	size = len;
	int len1 = floor(len/2);
	for(i=len1-1; i>=0; i--)
	{
		minHeapify(a, i);
	}
}

int priority_queue(int a[], int b[])	//This function returns the index of the extracted min.
{
	int i;
	buildMinHeap(a);
	for(i=len-1; i>0; i--)
	{ 	
		swap(&a[0], &a[i]);
		size--;
		minHeapify(a, 0);
	}
	for(int i=0; i<n; i++)
	{
		if(b[i]==a[constraint])
		{
			return i;
		}
	}
}

void insertLL(int digit)		//inserts data in the linked list. This stores the path from (x to y) in (P x y).
{
	struct number* p = (struct number*)malloc(sizeof(struct number));
	p->num = digit;
	p->left = NULL;
	p->right=NULL;
	if(head1==NULL)
	{
		head1 = p;
		return;
	}	
	struct number* ptr1 = head1;
	ptr1->left = p;			//stores data with the MSB on the rightmost node.
	p->right = ptr1;
	p->left=NULL;
	head1=p;
}

void deleteList(struct graphLL* node)	//deletes the adjacency list
{
	if(node==NULL)
		return;
	struct graphLL* current;
	current = node;
	struct graphLL* after; 
	while (current != NULL)  
	{ 
		after = current->next; 
		free(current); 
		current = after; 
	}
}

void deleteList_path(struct number* node)	//deletes the linked list used for storing path
{
	if(node==NULL)
		return;
	struct number* current;
	current = node;
	struct number* after; 
	while (current != NULL)  
	{ 
		after = current->right; 
		free(current); 
		current = after; 
	}
}

struct graphLL* insert(struct graphLL* node, int digit, int w)		//inserts data in the respective adjacency list
{
	struct graphLL* ptr1;
	struct graphLL* p = (struct graphLL*)malloc(sizeof(struct graphLL));
	p->data = digit;
	p->weight = w;
	p->next = NULL;
	if(node==NULL)
	{
		node=p;
		return node;
	}
	for(ptr1 = node; ptr1->next != NULL; ptr1 = ptr1->next);

	ptr1->next = p;
	return node;
}

void display(struct number* n)	//prints the linked list for displaying the path
{
	if(n==NULL)
		return;
	struct number *ptr = n;
	while(ptr!=NULL)
	{
		printf("%d ", ptr->num);
		ptr=ptr->right;
	}
	printf("\n");
}

int get_min(int arr[], int sor[])	//This function returns the index of the extracted min
{
	len = n;
	for(int i=0; i<n; i++)
	{
		sor[i] = arr[i];
	}
	constraint++;
	int min = priority_queue(sor, arr);
	return min;
}

int newGraph()
{
	char digit;
	int s;
	int d[n], parent[n], S[n], sor_array[n];
	if(prev_digit=='N')
		digit = 'N';
	else
		digit=fgetc(stdin);

	while(digit!=EOF)
	{
		if(digit=='N')
		{
			scanf("%d", &n);
			struct graphLL* a[n];
			int rem_array[n][n], rem_par[n][n];		//these arrays remember the updated weights and parents for faster calculations once these are explored
			for(int i=0; i<n; i++)
			{	
				a[i] = (struct graphLL*)malloc(sizeof(struct graphLL));
				a[i]->data=i+1;		//This will automatically create n vertices if any of the the vertex is not specified using E
				a[i]->weight=0;
				a[i]->next=NULL;
				for(int j=0; j<n; j++)
				{
					rem_array[i][j] = -5;		//initialize to a random value
					rem_par[i][j] = -5;
				}
			}
			while((digit=fgetc(stdin))!=EOF)
			{
				prev_digit = digit;
				if(digit=='N')
				{
					for(int i=0; i<n; i++)
					{
						deleteList(a[i]);	//frees the memory
						a[i]=NULL;
					}
					return 1;		//This call leads again to function newgraph
				}
				if(digit=='E')
				{
					int arr_size = 2*n-1;	//maximum possible individual array size
					int num1[arr_size], j=0;
					scanf("%d", &num1[0]);
					for(int i=1; i<2*n-1; i=i+2)	//we insert the numbers into an array and then enter into the respective adjacency list
					{
						scanf("%d", &num1[i]);
						scanf("%d", &num1[i+1]);
						a[num1[0]-1] = insert(a[num1[0]-1], num1[i], num1[i+1]);	//inserts the nodes with the edge values				
						if((digit=fgetc(stdin))=='\n')
							break;
					}
				}
				if(digit=='?')
				{
					int find[2];
					for(int i=0; i<2; i++)
						scanf("%d", &find[i]);
					if(find[0]==find[1])	//if inputs are same numbers
						printf("-1\n");
					else
					{

						struct graphLL *ptr = a[find[0]-1];	//The first number gives the pointer
						while(ptr!=NULL)
						{
							if(ptr->data==find[1])
							{
								printf("%d\n", ptr->weight);
								break;
							}
							ptr=ptr->next;
						}
						if(ptr==NULL)
							printf("-1\n");		//prints -1 if they do not have a common link
					}
				}
				if(digit=='D')
				{
					constraint = 0;
					int s, D_flag=0;
					int i, l=0;
					scanf("%d", &s);
					int d[n], parent[n], S[n], sor_array[n];
					if(s>n)		//If the input number is greater than n, it will print -1 for all vertices
					{
						for(int i=0; i<n; i++)
							printf("%d -1\n", i+1);
					}
					else
					{
						if(rem_array[s-1][0]==-5)	//checks if the value is explored and runs the dijkstra's algorithm only if unexplored
						{
							
							for(int i=0; i<n; i++)
							{
								d[i] = inf;
								parent[i] = -5;
								S[n] = -20;
							}
							d[s-1] = 0;
							S[0] = s;
							int k = 0;						

							while(k!=n)
							{
								struct graphLL *ptr = a[S[k]-1]->next;
								
								while(ptr!=NULL)
								{
									int temp = d[S[k]-1]+ptr->weight;
									if(temp<d[ptr->data-1])
									{
										d[ptr->data-1] = temp;
										parent[ptr->data-1] = S[k];
									}
									ptr=ptr->next;
								}
								int min = get_min(d, sor_array);	//this is the extract min function
								k++;
								S[k] = min+1;		
							}
							for(int i=0; i<n; i++)
							{
								rem_par[s-1][i] = parent[i];	//update the parent and weight values for remembering
								rem_array[s-1][i] = d[i];
							}
						}
					

						for(i=0; i<n; i++)
						{
							printf("%d ", S[i]);
							if(sor_array[i]==inf)
							{
								if(D_flag==0)	//the next 2 loops are used to mark the unreachable vertices as visited and output -1 for them
								{
									for(l=i; l<n; l++)
									{
										for(int p=n; p>=1; p--)
										{
											for(int q=0; q<n; q++)
											{
												if(S[q]==p)
													break;
												else if(q==l)
												{
													S[l]=p;
													break;
												}
											}
										}
									}
								}
								D_flag=1;	//This flag changes so as to make sure that the above loops run only once per 'D'
								printf("-1\n");
							}
							else
								printf("%d\n", sor_array[i]);
						}
						D_flag=0;
					}
				}
				if(digit=='P')
				{
					constraint = 0;
					deleteList_path(head1);
					head1=NULL;
					int key=0;
					int d[n], parent[n], S[n], sor_array[n];
					int path[2];
	
					for(int i=0; i<2; i++)
						scanf("%d", &path[i]);

					if(rem_array[path[0]-1][0]==-5)		//checks if the value is explored and runs the dijkstra's algorithm only if unexplored
					{
						s=path[0];
						for(int i=0; i<n; i++)
						{
							d[i] = inf;
							parent[i] = -5;
							S[n] = -20;
						}
						d[s-1] = 0;
						S[0] = s;
						int k = 0;
						int prev = k;

						while(k!=n)
						{
							struct graphLL *ptr = a[S[k]-1]->next;
							while(ptr!=NULL)
							{
								int temp = d[S[k]-1]+ptr->weight;
								if(temp<d[ptr->data-1])
								{
									d[ptr->data-1] = temp;
									parent[ptr->data-1] = S[k];
								}
								ptr=ptr->next;
							}
							int min = get_min(d, sor_array);
							k++;
							prev=k;
							S[k] = min+1;		
						}
						for(int i=0; i<n; i++)
						{
							rem_par[s-1][i] = parent[i];
							rem_array[s-1][i] = d[i];
						}
					}

					if(rem_array[path[0]-1][path[1]-1]==inf)
						printf("-1\n");
					else
					{
						printf("%d ", rem_array[path[0]-1][path[1]-1]);
						key=path[1];
						while(key!=-5)		//finds the path from y to x
						{
							insertLL(key);		
							key = rem_par[path[0]-1][key-1];	
						}
						display(head1);		//displays the path
					}
				}
			}	
		}					
	}

	return 0;
}

int main()
{
	int num = newGraph();
	while(num!=0)
		num = newGraph();		//calls newgraph everytime we press N
}
