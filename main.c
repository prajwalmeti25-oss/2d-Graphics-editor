#include <stdio.h>

#define ROWS 30
#define COLS 60

char canvas[ROWS][COLS];

/* Function Prototypes */
void clearCanvas();
void displayCanvas();

/* Clear the canvas */
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

/* Display the canvas */
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

int main()
{
    int choice;

    clearCanvas();

    do
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Display Canvas\n");
        printf("2. Clear Canvas\n");
        printf("3. Exit\n");
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
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 3);

    return 0;
}

