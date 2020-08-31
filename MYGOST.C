#include <cstddef>
#include <memory.h>

unsigned long PB__[1024];


#define ONE(i, key, NN1, NN2, uz, TempNdx)             \
{                                                      \
   TempNdx = key[i] + NN1;                             \
    fprintf(S1,"%x,",TempNdx);                         \
   NN2 = NN2 ^  (uz     [(TempNdx & 0x000000ff)]);     \
                                                        \
   NN2 = NN2 ^ ((uz+256)[(TempNdx & 0x0000ff00)>>8]);  \
                                                       \
   NN2 = NN2 ^ ((uz+512)[(TempNdx & 0x00ff0000)>>16]); \
                                                     \
   NN2 = NN2 ^ ((uz+768)[ TempNdx >>24]);              \
                                                        \
}                                                       \

#define TWO(n,mas,temp,N3,TempNdx,pod)  \
{                                           \
    while (TempNdx>0)                       \
    {                                      \
         mas[n]= TempNdx%16;               \
         TempNdx= TempNdx/16;             \
         n++;                               \
    }                                       \
    for (int i=0; i<=n/2; i++)              \
    {                                       \
          temp= mas[i];                     \
          mas[i]= mas[n-i-1];               \
          mas[n-i-1]= temp;                  \
    }                                        \
    static unsigned char N3[4] = {pod[(16*mas[0]+768)+mas[1]],pod[(16*mas[2]+512)+mas[4]], \
                            pod[(16*mas[3]+256)+mas[5]],pod[(16*mas[6])+mas[7]]};\
    fprintf(S1,"%02x%02x%02x%02x,",N3[0],N3[1],N3[2],N3[3]); \
    free(mas); \
    temp=0;\
    n=0;\
    TempNdx=0;      \
}                                                                                           \

//NN2 = NN2 ^  (uz     [(TempNdx & 0x000000ff)]);     \
//    fprintf(S1,"%x,",NN2);            \
//   NN2 = NN2 ^ ((uz+256)[(TempNdx & 0x0000ff00)>>8]);  \
//         fprintf(S1,"%x,",NN2);                    \
//   NN2 = NN2 ^ ((uz+512)[(TempNdx & 0x00ff0000)>>16]); \
//           fprintf(S1,"%x,",NN2);
/*
 * Џа®жҐ¤га , аҐ «Ё§гой п  «Ј®аЁв¬ § иЁда®ў ­Ёп
 *   ў аҐ¦Ё¬Ґ Їа®бв®© § ¬Ґ­л (1 и Ј)
 * N1_ptr, N2_ptr (in/out) - гЄ § вҐ«Ё ­  4-е Ў ©в®ўлҐ жҐ«лҐ
 * key (in) - ¬ ббЁў unsigned long[8] - Є«оз
 */
static void _Encrypt32 (unsigned long key[],
            unsigned long N1_ptr,
            unsigned long N2_ptr,
            unsigned long *out1,
            unsigned long *out2,
            int p)
{
  unsigned long N1 = N1_ptr;
  unsigned long N2 = N2_ptr;
  static unsigned char N3[4];
  unsigned long N5,N4;
  int n=0;
  static unsigned char mas[8];
  int temp;
  unsigned long TempNdx;
  unsigned long O=0x11111111,Tw=0x22222222,Th=0x33333333,Fo=0x44444444,F=0xFFFFFFFF;

    FILE *S1;
    S1 = fopen("Table.txt", "a");                               /*Фаил для записи значений*/
    fprintf(S1, "ВАРИАНТ № %d\n",p);
    fprintf(S1,"№,Значение N1,Значение N2,Значение подключа,Результат сложения с подключем,Результат подстановки по таблице замен,Результат операции сдвига,Результат операции Z=Y+N2(mod 2)\n");
    fprintf(S1, "1,%x,%x,%x,", N1,N2,O);
    N4=N2;
  ONE(0, key, N1, N2, PB__, TempNdx);                           /*Получаем результат опрерации Z=Y+N2(mod2) и сложения блока N1 с подключем*/
  TWO(n,mas,temp,N3,TempNdx,pod);                               /*Получаем результат подстановки по таблице замен*/
    N5=N4^N2;                                                   /*Получение результата операции сдвига*/
    fprintf(S1, "%08x,%x,\n2,%x,%x,%x,",N5, N2,N2,N1,Tw);
    N4,N5=0;

    N4=N1;
  ONE(1, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%08x,%x,\n3,%x,%x,%x,",N5,N1,N1,N2,Th);
    N4,N5=0;

    N4=N2;
  ONE(2, key, N1, N2, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N2;
    fprintf(S1, "%08x,%x,\n4,%x,%x,%x,",N5, N2,N2,N1,Fo);
    N4,N5=0;

    N4=N1;
  ONE(3, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%08x,%x,\n5,%x,%x,%x,",N5,N1,N1,N2,F);
    N4,N5=0;

    N4=N2;
  ONE(4, key, N1, N2, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N2;
    fprintf(S1, "%08x,%x,\n6,%x,%x,%x,",N5, N2,N2,N1,F);
    N4,N5=0;

    N4=N1;
  ONE(5, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%08x,%x,\n7,%x,%x,%x,",N5,N1,N1,N2,F);
    N4,N5=0;

    N4=N2;
  ONE(6, key, N1, N2, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N2;
    fprintf(S1, "%08x,%x,\n8,%x,%x,%x,",N5, N2,N2,N1,F);
    N4,N5=0;

    N4=N1;
  ONE(7, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%08x,%x,\n9,%x,%x,%x,",N5,N1,N1,N2,O);
    N4,N5=0;

    N4=N2;
  ONE(0, key, N1, N2, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N2;
    fprintf(S1, "%08x,%x,\n10,%x,%x,%x,",N5, N2,N2,N1,Tw);
    N4,N5=0;

    N4=N1;
  ONE(1, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%08x,%x,\n11,%x,%x,%x,",N5,N1,N1,N2,Th);
    N4,N5=0;

    N4=N2;
  ONE(2, key, N1, N2, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N2;
    fprintf(S1, "%08x,%x,\n12,%x,%x,%x,",N5, N2,N2,N1,Fo);
    N4,N5=0;

    N4=N1;
  ONE(3, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%08x,%x,\n13,%x,%x,%x,",N5,N1,N1,N2,F);
    N4,N5=0;

    N4=N2;
  ONE(4, key, N1, N2, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N2;
    fprintf(S1, "%08x,%x,\n14,%x,%x,%x,",N5, N2,N2,N1,F);
    N4,N5=0;

    N4=N1;
  ONE(5, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%08x,%x,\n15,%x,%x,%x,",N5,N1,N1,N2,F);
    N4,N5=0;

    N4=N2;
  ONE(6, key, N1, N2, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N2;
    fprintf(S1, "%08x,%x,\n16,%x,%x,%x,",N5, N2,N2,N1,F);
    N4,N5=0;

    N4=N1;
  ONE(7, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%08x,%x,\n17,%x,%x,%x,",N5,N1,N1,N2,O);
    N4,N5=0;

    N4=N2;
  ONE(0, key, N1, N2, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N2;
    fprintf(S1, "%08x,%x,\n18,%x,%x,%x,",N5, N2,N2,N1,Tw);
    N4,N5=0;

    N4=N1;
  ONE(1, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%08x,%x,\n19,%x,%x,%x,",N5,N1,N1,N2,Th);
    N4,N5=0;

    N4=N2;
  ONE(2, key, N1, N2, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N2;
    fprintf(S1, "%08x,%x,\n20,%x,%x,%x,",N5, N2,N2,N1,Fo);
    N4,N5=0;

    N4=N1;
  ONE(3, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%08x,%x,\n21,%x,%x,%x,",N5,N1,N1,N2,F);
    N4,N5=0;

    N4=N2;
  ONE(4, key, N1, N2, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N2;
    fprintf(S1, "%08x,%x,\n22,%x,%x,%x,",N5, N2,N2,N1,F);
    N4,N5=0;

    N4=N1;
  ONE(5, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%08x,%x,\n23,%x,%x,%x,",N5,N1,N1,N2,F);
    N4,N5=0;

    N4=N2;
  ONE(6, key, N1, N2, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N2;
    fprintf(S1, "%08x,%x,\n24,%x,%x,%x,",N5, N2,N2,N1,F);
    N4,N5=0;

    N4=N1;
  ONE(7, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%08x,%x,\n25,%x,%x,%x,",N5,N1,N1,N2,F);
    N4,N5=0;

    N4=N2;
  ONE(7, key, N1, N2, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N2;
    fprintf(S1, "%08x,%x,\n26,%x,%x,%x,",N5, N2,N2,N1,F);
    N4,N5=0;

    N4=N1;
  ONE(6, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%08x,%x,\n27,%x,%x,%x,",N5,N1,N1,N2,F);
    N4,N5=0;

    N4=N2;
  ONE(5, key, N1, N2, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N2;
    fprintf(S1, "%08x,%x,\n28,%x,%x,%x,",N5, N2,N2,N1,F);
    N4,N5=0;

    N4=N1;
  ONE(4, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%08x,%x,\n29,%x,%x,%x,",N5,N1,N1,N2,Fo);
    N4,N5=0;

    N4=N2;
  ONE(3, key, N1, N2, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N2;
    fprintf(S1, "%08x,%x,\n30,%x,%x,%x,",N5, N2,N2,N1,Th);
    N4,N5=0;

    N4=N1;
  ONE(2, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%08x,%x,\n31,%x,%x,%x,",N5,N1,N1,N2,Tw);
    N4,N5=0;

    N4=N2;
  ONE(1, key, N1, N2, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N2;
    fprintf(S1, "%08x,%x,\n32,%x,%x,%x,",N5, N2,N2,N1,O);
    N4,N5=0;

    N4=N1;
  ONE(0, key, N2, N1, PB__, TempNdx);
  TWO(n,mas,temp,N3,TempNdx,pod);
    N5=N4^N1;
    fprintf(S1, "%x,%x\n\n",N5,N1);
    N4,N5=0;


  fclose(S1);
  out2[0]=N1;
  out1[0]=N2;
  N1 = N2 = TempNdx = 0;

}

void MakeTestUz(void)
     {

      int i,j;
      ///extern unsigned char *pod;
      for(i=0;i<1024;i++)
        PB__[i]=pod[i];
      for(i=0;i<4;i++)
       for(j=0; j<256; j++)
        PB__[i*256+j]<<=(8*i);
      for(i=0;i<1024;i++)
        PB__[i]=(PB__[i]<<11) | (PB__[i]>>21);
     }

