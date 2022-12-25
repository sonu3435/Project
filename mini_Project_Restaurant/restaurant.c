#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct items{
    char item[20];
    int qty;
    float price;

};
struct orders{
    char customer[50];
    char date[20];
    int numOfItems;

    struct items itm[20];
};

void generateBillHeader(char name[50],char date[30]){
    printf("\n\n");
    printf("\t\t KANYAWATI_AND_SONS");
    printf("\n\t\t-------------------");
    printf("\ndate:%s",date);
    printf("\nInvoice To: %s",name);
    printf("\n");
    printf("--------------------------------------------------------\n");
    printf("Items");
    printf("\t\tQty\t\t");
    printf("Total\t\t");
    printf("\n-------------------------------------------------------");
    printf("\n\n");
}

void generateBillFfooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal  = total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal + (cgst*2);
    printf("-----------------------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%2.f","%",dis);
    printf("\n\t\t\t\t------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n---------------------------------------------------------\n");
    printf("Grand Total\t\t\t%.2f",grandTotal);
    printf("\n---------------------------------------------------------");
}

void generateBillBody(char item[30],int qty, float price){
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2ff\t\t",qty*price);
    printf("\n");
}



int main(){
   
   system("clear");
    int opt,n;
    struct orders ord;
    struct orders order;
    FILE* fp;
    char name[50];
    char saveBill = 'y',continueflag = 'y';
    while(continueflag == 'y'){
    system("clear");
    int invoiceFound = 0;
    float Total = 0;
    printf("\t\t\n===========KANYAWATI_AND_SONS===========\n");
    printf("\n\nPlease Enter your Prefered Operation\n\n");
    printf("\n1.Generate Invoice");
    printf("\n2.Show all Invoices");
    printf("\n3.Search Invoice");
    printf("\n4.Exit");

    printf("\n\nYour choice :\t");
    scanf("%d",&opt);
    fgetc(stdin);

    switch(opt){
        case 1:
        system("clear");
        printf("\nPlease Enter the name of the Customer : \t");
        fgets(ord.customer,50,stdin);
        strcpy(ord.date,__DATE__);
        printf("Please Enter the number of items : \t");
        scanf("%d",&n);
        ord.numOfItems = n;
        for(int i = 0; i < n; i++){
        fgetc(stdin);
        printf("\n\n");
        printf("Please enter the item %d :\t",i+1);
        fgets(ord.itm[i].item,20,stdin);
        ord.itm[i].item[strlen(ord.itm[i].item)-1] = 0;

        printf("Please Enter the Quantity :\t");
        scanf("%d",&ord.itm[i].qty);
        printf("Please Enter the Unit Price\t");
        scanf("%f",&ord.itm[i].price);
        Total += ord.itm[i].qty * ord.itm[i].price;
        }

        generateBillHeader(ord.customer,ord.date);
        for(int i = 0; i < ord.numOfItems; i++){

            generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
        }
        generateBillFfooter(Total);

        printf("\n Do you want to save the Invoice [y/n]:\t");
        scanf("%s",&saveBill);

        if(saveBill == 'y'){
            fp = fopen("Restaurant.dat","a+");
            fwrite(&ord,sizeof(struct orders),1,fp);
            if(fp != 0){
                printf("\nSuccessfully saved");
            }
            else
            printf("Error Saving");
            fclose(fp);
        }
        break;

        case 2:
        system("clear");
        fp = fopen("Restaurant.dat","r");
        printf("\n\t*****Your Previous Invoices*****\n");

        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            generateBillHeader(order.customer,order.date);
            for(int i = 0; i < order.numOfItems;i++){
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty*order.itm[i].price;
            }
            generateBillFfooter(tot);
        }
        fclose(fp);
        break;

        case 3:
        printf("\nenter the name of the Customer:\t");
       // fgetc(stdin);
        fgets(name,50,stdin);
        name[strlen(name)-1] = 0;
        system("clear");
        fp = fopen("Restaurant.dat","r");
        printf("\t*****Invoice Of %s*****",name);
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            if(strcmp(order.customer,name)){
            generateBillHeader(order.customer,order.date);
            for(int i = 0; i < order.numOfItems;i++){
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty*order.itm[i].price;
            }
            generateBillFfooter(tot);
            invoiceFound = 1;
        }
        }
        if(!(invoiceFound)){
            printf("Sorry the invoice for %s doesnot found\n",name);
        }
        fclose(fp);
        break;

        case 4 :
        printf("\n\t\t Bye Bye :)\n\n\n");
        exit(0);
        break;

        default:
        printf("Sorry Invalid Option");
        break;
    }
    printf("\nDo you want to perform another operation [y/n]:\t");
    scanf("%s",&continueflag);
   }
   
  printf("\n\t\t Bye Bye :)\n\n\n");  
  printf("\n\n\n");
}