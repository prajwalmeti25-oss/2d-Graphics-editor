#include <stdio.h>

#define ROWS 30
#define COLS 60
#define MAX_SHAPES 100

char canvas[ROWS][COLS];

int shapeType[MAX_SHAPES];
int sRow[MAX_SHAPES], sCol[MAX_SHAPES];
int sW[MAX_SHAPES], sH[MAX_SHAPES];
int shapeCount = 0;

void clearCanvas();
void displayCanvas();
void drawLine(int row, int col, int length);
void drawRectangle(int row, int col, int width, int height);
void drawTriangle(int row, int col, int size);
void drawCircle(int centerRow, int centerCol, int radius);
void redrawAll();
void addShape();
void listShapes();
void deleteShape();

void clearCanvas()
{
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            canvas[i][j] = ' ';
}

void displayCanvas()
{
    printf("\n===== CANVAS =====\n");
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
            printf("%c", canvas[i][j]);
        printf("\n");
    }
}

void drawLine(int row, int col, int length)
{
    for(int i = 0; i < length; i++)
        if(row >= 0 && row < ROWS && col + i >= 0 && col + i < COLS)
            canvas[row][col + i] = '*';
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
                canvas[i][j] = '*';
        }
    }
}

void redrawAll()
{
    clearCanvas();

    for(int i = 0; i < shapeCount; i++)
    {
        if(shapeType[i] == 1)
            drawLine(sRow[i], sCol[i], sW[i]);
        else if(shapeType[i] == 2)
            drawRectangle(sRow[i], sCol[i], sW[i], sH[i]);
        else if(shapeType[i] == 3)
            drawTriangle(sRow[i], sCol[i], sW[i]);
        else if(shapeType[i] == 4)
            drawCircle(sRow[i], sCol[i], sW[i]);
    }
}

void addShape()
{
    if(shapeCount >= MAX_SHAPES)
    {
        printf("Shape limit reached.\n");
        return;
    }

    printf("\n1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Triangle\n");
    printf("4. Circle\n");
    printf("Enter shape type: ");
    scanf("%d", &shapeType[shapeCount]);

    printf("Enter row and column: ");
    scanf("%d%d", &sRow[shapeCount], &sCol[shapeCount]);

    if(shapeType[shapeCount] == 1)
    {
        printf("Enter line length: ");
        scanf("%d", &sW[shapeCount]);
        sH[shapeCount] = 0;
    }
    else if(shapeType[shapeCount] == 2)
    {
        printf("Enter width and height: ");
        scanf("%d%d", &sW[shapeCount], &sH[shapeCount]);
    }
    else if(shapeType[shapeCount] == 3)
    {
        printf("Enter triangle size: ");
        scanf("%d", &sW[shapeCount]);
        sH[shapeCount] = 0;
    }
    else if(shapeType[shapeCount] == 4)
    {
        printf("Enter circle radius: ");
        scanf("%d", &sW[shapeCount]);
        sH[shapeCount] = 0;
    }
    else
    {
        printf("Invalid shape type.\n");
        return;
    }

    shapeCount++;
    redrawAll();
    printf("Shape added successfully.\n");
}

void listShapes()
{
    if(shapeCount == 0)
    {
        printf("No shapes available.\n");
        return;
    }

    printf("\n===== SHAPE LIST =====\n");
    for(int i = 0; i < shapeCount; i++)
    {
        printf("Index %d: Type %d, Row %d, Col %d, Value1 %d, Value2 %d\n",
               i, shapeType[i], sRow[i], sCol[i], sW[i], sH[i]);
    }
}

void deleteShape()
{
    int index;

    if(shapeCount == 0)
    {
        printf("No shapes to delete.\n");
        return;
    }

    listShapes();

    printf("Enter index to delete: ");
    scanf("%d", &index);

    if(index < 0 || index >= shapeCount)
    {
        printf("Invalid index.\n");
        return;
    }

    for(int i = index; i < shapeCount - 1; i++)
    {
        shapeType[i] = shapeType[i + 1];
        sRow[i] = sRow[i + 1];
        sCol[i] = sCol[i + 1];
        sW[i] = sW[i + 1];
        sH[i] = sH[i + 1];
    }

    shapeCount--;
    redrawAll();
    printf("Shape deleted successfully.\n");
}

int main()
{
    int choice;

    clearCanvas();

    do
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Add Shape\n");
        printf("2. Display Canvas\n");
        printf("3. List Shapes\n");
        printf("4. Delete Shape\n");
        printf("5. Clear Canvas\n");
        printf("6. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addShape();
                break;

            case 2:
                displayCanvas();
                break;

            case 3:
                listShapes();
                break;

            case 4:
                deleteShape();
                break;

            case 5:
                clearCanvas();
                shapeCount = 0;
                printf("Canvas cleared successfully.\n");
                break;

            case 6:
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 6);

    return 0;
}
