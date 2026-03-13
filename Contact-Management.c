#include <stdio.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

int isDuplicate(char name[], char phone[]) {
    FILE *fp = fopen("contacts.csv", "r");
    struct Contact c;

    if (fp == NULL) {
        return 0;
    }

    while (fscanf(fp, "%49[^,],%14[^,],%49[^\n]\n", c.name, c.phone, c.email) == 3) {               
        if (strcmp(c.name, name) == 0 || strcmp(c.phone, phone) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void addContact() {
    FILE *fp = fopen("contacts.csv", "a");
    struct Contact c;
    printf("Enter Name (no spaces): ");
    scanf(" %49s", c.name);
    printf("Enter Phone: ");
    scanf(" %14s", c.phone);
    printf("Enter Email: ");
    scanf(" %49s", c.email);

    if (isDuplicate(c.name, c.phone)) {
    printf("Duplicate contact found! Cannot add.\n");
    fclose(fp);
    return;
}

    fprintf(fp, "%s,%s,%s\n", c.name, c.phone, c.email);
    fclose(fp);

    printf("Contact added successfully!\n");
}

void searchContact() {
    FILE *fp = fopen("contacts.csv", "r");
    struct Contact c;
    char name[50];
    int found = 0;
    
    printf("Enter name to search: ");
    scanf(" %49s", name);

    while (fscanf(fp, "%49[^,],%14[^,],%49[^\n]\n", c.name, c.phone, c.email) == 3) {
        if (strcmp(c.name, name) == 0) {
            printf("\nName : %s\nPhone: %s\nEmail: %s\n", c.name, c.phone, c.email);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Contact not found!\n");

    fclose(fp);
}

void deleteContact() {
    FILE *fp = fopen("contacts.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    struct Contact c;
    char name[50];
    int found = 0;

    printf("Enter name to delete: ");
    scanf(" %49s", name);

    while (fscanf(fp, "%49[^,],%14[^,],%49[^\n]\n", c.name, c.phone, c.email) == 3) {
        if (strcmp(c.name, name) == 0) {                                            
            found = 1;
            continue;
        }
        
        fprintf(temp, "%s,%s,%s\n", c.name, c.phone, c.email);                  
        
        }

    fclose(fp);
    fclose(temp);

    remove("contacts.csv"); 
    rename("temp.csv", "contacts.csv");

    if (found)
        printf("Contact deleted successfully!\n");                          
    else
        printf("Contact not found!\n");
}

void viewAllContacts() {
    FILE *fp = fopen("contacts.csv", "r");
    struct Contact c;

    if (fp == NULL) {
        printf("No contacts found!\n");                                 
        return;
    }

    printf("\n--- All Contacts ---\n");

    while (fscanf(fp, "%49[^,],%14[^,],%49[^\n]\n", c.name, c.phone, c.email) == 3) {                         
        printf("Name : %s\n", c.name);
        printf("Phone: %s\n", c.phone);
        printf("Email: %s\n\n", c.email);
    }

    fclose(fp);
}

int main() {
    int choice;                                     

    do {
        printf("\n--- Contact Management System ---\n");                        
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Delete Contact\n");
        printf("4. View All Contacts\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: searchContact(); break;
            case 3: deleteContact(); break;
            case 4: viewAllContacts(); break;
            case 5: printf("Exiting...\n"); break;                              
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);                                 

    return 0;
}
