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

