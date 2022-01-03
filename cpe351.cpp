#include<iostream>
#include<stdio.h>
#include<cstdlib>
using namespace std;
struct node {
	int data;
	struct node *next;
};
struct node *createNode (int item){
	struct node *temp;
	temp = (struct node *)malloc(sizeof(node));
	temp->data=item;
	temp->next=NULL;
	return temp;
}
int isEmpty (struct node *header){
	if (header=NULL)
	//return 1;
	int g;
	else 
	return 0;
}
struct node * insertFront(struct node *header, int d)
{
	struct node *temp;
	temp=createNode(d);
	temp->next =header;
    header=temp;
    return header;
}


struct node * insertBack(struct node *header, int d)
{
	struct node *temp, *headertemp;
	temp=createNode(d);
    if(header==NULL){
        header=temp;
    return header;
    }
	headertemp=header;
	while(headertemp->next!=NULL)
      headertemp =headertemp->next;
    headertemp->next=temp;
    return header;
}

void insertAfter(struct node *afterNode, int d)
{
	struct node *temp;
	temp=createNode(d);
	temp->next=afterNode->next;
	afterNode->next=temp;
}
struct node * deleteFront(struct node *header)
{
	struct node *temp;
    if(header==NULL)
	return header;
    temp=header;
	header= header->next;
    free(temp);
    return header;
}


struct node * deleteBack(struct node *header)
{
	struct node *temp, *headertemp;
    if(header==NULL)
    return header;
	headertemp=header;
	while(headertemp->next->next!=NULL)
    headertemp =headertemp->next;
	temp=headertemp->next;
    headertemp->next=NULL;
    free(temp);
	return header;
}
void deleteAfter(struct node *afterNode)
{
	struct node *temp;
	if(afterNode->next==NULL || afterNode==NULL)
	return;
	temp =afterNode->next;
	afterNode->next=temp->next;
	free(temp);
}

struct node{
    int data;
    float arrivalTime,burstTime,processC,turnaroundTime,waitingTime,responseTime,relativeDelay;
    struct node *next;
};

void create_insert(node **p, int no,float arrT,float burstT,float *firstR){
    // CREATE NODE
    node *q,*r = *p;
    q = (node*)malloc(sizeof(node));
    q->data = no;
    q->arrivalTime = arrT;
    q->burstTime = burstT;
    q->responseTime = *firstR - arrT;
    q->processC = *firstR + burstT;
    q->turnaroundTime = q->processC - arrT;
    q->waitingTime = q->turnaroundTime - burstT;
    q->relativeDelay = q->turnaroundTime/burstT ;
    *firstR = *firstR + burstT; // Update First Response for next NODE

    // INSERT NODE AT END
    q->next = NULL;
    if(*p == NULL)
        *p = q;
    else{
        while(r->next != NULL)
            r = r->next;
        r->next = q;
    }
}

void gantt_chart(node *p, int process){
    int i;
   node *r = p;
    cout<<"\n\nGannt Chart:\n";
    for(i=1;i<= process; i++)
       cout<<"----------------";
    cout<<"\n";

    for(i=1; i<= process; i++){
        cout<<"|\t"<<setprecision(2) <<p->data<<"\t";
        p = p->next;
    }
    cout<<"|\n";

    for(i=1; i<= process; i++)
        cout<<"----------------";

    cout<<"\n";
    cout<<"\t"<<setprecision(2) <<r->arrivalTime;
    for(i=1; i<= process; i++){
        cout<<"\t"<<setprecision(2) <<r->processC;
        r = r->next;
    }
}

void display(node *p,int pr){
    float tTurnarTime,tWaitingTime,tRelDelay,tResTime,tBurstTime;
    tTurnarTime=tWaitingTime=tRelDelay=tResTime=tBurstTime= 0;
    printf("\n\n\nProcess Details:");
    while(p!=NULL){
        cout<<"\n Process "<<setprecision(2)<<p->data<<"\n";
        cout<<"Arrival Time: "<<setprecision(2)<<p->arrivalTime<<"\n";
        cout<<"Burst Time: "<<setprecision(2)<<p->burstTime<<"\n";
        cout<<"Turn Around Time: "<<setprecision(2)<<p->turnaroundTime<<"\n";
        cout<<"Waiting Time: "<<setprecision(2)<<p->waitingTime<<"\n";
        cout<<"Relative Delay: "<<setprecision(2)<<p->relativeDelay<<"\n";
        cout<<"Response Time: "<<setprecision(2)<<p->responseTime<<"\n";
        // Storing the Total value for average
        tTurnarTime += p->turnaroundTime; // ttat = ttat + p->tat
        tWaitingTime += p->waitingTime;
        tRelDelay+= p->relativeDelay;
        tResTime += p->responseTime;
        tBurstTime += p->burstTime;

        p = p->next;

    }
    cout<<"\n\n\nOverall Details:\n";
    cout<<" Throughput: "<<setprecision(2)<<pr/tBurstTime<<"\n";
    cout<<" Average Turn Around Time: "<<setprecision(2)<<tTurnarTime/pr<<"\n";
    cout<<" Average Waiting Time: "<<setprecision(2)<<tWaitingTime/pr<<"\n";
    cout<<" Average Relative Delay: "<<setprecision(2)<<tRelDelay/pr<<"\n"; 
    cout<<" Average Response Time: "<<setprecision(2)<<tResTime/pr<<"\n";
}

