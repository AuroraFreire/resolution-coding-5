#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LENGHT 100

char *FILENAME = "contact_book_data.csv";

typedef struct Contact
{
    char name[INPUT_LENGHT];
    char address[INPUT_LENGHT];
    char email[INPUT_LENGHT];
    char number[INPUT_LENGHT];
} Contact;

Contact contact_array[100];

int add_new_entry();

int main()
{
    add_new_entry();
    return 0;
}

int add_new_entry()
{
    FILE *fptr;
    fptr = fopen(FILENAME, "a");
    if (fptr == NULL)
    {
        printf("error opening file.\n");
        return 1;
    }
    char name[INPUT_LENGHT] = "name_here";
    char address[INPUT_LENGHT] = "address_here";
    char email[INPUT_LENGHT] = "email_here";
    char number[INPUT_LENGHT] = "number_here";
    printf("Enter name: ");
    fgets(name, INPUT_LENGHT, stdin);
    printf("Enter address: ");
    fgets(address, INPUT_LENGHT, stdin);
    printf("Enter email: ");
    fgets(email, INPUT_LENGHT, stdin);
    printf("Enter phone number: ");
    fgets(number, INPUT_LENGHT, stdin);
    fprintf(fptr, "\n%s,%s,%s,%s\n", name, address, email, number);
    fclose(fptr);
    printf("\nSaved contact!\n\n");
    return 0;
}

void print_contact(const Contact *contact)
{
    printf("Name: %s\n", contact->name);
    printf("Address: %s\n", contact->address);
    printf("Email: %s\n", contact->email);
    printf("Phone Number: %s\n", contact->number);
    printf("\n");
}

int read_from_csv(Contact contact_array[])
{
    FILE *fptr;
    char buffer[(INPUT_LENGHT * 4 + 5)];
    int i = 0;
    fptr = fopen(FILENAME, "r");
    if (fptr == NULL)
    {
        printf("Could not open %s\n", FILENAME);
        return 0;
    }
    while (fgets(buffer, sizeof(buffer), fptr))
    {
        char *p = buffer;
        while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')
            p++;
        if (*p == '\0')
            continue;
        char *new_line_pointer = strchr(buffer, '\n');
        if (new_line_pointer)
            *new_line_pointer = '\0';
        char *field = strtok(buffer, ",");
        int x = 0;
        while (field != NULL)
        {
            if (x == 0)
            {
                strncpy(contact_array[i].name, field, INPUT_LENGHT - 1);
                contact_array[i].name[INPUT_LENGHT - 1] = '\0';
            }
            else if (x == 1)
            {
                strncpy(contact_array[i].address, field, INPUT_LENGHT - 1);
                contact_array[i].address[INPUT_LENGHT - 1] = '\0';
            }
            else if (x == 2)
            {
                strncpy(contact_array[i].email, field, INPUT_LENGHT - 1);
                contact_array[i].email[INPUT_LENGHT - 1] = '\0';
            }
            else if (x == 3)
            {
                strncpy(contact_array[i].number, field, INPUT_LENGHT - 1);
                contact_array[i].number[INPUT_LENGHT - 1] = '\0';
            }
            x++;
            field = strtok(NULL, ",");
        }
        i++;
        if (i >= 100)
            break;
    }
    fclose(fptr);
    return i;
}

int list_contacts()
{
    int contact_count = read_from_csv(contact_array);
    for (int i = 0; i < contact_count; i++)
    {
        print_contact(&contact_array[i]);
    }
    return 0;
}