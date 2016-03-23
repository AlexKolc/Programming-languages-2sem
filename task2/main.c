#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fileBook;
const char *fileName;
int ID = 0;
char *helper;

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
int checkData(char *data);
void find(char *name);
void create(char *name, char *number);
void delete(int id);
void change(int id, char *command, char *newName);

int main(int argc, const char *argv[])
{
    fileName = argv[1];
    fileBook = fopen(fileName, "a+");
    book.sizeBook = 0;
    book.human = malloc(0 * sizeof(Contact));
    rewind(fileBook);
    int id;
    while (fscanf(fileBook, "%d", &id) == 1)
    {
        Contact x;
        x.id = id, x.name = readData(fileBook), x.number = readData(fileBook);
        checkData(x.name), x.name = helper;
        checkData(x.number), x.number = helper;
        book.human = realloc(book.human, (book.sizeBook + 1) * sizeof(Contact));
        book.human[book.sizeBook++] = x;
        if (id > ID) ID = id;
    }
    rewrite();
    ID++;
    char *command = malloc(50 * sizeof(char));
    char *data, *name, *number;
    while (1)
    {
        scanf("%s", command);
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
        if (i % 128 == 0) new = realloc(new, (++j * 128) * sizeof(char));
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
    freopen(fileName, "a+", fileBook);
}

int checkData(char *data)
{
    int i = -1, f;
    char *newData = malloc(strlen(data) * sizeof(char));
    if (data[0] >= 'a' && data[0] <= 'z' || data[0] >= 'A' && data[0] <= 'Z')
        f = 1;
    else
        f = 0;
    if (!f)
    {
        int j = 0, bracket = 0, countBrackets = 0;
        if (data[0] == '+') i++;
        while (data[++i] != '\0')
            if (data[i] >= '0' && data[i] <= '9')
                newData[j++] = data[i];
            else if (data[i] == '(')
                bracket = 1;
            else if (data[i] == ')')
            {
                if (!bracket)
                {
                    printf("+Error: Wrong input name or number\n");
                    return 0;
                }
                bracket = 0;
                countBrackets++;
                if (countBrackets > 1)
                {
                    printf("-Error: Wrong input name or number\n");
                    return 0;
                }
            }
            else if (data[i] == '-' && data[i + 1] == '\0' || data[i] != '-')
            {
                printf("*Error: Wrong input name or number\n");
                return 0;
            }
        if (bracket == 1)
        {
            printf("/Error: Wrong input name or number\n");
            return 0;
        }
        newData[j] = '\0';
    }
    else
    {
        while (data[++i] != '\0')
            if (data[i] >= 'A' && data[i] <= 'Z')
                newData[i] = (char) (data[i] - 'A' + 'a');
            else if  (data[i] >= 'a' && data[i] <= 'z')
                newData[i] = data[i];
            else
            {
                printf("^Error: Wrong input name or number\n");
                return 0;
            }
        newData[i] = '\0';
    }
    helper = newData;
    return 1;
}

void find(char *data)
{
    int f = 0;
    if (!checkData(data))
        return;
    else
        data = helper;
    int i;
    if (data[0] >= '0' && data[0] <= '9')
    {
        for (i = 0; i < book.sizeBook; i++)
        {
            if (!strcmp(book.human[i].number, data) && book.human[i].id) {
                printf("%d %s %s\n", book.human[i].id, book.human[i].name, book.human[i].number);
                f = 1;
            }
        }
    }
    else
    {
        for (i = 0; i < book.sizeBook; i++)
            if (strstr(book.human[i].name, data) && book.human[i].id) {
                printf("%d %s %s\n", book.human[i].id, book.human[i].name, book.human[i].number);
                f = 1;
            }
    }
    if (!f) printf("Error: Didn't find data\n");
}

void create(char *name, char *number)
{
    if (!checkData(name))
        return;
    else
        name = helper;
    if (!checkData(number))
        return;
    else
        number = helper;
    fprintf(fileBook, "%d %s %s\n", ID, name, number);
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
