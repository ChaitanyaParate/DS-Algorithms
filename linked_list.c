#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
int prn;
char name[50];
struct node* next;
};
void create(struct node* h){
struct node* temp = h;
int ch;
do{
struct node* curr = (struct node*)malloc(sizeof(struct node));
printf("\nEnter the PRN number : ");
scanf("%d" , &curr->prn);
printf("\nEnter the Name of the member :");
scanf("%s" , curr->name);
curr->next = NULL;
temp->next = curr;
temp = curr;
printf("\nDo you want to continue (1 for Yes / 0 for No): ");
scanf("%d" , &ch);
}while(ch == 1);
}
void display(struct node* h){
struct node* curr = h->next;
if(curr == NULL){
printf("List is Empty.\n");
}
else{
printf("%p\t%s\t%d\t%p\t(President)\n",curr, curr->name, curr->prn
, curr->next);
curr = curr->next;
while(curr != NULL && curr->next != NULL){
printf("%p\t%s\t%d\t%p\n", curr, curr->name, curr->prn,
curr->next);
curr = curr->next;
}
if (curr != NULL) {
printf("%p\t%s\t%d\t%p\t(Secretary)\n",curr, curr->name, curr->prn
, curr->next);
}
}
}
int len(struct node* h){
struct node* curr = (struct node*)malloc(sizeof(struct node));
curr = h->next;
int i = 0;
while (curr != NULL){
i++;
curr = curr->next;
}
return i;
}
void delete(struct node* h){
struct node* prev;
struct node* curr = h->next;
prev = h;
int ctr = 1 , pos;
printf("Enter the position that you want to delete : ");
scanf("%d" , &pos);
int k = len(h);
if(k<pos){
printf("Node can't be delete.");
}
else{
while(ctr<pos){
ctr++;
prev = curr;
curr = curr->next;
}
prev->next = curr->next;
curr->next = NULL;
free(curr);
printf("Node is delete.\n");
}
}
void insert(struct node* h){
struct node* curr;
int i = 1;
curr = h;
struct node* nnode = (struct node*)malloc(sizeof(struct node));
int k = len(h);
printf("Enter the new PRN number : ");
scanf("%d" , &nnode->prn);
printf("Enter the new name : ");
scanf("%s" , nnode->name);
nnode->next = NULL;
int pos;
printf("Enter the position : ");
scanf("%d" , &pos);
if(pos>k+1){
printf("Data Can't be Inserted.");
}
else{
while(i<pos){
i++;
curr = curr->next;
}
nnode->next = curr->next;
curr->next = nnode;
printf("Node is Inserted.\n");
}
}
void merge(struct node *h1 , struct node *h2){
struct node* curr1;
struct node* curr2;
struct node* temp;
int flag;
curr1 = h1->next;
curr2 = h2->next;
if(curr1->prn < curr2->prn){
temp = h1;
flag = 1;
}
else{
temp = h2;
flag = 0;
}
while(curr1 != NULL && curr2 != NULL){
if(curr1->prn < curr2->prn){
temp->next = curr1;
temp = curr1;
curr1 = curr1->next;
}
else{
temp->next = curr2;
temp = curr2;
curr2 = curr2->next;
}
}
if(curr1 == NULL){
temp->next = curr2;
}
if(curr2 == NULL){
temp->next = curr1;
}
if(flag == 1){
display(h1);
}
if(flag == 0){
display(h2);
}
}
void sort(struct node *h){
struct node *prev;
struct node *curr;
struct node *temp;
int l = len(h);
for(int i = 1 ; i<l ; i++){
prev = h;
curr = h->next;
for(int j = 0 ; j<l-i ; j++){
temp = curr->next;
if(curr->prn > temp->prn){
prev->next = temp;
curr->next = temp->next;
temp->next = curr;
prev = temp;
}
else{
prev = curr;
curr = curr->next;
}
}
}
}
void reverse(struct node *h){
struct node *prev;
struct node *curr;
struct node *future;
prev = NULL;
curr = h->next;
while(curr!=NULL){
future = curr->next;
curr->next = prev;
prev = curr;
curr = future;
}
h->next = prev;
}
int main(){
struct node* head1;
head1 = (struct node*)malloc(sizeof(struct node));
head1->next = NULL;
struct node* head2;
head2 = (struct node*)malloc(sizeof(struct node));
head2->next = NULL;
int ch;
do{
printf("\n1. Create member 1 linked list.\n");
printf("2. Display member 1 linked list.\n");
printf("3. Delete from member 1 linked list\n");
printf("4. Create member 2 linked list.\n");
printf("5. Display member 2 linked list.\n");
printf("6. Delete from member 2 linked list\n");
printf("7. Sort the member 1 linked list\n");
printf("8. Sort the member 2 linked list\n");
printf("9. Merge the two linked list\n");
printf("10. Reverse the member 1 linked list\n");
printf("11. Reverse the member 2 linked list\n");
printf("12. Insert an element in Member 1\n");
printf("13. Insert an element in Member 2\n");
printf("14. Exit\n");
printf("Enter your choice: ");
scanf("%d", &ch);
switch (ch)
{
case 1:
create(head1);
printf("Creating of Member 1 linked list is done Successfully");
break;
case 2:
display(head1);
break;
case 3:
delete(head1);
break;
case 4:
create(head2);
printf("Creating of Member 2 linked list is done Successfully");
break;
case 5:
display(head2);
break;
case 6:
delete(head2);
break;
case 7:
sort(head1);
printf("Sorting of member 1 linked list Completed Successfully\n");
break;
case 8:
sort(head2);
printf("Sorting of member 2 linked list Completed Successfully\n");
break;
case 9:
merge(head1 , head2);
printf("Merging Completed Successfully\n");
break;
case 10:
reverse(head1);
printf("Reverse of member 1 linked list Completed Successfully");
break;
case 11:
reverse(head2);
printf("Reverse of member 2 linked list Completed Successfully");
break;
case 12:
insert(head1);
printf("Inserted in Member 1\n");
break;
case 13:
insert(head2);
printf("Inserted in Member 2\n");
break;
case 14:
printf("Exiting....\n");
break;
default:
printf("You entered the wrong choice!\n");
break;
}
}while(ch != 14);
return 0;
}