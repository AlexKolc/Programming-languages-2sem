#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fileBook;
const char *fileName;
int ID;

typedef struct
{
    int id;
    char *name;
    char *number;
} Contact;

typedef struct
{
    int sizeBook;
    Contact *human;
} BookContacts;

BookContacts book;

char *readData(FILE *data);
void rewrite();
char *checkData(char *data);
int find(char *name);
void create(char *name, char *number);
void delete(int id);
void change(int id, char *command, char *newName);

int main(int argc, const char *argv[])
{
    fileName = argv[1];
    fileBook = fopen(argv[1], "a");
    book.sizeBook = 0;
    book.human = malloc(book.sizeBook * sizeof(Contact));

    int id;
    rewind(fileBook);
    while (fscanf(fileBook, "%d", &id) == 1)
    {
        Contact x;
        x.id = id, x.name = readData(fileBook), x.number = readData(fileBook);
        book.human = realloc(book.human, (book.sizeBook + 1) * sizeof(Contact));
        book.human[book.sizeBook++] = x;
    }

    if (book.sizeBook)
        ID = book.human[book.sizeBook - 1].id + 1;
    else
        ID = 1;

    char *command = malloc(50 * sizeof(char));
    char *data, *name, *number;
    while (scanf("%s", command) > 0)
    {
        if (!strcmp(command, "find"))
        {
            data = readData(stdin);
            find(data);
        }
        else if (!strcmp(command, "create"))
        {
            name = readData(stdin);
            number = readData(stdin);
            create(name, number);
        }
        else if (!strcmp(command, "delete"))
        {
            scanf("%d", &id);
            delete(id);
        }
        else if (!strcmp(command, "change"))
        {
            scanf("%d %s", &id, command);
            data = readData(stdin);
            change(id, command, data);
        }
        else if (!strcmp(command, "exit"))
            break;
        else
            printf("Error: Didn't find command\n");
        fflush(stdout);
    }

    free(command);
    free(book.human);
    fclose(fileBook);
    return 0;

}

char *readData(FILE *data)
{
    getc(data);
    char *new = malloc(0 * sizeof(char));
    char this = fgetc(data);
    int i = 0, j = 0;
    while (this != ' ' && this != '\n' && this != EOF)
    {
        if (i % 128 == 0) new = realloc(new, (j++ * 128) * sizeof(char));
        new[i++] = this;
        this = fgetc(data);
    }
    new[i] = '\0';
    ungetc(' ', data);
    return new;
}

void rewrite()
{
    freopen(fileName, "w", fileBook);
    int i;
    for (i = 0; i < book.sizeBook; i++)
        if (book.human[i].id)
            fprintf(fileBook, "%d %s %s\n", book.human[i].id, book.human[i].name, book.human[i].number);
    freopen(fileName, "a", fileBook);
}

char *checkData(char *data)
{
    int i = 0, f;
    char *newData = malloc(strlen(data) * sizeof(char));
    if (isalpha(data[0]))
        f = 1;
    else
        f = 0;
    if (!f)
    {
        int j = 0;
        while (data[i] != '\0')
        {
            if (isdigit(data[i]))
                newData[j++] = data[i];
            i++;
        }
        newData[j] = '\0';
    }
    else
    {
        while (data[i] != '\0')
            if (data[i] >= 'A' && data[i] <= 'Z')
                newData[i] = (char)(data[i++] - 'A' + 'a');
            else
                newData[i] = data[i++];
        data[i] = '\0';
    }
    return data;
}

int find(char *data)
{
    int f = 0;
    data = checkData(data);
    int i;
    if (isdigit(data[0]))
        for (i = 0; i < book.sizeBook; i++)
            if (!strcmp(checkData(book.human[i].number), data) && book.human[i].id)
            {
                printf("%d %s %s\n", book.human[i].id, book.human[i].name, book.human[i].number);
                f = 1;
            }
            else
                for (i = 0; i < book.sizeBook; i++)
                    if (strstr(checkData(book.human[i].name), data) && book.human[i].id) {
                        printf("%d %s %s\n", book.human[i].id, book.human[i].name, book.human[i].number);
                        f = 1;
                    }
    if (!f) printf("Error: Didn't find data\n");
    return 0;
}

void create(char *name, char *number)
{
    fprintf(fileBook, "%d %s %s\n", ID + 1, name, number);
    Contact x;
    x.id = ID++, x.name = name, x.number = number;
    book.human = realloc(book.human, (book.sizeBook + 1) * sizeof(Contact));
    book.human[book.sizeBook++] = x;
}

void delete(int id)
{
    int i;
    for (i = 0; i < book.sizeBook; i++)
        if (book.human[i].id == id) break;
    if (i != book.sizeBook)
    {
        book.human[i].id = 0;
        rewrite();
    }
}

void change(int id, char *command, char *newData)
{
    int i;
    for (i = 0; i < book.sizeBook; i++)
        if (book.human[i].id == id) break;
    if (i != book.sizeBook)
    {
        if (!strcmp(command, "name"))
            strcpy(book.human[i].name, newData);
        else if (!strcmp(command, "number"))
            strcpy(book.human[i].number, newData);
        else
        {
            printf("Error: Wrong data\n");
            return;
        }
        rewrite();
    }
    return;
}
