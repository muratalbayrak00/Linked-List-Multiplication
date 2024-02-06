
// C program to Multiply two numbers  represented as linked lists
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int onBase = 0;
int *bPointer = &onBase;
 // Linked list Node
 struct Node {
     int data;
     struct Node* next;
 };
 
 // Function to create a new Node with given data
 struct Node* newNode(int data)
     {
         struct Node* new_node =
         (struct Node*)malloc(sizeof(struct Node));
         new_node->data = data;
         new_node->next = NULL;
         return new_node;
     }
 
 // Function to insert a Node at the beginning of the Linked List
 void addLinkedList(struct Node** head_ref, int new_data)
     {
         // allocate Node
         struct Node* new_node = newNode(new_data);
         
         // link the old list off the new Node
         new_node->next = (*head_ref);
         
         // move the head to point to the new Node
         (*head_ref) = new_node;
     }
 
 // Function to reverse the linked list and return its length
 int reverseLinkedList(struct Node** head_ref)
     {
         struct Node* prev = NULL;
         struct Node* current = *head_ref;
         struct Node* next;
         int len = 0;
         while (current != NULL) {
         len++;
         next = current->next;
         current->next = prev;
         prev = current;
         current = next;
         }
         *head_ref = prev;
         return len;
     }
 
 // Function to make an empty linked list of given size
 struct Node* make_empty_list(int size)
     {
         struct Node* head = NULL;
         while (size--)
         addLinkedList(&head, 0);
         return head;
     }
 
 // Multiply contents of two linked lists => store in another list and return its head
 struct Node* multiply2Lists(struct Node* first, struct Node* second)
 {
         // reverse the lists to multiply from end m and n lengths of linked lists to make and empty list
         int m = reverseLinkedList(&first), n = reverseLinkedList(&second);
         
         // make a list that will contain the result of multiplication. m+n+1 can be max size of the list
         struct Node* result = make_empty_list(m + n + 1);
         
         // pointers for traverse linked lists and also to reverse them after
         struct Node *second_ptr = second,
         *result_ptr1 = result, *result_ptr2, *first_ptr;
 
         //multiply each Node of second list with first
     while (second_ptr) {
     
         int carry = 0;
         
         // each time we start from the next of Node from which we started last time
         result_ptr2 = result_ptr1;
         
         first_ptr = first;
         
             while (first_ptr) {
             
                     // multiply a first list's digit with a current second list's digit
                     int mul = first_ptr->data * second_ptr->data
                     + carry;
                     
                     // Assign the product to corresponding Node of result
                     result_ptr2->data += mul % onBase;
                     
                     // now resultant Node itself can have more than 1 digit
                     carry = mul / onBase + result_ptr2->data / onBase;
                     result_ptr2->data = result_ptr2->data % onBase;
                     
                     first_ptr = first_ptr->next;
                     result_ptr2 = result_ptr2->next;
             }
         
             // if carry is remaining from last multiplication
             if (carry > 0) {
                 result_ptr2->data += carry;
             }
         
         result_ptr1 = result_ptr1->next;
         second_ptr = second_ptr->next;
     }
 
         // reverse the result_list as it was populated from last Node
     reverseLinkedList(&result);
     reverseLinkedList(&first);
     reverseLinkedList(&second);
 
     // remove if there are zeros at starting
         while (result->data == 0) {
             struct Node* temp = result;
             result = result->next;
             free(temp);
         }
 
 // Return head of multiplication list
 return result;
 }
 
 // A utility function to print a linked list
 void printList(struct Node* Node)
  {
             while (Node != NULL) {
                 printf("%d", Node->data);
                    if (Node->next)
                        printf("");
                        Node = Node->next;
             }
     printf("\n");
 }
void Convert(struct Node* Node,int bases){
      int i=0;
      int dec=0;
      while(Node!=NULL){
           dec+=(Node->data)*(pow(bases,i));
           Node=Node->next;
           i++;
      }
      printf("%d\n",dec);

 }
 // Driver program to test above function
 int main(int argc, char* argv[])
 {
     
     struct Node* first = NULL;
     struct Node* second = NULL;
     
     if(argc==1)
            printf("Error message!");
         if(argc>=2)
         {
             
           FILE* input_file = fopen(argv[1],"r");
             
    
             if(input_file == NULL){
                 printf("no input!!!");
                 return 0;
             }
             
             char x;
             int a=0;
             while (!feof(input_file)){
                 x=fgetc(input_file);
                 
                 if(x=='\n'){
                     a++;
                 }else{
                     if(a==0){
                         
                         addLinkedList(&first, (int)(x)-48);
                     }
                     else if(a==1){
                         
                         addLinkedList(&second, (int)(x)-48);
                     }
                     else if(a==2){
                         
                         *bPointer =(int)(x)-48;
                         
                         break;
                     }
                 }
                 
             }
             fclose(input_file);
         }
     if(onBase == 1){
      *bPointer = 10;
     }
    
     reverseLinkedList(&first);
     reverseLinkedList(&second);

    
     
     printList(first);
     printList(second);
     
     // Multiply the two lists and see result
     struct Node* result = multiply2Lists(first, second);
     
     printList(result);
     reverseLinkedList(&first);
     reverseLinkedList(&second);
     reverseLinkedList(&result);

     Convert(first,onBase);
     Convert(second,onBase);
     Convert(result,onBase);
     
     
     return 0;
 }
 
