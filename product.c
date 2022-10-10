#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#define max 40
void addproduct();
void viewproduct();
void deleteproduct();
void buyproduct();
void modifyproduct();
void menu();
void del(int);
typedef struct
{
int id;
char prodname[max];
int quantity;
char date[12];
}product;
product prodct;
FILE *file;
int main()
{
int c;
while(1)
{
menu();
printf("\nPress any key To continue");

}


return 0;
}
void menu()
{
   int choice;
   printf("\n\t..........Inventory System.............\n\n");
   printf("\t\t1.Add Product\n");
   printf("\t\t2.View Product\n");
   printf("\t\t3.Modify Product\n");
   printf("\t\t4.Delete Product\n");
   printf("\t\t5.Buy Product\n");
   printf("\t\t0.Exit\n");
   printf("\n\t............................................\n");
   printf("Enter your choice: ");
   scanf("%d",&choice);
   switch(choice)
   {case 0:
            printf("Bye bye ........Thankyou\n");
            exit(0);
     case 1:
            addproduct();
            break;
     case 2:
           viewproduct();
           break;
    case 3:
          modifyproduct();
          break;
    case 4:
          deleteproduct();
          break;
  case 5:
          buyproduct();
          break;
  default:
          printf("Invalid choice..........");

   }

}
void addproduct()
{
        char ch;
        char mydate[12];
        time_t t = time(NULL);
        struct tm tm =*localtime(&t);
        sprintf(mydate,"%02d/%02d/%d",tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
        strcpy(prodct.date,mydate);
        file =fopen("store.txt","ab");
        printf("Enter Product id:  ");
        scanf("%d",&prodct.id);

        printf("Enter Product name:  ");
        fflush(stdin);
       // scanf("%c",&ch);
        fgets(prodct.prodname,max,stdin);

        printf("Enter Product quantity:  ");
        scanf("%d",&prodct.quantity);
        fwrite(&prodct,sizeof(prodct),1,file);
       fclose(file);
}
void viewproduct()
{
printf(" ...................Product List..............\n\n");
printf("%-10s %-20s %-20s%s\n", "PID","Product Name","Quantity","Date");
printf("\n.............................................\n\n");
file = fopen("store.txt","rb");
while(fread(&prodct,sizeof(prodct),1,file)==1)
  { printf("%-10d %-30s %-30d %s\n",prodct.id,prodct.prodname,prodct.quantity,prodct.date);
  }

   fclose(file);
}
void modifyproduct()

{    int found,id;
     char ch;
     printf("...........Update Products...........\n");
     printf("Enter Product Id: ");
     scanf("%d",&id);

     file = fopen("store.txt","rb+");
     while(fread(&prodct,sizeof(prodct),1,file)==1)
     {
         if(id==prodct.id)
         {
            found=1;
            printf("Enter new product name: ");
            fflush(stdin);
           // scanf("%c",&ch);
            fgets(prodct.prodname,max,stdin);

            printf("Enter new product quantity: ");
            fflush(stdin);
            scanf("%d",&prodct.quantity);
            fseek(file,-sizeof(prodct),1);
            fwrite(&prodct,sizeof(prodct),1,file);
            fclose(file);
            break;
         }
     }
        if(found==1)
            printf("Update successfully");
       else
            printf("Product not found");

}
void deleteproduct()
{
    int found,id;
    char ch;
     printf("...........Delete Products...........\n");
 printf("Enter Product Id: ");
     scanf("%d",&id);
     FILE *fp;
     file = fopen("store.txt","rb");

     while(fread(&prodct,sizeof(prodct),1,file)==1)
     {
         if(id==prodct.id)
         {
            found=1;
            fclose(file);
            break;
         }
     }
        if(found==1)
         {    printf("\nDeleted successfully");
              del(id);
         }
       else
            printf("\n\n Product not found");

}
void del(int id)
{
     int found;
     file = fopen("store.txt","rb");
     FILE *temp;
     temp = fopen("temp.txt","wb");
     while(fread(&prodct,sizeof(prodct),1,file)==1)
     {
             if(id==prodct.id)
             {
               found=1;
             }
             else
             { fwrite(&prodct,sizeof(prodct),1,temp);
             }
     }
     fclose(file);
     fclose(temp);
     remove("store.txt");
     rename("temp.txt","store.txt");
}
void buyproduct()
{
     int found,id;
     printf("...........Buy Products...........\n");
     printf("Enter Product Id: ");
     scanf("%d",&id);

     file = fopen("store.txt","rb+");
 while(fread(&prodct,sizeof(prodct),1,file)==1)
     {
         if(id==prodct.id)
         {
            found=1;
            prodct.quantity = prodct.quantity-1;

            fseek(file,-sizeof(prodct),1);
            fwrite(&prodct,sizeof(prodct),1,file);
            fclose(file);
             if(prodct.quantity ==0)
                  del(prodct.id);
             break;

          }
     }

     if(found ==1)
     { printf("\nProduct Buy successfully");
     }
     else
     { printf("\n Product Not Found");
     }

}
