#include <stdio.h>

#define ROWS 30
#define COLS 60

char canvas[ROWS][COLS];

void clearCanvas();
void displayCanvas();
void drawLine(int row, int col, int length);
void drawRectangle(int row, int col, int width, int height);

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
        if(row >= 0 && row < ROWS && col + i < COLS)
        {
            canvas[row][col + i] = '*';
        }
    }
}

void drawRectangle(int row, int col, int width, int height)
{
    for(int i = 0; i < width; i++)
    {
        if(col + i < COLS)
        {
            canvas[row][col + i] = '*';
            canvas[row + height - 1][col + i] = '*';
        }
    }

    for(int i = 0; i < height; i++)
    {
        if(row + i < ROWS)
        {
            canvas[row + i][col] = '*';
            canvas[row + i][col + width - 1] = '*';
        }
    }
}

int main()
{
    int choice;
    int row, col, length, width, height;

    clearCanvas();

    do
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Display Canvas\n");
        printf("2. Clear Canvas\n");
        printf("3. Draw Line\n");
        printf("4. Draw Rectangle\n");
        printf("5. Exit\n");
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
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 5);

    return 0;
}
