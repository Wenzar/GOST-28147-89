#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "tdata.c"
#include "mygost.c"
#include <locale.h>


int main()
{
     unsigned long key[8],in[2],ou[2];
     int i,j,a,b;
     setlocale(LC_ALL, "Rus");

     for(i=0;i<8;i++)key[i]=Key04[i];

     printf("Таблицы сформированы в Table.txt\nПри открытии Table.txt в Excel использовать символ разделитель 'запятая'\nПри многократном запуске программы не забывайте удалять Table.txt, чтобы избегать дублирования! ");
     MakeTestUz();
     in[0]=Plaintext02[0];
     in[1]=Plaintext02[1];

     for(int a=0,p=1; a<=29; a++)
     {
     _Encrypt32(key,in[0],in[1], ou, ou+1,p);
     p+=1;
     in[0]+=0x00000001;
     in[1]+=0x00000001;
     }
     printf("\n");

     return(0);
}
