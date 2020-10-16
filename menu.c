#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include <time.h>
#include<math.h>

#include"queue1.h"

#include"tree1.h"

void disp_menu()
{
	printf("\t\t");
	printf(" ______________________________\n\t\t");
	printf("|                              |\n\t\t");
	printf("|\t     MENU              |\n\t\t");
	printf("|______________________________|\n\t");
	printf("\t|                              |\n\t\t");
	printf("|\t1. Add new medicine    |\n\t\t");
	printf("|\t2. Update stock        |\n\t\t");
	printf("|\t3. Search medicine     |\n\t\t");
	printf("|\t4. Display             |\n\t\t");
	printf("|\t5. Sell                |\n\t\t");
	printf("|\t6. Validity check      |\n\t\t");
	printf("|\t7. Quit                |\n\t\t");
	printf("|                              |\n\t\t");
	printf("|______________________________|\n");
}

int main()
{
	tree *t,*temp;
	t=NULL;
	temp=(tree*)malloc(sizeof(tree));
	char name[50];
	int o;
	int qt;
	printf("==========================================================================================================================================");
	printf("\n\t\t\t\t\t\tWELCOME TO ABC PHARMACEUTICALS\n");
	printf("==========================================================================================================================================\n");

	while(1)
	{
		printf("\n\n");
		disp_menu();
		printf("\n\nOption: 	");
		scanf("%d",&o);

		switch(o)
		{
			case 1:
				printf("\n\nAdding medicine.....\n\n");
                printf("\nEnter id            : ");
                scanf("%d",&temp->id);
                printf("Enter name          : ");
			    scanf("%s",temp->name);
				printf("Enter seller        : ");
                scanf("%s",temp->seller);
                printf("Enter quantity(tabs): ");
                scanf("%d",&temp->total);
                printf("Price/tab           : ");
                scanf("%f",&temp->cost);
                t=insert(t,temp);
                printf("MEDICINE ADDED!\n");

				break;

			case 2:
				printf("\n\nUpdating stock....\n\n");
				printf("Enter the name of medicine: ");
				scanf("%s",name);
				printf("\nEnter the amount you want to buy: ");
				scanf("%d",&qt);
				if(give_queue(t,name)==NULL)
				{
					printf("\n\nMedicine not found!!");
					continue;
				}
				enqueue(give_queue(t,name),qt);
				cal_tot(givetree(t,name));
				printf("\nSTOCK UPDATED!\n");
				break;


            case 3:
            	printf("\n\nSearch Results...\n\n");
                printf("\nEnter name to search: ");
                scanf("%s",name);
                if(give_queue(t,name)==NULL)
				{
					printf("\n\nMedicine not found!!");
					continue;
				}
                search(t,name);
                break;

			case 4:
				inorder(t);
				break;
			case 5:
				printf("\n\nSelling Medicine....\n\n");
				char ch;
				char temp[15][15];
				float price[15],tot=0;
				int q[15],i=0;
				do{
					printf("\nEnter the name of medicine: ");
					scanf("%s",name);
					strcpy(temp[i],name);
					printf("\nEnter the amount you want to sell: ");
					scanf("%d",&qt);
					q[i]=qt;
					if(give_queue(t,name)==NULL)
					{
						printf("\n\nMedicine not found!!");
						continue;
					}
					int r=check(givetree(t,name),qt);
					if(r!=-1){

						sell(give_queue(t,name),qt);
						cal_tot(givetree(t,name));
						       float c;
						c=give_cost(t,t->name);
						c*=qt;
						price[i]=c;
						tot+=price[i];
						i++;

					}
					printf("\n\nDo you want to continue ? (y/n):  ");
					scanf(" %c",&ch);
				}while(ch=='y'||ch=='Y');
				printf("\n-----------------------------------\n");
				printf("\t    BILL\n\nITEM.NO\tNAME\tQTY\tPRICE\n");
				for(int j=0;j<i;j++){
					printf("%d\t%s\t%d\t%.2f\n",j+1,temp[j],q[j],price[j]);

				}
				printf("\n\t\tTOTAL :Rs.%.2f\n",tot);
				printf("-----------------------------------\n");

				break;
				case 6:
					printf("\n\n");
					int f=warn(t);
					if(f==1)
                        printf("All medicines are valid!\n");
					break;

			case 7:
			printf("\n\tThank you for using our service. For details contact- 235-4590 \n\n\tPlease ensure you take your belongings when you leave\n");
				exit(0);
		}
	}
return 0;
}
