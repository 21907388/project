#include<iostream>
#include<cstdlib>
#include <iomanip>
#include<getopt.h>
#include<fstream>

using namespace std;

struct node{
    int data;
    float arrivalTime,burstTime,processC,turnaroundTime,waitingTime,responseTime,finishingTime,relativeDelay,priority;
    struct node *next;
};
struct node* create_node( int no,float bursT,float arrT,float pr) {
	struct node *header = NULL;
	header = (struct node *) malloc(sizeof(node));
	header->data = no;
	header->burstTime = bursT;
	header->arrivalTime = arrT;
	header->next = NULL;

	return header;
}
struct node* sort_priority(struct node* header) {
	struct node* temp = header;
	struct node* i = temp;
	struct node* j = temp->next;
	for (i = temp; i != NULL; i = i->next) {
		for (j = i->next; j != NULL; j = j->next) {
			if ((int)(i->priority) - '0' > (int)(j->priority) - '0') {
				struct node* tempp = create_node(i->data, i->burstTime, i->arrivalTime, i->priority);
				i->data = j->data;
				i->burstTime = j->burstTime;
				i->arrivalTime = j->arrivalTime;
				i->priority = j->priority;

				j->data = tempp->data;
				j->burstTime = tempp->burstTime;
				j->arrivalTime= tempp->arrivalTime;
				j->priority = tempp->priority;

			}
		}
	}
	struct node* tempp = temp;
	return temp;
}

struct node* check_completion(struct node* header, int counter) {
	struct node* temp = header;
	struct node* i = temp;
	struct node* j = i->next;

	for (i = temp; i != NULL; i = i->next) {

		for (j = i->next; j != NULL; j = j->next) {

			if ((((int)(i->burstTime) - '0') > ((int)(j->burstTime) - '0')) &&
				(((int)(j->arrivalTime) - '0') <= counter)) {
				struct node* tempp = create_node(i->data, i->burstTime, i->arrivalTime, i->priority);

				i->data = j->data;
				i->burstTime = j->burstTime;
				i->arrivalTime = j->arrivalTime;
				i->priority = j->priority;

				j->data = tempp->data;
				j->burstTime = tempp->burstTime;
				j->arrivalTime = tempp->arrivalTime;
				j->priority = tempp->priority;
			}
		}
	}
	struct node* tempp = temp;
	return temp;
}

int is_empty_node(struct node* header) {
	if (header == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
struct node* sort_list(struct node* header) {
	struct node* temp = header;
	struct node* i = temp;
	struct node* j = temp->next;

	for (i = temp; i != NULL; i = i->next) {
		for (j = i->next; j != NULL; j = j->next) {
			if ((int)(i->arrivalTime) - '0' > (int)(j->arrivalTime) - '0') {
				struct node* tempp = create_node(i->data, i->burstTime, i->arrivalTime, i->priority);

			
				i->data = j->data;
				i->burstTime = j->burstTime;
				i->arrivalTime = j->arrivalTime;
				i->priority = j->priority;

				j->data = tempp->data;
				j->burstTime = tempp->burstTime;
				j->arrivalTime = tempp->arrivalTime;
				j->priority = tempp->priority;
			}

		}
	}
	struct node* tempp = temp;

	return temp;
}


struct node* delete_front(struct node* header) {
	struct node* temp;
	if (header == NULL)
		return header;

	temp = header;
	header = header->next;
	free(temp);

	return header;
}

void newNodeins(node **p, int no,float arrT,float burstT,float *firstR,float py){

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

void showFCFSinFile(node *p,int pr){
    float tTurnarTime,tWaitingTime,tRelDelay,tResTime,tBurstTime;
    tTurnarTime=tWaitingTime=tRelDelay=tResTime=tBurstTime= 0;
    ofstream fin("output.txt");
    fin<<"\n\n\nProcess Details after first come, first served: ";
    while(p!=NULL){
        fin<<"\n Process "<<setprecision(2)<<p->data<<"\n";
        fin<<"Arrival Time: "<<setprecision(2)<<p->arrivalTime<<"\n";
        
        fin<<"Burst Time: "<<setprecision(2)<<p->burstTime<<"\n";
        
        fin<<"Waiting Time: "<<setprecision(2)<<p->waitingTime<<"\n";
    
        
        tWaitingTime += p->waitingTime;
        
        p = p->next;

    }
    fin<<"\n\n\nOverall Details:\n";
    fin<<" Throughput: "<<setprecision(2)<<pr/tBurstTime<<"\n";
      fin<<" Average Waiting Time: "<<setprecision(2)<<tWaitingTime/pr<<"\n";

}
void shortestjobfirst(struct node* header) {

	struct node *temp = header;

	int wtm = 0, counter = 0;
	int pr = 1;
	float average = 0;
	temp = sort_list(temp);

	

	cout << "Scheuling Method: Shortest Job First(Non-Preemptive)" << endl;
	cout << "Process Waiting Times: " << endl;

	while (!(is_empty_node(temp))) {
		temp = check_completion(temp, counter);

		if (counter < (float)temp->arrivalTime - '0') {
			counter++;
			continue;
		}
	cout<< "P" << temp->data << ": " << wtm << endl;
		average += wtm;
		wtm += (float)temp->burstTime - '0';

		counter += (float)temp->burstTime - '0';

		temp = delete_front(temp);


		pr++;
	}
	cout << "Average waiting time " << average / (pr - 1);


}

void shortestjobfirstinFile(struct node* header) {

	struct node *temp = header;

	float wtm = 0, counter = 0;
	float pr = 1;
	float average = 0;
	temp = sort_list(temp);

	ofstream fin("output.txt");

	fin << "Scheuling Method: Shortest Job First(Non-Preemptive)" << endl;
	fin << "Process Waiting Times: " << endl;

	while (!(is_empty_node(temp))) {
		temp = check_completion(temp, counter);

		if (counter < (float)temp->arrivalTime - '0') {
			counter++;
			continue;
		}
		fin << "P" << temp->data << ": " << wtm << endl;
		average += wtm;
		wtm += (float)temp->burstTime - '0';

		counter += (float)temp->burstTime - '0';

		temp = delete_front(temp);


		pr++;
	}
	fin << "Average waiting time " << average / (pr - 1);

	cout << "Schduling done, check file output.txt for details";

}
void priorityschinFile(struct node* header) {

	struct node *temp = header;

	float wtm = 0;
	float pr = 1;
	float average = 0, counter = 0;
	temp = sort_priority(temp);
	ofstream fin("output.txt");

	fin << "Scheuling Method: Priority Scheduling(Non-Preemptive)" << endl;
	fin << "Process Waiting Times: " << endl;

	while (!(is_empty_node(temp))) {


		if (counter < (float)temp->arrivalTime - '0') {
			counter++;
			continue;
		}


		fin << "P" << temp->data << ": " << wtm << endl;
		average += wtm;
		wtm += (float)temp->burstTime - '0';

		counter += (float)temp->burstTime - '0';

		temp = delete_front(temp);


		pr++;
	}
	fin << "Average waiting time " << average / (pr - 1);

	cout << "Schduling done, check file output.txt for details";

}

void prioritysch(struct node* header) {

	struct node *temp = header;

	float wtm = 0;
	float pr = 1;
	float average = 0, counter = 0;
	temp = sort_priority(temp);


	cout << "Scheuling Method: Priority Scheduling(Non-Preemptive)" << endl;
	cout<< "Process Waiting Times: " << endl;

	while (!(is_empty_node(temp))) {


		if (counter < (float)temp->arrivalTime - '0') {
			counter++;
			continue;
		}


		cout << "P" << temp->data << ": " << wtm << endl;
		average += wtm;
		wtm += (float)temp->burstTime - '0';

		counter += (float)temp->burstTime - '0';

		temp = delete_front(temp);


		pr++;
	}
	cout << "Average waiting time " << average / (pr - 1);

	

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
    bool loop=true;
    float arrival_time,burst_time,first_response=0,prio;
    	ifstream fin;
   
    	fin.open("input.txt");

	if (fin.is_open()) {

		while (fin >> i >> burst_time >> arrival_time >> prio) {
			
			 newNodeins(&head,i,arrival_time,burst_time,&first_response,prio);
		}
	}
	

	fin.close();
    
    
    while(loop){

    	cout<<"Enter the no. of Process: ";
    cin>>process;
    
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
			   
               showFCFSinFile(head,process);
               
               
		    break;
		    case 3 :
		       cout<<" \n\tShortest-Job-First Scheduling";
		      
		      shortestjobfirst(head);
			break;   
		    case 4 :
		    	cout<<" \n\tPriority Scheduling";
		    prioritysch(head);
			break;	
		    case 5 :
		    	cout<<" \n\tRound-Robin Scheduling";
				
			}
			case 3:
			  showFCFS(head,process);
			  shortestjobfirst(head);
			  prioritysch(head);
			  	
		}
	}
	cin.ignore();

	return 0;
}
