#ifndef CONTACT_H
#define CONTACT_H
#define MAX_CONTACTS 100

typedef struct //Contact structure
{
    char name[30];
    char phone[11];
    char email[40];
}Contact; 

typedef struct//Array structure with count
{
    Contact contacts[100];
    int contactCount ;
} AddressBook;

void create(AddressBook *addressBook);
void search(AddressBook *addressBook);
void edit(AddressBook *addressBook);
void del(AddressBook *addressBook);
void list(AddressBook *addressBook, int choice);
void initialize(AddressBook *addressBook);
void save_exit(AddressBook *AddressBook);

#endif