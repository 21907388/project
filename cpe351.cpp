#include<iostream>
#include<cstdlib>
#include <iomanip>
#include<getopt.h>

using namespace std;

struct node{
    int data;
    float arrivalTime,burstTime,processC,turnaroundTime,waitingTime,responseTime,relativeDelay,priority;
    struct node *next;
};

void newNodeins(node **p, int no,float arrT,float burstT,float *firstR){

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
    *firstR = *firstR + burstT; 


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
    cout<<"\n\n\nProcess Details after first come, first served: ";
    while(p!=NULL){
        cout<<"\n Process "<<setprecision(2)<<p->data<<"\n";
        cout<<"Arrival Time: "<<setprecision(2)<<p->arrivalTime<<"\n";
        
        cout<<"Burst Time: "<<setprecision(2)<<p->burstTime<<"\n";
        
        cout<<"Waiting Time: "<<setprecision(2)<<p->waitingTime<<"\n";
    
        
        tWaitingTime += p->waitingTime;
        
        p = p->next;

    }
    cout<<"\n\n\nOverall Details:\n";
    cout<<" Throughput: "<<setprecision(2)<<pr/tBurstTime<<"\n";
      cout<<" Average Waiting Time: "<<setprecision(2)<<tWaitingTime/pr<<"\n";

}

void printoutput(char filename[50]){
	cout<<"can not write output to"<<filename;
}
int main(int argc,char **argv){
	int option,oflag=0,fflag=0;
	char *filename;
	while ((option=getopt(argc,argv,"of"))!=-1){
		switch (option){
			case 'o':
			if (oflag){
				cout<<"only one option\n";
				exit(1);
			}
			else {
			oflag++;
			fflag++;
			}
			cout<<"  output command!";
			filename=optarg;
			cout<<" can not do this action ";
			exit(1);
			break;
			case 'f':
			if	(fflag){
				cout<<"only one option\n";
				exit(1);
			}
			else {
			oflag++;
			fflag++;
			}
			cout<<" input command!(can not be done you need to enter the input)";
			filename=optarg;
			cout<<" can not do this action on";
			exit(1);
			break;
				
			
		}
	}
 node *head = NULL;
    int process,i,options;
    float arrival_time,burst_time,first_response,prio;
   cout<<"Enter the no. of Process: ";
    cin>>process;
    for(i=1; i<= process; i++){
        cout<<"\nEnter the Details for Process "<<i<<" \n";
        cout<<"\tArrival Time: ";
        cin>>arrival_time;
       cout<<"\tBurst Time: ";
        cin>>burst_time;
         cout<<"\tPriority: ";
        cin>>prio;
        if(i==1)
            first_response = arrival_time;
        newNodeins(&head,i,arrival_time,burst_time,&first_response);
    }
    
    cout<<"\n\t CPU SCHEDULING SIMILATOR \n";
    	cout<<"\n Please pick one option among the ones below (if this is your frist time it is recommand that you pick option <1>) ";
	cout<<" \n 1) Scheduling Method (None)";
	cout<<" \n 2) Preemptive Mode (Off)";
	cout<<" \n 3) Show Result ";
	cout<<" \n 4) End Program\n ";
	cin>>options;

	switch (options){
		case 1 :
			cout<<" \t Scheduling method ";
			int sched;
			cout<<" Please pick one scheduling method among the ones below";
			cout<<" \n 1)None: None of scheduling method chosen";
            cout<<" \n 2)First Come, First Served Scheduling";
            cout<<" \n 3)Shortest-Job-First Scheduling";
            cout<<" \n 4)Priority Scheduling";
            cout<<" \n 5)Round-Robin Scheduling\n "; 
            cin>>sched;
            switch (sched){
            case 1 :
			   cout<<" None of the scheduling method chosen";
			   
			   break;
			case 2 :
			   cout<<" \n\tFirst come, frirst served scheduling";
		    
               displayGantchatt(head,process);
               showFCFS(head,process);
               
               
		    break;
		    case 3 :
		       cout<<" \n\tShortest-Job-First Scheduling";
		    
			break;   
		    case 4 :
		    	cout<<" \n\tPriority Scheduling";
		    
			break;	
		    case 5 :
		    	cout<<" \n\tRound-Robin Scheduling";
				
			}
			case 3:
			  showFCFS(head,process);	
		}


    
   
	return 0;
}
