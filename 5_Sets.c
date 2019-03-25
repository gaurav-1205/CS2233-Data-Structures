#include <stdio.h>
#include <stdlib.h>

int n;		//number of disjoint singleton sets
char prev_digit;

struct set
{
	int data;
	int rank;
	struct set* parent;
};

int makeSet()
{
	char digit;
	if(prev_digit=='N')
		digit = 'N';
	else
		digit=fgetc(stdin);

	while(digit!=EOF)
	{
		if(digit=='N')
		{
			scanf("%d", &n);
			struct set* a[n];
			for(int i=0; i<n; i++)
			{	
				a[i] = (struct set*)malloc(sizeof(struct set));
				a[i]->data=i+1;		//This will create n disjoint singleton sets
				a[i]->rank=1;
				a[i]->parent=a[i];
			}
			while((digit=fgetc(stdin))!=EOF)
			{
				prev_digit = digit;
				if(digit=='N')
				{ 
					for(int i=0; i<n; i++)
						free(a[i]);	//frees the memory
					return 1;		//This call leads again to function makeSet
				}
				if(digit=='R')
				{
					int get_rank;
					scanf("%d", &get_rank);
					if(get_rank>n || get_rank<=0)
						printf("-1\n");
					else
						printf("%d\n", a[get_rank-1]->rank);
				}
				if(digit=='U')
				{
					int u[2];
					for(int i=0; i<2; i++)
						scanf("%d", &u[i]);
					if((u[0]<=n)&&(u[1]<=n)&&(u[0]>0)&&(u[1]>0))
					{
						struct set* ptr1 = a[u[0]-1];
						struct set* ptr2 = a[u[1]-1];
						while(ptr1->parent->data!=ptr1->data)
							ptr1=ptr1->parent;
						while(ptr2->parent->data!=ptr2->data)
							ptr2=ptr2->parent;
						if(ptr1->rank==ptr2->rank)
						{
							ptr1->rank++;
							ptr2->parent=ptr1;
						}
						else if(ptr1->rank < ptr2->rank)
							ptr1->parent=ptr2;
						else if(ptr1->rank >= ptr2->rank)
							ptr2->parent=ptr1;
					}
				}
				if(digit=='?')
				{
					int q[2];
					for(int i=0; i<2; i++)
						scanf("%d", &q[i]);
					if((q[0]<=n)&&(q[1]<=n)&&(q[0]>0)&&(q[1]>0))
					{
						struct set* ptr1 = a[q[0]-1];
						struct set* ptr2 = a[q[1]-1];
						while(ptr1->parent->data!=ptr1->data)
							ptr1=ptr1->parent;
						while(ptr2->parent->data!=ptr2->data)
							ptr2=ptr2->parent;
						if(ptr1->data==ptr2->data)
							printf("1\n");
						else
							printf("0\n");
					}
					else
						printf("-1\n");
				}
				if(digit=='S')
				{
					int s;
					scanf("%d", &s);
					if((s<=n)&&(s>0))
					{
						struct set* ptr1 = a[s-1];
						while(ptr1->parent->data!=ptr1->data)
							ptr1=ptr1->parent;
						printf("%d\n", ptr1->data);
					}
					else
						printf("-1\n");
				}
			}
		}
	}
	return 0;
}

int main()
{
	int num = makeSet();
	while(num!=0)
		num = makeSet();		//calls newgraph everytime we press N
}