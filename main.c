#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct node_ {
	int row;
	int col;
	char head_tail;
	struct node_ *next;
}node;
node* create_element(int row, int col,char ch) {
	node* element = malloc(sizeof(node));
	element->row = row;
	element->col = col;
	element->next = NULL;
	element->head_tail = ch;
	return element;
}
void add(node** head,int row,int col,char ch) {
	node* element = create_element(row, col, ch);
	if (*head) {
		element->head_tail = (*head)->head_tail;
		(*head)->head_tail = ch;
	}
	element->next = *head;
	*head = element;
}
void add_and_remove_last(node** head, int row, int col, char ch) {
	node* run;
	add(head, row, col, ch);
	run = *head;
	while (run->next && run->next->next)
		run = run->next;
	if (run->next) {
		free(run->next);
		run->next = NULL;
	}
}
enum move {UP,DOWN,LEFT,RIGHT};
int* calc_next_position(int row, int col, enum move m,int len_of_matrix) {
	int* pos = malloc(sizeof(int) * 2);
	printf("%d\n", m);
	switch (m) {
		case UP:
			row = (row - 1 + len_of_matrix ) % len_of_matrix;
			break;
		case DOWN:
			row = (row + 1) % (len_of_matrix);
			break;
		case LEFT:
			col = (col - 1 + len_of_matrix) % len_of_matrix;
			break;
		case RIGHT:
			col = (col + 1) % len_of_matrix;
			break;
	}
	pos[0] = row;
	pos[1] = col;
	return pos;
}
int check_distinct(int* arr, int len) {
	int i, r;
	for (i = 0; i < len - 1; i++)
		for (r = i + 1; r < len; r++)
			if (arr[i] == arr[r])
				return 0;
	return 1;
}
void update_matrix_player(node* player, char** matrix) {
	while (player) {
		matrix[player->row][player->col] = player->head_tail;
		player = player->next;
	}
}
void update_matrix(node* player1, node* player2,char **mat,int len) {
	int i, r;
	for (i = 0; i < len; i++)
		for (r = 0; r < len; r++)
			if (mat[i][r]!='F'&&mat[i][r]!='X'&&mat[i][r]!=' ')
				mat[i][r] = ' ';
	update_matrix_player(player1, mat);
	update_matrix_player(player2, mat);
}
void print_roof_down_matrix(int len){
	int i;
	for (i = 0; i < len + 2; i++)
		putchar('#');
	putchar('\n');
}
void print_matrix(char** matrix,int len) {
	int i, r;
	print_roof_down_matrix(len);
	for (i = 0; i < len; i++) {
		putchar('#');
		for (r=0;r<len;r++)
			putchar(matrix[i][r]);
		printf("#\n");
	}
	print_roof_down_matrix(len);
}
void print_enter_player_msg(int player) {
	printf("Please enter theese properties of player %d:\n", player);
	puts("<Head shape> <Body shape>");
	puts("<Up button> <Down button> <Left button> <Right button>");
}
void print_wrong_keys_msg(int player) {
	printf("The properties entered for player %d are not distinct!\n", player);
}
void input_propertise_player(int player,int *arr) {
	int index = 3 + player * 6;
	print_enter_player_msg(player);
	scanf("%c %c", &arr[index], &arr[index + 1]);
	getchar();
	scanf("%c %c %c %c", &arr[index + 2], &arr[index + 3], &arr[index + 4], &arr[index + 5]);
	getchar();
	while (check_distinct(arr, index + 6) == 0) {
		print_wrong_keys_msg(player);
		scanf("%c %c", &arr[index], &arr[index + 1]);
		getchar();
		scanf("%c %c %c %c", &arr[index + 2], &arr[index + 3], &arr[index + 4], &arr[index + 5]);
		getchar();
	}
}
void input_properties(int* arr) {
	input_propertise_player(0,arr);
	input_propertise_player(1,arr);
}
int check_collusion(node* player1, node* player2) {
	node* head = player1;
	while (player1 = player1->next)
		if (head->col == player1->col && head->row == player1->row)
			return 1;
	while (player2) {
		if (head->col == player2->col && head->row == player2->row)
			return 1;
		player2 = player2->next;
	}
	return 0;
}
void exit_game_with_error() {
	//to implements
}
void print_lost(char loser, char winner){
	puts("%c head lost to %c head", loser, winner);//implements the right
}
void print_game_on_msg() {
	puts("GAME ON!!!!");
}
void print_game_over_msg() {
	puts("GAME OVER!!!!");//implements the right
}
void print_winner(char winner) {
	printf("%c head winner!", winner);//implements the right
}
void print_tie_msg() {
	puts("TIE");//implements the right
}
void print_border_row(int size) {
	//to implements
}
void print_enter_size_msg() {
	puts("Please enter size:");
}
void print_wrong_size_msg() {
	//to implements
}
void print_wrong_coordinates_msg() {
	puts("These coordinates are not valid!");
}
void print_enter_food_msg() {
	puts("Please enter coordinates for food:");
}
void print_enter_boost_msg() {
	puts("Please enter coordinates for boost:");
}
void print_ask_move_msg(char head) {
	printf("%c head! whats your move?\n",head);
}
void print_wrong_move_msg() {
	printf("Wrong move!");
}
int check_valid_move(int* arr, int p, char ch) {
	int i;
	for (i = p; i < p + 4; i++)
		if (ch == (char)arr[i])
			return 1;
	return 0;
}
int* player_move(node* player,int p,int *arr,int len) {
	char ch,i;
	while(1){
		print_ask_move_msg(player->head_tail);
		scanf("%c", &ch);
		getchar();
		if (check_valid_move(arr, 5+p*6, ch))
			break;
		else
			print_wrong_move_msg();
	}
	for (i = 5 + p * 6; i < 5 + p * 6 + 4 && ((char)arr[i]) != ch; i++);
	return calc_next_position(player->row, player->col, i - 5 - p * 6, len);
}
int check_if_need_cal_judge(char** mat, int len_matrix) {
	int i, r, sum=0,count=0;
	for(i=0;i<len_matrix;i++)
		for (r = 0; r < len_matrix; r++) {
			if (mat[i][r] == 'F')
				sum += 1;
			if (mat[i][r] == 'X')
				sum += 2;
			if (mat[i][r] == ' ')
				count++;
		}
	if (count < 4 && sum == 1)
		sum = 3;
	if (sum == 0 && count > 0)
		sum = 2;
	return sum;
}
void judge_move(char **mat,int len_matrix,char f_or_x) {
	int row, col;
	while (1) {
		scanf("%d %d", &row, &col);
		getchar();
		if (row<len_matrix&&col<len_matrix&&col>=0&&row>=0&&mat[row][col] == ' ')
			break;
		print_wrong_coordinates_msg();
	}
	mat[row][col] = f_or_x;
}
void call_judge_if_need(char** mat, int len_matrix) {
	int sum = check_if_need_cal_judge(mat, len_matrix);
	switch (sum) {
		case 1:
			print_enter_boost_msg();
			judge_move(mat, len_matrix, 'X');
			print_matrix(mat, len_matrix);
			break;
		case 2:
			print_enter_food_msg();
			judge_move(mat, len_matrix, 'F');
			print_matrix(mat, len_matrix);
			break;
	}
}
int check_if_game_over(char** mat, int len_matrix) {
	int i, r;
	for (i = 0; i < len_matrix; i++)
		for (r = 0; r < len_matrix; r++)
			if (mat[i][r] == 'F' || mat[i][r] == ' ')
				return 0;
	return 1;
}
int player_move2(node **p,node* p2,char **mat,int *arr,int pp,int len) {
	while(1){
		int *pos = player_move(*p, pp,arr, len);
		char ch= mat[pos[0]][pos[1]];
		if (mat[pos[0]][pos[1]] == 'F')
			add(p, pos[0], pos[1], arr[4 + pp * 6]);
		else
			add_and_remove_last(p, pos[0], pos[1], arr[4 + pp * 6]);
		if (check_collusion(*p,p2))
			return 0;//lose
		update_matrix(*p,p2,mat,len);
		print_matrix(mat, len);
		if (check_if_game_over(mat, len))
			return 2;
		call_judge_if_need(mat, len);
		if (ch != 'X')
			break;
	}
	return 1;
}
int input_size() {
	int size;
	while (1) {
		print_enter_size_msg();
		scanf("%d", &size);
		getchar();
		if (size >= 3  && size <= 15)
			break;
		print_wrong_size_msg();
	}
	return size;
}
int check_longer(node* p, node* p2) {
	while (p && p2) {
		p = p->next;
		p2 = p2->next;
	}
	if (p)
		return 1;
	if (p2)
		return 2;
	return 3;
}
void end_game(int result,node *p,node *p2) {
	int longer = check_longer(p, p2);
	switch (result) {
		case 0:
			print_lost(p->head_tail, p2->head_tail);
			print_game_over_msg();
			exit(0);
			break;
		case 2:
			switch (longer) {
				case 1:
					print_winner(p->head_tail);
					break;
				case 2:
					print_winner(p2->head_tail);
					break;
				case 3:
					print_tie_msg();
					break;
			}
			print_game_over_msg();
			exit(0);
			break;
	}
}
char** init_matrix(int size) {
	char** p = malloc(sizeof(char*) * size);
	int i,r;
	for (i = 0; i < size; i++) {
		p[i] = malloc(sizeof(char) * size);
		for (r = 0; r < size; r++)
			p[i][r] = ' ';
	}
	return p;
}

void game1(node** p, node** p2, char** mat, int* arr, int len) {
	int result;
	judge_move(mat, len, 'F');
	print_matrix(mat, len);
	print_enter_boost_msg();
	judge_move(mat, len, 'X');
	print_matrix(mat, len);
	print_game_on_msg();
	print_matrix(mat, len);
	while (1) {
		result = player_move2(p, *p2, mat, arr, 0, len);
		end_game(result, *p, *p2);
		result = player_move2(p2, *p, mat, arr, 1, len);
		end_game(result, *p, *p2);
	}
}
void game2() {
	node* p = NULL, * p2 = NULL;
	char** mat;
	int* arr = malloc(sizeof(int) * 15), size;
	arr[0] = '#';
	arr[1] = 'F';
	arr[2] = 'X';
	input_properties(arr);
	size = input_size();
	add(&p, 0, 0, arr[3]);
	add(&p2, size - 1, size - 1, arr[9]);
	mat = init_matrix(size);
	update_matrix(p, p2, mat,size);
	print_matrix(mat, size);
	print_enter_food_msg();
	game1(&p, &p2, mat, arr, size);
}
int main() {
	game2();
	return 0;
}