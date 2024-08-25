// Tiamzon, Edgar Alan Emmanuel III B.
// Exercise 0
// C3L

#include <stdio.h>
#include <stdlib.h>

typedef struct node_tag {
    int value;
    struct node_tag *next;
} NODE;

//function that checks if the list is empty
int isEmpty(NODE *head) {
    if (head == NULL){
      return 1;
    }
    else{
      return 0;
    }
}

NODE *createNode(int data) {
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
    if (newNode == NULL) {
        printf("Memory Allocation Failed!\n");
        exit(1);
    }
 
    newNode->value = data; // this sets the 'value' from the new node into the argument (int data)
    newNode->next = NULL; // the last node becomes NULL which is not currently linked to any other node
    return newNode; // returns the pointer to the newly created node
}

void insert(NODE **head, int value) {
    NODE *newNode = createNode(value); // calls the function which allocates memory for the new node
    newNode->next = *head; // links to the head node of the list
    *head = newNode; // updates the head of the list to the new node

    printf("\nSuccessfully Added!\n"); 
}

int delete(NODE **head) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return -1; // indication for failed print list
    } 
    else {
        NODE *temp = *head;
        int delete_val = temp->value;
        *head = (*head)->next; // this updates the head pointer to the second pointer to effectively removes it from the list
        free(temp); // frees the memory
        return delete_val; // this stores the in pointer "temp"
    }
}

void printList(NODE *head) {
    if (isEmpty(head)) {
        printf("List is empty!\n");
    } 
    else {
        // transverses the list from the head to the last node stored in each node
        NODE *temp = head;
        while (temp != NULL) {
            printf("%d ", temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    NODE *head = NULL;
    int choice;

    while (1) {
        // main menu
        printf("\n==========MENU==========\n");
        printf("[1] Insert Value\n");
        printf("[2] Delete Value\n");
        printf("[3] Print List\n");
        printf("[4] Exit\n");
        printf("========================\n");

        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int value;
            printf("Enter Value: ");
            scanf("%d", &value);
            insert(&head, value);
        } 
        else if (choice == 2) {
            if (!isEmpty(head)) { // calls the function which checks if the list has any nodes
                int delete_val = delete(&head); // calls the function to delete
                if (delete_val != -1) { // this line checks if there is a return valid node, meaning the list is not empty
                    printf("%d is Deleted!\n", delete_val);
                }
            } 
                else {
                printf("List is empty!\n");
            }
        } 
        else if (choice == 3) {
            printList(head); // prints all the entered value
        } 
        else if (choice == 4) {
            printf("\nProgram Terminated...\n");
            break;
        } 
        else {
            printf("ERROR: Invalid choice!\n");
        }
    }

    return 0;
}
