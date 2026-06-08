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
void modifyShape();
void saveDrawing();
void loadDrawing();

void clearCanvas()
{
    int i, j;
    for(i = 0; i < ROWS; i++)
        for(j = 0; j < COLS; j++)
            canvas[i][j] = ' ';
}

void displayCanvas()
{
    int i, j;
    printf("\n===== CANVAS =====\n");
    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
            printf("%c", canvas[i][j]);
        printf("\n");
    }
}

void drawLine(int row, int col, int length)
{
    int i;
    for(i = 0; i < length; i++)
        if(row >= 0 && row < ROWS && col + i >= 0 && col + i < COLS)
            canvas[row][col + i] = '*';
}

void drawRectangle(int row, int col, int width, int height)
{
    int i;

    for(i = 0; i < width; i++)
    {
        if(row >= 0 && row < ROWS && col + i >= 0 && col + i < COLS)
            canvas[row][col + i] = '*';

        if(row + height - 1 >= 0 && row + height - 1 < ROWS &&
           col + i >= 0 && col + i < COLS)
            canvas[row + height - 1][col + i] = '*';
    }

    for(i = 0; i < height; i++)
    {
        if(row + i >= 0 && row + i < ROWS && col >= 0 && col < COLS)
            canvas[row + i][col] = '*';

        if(row + i >= 0 && row + i < ROWS &&
           col + width - 1 >= 0 && col + width - 1 < COLS)
            canvas[row + i][col + width - 1] = '*';
    }
}

void drawTriangle(int row, int col, int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(row + i >= 0 && row + i < ROWS && col >= 0 && col < COLS)
            canvas[row + i][col] = '*';

        if(row + i >= 0 && row + i < ROWS && col + i >= 0 && col + i < COLS)
            canvas[row + i][col + i] = '*';

        if(row + size - 1 >= 0 && row + size - 1 < ROWS &&
           col + i >= 0 && col + i < COLS)
            canvas[row + size - 1][col + i] = '*';
    }
}

void drawCircle(int centerRow, int centerCol, int radius)
{
    int i, j, dx, dy, distance;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            dx = i - centerRow;
            dy = j - centerCol;
            distance = dx * dx + dy * dy;

            if(distance >= radius * radius - radius &&
               distance <= radius * radius + radius)
                canvas[i][j] = '*';
        }
    }
}

void redrawAll()
{
    int i;
    clearCanvas();

    for(i = 0; i < shapeCount; i++)
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

    printf("\n1. Line\n2. Rectangle\n3. Triangle\n4. Circle\n");
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
    int i;

    if(shapeCount == 0)
    {
        printf("No shapes available.\n");
        return;
    }

    printf("\n===== SHAPE LIST =====\n");
    for(i = 0; i < shapeCount; i++)
    {
        printf("Index %d: Type %d, Row %d, Col %d, Value1 %d, Value2 %d\n",
               i, shapeType[i], sRow[i], sCol[i], sW[i], sH[i]);
    }
}

void deleteShape()
{
    int index, i;

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

    for(i = index; i < shapeCount - 1; i++)
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

void modifyShape()
{
    int index;

    if(shapeCount == 0)
    {
        printf("No shapes to modify.\n");
        return;
    }

    listShapes();
    printf("Enter index to modify: ");
    scanf("%d", &index);

    if(index < 0 || index >= shapeCount)
    {
        printf("Invalid index.\n");
        return;
    }

    printf("Enter new shape type 1-Line 2-Rectangle 3-Triangle 4-Circle: ");
    scanf("%d", &shapeType[index]);

    printf("Enter new row and column: ");
    scanf("%d%d", &sRow[index], &sCol[index]);

    if(shapeType[index] == 1)
    {
        printf("Enter new line length: ");
        scanf("%d", &sW[index]);
        sH[index] = 0;
    }
    else if(shapeType[index] == 2)
    {
        printf("Enter new width and height: ");
        scanf("%d%d", &sW[index], &sH[index]);
    }
    else if(shapeType[index] == 3)
    {
        printf("Enter new triangle size: ");
        scanf("%d", &sW[index]);
        sH[index] = 0;
    }
    else if(shapeType[index] == 4)
    {
        printf("Enter new circle radius: ");
        scanf("%d", &sW[index]);
        sH[index] = 0;
    }
    else
    {
        printf("Invalid shape type.\n");
        return;
    }

    redrawAll();
    printf("Shape modified successfully.\n");
}

void saveDrawing()
{
    FILE *fp;
    int i;

    fp = fopen("drawing.txt", "w");

    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    fprintf(fp, "%d\n", shapeCount);

    for(i = 0; i < shapeCount; i++)
    {
        fprintf(fp, "%d %d %d %d %d\n",
                shapeType[i], sRow[i], sCol[i], sW[i], sH[i]);
    }

    fclose(fp);
    printf("Drawing saved successfully.\n");
}

void loadDrawing()
{
    FILE *fp;
    int i;

    fp = fopen("drawing.txt", "r");

    if(fp == NULL)
    {
        printf("drawing.txt not found.\n");
        return;
    }

    fscanf(fp, "%d", &shapeCount);

    for(i = 0; i < shapeCount; i++)
    {
        fscanf(fp, "%d%d%d%d%d",
               &shapeType[i], &sRow[i], &sCol[i], &sW[i], &sH[i]);
    }

    fclose(fp);
    redrawAll();
    printf("Drawing loaded successfully.\n");
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
        printf("5. Modify Shape\n");
        printf("6. Save Drawing\n");
        printf("7. Load Drawing\n");
        printf("8. Clear Canvas\n");
        printf("9. Exit\n");
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
                modifyShape();
                break;

            case 6:
                saveDrawing();
                break;

            case 7:
                loadDrawing();
                break;

            case 8:
                clearCanvas();
                shapeCount = 0;
                printf("Canvas cleared successfully.\n");
                break;

            case 9:
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 9);

    return 0;
}
