#include<iostream>
#include<cstdlib>
#include <iomanip>

using namespace std;

struct node{
    int data;
    float arrivalTime,burstTime,processC,turnaroundTime,waitingTime,responseTime,relativeDelay;
    struct node *next;
};

void newNodeins(node **p, int no,float arrT,float burstT,float *firstR){
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

void displayGantchatt(node *p, int process){
    int i;
   node *r = p;
    cout<<"\n\nGannt Chart:\n";
    for(i=1;i<= process; i++)
       cout<<"--------";
    cout<<"\n";

    for(i=1; i<= process; i++){
        cout<<"|  P"<<setprecision(2) <<p->data<<"   ";
        p = p->next;
    }
    cout<<"|\n";

    for(i=1; i<= process; i++)
        cout<<"--------";

    cout<<"\n";
    cout<<setprecision(2) <<r->arrivalTime<<"\t";
    for(i=1; i<= process; i++){
        cout<<setprecision(2) <<r->processC<<"\t";
        r = r->next;
    }
}

void showFCFS(node *p,int pr){
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

int main(){
 node *head = NULL;
    int process,i;
    float arrival_time,burst_time,first_response;
    printf("Enter the no. of Process: ");
    scanf("%d",&process);
    for(i=1; i<= process; i++){
        printf("\nEnter the Details for Process %d: \n",i);
        printf("\tArrival Time: ");
        scanf("%f",&arrival_time);
        printf("\tBurst Time: ");
        scanf("%f",&burst_time);
        if(i==1)
            first_response = arrival_time;
        newNodeins(&head,i,arrival_time,burst_time,&first_response);
    }

    printf("\n<-------------------------------------------------  START ------------------------------------->\n");
    displayGantchatt(head,process);
    showFCFS(head,process);
    printf("\n<-------------------------------------------------  END ------------------------------------->\n");

	return 0;
}
