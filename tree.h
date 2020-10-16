#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include <time.h>
#include<math.h>

typedef struct tree
{
	int id;
	char name[50];
	char seller[50];
	int total;
	float cost;
	queue *q;
	struct tree *right, *left;
}tree;

queue* give_queue(tree* t, char name[])
{
	if(t==NULL)
    {
        printf("\n\nError!");
        return NULL;
    }

    if(strcmp(t->name,name)==0)
    {
       return t->q;
    }

    if(strcmp(name,t->name)<0)
        give_queue(t->left,name);
    else if(strcmp(name,t->name)>0)
        give_queue(t->right,name);

}

float give_cost(tree* t,char name[])
{
	if(t==NULL)
    {
        printf("Not found");
        return 0;
    }

    if(strcmp(t->name,name)==0)
    {
    	return t->cost;
    }

    if(strcmp(name,t->name)<0)
        give_cost(t->left,name);
    else if(strcmp(name,t->name)>0)
        give_cost(t->right,name);

}

tree* givetree(tree *t,char name[])
{
	if(t==NULL)
    {
        printf("Not found");
        return 0;
    }

    if(strcmp(t->name,name)==0)
    {
    	return t;
    }

    if(strcmp(name,t->name)<0)
        give_cost(t->left,name);
    else if(strcmp(name,t->name)>0)
        give_cost(t->right,name);

}



void cal_tot(tree *t)
{
	if(t!=NULL)
	{
		t->total=0;
		for(int i=t->q->front;i<=t->q->rear;i++)
			t->total+=t->q->qty[i];
	}

}


tree* insert(tree *t,tree *temp)
{
    if(t==NULL)
    {
        t=(tree*)malloc(sizeof(tree));
        //printf("Enter manufacture date(dd/mm/yyy) 	: ");
    //scanf("%s",mfg);
    //printf("Enter expiry date(dd/mm/yyyy) 		: ");
    //scanf("%s",exp);

        if(t==NULL)
            printf("Out of space");

        else
        {

        	t->id=temp->id;
            strcpy(t->name,temp->name);
            strcpy(t->seller,temp->seller);
            t->total=temp->total;
            t->cost=temp->cost;
            //strcpy(t->mfg,mfg);
            //strcpy(t->exp,exp);
            t->right=t->left=NULL;

            t->q=createQueue(20);
            enqueue(t->q,t->total);
        }
    }

    else if(strcmp(temp->name,t->name)<0){
        //printf("Added to left!\n");
        t->left=insert(t->left,temp);

    }
        else if(strcmp(temp->name,t->name)>0){
        t->right=insert(t->right,temp);
        //printf("Added to Right!\n");
        }

    return t;
}

void display(tree *t)
{
    if(t==NULL)
        return;
    printf("\n-------------------------------------------------------------------\n");
	printf("ID 	        :%d\n",t->id);
	printf("Name 	        :%s\n",t->name);
	printf("Seller 	        :%s\n",t->seller);
	printf("Total Quantity	:%d tabs\n",t->total);
	printf("Price/tab	:Rs.%.2f\n",t->cost);
    printf("Stock       :\n");
    if(t->total>0)
    {
        printf("           Quantity    Manufacture Date    Expiry Date    Validity(days)\n");
        for(int i=t->q->front;i<=t->q->rear;i++)
        {
            printf("Batch %2d\t",i+1);
            printf("%3d\t",t->q->qty[i]);
            printf("   %2d/%2d/%4d\t",t->q->manf[i].dd, t->q->manf[i].mm, t->q->manf[i].yy);
            printf("   %2d/%2d/%4d\t",t->q->exp[i].dd, t->q->exp[i].mm, t->q->exp[i].yy);
            printf("   %4d\n",t->q->validity[i]);
        }

    printf("\n-------------------------------------------------------------------\n");

    }

	//printf("Manufacture date 		:%s",t->mfg);
	//printf("Expiry date		 		:%s",t->exp);
}


int check(tree *t, int a)
{
	int f=-1;
	if(t!=NULL)
	{

		for(int i=t->q->front;i<=t->q->rear;i++)
		{
			if(t->q->validity[i]<20)
			{
				printf("\nValidity of %s is %d days please dispose medicine immediately!!",t->name,t->q->validity[i]);
				int ch;
				printf("\n1-dispose now\n2-Remind me later\n  Option: ");
				scanf("%d",&ch);
				if(ch==1)
				{
					printf("\nDisposing medicine....");
                    int temp=t->q->qty[i];
                    if(i==t->q->front){
                        t->q->front = (t->q->front + 1)%t->q->capacity;

                    }
                    else{
                        t->q->qty[i]=t->q->qty[i+1];
                        t->q->validity[i]=t->q->validity[i+1];
                        t->q->manf[i]=t->q->manf[i+1];
                        t->q->exp[i]=t->q->exp[i+1];
                        t->q->rear=(t->q->rear-1)%t->q->capacity;
                    }

                    t->q->size = t->q->size - 1;
                    t->total-=temp;
        			return -1;
        		}
        	}

        }
    }
    if(t->total<a)
    {
    	printf("\nNot enough stock!! ");
    	return -1;
    }
    else
    {
    	return 1;

    }
}

int warn(tree *t)
{
    int f=1;
	if(t!=NULL)
	{
		for(int i=t->q->front;i<=t->q->rear;i++)
		{
			if(t->q->validity[i]<20)
			{
			    f=-1;
				printf("\nValidity of %s is %d please dispose medicine immediately!!",t->name,t->q->validity[i]);
				int ch;
				printf("\n\n1-dispose now\n2-Remind me later\n  Option: ");
				scanf("%d",&ch);
				if(ch==1)
				{
					printf("\n\nDisposing medicine....\n");
                    int temp=t->q->qty[i];
                    if(i==t->q->front){
                        t->q->front = (t->q->front + 1)%t->q->capacity;

                    }
                    else{
                        t->q->qty[i]=t->q->qty[i+1];
                        t->q->validity[i]=t->q->validity[i+1];
                        t->q->manf[i]=t->q->manf[i+1];
                        t->q->exp[i]=t->q->exp[i+1];
                        t->q->rear=(t->q->rear-1)%t->q->capacity;
                    }

        			t->q->size = t->q->size - 1;
        			t->total-=temp;

				}
			}
			warn(t->left);
			warn(t->right);
		}
	}
    return f;
}




void search(tree *t,char name[50])
{
    if(t==NULL)
    {
        printf("Not found");
        return;
    }

    if(strcmp(t->name,name)==0)
    {
        display(t);
        return;
    }

    if(strcmp(name,t->name)<0)
        search(t->left,name);
    else if(strcmp(name,t->name)>0)
        search(t->right,name);
}



void inorder(tree *t)
{
    if(t==NULL)
        return;
    inorder(t->left);
    display(t);
    inorder(t->right);
}
