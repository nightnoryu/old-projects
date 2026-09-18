#include <stdio.h>
#include <stdlib.h>

char matrix[3][3];

char check(void);
void init_matrix(void);
void get_player_move(void);
void get_computer_move(void);
void disp_matrix(void);

int main(void)
{
	init_matrix();
	char done = ' ';

	printf("This is a tic tac toe game.\n");
	printf("You will play against an evil genius: a computer himself.\n");
	do
	{
		disp_matrix();
		get_player_move();
		done = check();
		if (done != ' ') break;
		get_computer_move();
		done = check();
	} while (done == ' ');

	if (done == 'X')
		printf("You won! I lied, computers are actually dumb.\n");
	else
		printf("A soulles computer won! What a pitty...\n");
	disp_matrix();

	return EXIT_SUCCESS;
}

void init_matrix(void)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			matrix[i][j] = ' ';
}

void get_player_move(void)
{
	int x, y;

	printf("Enter x and y coordinates of your move: ");
	scanf("%d %d", &x, &y);

	x--; y--;

	if (matrix[y][x] != ' ')
	{
		printf("Invalid move, try again\n");
		get_player_move();
	} else
		matrix[y][x] = 'X';
}

void get_computer_move(void)
{
	int i, j;

	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
			if (matrix[i][j] == ' ') break;
		if (matrix[i][j] == ' ') break;
	}

	if (i * j == 9)
	{
		printf("draw\n");
		exit(0);
	}

	matrix[i][j] = '0';
}

void disp_matrix(void)
{
	for (int i = 0; i < 3; ++i)
	{
		printf(" %c | %c | %c ", matrix[i][0], matrix[i][1], matrix[i][2]);
		if (i != 2)
			printf("\n---|---|---\n");
	}
	printf("\n");
}

char check(void)
{
	for (int i = 0; i < 3; ++i) // Check rows
		if (matrix[i][0] == matrix[i][1] && matrix[i][1] == matrix[i][2])
			return matrix[i][0];

	for (int i = 0; i < 3; ++i) // Check columns
		if (matrix[0][i] == matrix[1][i] && matrix[1][i] == matrix[2][i])
			return matrix[0][i];

	/* Check diagonals */
	if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2])
		return matrix[0][0];
	if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0])
		return matrix[0][2];

	return ' ';
}

