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
int list_contacts();
int search_contacts();
void print_help();
void clear_screen();
void strip_newline(char *s);

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        FILENAME = argv[1];
    }
    char input[INPUT_LENGHT];
    print_help();
    while (1)
    {
        printf("PS C:\\Users\\yourname> ");
        if (fgets(input, INPUT_LENGHT, stdin) == NULL)
            break;
        strip_newline(input);
        char command = tolower((unsigned char)input[0]);
        if (command == 'a')
        {
            add_new_entry();
        }
        else if (command == 'l')
        {
            list_contacts();
        }
        else if (command == 's')
        {
            search_contacts();
        }
        else if (command == 'c')
        {
            clear_screen();
        }
        else if (command == 'h')
        {
            print_help();
        }
        else if (command == 'q')
        {
            return 0;
        }
        else
        {
            printf("'%s' is not a known command.\n\n", input);
        }
    }
    return 0;
}

void strip_newline(char *s)
{
    char *nl = strchr(s, '\n');
    if (nl)
        *nl = '\0';
}

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void print_help()
{
    printf("\nCommands:\n");
    printf("a - Add new contact\n");
    printf("l - List all contacts\n");
    printf("s - Search contacts\n");
    printf("c - Clear the terminal\n");
    printf("h - Show this help menu\n");
    printf("q - Quit\n\n");
}

int add_new_entry()
{
    FILE *fptr;
    fptr = fopen(FILENAME, "a");
    if (fptr == NULL)
    {
        printf("error opening file\n");
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
    strip_newline(name);
    strip_newline(address);
    strip_newline(email);
    strip_newline(number);
    fprintf(fptr, "\"%s\",\"%s\",\"%s\",\"%s\"\n", name, address, email, number);
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

static void copy_field(char *dest, const char *src)
{
    strncpy(dest, src, INPUT_LENGHT - 1);
    dest[INPUT_LENGHT - 1] = '\0';
}

int read_from_csv(Contact contact_array[])
{
    FILE *fptr;
    char buffer[(INPUT_LENGHT * 4 + 16)];
    int i = 0;
    fptr = fopen(FILENAME, "r");
    if (fptr == NULL)
    {
        printf("Couldn't open %s\n", FILENAME);
        return 0;
    }
    while (fgets(buffer, sizeof(buffer), fptr))
    {
        char *p = buffer;
        while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')
            p++;
        if (*p == '\0')
            continue;
        strip_newline(buffer);
        char fields[4][INPUT_LENGHT] = {{0}};
        int x = 0;
        p = buffer;
        while (*p && x < 4)
        {
            int fi = 0;
            if (*p == '"')
            {
                p++;
                while (*p && *p != '"' && fi < INPUT_LENGHT - 1)
                    fields[x][fi++] = *p++;
                if (*p == '"')
                    p++;
            }
            else
            {
                while (*p && *p != ',' && fi < INPUT_LENGHT - 1)
                    fields[x][fi++] = *p++;
            }
            fields[x][fi] = '\0';
            if (*p == ',')
                p++;
            x++;
        }
        copy_field(contact_array[i].name, fields[0]);
        copy_field(contact_array[i].address, fields[1]);
        copy_field(contact_array[i].email, fields[2]);
        copy_field(contact_array[i].number, fields[3]);
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

int search_contacts()
{
    char query[INPUT_LENGHT];
    printf("Search: ");
    if (fgets(query, INPUT_LENGHT, stdin) == NULL)
        return 0;
    strip_newline(query);
    if (query[0] == '\0')
    {
        printf("Empty search\n\n");
        return 0;
    }
    int count = read_from_csv(contact_array);
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (strstr(contact_array[i].name, query) ||
            strstr(contact_array[i].address, query) ||
            strstr(contact_array[i].email, query) ||
            strstr(contact_array[i].number, query))
        {
            print_contact(&contact_array[i]);
            found++;
        }
    }
    if (found == 0)
        printf("No matches\n\n");
    return 0;
}