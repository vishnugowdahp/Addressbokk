#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

//-----------------------------------------Sorting------------------------------------------
//If user is asking name sorted
void sortname(AddressBook *addressBook)
{  
    int i=0,j=0;
    for(i=0; i<(addressBook->contactCount)-1; i++)
    {
        for(j=0; j<(addressBook->contactCount)-i-1; j++)
        {
            if(strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j]  = addressBook->contacts[j + 1];
                addressBook->contacts[j +1] = temp;
            }
        }
    }
}
//If user is asking phone sorted
void sortphone(AddressBook *addressBook)
{ 
    int i=0,j=0;
    for(i=0; i<(addressBook->contactCount)-1; i++)
    {
        for(j=0; j<(addressBook->contactCount)-i-1; j++)
        {
            if(strcasecmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j]  = addressBook->contacts[j + 1];
                addressBook->contacts[j +1] = temp; 
            } 
        }
    }
}
//If user is asking mail sorted
void sortemail(AddressBook *addressBook)
{
    int i=0,j=0;
    for(i=0; i<(addressBook->contactCount)-1; i++)
    {
        for(j=0;j<(addressBook->contactCount)-i-1;j++)
        {
            if(strcasecmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j]  = addressBook->contacts[j + 1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }
}
//-----------------------------------------List contact function------------------------------------------------
void list(AddressBook *addressBook, int choice) 
{
    /*
        1. Read the input from user if listing to be done using sorting name, phone number or email
        2. Pass the same to respective function
        3. Then display it the screen
    */
    char name[20],phone[11],email[30];
    int i=0,j=0;
       for(i=0; i<65; i++)
       {
           printf("=");
       }
       printf("\nName\t\tPhone No\t\tEmail id\n");
       for(i =0; i<65; i++)
       {
           printf("=");
       }
    switch(choice)
    { 
        
        //if asked to list by name
        case 1: sortname(addressBook);
        for(i=0; i < addressBook->contactCount;i++)
        {
            printf("\n%-10s\t%-10s\t%-10s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }  
        break;
        //if asked to list by phone
        case 2: sortphone(addressBook);
        for(i=0; i < addressBook->contactCount;i++)
        {
            printf("\n%-10s\t%-10s\t%-10s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;
        //if asked to list by mail
        case 3: sortemail(addressBook);
        for(i=0; i < addressBook->contactCount;i++)
        {
            printf("\n%-10s\t%-10s\t%-10s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;
        default : printf("Enter a valid input..!!\n");
        break;
    }
}
//-----------------------------------------------------------------------------------------
//Initialize is a function that initializes count to 0 and arranges the contact after recieving from .csv file
void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization
    fetch_enter(addressBook);
    void sortname(AddressBook *addressBook);
    void sortphone(AddressBook *addressBook);
    void sortemail(AddressBook *addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    save_exit(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

//-----------------------------------Validation---------------------------------------------
//Validation of Name, Phone number, Email id
int valid_name(char name[])
{  
    int i=0;
    while(name[i])
    {
        if(name[i]>='a' && name[i]<='z' || name[i]>='A' && name[i]<='Z')//Alpabets a-z or A-Z 
        i++;
        else if(name[i]==' ' || name[i]=='.')//Space and dot is allowed
        i++;
        else
        {
            printf("Enter a valid name with characters, space and a dot only\n");
            return 1;
        }
    }
    return 0;
}
int valid_phone(char phone[])
{
    int i=0;
    while(phone[i])
    {
        if(phone[i]>='0' && phone[i]<='9')//Only numbers 0-9 are allowed
        i++;
        else
        {
            printf("Enter a valid phone number with digits 0-9 only\n");
            return 1;
        }
    }
    if(i==10)//Exact 10 digits are allowed
    return 0;
    else 
    {
        printf("Enter a valid phone number with 10 digits only\n");
        return 1;
    }
}
int valid_mail(char email[])
{ 
    char *small,*small1;
    small = strstr(email,".com");//Should contain .com
    small1= strstr(email,"@");
    if(small == NULL || small1 == NULL)
    {
        printf("Please enter valid mail id in name@domain.com format only\n");
        return 1;
    } 
    else
    small = small + 4;
    if(*small == '\0')//Should end with .com
    return 0;
    else 
    {
        printf("Please enter valid mail id in name@domain.com format only\n");
        return 1;
    }  
}
//-------------------------------------------Create contact function------------------------------------------------
void create(AddressBook *addressBook)
{   
    /*  
        1. Read the contact details from the user to variables
        2. Validate each details from validation function
        3. Then copy each details from variables to structure using strcpy()
     */
    char name[20],phone[11],email[30];
    int res=0,i=0;
    //ask the name
    do
    {
        printf("\nEnter the Name: ");
        scanf(" %[^\n]",name);
        res = valid_name(name);   
    }while(res); 
    //ask the phone number
    do
    {
        printf("Enter the Contact Number: ");
        scanf(" %[^\n]",phone);
        res=valid_phone(phone);  
    }while(res);
    //check if it already exits
    for(i=0; i<addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone,phone)==0)
        {
            printf("This number already exists!!\n");
            return ;
        }
    }
    //ask the email
    do
    {
        printf("Enter the Email-id : ");
        scanf(" %[^\n]",email);
        res=valid_mail(email);
    }while(res);
    //check if the email exists
    for(i=0; i<addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email,email)==0)
        {
            printf("This email already exists!!\n");
            return;
        }
    }
    //copy from variables to main structure
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);
    printf("\nContact successfully added..!!!\n");
    addressBook->contactCount++;
}

//-----------------------------------------Search contact function------------------------------------------------
void search(AddressBook *addressBook) 
{
    /*
        1. Read the search-by from user
        2. Compare the detail with each in structure
        3. Display the matched detail on screen
    */
    char name[20],phone[11],email[30];
    int i=0,flag=0;
	int res=0,op=0;
    printf("Enter search-by :\n 1.Name\n 2.Phone Number\n 3.Email id\n");
    scanf("%d",&op);
    switch(op)
    {
        //Using name
        case 1: 
        do 
        {
            printf("Enter the name: ");
            scanf(" %[^\n]",name);
            if(name[0]>='a' && name[0]<='z')
            name[0] = name[0]-32;
            res = valid_name(name);
        }while(res);

        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strstr(addressBook->contacts[i].name,name))
            { 
                if(flag==0)
                {
                    printf("Match found...!!!\n");
                }
                printf("Name = %s\tContact Number = %s\tEmail-id = %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                flag++;
            }
        }
        if(flag==0)
        {
            printf("Info not matched :(\nTry again..!!\n");
        }
        break;
        //using phone number
        case 2:
        do
        {
            printf("\nEnter Contact number : \n");
            scanf(" %[^\n]",phone);
            res = valid_phone(phone);
        }while(res);

        for(i=0; i<=(addressBook->contactCount); i++)
        {
            if(strstr(addressBook->contacts[i].phone,phone))
            { 
                printf("Contact matched!!!\n");
                printf("Name = %s\tContact Number = %s\tEmail id = %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                flag++;
                return;
            } 
        }
        if(flag==0)
        {
            printf("Info not matched!!!\nTry again\n");
        }
        break;
       //using email id
       case 3:
       do
       {
            printf("\nEnter email id\n");
            scanf(" %[^\n]",email);
            res = valid_mail(email);
        }while(res);
        for(i=0; i<=(addressBook->contactCount); i++)
        {
            if(strstr(addressBook->contacts[i].email,email))
            { 
                printf("Contact matched!!!\n");
                printf("Name = %s\tContact Number = %s\tEmail id = %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                flag++;
                return;
            }
        }
        if(flag==0)
        {
            printf("Info not matched :(\nTry again..!!\n");
        }
        break;
        default : printf("Enter a valid input..!!\n");
    } 
}

//-----------------------------------------Edit contact function------------------------------------------------

void edit(AddressBook *addressBook)
{
	/*
        1. Read the search-by from user 
        2. Ask what to edit
        3. Read the new detail and validate
        4. Update the old detail with new
    */
    char name[20],phone[11],email[30];
    int i,count=0,res=0;
    int op,index,choice;
    printf("Enter search by:\n 1.Name\n 2.Phone Number\n 3.Email id\n");
    scanf("%d",&op);

    switch(op)
    {
        case 1: 
        { 
            do
            {
                printf("Enter the Name : ");
                scanf(" %[^\n]",name);
                res = valid_name(name);
            }while(res);
            for(i=0; i<addressBook->contactCount; i++)
            {
                if(strstr(addressBook->contacts[i].name,name))
                {
                    printf("Name = %s\tContact = %s\tEmail id = %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    index = i;
                    count++;  
                } 
            } 
            if(count==1)
            {
                for(i=0; i<addressBook->contactCount; i++)
                {
                   if(strstr(addressBook->contacts[i].name,name))
                   {
                      printf("Enter the detail to be edited :\n1.Name\n2.Phone\n3.Email id\n");
                      scanf("%d",&choice);
                        
                       if(choice == 1)
                       {
                          printf("Enter the New Name:");
                          scanf(" %[^\n]",addressBook->contacts[i].name);
                          printf("\nContact updated successfully...!!!\n");
                          return;
                        }
                        else if(choice == 2)
                        {
                           printf("Enter the New Phone Number:");
                           scanf(" %[^\n]",addressBook->contacts[i].phone);
                           printf("\nContact updated successfully...!!!\n");
                           return;
                        }
                        else if(choice == 3)
                        {
                            printf("Enter the New Email id:");
                            scanf(" %[^\n]",addressBook->contacts[i].email);
                            printf("\nContact updated successfully...!!!\n");
                            return;
                        }
                        else
                        {
                            printf("Enter a valid input...!!!\n");
                            return;
                        }
                    }
                }
            }
            if(count > 1)
            {
                printf("There are multiple names matched!!\n");
                printf("Enter the phone number :");
                scanf(" %[^\n]",phone);
                for(i=0; i<addressBook->contactCount; i++)
                {
                   if(strstr(addressBook->contacts[i].phone,phone))
                   {
                      printf("Enter the details to be edited :\n1.Name\n2.Phone\n3.Email-Id\n");
                      scanf("%d",&choice);

                       if(choice == 1)
                       {
                          printf("Enter the New Name:");
                          scanf(" %[^\n]",addressBook->contacts[i].name);
                          printf("Contact updated successfully...!!!\n");
                          return;
                        }
                        else if(choice == 2)
                        {
                           printf("Enter the New Phone Number:");
                           scanf(" %[^\n]",addressBook->contacts[i].phone);
                           printf("Contact updated successfully...!!!\n");
                           return;
                        }
                        else if(choice == 3)
                        {
                            printf("Enter the New Email id:");
                            scanf(" %[^\n]",addressBook->contacts[i].email);
                            printf("Contact updated successfully...!!!\n");
                            return;
                        }
                    }
                }
                printf("Information not found :(\n");
            }
            if(count)
            { 
                for(i=0;i<addressBook->contactCount;i++)
                {
                    printf("\nAfter updation...!!\n");
                    printf("Name = %s\tContact = %s\tEmail-id = %s\n",addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
                    return;
                }
            }
        }
        break;
        case 2:
        {
            count=0;
            printf("Enter the Contact Number : ");
            scanf(" %[^\n]",phone);
            for(i=0; i<addressBook->contactCount; i++)
            {
                if(strstr(addressBook->contacts[i].phone,phone))
                {
                    printf("Name = %s\tContact = %s\tEmail-id = %s\t",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    count++;
                }
            }
            if(count)
            {
                for(i=0; i<addressBook->contactCount; i++)
                {
                   if(strstr(addressBook->contacts[i].phone,phone))
                   {
                      printf("Enter the detail to be edited :\n1.Name\n2.Phone\n3.Email id\n");
                      scanf("%d",&choice);
                        
                       if(choice == 1)
                       {
                          printf("Enter the New Name:");
                          scanf(" %[^\n]",addressBook->contacts[i].name);
                          printf("\nContact updated successfully...!!!\n");
                          return;
                        }
                        else if(choice == 2)
                        {
                           printf("Enter the New Phone Number:");
                           scanf(" %[^\n]",addressBook->contacts[i].phone);
                           printf("\nContact updated successfully...!!!\n");
                           return;
                        }
                        else if(choice == 3)
                        {
                            printf("Enter the New Email id:");
                            scanf(" %[^\n]",addressBook->contacts[i].email);
                            printf("\nContact updated successfully...!!!\n");
                            return;
                        }
                        else
                        {
                            printf("Enter a valid input...!!!\n");
                            return;
                        }
                    }
                    printf("Information not found\n");
                }
            }
        }
        break;
        case 3:
        {
            count=0;
            printf("Enter the email-Id:");
            scanf(" %[^\n]",email);
           for(i=0;i<addressBook->contactCount;i++)
           {
                if(strstr(addressBook->contacts[i].email,email))
                {
                    printf("Name = %s\nContact = %s\nEmail-id = %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    count++;
                }
            } 
            if(count)
            {
                for(i=0; i<addressBook->contactCount; i++)
                {
                   if(strstr(addressBook->contacts[i].email,email))
                   {
                      printf("Enter the detail to be edited :\n1.Name\n2.Phone\n3.Email id\n");
                      scanf("%d",&choice);
                        
                       if(choice == 1)
                       {
                          printf("Enter the New Name:");
                          scanf(" %[^\n]",addressBook->contacts[i].name);
                          printf("\nContact updated successfully...!!!\n");
                          return;
                        }
                        else if(choice == 2)
                        {
                           printf("Enter the New Phone Number:");
                           scanf(" %[^\n]",addressBook->contacts[i].phone);
                           printf("\nContact updated successfully...!!!\n");
                           return;
                        }
                        else if(choice == 3)
                        {
                            printf("Enter the New Email id:");
                            scanf(" %[^\n]",addressBook->contacts[i].email);
                            printf("\nContact updated successfully...!!!\n");
                            return;
                        }
                        else
                        {
                            printf("Enter a valid input...!!!\n");
                            return;
                        }
                    }
                    printf("Information not found\n");
                }
            }
        }
        break;
        default:printf("Enter a valid input...!!!\n");
        break;
    }
}
//-----------------------------------------Delete contact function------------------------------------------------
void del(AddressBook *addressBook)
{
    /*
        1. Read the search-by from user 
        2. Display the details
        3. Confirm if really deletion is accessed
        4. Delete the contact
    */
    char name[20],phone[11],email[30],choice;
    int op,res,i,j,flag = 0;

    printf("Enter search-by :\n 1.Name\n 2.Phone Number\n 3.Email id\n");
    scanf("%d", &op);
    
    switch(op)
    {
        // ----------------- CASE 1 : Delete by Name -----------------
        case 1:
        {
            printf("Enter the name: ");
            scanf(" %[^\n]", name);

            for(i = 0; i < addressBook->contactCount; i++)
            { 
                if(strstr(addressBook->contacts[i].name, name))
                {  
                    printf("Name = %s\tContact Number = %s\tEmail-id = %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    flag++;
                }
            }

            if(flag > 1)   // multiple matches ask by phone
            {
                printf("Multiple matches!!!\n");
                do 
                {
                    printf("Enter Contact Number:\n");
                    scanf(" %[^\n]", phone);
                    res = valid_phone(phone);
                } while(res);

                for(i = 0; i < addressBook->contactCount; i++)
                {
                    if(strstr(addressBook->contacts[i].phone, phone))
                    {
                        break;
                    }
                }
            }
            else if(flag == 1) // single match found
            {
                for(i = 0; i < addressBook->contactCount; i++)
                {
                    if(strstr(addressBook->contacts[i].name, name))
                    {
                        break;
                    }
                }
            }
            else
            {
                printf("Contact not found..!!\n");
                return;
            }
            if(flag)
            {
                do
                {
                    printf("Delete this contact? (Y/N): ");
                    scanf(" %c", &choice);
                    if(choice == 'y' || choice == 'Y')
                    {
                        for(j = i; j < addressBook->contactCount - 1; j++)
                        {
                            addressBook->contacts[j] = addressBook->contacts[j+1];
                        }
                        addressBook->contactCount--;
                        printf("Contact deleted successfully...\n");
                        return;
                    }
                    else if(choice == 'n' || choice == 'N')
                    {
                        printf("Ok retained...\n");
                        return;
                    }
                    else
                    {
                        printf("Enter a valid input..!!\n");
                    }
                }while(choice);
            }
        }
        break;

        // ----------------- CASE 2 : Delete by Phone -----------------
        case 2:
        {   
            flag=0;
            do 
            {
                printf("Enter the Chone number: ");
                scanf(" %[^\n]", phone);
                res = valid_phone(phone);
            } while(res);

            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(strstr(addressBook->contacts[i].phone, phone))
                {
                    printf("Name = %s\tContact Number = %s\tEmail id = %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    flag++;
                }
            }
            if(flag)
            {
                do
                {
                    printf("Delete this contact? (Y/N): ");
                    scanf(" %c", &choice);
                    if(choice == 'y' || choice == 'Y')
                    {
                        for(j = i; j < addressBook->contactCount - 1; j++)
                        {
                            addressBook->contacts[j] = addressBook->contacts[j+1];
                        }
                        addressBook->contactCount--;
                        printf("Contact deleted successfully...\n");
                        return;
                    }
                    else if(choice == 'n' || choice == 'N')
                    {
                        printf("Ok retained...\n");
                        return;
                    }
                    else
                    {
                        printf("Enter a valid input..!!\n");
                    }
                }while(choice);
            }
            printf("Contact not found\n");
        }
        break;
        // ----------------- CASE 3 : Delete by Email -----------------
        case 3:
        {    
            do 
            {
                printf("Enter the Email id: ");
                scanf(" %[^\n]", email);
                res = valid_mail(email);
            } while(res);

            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(strstr(addressBook->contacts[i].email, email)) // exact match
                {
                    printf("Name = %s\tContact Number = %s\tEmail-id = %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    flag++;
                }
            }
            if(flag)
            {
                do
                {
                    printf("Delete this contact? (Y/N): ");
                    scanf(" %c", &choice);
                    if(choice == 'y' || choice == 'Y')
                    {
                        for(j = i; j < addressBook->contactCount - 1; j++)
                        {
                            addressBook->contacts[j] = addressBook->contacts[j+1];
                        }
                        addressBook->contactCount--;
                        printf("Contact deleted successfully...\n");
                        return;
                    }
                    else if(choice == 'n' || choice == 'N')
                    {
                        printf("Ok retained...\n");
                        return;
                    }
                    else
                    {
                        printf("Enter a valid input..!!\n");
                    }
                }while(choice);
            }
            printf("Contact not found\n");
        }
        break;
        default: printf("Invalid option!\n");
    }
}
