#include <stdio.h>
#include "file.h"
//While exit the program the functions done to be saved and retrieved once we login
void save_exit(AddressBook *addressBook) 
{
    /*
        1. Open a file in .csv
        2. Copy from Structure in Write mode
        3. Close the file
    */
    int i;
    char ch;
    FILE *fptr=fopen("file.csv","w");//open the .csv file and write the everything in structure array to .csv file
    if(fptr==NULL)
    {
        printf("File doesn't exist\n");
    }
    for(i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fptr,"%d,%s,%s,%s\n", i+1, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}
//When we login back the values get copied back from .csv file
void fetch_enter(AddressBook *addressBook) 
{
    /*
        1. open the .csv file and copy it to structure
        2. Specify the format
        3. Close the file
    */
    int i;
    addressBook -> contactCount = 0;
    FILE *fptr=fopen("file.csv","r");//open the .csv file and read the everything in .csv file to structure array
    if(fptr==NULL)
    {
        return; 
    }
    for(i=0; addressBook -> contactCount<MAX_CONTACTS;)
    {
        int res=fscanf(fptr,"%d,%29[^,],%10s,%s39\n", &i, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        if(res!=4)
        break;
        addressBook -> contactCount++;
    }
    fclose(fptr);
}