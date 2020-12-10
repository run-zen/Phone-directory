#include<stdio.h>
#include <string.h>
#include<ctype.h>

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
     printf("\n%d  %d\n", l1,l2);
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
          printf("\n %d   %d\n", last1, last2);
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
               printf("\nHere\n");
               return 0;
          }

     }
}

int main() {
   char str1[50] = "Hell worl";
   char str2[50] = "Hello World";
   // Extract the first token
   int x = compareStr(str1,str2);
   printf( " %d\n", x); //printing the token
   return 0;
}
