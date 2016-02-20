#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[])
{
    int n, i, j, size, max;
    scanf("%d", &n);
    /*Выделение памяти под таблицу умножения*/
    int **table = (int **) malloc((n + 1) * sizeof(int *));
    /*+ заполнение значениями*/
    for (i = 1; i <= n; ++i)
    {
        table[i] = (int *) malloc((n + 1) * sizeof(int));
        for (j = 1; j <= n; ++j)
        {
            table[i][j] = i * j;
        }
    }
    /*Выполнение запросов*/
    int x1, y1, x2, y2;
    scanf("%d", &x1);
    while (x1)
    {
        scanf("%d %d %d", &y1, &x2, &y2);
        max = table[x2][y2];
        size = 0;
        while (max)
        {
            size++;
            max /= 10;
        }
        for (i = x1; i <= x2; ++i)
        {
            for (j = y1; j <= y2; ++j)
            {
                printf("%*d", size + 1, table[i][j]);
            }
            printf("\n");
        }
        scanf("%d", &x1);
    }
    /*освобождение памяти*/
    for (i = 1; i <= n; ++i)
    {
        free(table[i]);
    }
    free(table);
    return 0;
}
