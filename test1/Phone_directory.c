#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct node {
     char name[50];
     char number[20];
     struct node* next;
     struct node* prev;
};

int strCmp(char s1[], char s2[]) {
     int count = 0;
     for(int i=0; s1[i] != '\0'; i++) {
          if(tolower(s1[i]) == tolower(s2[i])) {
               count++;
          }
          else
               break;
     }

     return count;
}

int compareStr(char str1[], char str2[]) {
     char s1[50], s2[50];
     strcpy(s1,str1);
     strcpy(s2,str2);

     int last1 = strlen(s1);
     int last2 = strlen(s2);
     char *a = strtok(s1, " ");
     char *b = strtok(s2, " ");
     int l1 = strlen(a);
     int l2 = strlen(b);
     int  n;
     if(l1 <= l2)
          n = l1;
     else
          n = l2;
     for(int i=0; i < n; i++) {
          if(tolower(a[i]) < tolower(b[i]))
               return -1;
          else if(tolower(a[i]) > tolower(b[i]))
               return 1;
     }
     if(l1 < l2) {
          return -1;
     }
     else if(l1 > l2) {
          return 1;
     }
     else {
          last1 = last1 - l1 -1;
          last2 = last2 - l2 -1;
          int i = l1+1;
          int j = l2+1;
          while(s1[i] != '\0' && s2[j] != '\0') {
               if(tolower(s1[i]) < tolower(s2[j])) {
                    return -1;
               }
               else if(tolower(s1[i]) > tolower(s2[j]))
                    return 1;
               i++;
               j++;
          }
          if(last1 < last2) {
               return -1;
          }
          else if(last1 > last2) {
               return 1;
          }
          else {
               return 0;
          }

     }
}

struct node* root = NULL;

int ischar(char c) {
     if ((c>= 'a' && c<='z') || (c>='A' && c<='Z'))
          return 1;
     else
          return 0;
}

void pushEnd(struct node** head_ref, char name[], char number[]) {
     struct node* new_node = (struct node*)malloc(sizeof(struct node));

     strcpy(new_node->name, name);
     strcpy(new_node->number, number);

     new_node->next = NULL;

     if(*head_ref == NULL) {
          new_node->prev = NULL;
          *head_ref = new_node;
          return;
     }

     struct node* last = *head_ref;
     while(last->next != NULL) {
          last = last->next;
     }
     last->next = new_node;
     new_node->prev = last;

     return;

}

void push(struct node** head_ref, char name[], char number[])
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));

    strcpy(new_node->name, name);
    strcpy(new_node->number, number);

    new_node->next = (*head_ref);
    new_node->prev = NULL;

    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;

    (*head_ref) = new_node;
}

void readPhoneBook() {
     char name[100], number[100];
     char c;
     FILE *fptr;
     if ((fptr = fopen("Phone.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
     }
     c = fgetc(fptr);
     while(ischar(c))
     {
          int j=-1;
          while(c != ',') {
               name[++j] = c;
               c = fgetc(fptr);
          }
          name[++j] = '\0';
          c = fgetc(fptr);
          j = -1;
          while(c != ',') {
               number[++j] = c;
               c = fgetc(fptr);
          }
          number[++j] = '\0';
          /*
          printf("\nName : %s", name);
          printf("\nNumber : %s", number);
          printf("\n");
          */
          push(&root,name,number);
          c = fgetc(fptr);
     }
     fclose(fptr);
}

void sortedInsert(struct node** head_ref, struct node* new_node)
{
    struct node* current;
    int match = compareStr((*head_ref)->name, new_node->name);
    if (*head_ref == NULL || match == 1 || match == 0 )
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        current = *head_ref;
        while (current->next!=NULL && compareStr(current->next->name,new_node->name) == -1)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void insertionSort(struct node **head_ref)
{
    struct node *sorted = NULL;

    struct node *current = *head_ref;
    while (current != NULL)
    {
        struct node *next = current->next;

        sortedInsert(&sorted, current);

        current = next;
    }

    *head_ref = sorted;
}



void displayContacts(struct node* head_ref) {

     if(head_ref == NULL) {
          printf("\nNo Contacts to display");
          return;
     }
     printf("\nThe Contacts are : ");
     while(head_ref != NULL) {
          printf("\n");
          printf("\nName : %s", head_ref->name);
          printf("\nNumber : %s", head_ref->number);
          head_ref = head_ref->next;
     }
     printf("\n");
}

void searchByName(char str[]) {
     struct node* temp = root;
     struct node* searchlist = NULL;

     int match = 0;
     int found = 0;
     int strLen = strlen(str);
     char name[50], number[20];
     while(temp != NULL) {
          int len = strlen(temp->name);
          match = strCmp(str, temp->name);
          if(match == len && match == strLen) {
               push(&searchlist, temp->name, temp->number);
          }
          else if(match > 0 && match >= strLen) {
               strcpy(name, temp->name);
               strcpy(number, temp->number);
               pushEnd(&searchlist,name, number);
               found = 1;
          }
          temp = temp->next;
     }
     if(found) {
          struct node* head_ref = searchlist;
          printf("\n\n\tMost Probable Contacts are : ");
          while(head_ref != NULL) {
               printf("\n\n\t  Name : %s\n\t  Number : %s", head_ref->name, head_ref->number);
               head_ref = head_ref->next;
          }
     }
     else {
          printf("\n\n\t  No contacts found.\n");
     }
     printf("\n");
     return;
}

void searchByNumber(char str[]) {
     struct node* temp = root;
     struct node* searchlist = NULL;
     int match = 0;
     int found = 0;
     int strLen = strlen(str);
     char name[50], number[20];
     while(temp != NULL) {
          int len = strlen(temp->number);
          match = strCmp(str, temp->number);
          if(match == len && match == strLen) {
               push(&searchlist, temp->name, temp->number);
          }
          else if(match > 0 && match >= strLen) {
               strcpy(name, temp->name);
               strcpy(number, temp->number);
               pushEnd(&searchlist,name, number);
               found = 1;
          }
          temp = temp->next;
     }

     if(found) {
          struct node* head_ref = searchlist;
          printf("\n\n\tMost Probable Contacts are : ");
          while(head_ref != NULL) {
               printf("\n\n\t  Name : %s\n\t  Number : %s", head_ref->name, head_ref->number);
               head_ref = head_ref->next;
          }
     }
     else {
          printf("\n\n\t  No contacts found.\n");
     }

     printf("\n");
     return;
}

void searchContact() {
     char str[100];
     int choice;
     printf("\n\n\tSearch Menu --");
     printf("\n\n\t  1.Search by name.\n\t  2.Search by number.\n\t  3.Go back");
     while(1) {
          printf("\n\n  Enter your choice : ");
          getchar();
          scanf("%d", &choice);
          if(choice == 1 ) {
               printf("\n  Enter name : ");
               scanf("%s", str);
               searchByName(str);
               break;
          }
          else if(choice == 2) {
               printf("\n  Enter number : ");
               scanf("%s", str);
               searchByNumber(str);
               break;
          }
          else if(choice == 3) {
               break;
          }
          else
          {
               printf("\n Invalid Choice : Enter again.");
          }
     }
}

void saveList() {
     struct node* temp = root;
     FILE *fptr;
     if ((fptr = fopen("Phone.txt", "w")) == NULL) {
        printf("Error! opening file");
        exit(1);
     }
     while(temp != NULL) {
          fputs(temp->name,fptr);
          fprintf(fptr, "%c", ',');
          fputs(temp->number,fptr);
          fprintf(fptr, "%c", ',');
          temp = temp->next;
     }

     fclose(fptr);
}

void addContact() {
     char name[50],number[50];
     FILE *fptr;
     if ((fptr = fopen("Phone.txt", "a+")) == NULL) {
        printf("Error! opening file");
        exit(1);
     }
     printf("\nEnter name : ");
     getchar();
     gets(name);
     fputs(name,fptr);
     fprintf(fptr, "%c", ',');
     printf("\nEnter number : ");
     scanf("%s",number);
     fputs(number,fptr);
     fprintf(fptr, "%c", ',');
     push(&root,name, number);

     fclose(fptr);
}

void deleteByName(char str[]) {
     struct node* temp = root;
     int strLen = strlen(str);
     int match = 0, found = 0;
     char name[50], number[20];
     while(temp != NULL) {
          int len = strlen(temp->name);
          match = strCmp(str, temp->name);
          if(match == len && match == strLen) {
               strcpy(name, temp->name);
               strcpy(number, temp->number);
               found = 1;
               if(temp == root)
                    root = temp->next;
               if(temp->prev != NULL)
                    temp->prev->next = temp->next;
               if(temp->next != NULL)
                    temp->next->prev = temp->prev;

               free(temp);
          }
          temp = temp->next;
     }

     if(found) {
          printf("\n\n\tContact Deleted : ");
          printf("\n\n\t  Name : %s\n\t  Number : %s", name, number);
          saveList();
     }
     else {
          printf("\n\n\t  No contact named \"%s\" \n", str);
          printf("\n\n\t  Try Searching for the contact first.\n");
     }

}

void deleteByNumber(char str[]) {
     struct node* temp = root;
     int strLen = strlen(str);
     int match = 0, found = 0;
     char name[50], number[20];
     while(temp != NULL) {
          int len = strlen(temp->number);
          match = strCmp(str, temp->number);
          if(match == len && match == strLen) {
               strcpy(name, temp->name);
               strcpy(number, temp->number);
               found = 1;
               if(temp == root)
                    root = temp->next;
               if(temp->prev != NULL)
                    temp->prev->next = temp->next;
               if(temp->next != NULL)
                    temp->next->prev = temp->prev;

               free(temp);
          }
          temp = temp->next;
     }

     if(found) {
          printf("\n\n\tContact Deleted : ");
          printf("\n\n\t  Name : %s\n\t  Number : %s", name, number);
          saveList();
     }
     else {
          printf("\n\n\t  No contact with number \"%s\" \n", str);
          printf("\n\n\t  Try Searching for the contact first.\n");
     }
}

void deleteContact() {
     char str[100];
     int choice;
     printf("\n\nDelete Menu -- ");
     printf("\n\n\t  1.Delete by name.\n\t  2.Delete by number.\n\t  3.Go back.");
     while(1) {
          printf("\n\n  Enter your choice : ");
          getchar();
          scanf("%d", &choice);
          if(choice < 1 || choice > 3) {
               printf("\n Invalid Choice : Enter again.");
               continue;
          }
          else if(choice == 1 ) {
               printf("\n  Enter name to delete : ");
               getchar();
               gets(str);
               deleteByName(str);
               break;
          }
          else if(choice == 2) {
               printf("\n  Enter number to delete : ");
               getchar();
               gets(str);
               deleteByNumber(str);
               break;
          }
          else if(choice == 3) {
               break;
          }
     }
}

int main() {
     readPhoneBook();
     int choice;
     while(1) {
          printf("\n\t***************************************");
          printf("\n\t\t\tMenu");
          printf("\n\n\t1.Show Contacts\t\t2.Add Contact");
          printf("\n\n\t3.Search Contact\t4.Delete Contact");
          printf("\n\n\t5.Exit");
          printf("\n\n Enter Choice : ");
          scanf("%d", &choice);
          if(choice == 5) {
               printf("\n\n Thank You for using.\n");
               break;
          }
          switch (choice) {
               case 1: insertionSort(&root); displayContacts(root); break;
               case 2: addContact(); break;
               case 3: searchContact(); break;
               case 4: deleteContact(); break;
          }
     }
     return 0;
}
