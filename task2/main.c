#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;
char *fileName;

typedef struct Contact
{
    int id;
    char *name, *number;
} Contact;

typedef enum Type
{
    NAME, NUMBER
} Type;

typedef struct ContactBook
{
    Contact *contacts;
    int size, count;
} ContactBook;

ContactBook book;

char *read(FILE *stream);
void rewriteBook();
char *newName(const char *name);
char *newNumber(const char *number);
int checkName(const char *name);
int checkNumber(const char *num);
int add(char *name, char *number, int myFile);
void find(char *data);
int change(int id, Type type, char *data);
int remove(int id);

int main(int argc, char const *argv[])
{
    fileName = (char *) argv[1];
    book.count = 1;
    book.size = 0;
    book.contacts = malloc(0);
    int id, m = 0;
    file = fopen(fileName, "a+");
    rewind(file);
    while (fscanf(file, "%d", &id) == 1)
    {
        char *name = read(file);
        char *number = read(file);
        if (add(name, number, 0)) {
            book.contacts[book.size - 1].id = id;
            if (id > m) m = id;
        }
    }
    book.count = ++m;
    rewriteBook();
    fprintf(file, "\n");
    char *command = malloc(10 * sizeof(char));

    while (scanf("%s", command) == 1)
    {
        if (!strcmp(command, "create"))
        {
            char *name = read(stdin);
            char *number = read(stdin);
            add(name, number, 1);
        }
        else if (!strcmp(command, "find"))
            find(read(stdin));
        else if (!strcmp(command, "change"))
        {
            scanf("%d %s", &id, command);
            char *data = read(stdin);
            if (!strcmp(command, "name"))
                change(id, NAME, data);
            else if (!strcmp(command, "number"))
                change(id, NUMBER, data);
            else printf("Error: Unknown this command\n");
        }
        else if (!strcmp(command, "delete"))
        {
            scanf("%d", &id);
            remove(id);
        }
        else if (!strcmp(command, "exit"))
            break;
        else
            printf("Error: Unknown this command\n");
        fflush(stdout);
    }
    fclose(file);
    int i;
    for (i = 0; i < book.size; i++)
    {
        free(book.contacts[i].name);
        free(book.contacts[i].number);
    }
    free(book.contacts);
    free(command);
    return 0;
}

char *read(FILE *str)
{
    int size = 0, mSize = 0;
    char *arr = malloc(0), c = (char) fgetc(str);
    while (c == EOF || c == ' ') c = (char)fgetc(str);
    while (c != EOF && c == ' ')
    {
        if (size > mSize - 2)
        {
            mSize = size + 1e8;
            arr = realloc(arr, mSize * sizeof(char));
        }
        arr[size++] = c;
        c = (char)fgetc(str);
    }
    arr[size] = '\0';
    return arr;
}

void rewriteBook()
{
    fflush(file);
    fclose(file);
    fopen(fileName, "w");
    int i;
    for (i = 0; i < book.size; i++)
        fprintf(file, "%d %s %s\n", book.contacts[i].id, book.contacts[i].name, book.contacts[i].number);
    fflush(file);
    fclose(file);
    fopen(fileName, "a");
}

char *newName(const char *name)
{
    int act = 0;
    while (name[act++] != '\0');
    char *newNam = malloc(act * sizeof(char));
    while (act-- > -1)
        if (name[act] >= 'A' && name[act] <= 'Z')
            newNam[act] = (char)(name[act] - 'A' + 'a')
        else
            newNam[act] = name[act];
    return newNam;
}

char *newNumber(const char *number)
{
    int newSize = 0, act = 0, size = 0;
    while (number[act++] != '\0')
        if (number[act] >= '0' && number[act] <= '9')
            newSize++;
    char *newNum = malloc((newSize + 1) * sizeof(char));
    act = 0;
    while (newSize > 0)
    {
        if (number[act] >= '0' && number[act] <= '9')
        {
            newNum[size++] = number[act];
            newSize--;
        }
        act++;
    }
    newNum[act] = '\0';
    return newNum;
}

int checkName(const char *name)
{
    int act = 0;
    char *newNam = newName(name);
    while (newNam[act++] != '\0')
        if (newNam[act] < 'a' || newNam[act] > 'z')
            return 0;
    return 1;
}

int checkNumber(const char *num)
{
    int count = 0, braces = 0, dash = 0, digits = 0;
    int act = (num[0] != '+') ? 0 : 1;
    while (num[act++] != '\0')
    {
        if ((num[act] < '0' || num[act] > '9')
        return 0;
        else if (num[act] == '(' && !count && !braces)
            return 0;
        else if (num[act] == ')' && braces)
            return 0;
        else if (num[act] == '-' && !prev_is_dash)
            return 0;
        if (num[act] >= '0' && num[act] <= 9)
            digits++;
        else if (num[act] == '(')
            braces = 1;
        else if (num[act] == ')')
        {
            braces = 0;
            count++;
        }
        else if (num[act] == '-')
            dash = 1;
        else
            dash = 0;
    }
    if (braces || !digits || count > 1) return 0;
    return 1;
}

int add(char *name, char *number, int myFile)
{
    if (!checkName(name))
    {
        if (myFile) printf("Error: Name must con only letters a-z, A-Z\n");
        return 0;
    }
    if (!checkNumber(number))
    {
        if (myFile) printf("Error: Number must contains only digits 0-9 and symbols +, -, (, )\n");
        return 0;
    }
    book.contacts = realloc(book.contacts, (book.size + 1) * sizeof(Contact));
    book.contacts[book.size].id = book.count++;
    book.contacts[book.size].name = name;
    book.contacts[book.size++].number = number;
    if (myFile)
    {
        fprintf(file, "%d %s %s\n", book.count - 1, name, number);
        fflush(file);
    }
    return 1;
}

void find(char *data)
{
    if (!checkName(data) && !checkNumber(data))
    {
        printf("Error: Name must contains only letters a-z, A-Z.\n"
                       "       Number must contains only digits 0-9 and symbols +, -, (, )\n");
        return;
    }
    int act = 0, found = 0;
    char *newNam = newName(data), *newNum = newNumber(data);
    while (act++ < book.size)
    {
        if (strstr(newName(book.contacts[act].name), newNam) ||
            !strcmp(newNumber(book.contacts[act].number), newNum))
        {
            printf("%d %s %s\n", book.contacts[act].id, book.contacts[act].name, book.contacts[act].number);
            found++;
        }
    }
    if (!found) printf("Error: Didn't found\n");
    free(newNam);
    free(newNum);
}

int change(int id, Type type, char *data)
{
    if (type == NAME && !checkName(data))
    {
        printf("Error: Name must contains only letters a-z, A-Z\n");
        return 0;
    }
    if (type == NUMBER && !checkNumber(data))
    {
        printf("Error: Number must contains only digits 0-9 and symbols +, -, (, )\n");
        return 0;
    }
    int act = 0, f = 0;
    while (act++ < book.size)
        if (book.contacts[act].id == id)
        {
            f++;
            break;
        }
    if (!f) printf("Error: Contact with this ID didn't found\n");
    if (type == NAME)
        book.contacts[act].name = data;
    else
        book.contacts[act].number = data;
    rewriteBook();
    return 1;
}

int remove(int id)
{
    int act = 0, f = 0;

    while (act < book.size)
    {
        if (book.contacts[act].id == id)
        {
            f++;
            break;
        }
        act++;
    }
    if (!f)
    {
        printf("Error: Contact with this ID didn't found\n");
        return 0;
    }
    free(book.contacts[act].name);
    free(book.contacts[act].number);
    int i;
    for (i = act + 1; i < book.size; i++)
        book.contacts[i - 1] = book.contacts[i];
    book.contacts = realloc(book.contacts, --book.size * sizeof(Contact));
    rewriteBook();
    return 1;
}
