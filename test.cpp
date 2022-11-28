#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
int main ()
{
   char str1[15];
   char str2[15];
   int ret;
 
 
   strcpy(str1, "string1");
   strcpy(str2, "string2");
 
   cout<< strcpy(str1, str2);
   cout<< "  "<< str1;

   
   return(0);
}