#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char preprocessing(char message[]);
int encryption(char message[],int key);
int decryption(char message[],int key);
int main()
{
   char message1[80],message2[80];
   int key1,key2;
   scanf("%d %d\n",&key1,&key2);
   gets(message1);
   gets(message2);
   preprocessing(message1);
   encryption(message1,key1);
   decryption(message2,key2);
   printf("%s\n%s",message1,message2);
   return 0;

}

char preprocessing(char message[])
   {
    int i,j;
    char ch;
    i=j=0;
    for(i=0;message[i]!='\0';i++)
    {
        ch=message[i];
        if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
        {
            if(ch<='z'&&ch>='a')
                message[i]=toupper(message[i]);
            message[j++]=message[i];
        }

    }
    message[j]='\0';
}

int encryption(char message[],int key)
{
int i;
char ch;
for(i=0;message[i]!='\0';i++)
{
    ch=message[i]+key;
    if(ch>'Z')
        ch=ch-'Z'+'A'-1;
    message[i]=ch;
}
}

int decryption(char message[],int key)
{
int i;
char ch;
for(i=0;message[i]!='\0';i++)
{
    ch=message[i]-key;
    if(ch<'A')
        ch=ch+'Z'-'A'+1;
    message[i]=ch;
}
}

