#include <stdio.h>

#define ROWS 30
#define COLS 60

char canvas[ROWS][COLS];

void clearCanvas();
void displayCanvas();
void drawLine(int row, int col, int length);
void drawRectangle(int row, int col, int width, int height);
void drawTriangle(int row, int col, int size);
void drawCircle(int centerRow, int centerCol, int radius);

void clearCanvas()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            canvas[i][j] = ' ';
        }
    }
}

void displayCanvas()
{
    printf("\n===== CANVAS =====\n");

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

void drawLine(int row, int col, int length)
{
    for(int i = 0; i < length; i++)
    {
        if(row >= 0 && row < ROWS && col + i >= 0 && col + i < COLS)
            canvas[row][col + i] = '*';
    }
}

void drawRectangle(int row, int col, int width, int height)
{
    for(int i = 0; i < width; i++)
    {
        if(row >= 0 && row < ROWS && col + i >= 0 && col + i < COLS)
            canvas[row][col + i] = '*';

        if(row + height - 1 >= 0 && row + height - 1 < ROWS && col + i >= 0 && col + i < COLS)
            canvas[row + height - 1][col + i] = '*';
    }

    for(int i = 0; i < height; i++)
    {
        if(row + i >= 0 && row + i < ROWS && col >= 0 && col < COLS)
            canvas[row + i][col] = '*';

        if(row + i >= 0 && row + i < ROWS && col + width - 1 >= 0 && col + width - 1 < COLS)
            canvas[row + i][col + width - 1] = '*';
    }
}

void drawTriangle(int row, int col, int size)
{
    for(int i = 0; i < size; i++)
    {
        if(row + i >= 0 && row + i < ROWS && col >= 0 && col < COLS)
            canvas[row + i][col] = '*';

        if(row + i >= 0 && row + i < ROWS && col + i >= 0 && col + i < COLS)
            canvas[row + i][col + i] = '*';

        if(row + size - 1 >= 0 && row + size - 1 < ROWS && col + i >= 0 && col + i < COLS)
            canvas[row + size - 1][col + i] = '*';
    }
}

void drawCircle(int centerRow, int centerCol, int radius)
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            int dx = i - centerRow;
            int dy = j - centerCol;
            int distance = dx * dx + dy * dy;

            if(distance >= radius * radius - radius &&
               distance <= radius * radius + radius)
            {
                canvas[i][j] = '*';
            }
        }
    }
}

int main()
{
    int choice;
    int row, col, length, width, height, size, radius;

    clearCanvas();

    do
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Display Canvas\n");
        printf("2. Clear Canvas\n");
        printf("3. Draw Line\n");
        printf("4. Draw Rectangle\n");
        printf("5. Draw Triangle\n");
        printf("6. Draw Circle\n");
        printf("7. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                displayCanvas();
                break;

            case 2:
                clearCanvas();
                printf("Canvas Cleared Successfully!\n");
                break;

            case 3:
                printf("Enter Row Column Length: ");
                scanf("%d%d%d", &row, &col, &length);
                drawLine(row, col, length);
                break;

            case 4:
                printf("Enter Row Column Width Height: ");
                scanf("%d%d%d%d", &row, &col, &width, &height);
                drawRectangle(row, col, width, height);
                break;

            case 5:
                printf("Enter Row Column Size: ");
                scanf("%d%d%d", &row, &col, &size);
                drawTriangle(row, col, size);
                break;

            case 6:
                printf("Enter Center Row Center Column Radius: ");
                scanf("%d%d%d", &row, &col, &radius);
                drawCircle(row, col, radius);
                break;

            case 7:
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 7);

    return 0;
}
