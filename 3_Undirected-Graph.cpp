#include <bits/stdc++.h>
using namespace std;

struct graphLL	//this is used to access the adjacency list
{
	int data;
	struct graphLL* next;
};

struct queue1	//This queue is used for breadth first search
{
	int num;
	struct queue1* right;
};

struct queue1 *head_q=NULL, *tail_q=NULL;

void deleteList(struct graphLL* node)	//empties the linked list
{
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

void deleteQueue(struct queue1* node)	//empties the queue
{
	struct queue1* current;
	current = node;
	struct queue1* after; 

	while (current != NULL)  
	{ 
		after = current->right; 
		free(current); 
		current = after; 
	}
}
int n=200; 
void enqueue(int v)
{
	struct queue1* p = (struct queue1*)malloc(sizeof(struct queue1));
	p->num = v;
	p->right = NULL;
	if(tail_q==NULL && head_q==NULL)
	{
		tail_q=p;
		head_q=p;
	}
	else
	{
		head_q->right = p;
		head_q=p;
	}
}

int dequeue()
{
	if (tail_q!=NULL)
	{
		int t_num = tail_q->num;
		tail_q=tail_q->right;
		if (tail_q==NULL)
			head_q=NULL;
		return t_num;
	}
	return -20;
}

struct graphLL* insert(struct graphLL* node, int digit)		//inserts data in the linked list
{
	
	struct graphLL* ptr1;
	struct graphLL* p = (struct graphLL*)malloc(sizeof(struct graphLL));
	p->data = digit;
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

int main(){
	int parent[n];
	char digit;
	struct graphLL* a[n]={NULL};
	int rem_u=0;	//remember the previous input number for optimization
	
	while((digit=fgetc(stdin))!=EOF)
	{
		if(digit=='N')
		{
			scanf("%d", &n);
			if(a[n]!=NULL)	//memory management
			{
				for(int i=1; i<=n; i++)
				{
					deleteList(a[i-1]);
					deleteQueue(tail_q);
					a[i-1]=NULL;
					tail_q=NULL;
					head_q=NULL;
				}
			}
			for(int i=1; i<=n; i++)	//initailizing the adjacency list
			{
				a[i-1] = (struct graphLL*)malloc(sizeof(struct graphLL));
				a[i-1]->data=i;
			}				
		}

		if(digit=='E')
		{
			int num1[n], j=0;
			scanf("%d", &num1[0]);
			for(int i=1; i<n; i++)	//we insert the numbers into an array and then enter into the respective adjacency list
			{
				scanf("%d", &num1[i]);
				a[num1[0]-1] = insert(a[num1[0]-1], num1[i]);
				if((digit=fgetc(stdin))=='\n')
					break;
			}
			j=num1[0]-1;
		}

		if(digit=='?')
		{
			int find[2];
			for(int i=0; i<2; i++)
				scanf("%d", &find[i]);
			struct graphLL *ptr = a[find[0]-1];
			while(ptr!=NULL)
			{
				if(ptr->data==find[1])
				{
					printf("1\n");
					break;
				}
				ptr=ptr->next;
			}
			if(ptr==NULL)
				printf("0\n");
		}

		if(digit=='B')
		{
			string s1="";	//This is the output string. I will concatenate it with the the BFS values
			int color[n];	// 0->White; 1->gray; 2->black
			for(int i=0;i<n;i++)
			{
				color[i]=0;		//initializing all colors to white
				parent[i]=-1;	//initializing parents to -1
			}
			int s;
			scanf("%d", &s);
			rem_u=s;	//this value remembers the previous value of input for faster calculations
			int d[n], pi[n], j=0;
			j=s-1;
			enqueue(j+1);
			parent[j] = -20;	//after enqueing, the element's parent will be equal to -20
			color[j]=1;		//color will be gray
			
			while((head_q!=NULL)&&(tail_q!=NULL))	//while Q is not equal to null
			{
				int u = dequeue();
				s1=s1+to_string(u)+" ";		//concatenating the output part
				color[u-1]=2;		//after dequeing, the color will be black
				
				for (struct graphLL* temp=a[u-1]; temp!=NULL; temp=temp->next)
				{
					if (color[temp->data -1]==0)	//if the node is unvisited
					{
						enqueue(temp->data); 	//enqueues the corresponding elements
						color[temp->data -1]=1;
						parent[temp->data -1] = u;
					}
				}
			}

			cout<<s1<<"\n";

			for(int i=0; i<n; i++)
			{
				if(parent[i]==-1)				
					parent[i]=-5;	//assigning the parents as -5 if the number has no link with the input vertex			
			}

		}
		if(digit=='P')
		{
			int path[2];
			for(int i=0; i<2; i++)
			{
				scanf("%d", &path[i]);
			}
			if(path[0]!=rem_u)		//if the input is not same as the previous one, we need to do BFS again
			{
				int color[n];
				for(int i=0;i<n;i++)
				{
					color[i]=0;
					parent[i]=-1;
				}
				int s=path[0];
				rem_u=s;
				int d[n], pi[n], j=0;
				
				j=s-1;
		
				enqueue(j+1);
				parent[j] = -20;
				color[j]=1;
				
				while((head_q!=NULL)&&(tail_q!=NULL))
				{
					int u = dequeue();
					color[u-1]=2;

					for (struct graphLL* temp=a[u-1]; temp!=NULL; temp=temp->next)
					{
						if (color[temp->data -1]==0)
						{
							enqueue(temp->data); color[temp->data -1]=1;
							parent[temp->data -1] = u;

						}
					}
				}
				for(int i=0; i<n; i++)
				{
					if(parent[i]==-1)				
						parent[i]=-5;		
				}

			}
			if(parent[path[1]-1]==-5)	//if the 2nd number does not occur in 1st number's path, then we output -1
			{
				cout<<-1<<"\n";
			}
			else
			{
				int temp1=path[1]-1;
				string s_path = "";
				while(parent[temp1]!=-20)
				{
					s_path=to_string(temp1+1)+" "+s_path;	//concatenating the output part
					temp1=parent[temp1]-1;
				}
				s_path=to_string(path[0])+" "+s_path;
				cout << s_path << "\n";
			}
			
		}		
	}
	
	return 0;
}