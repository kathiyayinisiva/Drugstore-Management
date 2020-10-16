#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include <time.h>
#include<math.h>
struct Date
{
	int dd,mm,yy;
};
typedef struct Date Date;

typedef struct queue
{
	int *validity;
	Date manf[20],exp[20];
	int *qty;
	int front,rear,size,capacity;

}queue;

int dater(int x)
{ int y=0;
    switch(x)
    {
        case 1: y=0; break;
        case 2: y=31; break;
        case 3: y=59; break;
        case 4: y=90; break;
        case 5: y=120;break;
        case 6: y=151; break;
        case 7: y=181; break;
        case 8: y=212; break;
        case 9: y=243; break;
        case 10:y=273; break;
        case 11:y=304; break;
        case 12:y=334; break;
        default: printf("Invalid Inputnnnn"); exit(1);
    }
    return(y);
}


int validate(struct Date m, struct Date e)
{

    int ref,dd1,dd2,i,vald;
    ref = m.yy;
    dd1=0;
    dd1=dater(m.mm);
    for(i=ref;i<m.yy;i++)
    {
        if(i%4==0)
        dd1+=1;
    }
    dd1=dd1+m.dd+(m.yy-ref)*365;
    dd2=0;
    for(i=ref;i<e.yy;i++)
    {
        if(i%4==0)
        dd2+=1;
    }
    dd2=dater(e.mm)+dd2+e.dd+((e.yy-ref)*365);
    vald=abs(dd2-dd1);
    return vald;
}



queue* createQueue(int maxelements)
{
    queue* q = (queue*) malloc(sizeof(queue));
    q->capacity = maxelements;

    q->front = q->size = 0;
    q->rear = maxelements - 1;

    q->qty = (int*) malloc(q->capacity * sizeof(int));
    q->validity = (int*)malloc(q->capacity * sizeof(int));
    return q;
}

int isFull(queue* q)
{
return (q->size == q->capacity);
}

int isEmpty(queue* q)
{
return (q->size == 0);
}

void enqueue(queue* q,int total)
{


    if (isFull(q))
        return;
    q->rear = (q->rear + 1)%q->capacity;
    //printf("Enter quantity: ");
    q->qty[q->rear]=total;
    //printf("Enter quantity: ");
    //scanf("%d",&q->qty[q->rear]);
    printf("\nEnter manufacture date(dd mm yyyy)  : ");
    scanf("%d %d %d",&q->manf[q->rear].dd,&q->manf[q->rear].mm,&q->manf[q->rear].yy);
    printf("Enter expiry date       (dd mm yyyy): ");
    scanf("%d %d %d",&q->exp[q->rear].dd,&q->exp[q->rear].mm,&q->exp[q->rear].yy);
    time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
    Date to ;

    to.yy=tm.tm_year + 1900;
    to.mm= tm.tm_mon + 1;
    to.dd=tm.tm_mday;
    q->validity[q->rear]=validate(to,q->exp[q->rear]);
    q->size = q->size + 1;

}

void sell(queue *q, int amt)
{
	int qt;
	qt=amt;
	/*if(q->validity[q->front]<10)
	{
		printf("\nMedicine valid only %d days",q->validity[q->front]);

		printf("\nDisposing medicine....");
		q->front = (q->front + 1)%q->capacity;
        q->size = q->size - 1;
        printf("\nTry again...");
        return;
	}*/
	if(q->qty[q->front]<amt){
		int t;
		t=q->qty[q->front];
		q->front = (q->front + 1);
        q->size = q->size - 1;
        sell(q,amt-t);
	}
	else if(q->qty[q->front]==amt)
	{
		q->front = (q->front + 1);
        q->size = q->size - 1;
	}
	else{
		q->qty[q->front]-=amt;

	}
}

void disp(queue *q)
{
	for(int i=q->front;i<=q->rear;i++)
	{
		printf("Quantity   :  %d 	Manufacture date 	:  %d-%d-%d 	Expiry date 	:  %d-%d-%d 	Validity   :  %d\n",q->qty[i],q->manf[i].dd,q->manf[i].mm,q->manf[i].yy,q->exp[i].dd,q->exp[i].mm,q->exp[i].yy,q->validity[i]);
	}
}

