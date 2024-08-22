#include<stdio.h>
#include<stdlib.h>
struct Node{
    int data;
    struct Node*next;
};
struct Node* createNode(int data){
    struct Node * newNode=(struct Node*)malloc(sizeof(struct Node));
    if (newNode==NULL){
        printf("Memory allocation failed.\n");
        exit(1);}
        newNode->data=data;
        newNode->next=NULL;
        return newNode;
}
void displaylist(struct Node* head){
    struct Node* temp=head;
    printf("\nData entered in the list:\n\n");
    while(temp!=NULL){
        printf("Data=%d\n",temp->data);
        temp=temp->next;
    }
}
int main(){
    int numNodes,data;
    struct Node *head=NULL,*temp=NULL;
    printf("Input the number of nodes  : ");
    scanf("%d",&numNodes);
    if (numNodes<=0){
        printf("Number of nodes should be greater than zero.\n");
        return 1;
    }
    for(int i=0;i<numNodes;i++){
        printf("\nInput data for node %d:",i+1);
        scanf("%d",&data);
        struct  Node* newNode=createNode(data);
        if(head==NULL){
            head=newNode;
            temp=newNode;}
        else{
            temp->next=newNode;
            temp=newNode;
        }
    }
    displaylist(head);
    return 0;
}
    


