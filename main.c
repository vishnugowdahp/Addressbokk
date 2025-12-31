/* 
    Name : Vishnu Gowda H P
    Topic : Address Book Project
    Description : Design and implement C program to create, search, list, edit and delete contact along with retaining the previous inputs 
    Pre-requisites : Functions, Arrays, Pointers, Structures, Strings and File Concepts
    Sample Input :  -----Main Menu-----
                    1.Create Contact
                    2.Search Contact
                    3.Edit Contact
                    4.Delete Contact
                    5.List all Contact
                    6.Save and Exit

                    Please enter the service :
                    1                 
                    Enter the name :
                    Tejas
                    Enter the contact number :
                    1234567
    Sample Output : Error: Number should contain 10 digits.

    Sample Input :  Please enter the service :
                    2
                    Enter the search-by :
                    1. Name
                    2. Contact Number
                    3. Email id
                    1
                    Enter the name :
                    Tejas
    Sample Output : Contact matched..!!!
                    Name = Tejas   Contact = 1234567890  Email id = tejas@gmail.com

    Sample Input :  Please enter the service :
                    5
                    Enter the sort-by :
                    1. Name
                    2. Contact Number
                    3. Email id
                    2
    Sample Output : ===================================
                    Name      Contact     Email
                    ===================================
                    a         1234567890  a@gmail.com
                    b         0987654321  b@gmail.com
                    ===================================

    Sample Input :  Please enter the service :
                    3
                    Enter the search-by :
                    1. Name
                    2. Contact Number
                    3. Email id
                    2
                    Enter the contact number :
                    1234567890
                    Name = a  Contact = 1234567890 Email = a@gmail.com
                    Enter the detail to be edited :
                    1
                    Enter the new name : 
                    Geetha
    Sample Output : Name = Geetha  Contact = 1234567890 Email = a@gmail.com
                    Contact Updated Successfully...!!!

    Sample Input :  Please enter the service :
                    6
    Sample Output : Contacts Saved Successfully!!!
                    Thank you..!!
                    See you again!!!
*/
#include<stdio.h>
#include"contact.h"

int main()
{ 
    int option; 
    AddressBook addressBook;
    initialize(&addressBook);
    do
    {
        printf("\n==========Main Menu============\n\t1.Create Contact\n\t2.Search Contact\n\t3.Edit Contact\n\t4.Delete Contact\n\t5.List all Contact\n\t6.Save and Exit\n");
        printf("\nPlease enter the service : ");
        scanf("%d",&option);
        switch(option)
        {
            case 1: create(&addressBook);
                break;
            case 2: search(&addressBook);
                break;
            case 3: edit(&addressBook);
                break;
             case 4: del(&addressBook);
                break;
            case 5: 
                printf("Select sort by :\n");
                printf("1. Sort by Name\n");
                printf("2. Sort by Phone number\n");
                printf("3. Sort by Email id\n");
                printf("Please select Sort-by : ");
                int choice;
                scanf("%d", &choice);
                list(&addressBook,choice);
                break;
            case 6:
                save_exit(&addressBook);
                printf("Contacts Saved Successfully!!!\n");
                printf("Thank you..!!\nSee you again!!!\n");
                break;
            default: printf("Enter a valid input!!!\n");
        }
    }
    while(option!=6);
    return 0;
}
