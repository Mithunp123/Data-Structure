#include <stdio.h>  
#include <stdlib.h>  

// Define the structure for a doubly linked list node
struct node  
{  
    struct node *prev;  
    struct node *next;  
    int data;  
};  

// Initialize head as NULL
struct node *head = NULL;  

// Function declarations
void insertion_beginning();  
void insertion_last();  
void insertion_specified();  
void deletion_beginning();  
void deletion_last();  
void deletion_specified();  
void display();  
void search();  

int main()  
{  
    int choice = 0;  
    while (choice != 9)  
    {  
        printf("\n********* Main Menu *********\n");  
        printf("1. Insert at beginning\n");  
        printf("2. Insert at last\n");  
        printf("3. Insert at a specified location\n");  
        printf("4. Delete from beginning\n");  
        printf("5. Delete from last\n");  
        printf("6. Delete the node after the given data\n");  
        printf("7. Search\n");  
        printf("8. Show\n");  
        printf("9. Exit\n");  
        printf("Enter your choice: ");  
        scanf("%d", &choice);  

        switch (choice)  
        {  
            case 1:  
                insertion_beginning();  
                break;  
            case 2:  
                insertion_last();  
                break;  
            case 3:  
                insertion_specified();  
                break;  
            case 4:  
                deletion_beginning();  
                break;  
            case 5:  
                deletion_last();  
                break;  
            case 6:  
                deletion_specified();  
                break;  
            case 7:  
                search();  
                break;  
            case 8:  
                display();  
                break;  
            case 9:  
                exit(0);  
                break;  
            default:  
                printf("Invalid choice. Please enter a number between 1 and 9.\n");  
        }  
    }  
    return 0;  
}  

// Insert a node at the beginning
void insertion_beginning()  
{  
    struct node *ptr;   
    int item;  
    ptr = (struct node *)malloc(sizeof(struct node));  
    if (ptr == NULL)  
    {  
        printf("Memory allocation failed.\n");  
        return;  
    }  
    printf("Enter item value: ");  
    scanf("%d", &item);  
    ptr->data = item;  
    ptr->prev = NULL;  
    ptr->next = head;  
    if (head != NULL)  
    {  
        head->prev = ptr;  
    }  
    head = ptr;  
    printf("Node inserted at the beginning.\n");  
}  

// Insert a node at the end
void insertion_last()  
{  
    struct node *ptr, *temp;  
    int item;  
    ptr = (struct node *)malloc(sizeof(struct node));  
    if (ptr == NULL)  
    {  
        printf("Memory allocation failed.\n");  
        return;  
    }  
    printf("Enter item value: ");  
    scanf("%d", &item);  
    ptr->data = item;  
    ptr->next = NULL;  
    if (head == NULL)  
    {  
        ptr->prev = NULL;  
        head = ptr;  
    }  
    else  
    {  
        temp = head;  
        while (temp->next != NULL)  
        {  
            temp = temp->next;  
        }  
        temp->next = ptr;  
        ptr->prev = temp;  
    }  
    printf("Node inserted at the end.\n");  
}  

// Insert a node at a specified position
void insertion_specified()  
{  
    struct node *ptr, *temp;  
    int item, loc, i;  
    ptr = (struct node *)malloc(sizeof(struct node));  
    if (ptr == NULL)  
    {  
        printf("Memory allocation failed.\n");  
        return;  
    }  
    printf("Enter position to insert node (0 for beginning): ");  
    scanf("%d", &loc);  
    if (loc < 0)  
    {  
        printf("Invalid position.\n");  
        free(ptr);  
        return;  
    }  
    if (loc == 0)  
    {  
        insertion_beginning();  
        return;  
    }  
    temp = head;  
    for (i = 0; i < loc - 1; i++)  
    {  
        if (temp == NULL)  
        {  
            printf("Position out of range.\n");  
            free(ptr);  
            return;  
        }  
        temp = temp->next;  
    }  
    printf("Enter item value: ");  
    scanf("%d", &item);  
    ptr->data = item;  
    ptr->next = temp->next;  
    ptr->prev = temp;  
    if (temp->next != NULL)  
    {  
        temp->next->prev = ptr;  
    }  
    temp->next = ptr;  
    printf("Node inserted at position %d.\n", loc);  
}  

// Delete a node from the beginning
void deletion_beginning()  
{  
    struct node *ptr;  
    if (head == NULL)  
    {  
        printf("List is empty.\n");  
        return;  
    }  
    ptr = head;  
    head = head->next;  
    if (head != NULL)  
    {  
        head->prev = NULL;  
    }  
    free(ptr);  
    printf("Node deleted from the beginning.\n");  
}  

// Delete a node from the end
void deletion_last()  
{  
    struct node *ptr;  
    if (head == NULL)  
    {  
        printf("List is empty.\n");  
        return;  
    }  
    if (head->next == NULL)  
    {  
        free(head);  
        head = NULL;  
    }  
    else  
    {  
        ptr = head;  
        while (ptr->next != NULL)  
        {  
            ptr = ptr->next;  
        }  
        ptr->prev->next = NULL;  
        free(ptr);  
    }  
    printf("Node deleted from the end.\n");  
}  

// Delete the node after a given node
void deletion_specified()  
{  
    struct node *ptr, *temp;  
    int val;  
    printf("Enter the data after which the node is to be deleted: ");  
    scanf("%d", &val);  
    ptr = head;  
    while (ptr != NULL && ptr->data != val)  
    {  
        ptr = ptr->next;  
    }  
    if (ptr == NULL || ptr->next == NULL)  
    {  
        printf("Node with given data not found or no node to delete after the given data.\n");  
        return;  
    }  
    temp = ptr->next;  
    ptr->next = temp->next;  
    if (temp->next != NULL)  
    {  
        temp->next->prev = ptr;  
    }  
    free(temp);  
    printf("Node deleted after data %d.\n", val);  
}  

// Display all nodes in the list
void display()  
{  
    struct node *ptr;  
    printf("\nList contents:\n");  
    ptr = head;  
    while (ptr != NULL)  
    {  
        printf("%d\n", ptr->data);  
        ptr = ptr->next;  
    }  
}  

// Search for a node by value
void search()  
{  
    struct node *ptr;  
    int item, i = 0;  
    ptr = head;  
    if (ptr == NULL)  
    {  
        printf("List is empty.\n");  
        return;  
    }  
    printf("Enter item to search: ");  
    scanf("%d", &item);  
    while (ptr != NULL)  
    {  
        if (ptr->data == item)  
        {  
            printf("Item found at position %d.\n", i + 1);  
            return;  
        }  
        i++;  
        ptr = ptr->next;  
    }  
    printf("Item not found.\n");  
}
