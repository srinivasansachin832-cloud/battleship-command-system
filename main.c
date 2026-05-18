# main.c

Create a file named `main.c` and paste this:

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define NUM_SHIPS 3
#define SHIP_SIZE 2
#define TOTAL_SHIP_SEGMENTS (NUM_SHIPS * SHIP_SIZE)

/*
 * Battleship Command System
 * ------------------------------------------------------------
 * A single-player Battleship simulation written in C for a
 * computer engineering programming project. The program models
 * a 10x10 targeting grid using two-dimensional arrays, randomly
 * places three two-segment ships, validates user input, tracks
 * board state, detects hits/misses/sunk ships, and reports
 * performance statistics after each game.
 */

void initializeBoard(int board[SIZE][SIZE]);
void initializeShipMap(int shipMap[SIZE][SIZE]);
void printBoard(int board[SIZE][SIZE]);
void placeShips(int shipMap[SIZE][SIZE]);
int isPlacementValid(int shipMap[SIZE][SIZE], int row, int col, int orientation);
void commitShipPlacement(int shipMap[SIZE][SIZE], int shipId, int row, int col, int orientation);
void clearInputBuffer(void);
int readShot(int *row, int *col);
void printRoundStats(int totalShots, int totalHits, int totalMisses, int longestHitStreak);

int main(void)
{
    char playAgain;
    int gamesPlayed = 0;
    int cumulativeShots = 0;
    int cumulativeHits = 0;
    int cumulativeMisses = 0;

    srand((unsigned int)time(NULL));

    printf("=====================================\n");
    printf("      BATTLESHIP COMMAND SYSTEM\n");
    printf("=====================================\n");
    printf("A C-based grid targeting simulation.\n");

    do {
        int board[SIZE][SIZE];
        int shipMap[SIZE][SIZE];
        int shipHits[NUM_SHIPS] = {0};

        int totalHits = 0;
        int totalMisses = 0;
        int totalShots = 0;
        int currentHitStreak = 0;
        int longestHitStreak = 0;
        int shipsSunk = 0;

        initializeBoard(board);
        initializeShipMap(shipMap);
        placeShips(shipMap);

        gamesPlayed++;

        printf("\nGame %d started.\n", gamesPlayed);
        printf("Grid: %dx%d\n", SIZE, SIZE);
        printf("Ships: %d ships, each covering %d connected spots\n", NUM_SHIPS, SHIP_SIZE);
        printf("Legend: 0 = unknown, 1 = miss, 2 = hit\n");

        while (totalHits < TOTAL_SHIP_SEGMENTS) {
            int row, col;
            int shipId;

            printBoard(board);

            if (!readShot(&row, &col)) {
                printf("Invalid input. Please enter numbers only.\n");
                continue;
            }

            if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
                printf("Invalid coordinates. Enter values from 1 to %d.\n", SIZE);
                continue;
            }

            if (board[row][col] != 0) {
                printf("You already fired at that coordinate. Choose a new target.\n");
                continue;
            }

            totalShots++;
            shipId = shipMap[row][col];

            if (shipId >= 0) {
                board[row][col] = 2;
                totalHits++;
                shipHits[shipId]++;
                currentHitStreak++;

                if (currentHitStreak > longestHitStreak) {
                    longestHitStreak = currentHitStreak;
                }

                printf("\nHIT! Target confirmed on Ship #%d.\n", shipId + 1);

                if (shipHits[shipId] == SHIP_SIZE) {
                    shipsSunk++;
                    printf("Ship #%d has been sunk! Ships sunk: %d/%d\n",
                           shipId + 1, shipsSunk, NUM_SHIPS);
                }
            } else {
                board[row][col] = 1;
                totalMisses++;
                currentHitStreak = 0;
                printf("\nMISS! No ship detected at that coordinate.\n");
            }
        }

        printBoard(board);

        printf("\n=====================================\n");
        printf("              MISSION COMPLETE\n");
        printf("=====================================\n");
        printf("All enemy ships were destroyed.\n");

        printRoundStats(totalShots, totalHits, totalMisses, longestHitStreak);

        cumulativeShots += totalShots;
        cumulativeHits += totalHits;
        cumulativeMisses += totalMisses;

        do {
            printf("\nPlay again? (y/n): ");
            scanf(" %c", &playAgain);
            clearInputBuffer();

            if (playAgain != 'y' && playAgain != 'Y' &&
                playAgain != 'n' && playAgain != 'N') {
                printf("Please enter y or n.\n");
            }
        } while (playAgain != 'y' && playAgain != 'Y' &&
                 playAgain != 'n' && playAgain != 'N');

    } while (playAgain == 'y' || playAgain == 'Y');

    printf("\n=====================================\n");
    printf("          SESSION SUMMARY\n");
    printf("=====================================\n");
    printf("Games Played: %d\n", gamesPlayed);
    printf("Cumulative Shots: %d\n", cumulativeShots);
    printf("Cumulative Hits: %d\n", cumulativeHits);
    printf("Cumulative Misses: %d\n", cumulativeMisses);

    if (cumulativeShots > 0) {
        printf("Cumulative Accuracy: %.2f%%\n",
               (cumulativeHits / (float)cumulativeShots) * 100.0f);
    }

    printf("Thanks for playing.\n");

    return 0;
}

void initializeBoard(int board[SIZE][SIZE])
{
    int row, col;

    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            board[row][col] = 0;
        }
    }
}

void initializeShipMap(int shipMap[SIZE][SIZE])
{
    int row, col;

    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            shipMap[row][col] = -1;
        }
    }
}

void printBoard(int board[SIZE][SIZE])
{
    int row, col;

    printf("\n      ");
    for (col = 1; col <= SIZE; col++) {
        printf("%2d ", col);
    }

    printf("\n     ");
    for (col = 0; col < SIZE; col++) {
        printf("---");
    }
    printf("\n");

    for (row = 0; row < SIZE; row++) {
        printf("%2d |  ", row + 1);

        for (col = 0; col < SIZE; col++) {
            printf("%2d ", board[row][col]);
        }

        printf("\n");
    }
}

void placeShips(int shipMap[SIZE][SIZE])
{
    int shipId = 0;

    do {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        int orientation = rand() % 2;  /* 0 = horizontal, 1 = vertical */

        if (isPlacementValid(shipMap, row, col, orientation)) {
            commitShipPlacement(shipMap, shipId, row, col, orientation);
            shipId++;
        }

    } while (shipId < NUM_SHIPS);
}

int isPlacementValid(int shipMap[SIZE][SIZE], int row, int col, int orientation)
{
    int segment;

    for (segment = 0; segment < SHIP_SIZE; segment++) {
        int testRow = row;
        int testCol = col;

        if (orientation == 0) {
            testCol = col + segment;
        } else {
            testRow = row + segment;
        }

        if (testRow < 0 || testRow >= SIZE || testCol < 0 || testCol >= SIZE) {
            return 0;
        }

        if (shipMap[testRow][testCol] != -1) {
            return 0;
        }
    }

    return 1;
}

void commitShipPlacement(int shipMap[SIZE][SIZE], int shipId, int row, int col, int orientation)
{
    int segment;

    for (segment = 0; segment < SHIP_SIZE; segment++) {
        int targetRow = row;
        int targetCol = col;

        if (orientation == 0) {
            targetCol = col + segment;
        } else {
            targetRow = row + segment;
        }

        shipMap[targetRow][targetCol] = shipId;
    }
}

void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* discard extra input */
    }
}

int readShot(int *row, int *col)
{
    int userRow, userCol;

    printf("\nEnter target row (1-%d): ", SIZE);
    if (scanf("%d", &userRow) != 1) {
        clearInputBuffer();
        return 0;
    }

    printf("Enter target column (1-%d): ", SIZE);
    if (scanf("%d", &userCol) != 1) {
        clearInputBuffer();
        return 0;
    }

    clearInputBuffer();

    *row = userRow - 1;
    *col = userCol - 1;

    return 1;
}

void printRoundStats(int totalShots, int totalHits, int totalMisses, int longestHitStreak)
{
    printf("\n---------- ROUND STATISTICS ----------\n");
    printf("Total Shots Taken: %d\n", totalShots);
    printf("Total Hits: %d\n", totalHits);
    printf("Total Misses: %d\n", totalMisses);

    if (totalShots > 0) {
        printf("Accuracy: %.2f%%\n", (totalHits / (float)totalShots) * 100.0f);
    } else {
        printf("Accuracy: 0.00%%\n");
    }

    printf("Longest Hit Streak: %d\n", longestHitStreak);
    printf("--------------------------------------\n");
}
