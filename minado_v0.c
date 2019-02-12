#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/*

 -Licença: MIT https://opensource.org/licenses/MIT

 -Copyright (c) 2015, Cauê Felchar

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
 deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

 - TODO:
  - pedir tamanho (transformar a matriz do field em dinâmica?)
  - ????
  - lançar no github

*/

#define MAX_I 7
#define MAX_J 13
#define BOMB '9'
#define CLEAR "clear" // cls no windows
#define SAVE_FILE_NAME "the_game.txt"

typedef struct field {
	signed char mat[MAX_I + 1][MAX_J + 1];
	short int score;
} field;
typedef struct choice_struct { short int i, j; } choice_struct;

void draw_field(field* state) {
	system(CLEAR);
	for (int i = 0; i <= MAX_I; i++) {
		printf("\n%2d ", MAX_I + 1 - i);
		for (int j = 0; j <= MAX_J; j++) {
			printf("%2c  ", state->mat[i][j] >= 'a'
			                  ? (state->mat[i][j] - ('a' - '0') == '0')
			                        ? ' '
			                        : state->mat[i][j] - ('a' - '0')
			                  : '#');
		}
		printf("\n");
	}
	printf("\n   ");
	for (int j = 0; j <= MAX_J; j++) {
		printf("%2d  ", j + 1);
	}
	printf("\nscore: %i\n", state->score);
}

field* load_field(const char file[]) {
	field* state = (field*)malloc(sizeof(field));
	state->score = 0;
	FILE* field_base = fopen(file, "r");
	for (int i = 0; i <= MAX_I; i++) {
		for (int j = 0; j <= MAX_J; j++) {
			fscanf(field_base, "%c ", &state->mat[i][j]);
			if (state->mat[i][j] == '0') {
				state->score += 1;
			}
		}
	}
	fclose(field_base);
	return state;
}

void save_field(field* state, const char file[]) {
	remove(file);
	state->score = 0;
	FILE* out = fopen(file, "w");
	for (int i = 0; i <= MAX_I; i++) {
		for (int j = 0; j <= MAX_J; j++) {
			fprintf(out, "%c ", state->mat[i][j]);
			if (state->mat[i][j] == '0')
				state->score += 1;
		}
		fprintf(out, "\n");
	}
	fclose(out);
}

choice_struct get_input() {
	choice_struct there_is_none = {-1, -1};
	printf("Digite o X e o Y do ponto onde gostaria de clicar:\n");
	while (there_is_none.i < 0 || there_is_none.i > MAX_I ||
	       there_is_none.j < 0 || there_is_none.j > MAX_J) {
		scanf("%hd %hd", &there_is_none.j, &there_is_none.i);
		if (there_is_none.i == 666 || there_is_none.j == 666) {
			exit(1);
		}
		there_is_none.j -= 1;
		there_is_none.i = MAX_I + 1 - there_is_none.i;
	}
	return there_is_none;
}

short int cont_bombs(short int i, short int j, field* state) {
	short int bomb = 0;
	for (int mod_i = -1; mod_i <= 1; mod_i++) {
		for (int mod_j = -1; mod_j <= 1; mod_j++) {
			if ((i == 0 && mod_i == -1) || (i == MAX_I && mod_i == 1))
				continue;
			if ((j == 0 && mod_j == -1) || (j == MAX_J && mod_j == 1))
				continue;
			if (state->mat[i + mod_i][j + mod_j] == BOMB) {
				bomb++;
			}
		}
	}
	return bomb;
}

void make_visible(int i, int j, field* state) {
	if (i < 0 || j < 0 || i > MAX_I || j > MAX_J)
		return;
	if (state->mat[i][j] == BOMB || state->mat[i][j] >= 'a')
		return;
	short int bomb_n = cont_bombs(i, j, state);
	state->mat[i][j] = 'a' + bomb_n;
	if (bomb_n == 0) {
		for (int mod_i = -1; mod_i <= 1; mod_i++) {
			if ((i == 0 && mod_i == -1) || (i == MAX_I && mod_i == 1))
				continue;
			for (int mod_j = -1; mod_j <= 1; mod_j++) {
				if ((j == 0 && mod_j == -1) || (j == MAX_J && mod_j == 1))
					continue;
				make_visible(i + mod_i, j + mod_j, state);
			}
		}
	}
	return;
}

bool act_on_input(choice_struct ch, field* state) {
	if (state->mat[ch.i][ch.j] == BOMB) {
		return false;
	} else {
		if (state->score == 0)
			return false;
		make_visible(ch.i, ch.j, state);
	}
	return true;
}

void create_game(const char file[]) {
	int dif = 8;
	do {
		printf("How many mines would you like? (standard 8, maximum %i)\n",
		       (MAX_I+1) * (MAX_J+1));
		scanf("%i", &dif);
	} while (dif > (MAX_I+1) * (MAX_J+1) || dif <= 0);
	remove(file);
	field* new_game = (field*)malloc(sizeof(field));
	int mat_x[dif], mat_y[dif];
	for (int i = 0; i < dif; i++) {
		mat_x[i] = rand() % (MAX_I + 1);
		mat_y[i] = rand() % (MAX_J + 1);
	}
	for (int i = 0; i <= MAX_I; i++) {
		for (int j = 0; j <= MAX_J; j++) {
			new_game->mat[i][j] = '0';
		}
	}
	for (int i = 0; i < dif; i++) {
		new_game->mat[mat_x[i]][mat_y[i]] = BOMB;
	}
	save_field(new_game, file);
	free(new_game);
}

int main() {

	srand(time(NULL));

	FILE* existence_test;
	char choice = '0';

	if ((existence_test = fopen(SAVE_FILE_NAME, "r")) != NULL) {
		fclose(existence_test);
		while (choice != 'y' && choice != 'n') {
			printf("Continue last game? (y/n)\n");
			scanf("%c", &choice);
			getchar();
		}
		if (choice == 'n')
			create_game(SAVE_FILE_NAME);
	} else { create_game(SAVE_FILE_NAME); }

	field* state = load_field(SAVE_FILE_NAME);
	bool playing = true;

	while (playing) {
		save_field(state, SAVE_FILE_NAME);
		draw_field(state);
		if(state->score == 0){
			break;
		}
		choice_struct ch = get_input();
		playing = act_on_input(ch, state);
	}

	if (state->score > 0) {
		draw_field(state);
		printf("You lost :<\n");
		remove(SAVE_FILE_NAME);
	} else {
		draw_field(state);
		printf("You won!\n");
		remove(SAVE_FILE_NAME);
	}
	return 0;
}