#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#define initialX 20
#define initialY 19

void update();
void treasure(int, int, char*);
void player(int, int, char*);
void frame(int, int, int, int);
void enemy(int, int);
void enemyGhost(int, int);
int moveEnemy(int, int);
int enemyDirection(int, int, int);


struct enemyVectors{
	int x;
	int y;
	int speed;
};

int main(){

	clrscr(); // clears the screen
	textcolor(GREEN); // text color
	nocursor(); // makes the cursor invisible
	int frameSize[2] = {41, 20}; // play area size

	int lives = 3;
	int level = 1;


	//player
	int y = 19;
	int x = 20;
	int key = 0;
	char* hearts[3] = {"♥","♥","♥"};


	// enemies
	struct enemyVectors enemy1;
	struct enemyVectors enemy2;
	struct enemyVectors enemy3;
	struct enemyVectors enemy4;
	struct enemyVectors ghost;
	enemy1.x = 2;
	enemy1.y = 17;
	enemy2.x = 39;
	enemy2.y = 6;
	enemy3.x = 30;
	enemy3.y = 12;
	enemy4.x = 2;
	enemy4.y = 6;
	ghost.x = 6;
	ghost.y = 12;
	enemy1.speed = 2;
	enemy2.speed = 2;
	enemy3.speed = 3;
	enemy4.speed = 6;
	ghost.speed = 8;


	int running = 1;
	while(running){
		// events and keypress 67  68 for x++ and x--
		while (kbhit()) {
			key = getch();
			switch (key) {
				case 65: y--; break;
				case 66: y++; break;
				case 113: running = 0; break;
				case 81: running = 0; break;
			}
		}

		// @@@ ENEMY MOVEMENT @@@
		enemy1.x = moveEnemy(enemy1.x, enemy1.speed);
		enemy2.x = moveEnemy(enemy2.x, enemy2.speed);
		enemy3.x = moveEnemy(enemy3.x, enemy3.speed);
		enemy4.x = moveEnemy(enemy4.x, enemy4.speed);
		ghost.x = moveEnemy(ghost.x, ghost.speed);

		// changes direction of the enemies
		enemy1.speed = enemyDirection(enemy1.x, frameSize[0] - 2, enemy1.speed);
		enemy2.speed = enemyDirection(enemy2.x, frameSize[0] - 2, enemy2.speed);
		enemy3.speed = enemyDirection(enemy3.x, frameSize[0] - 2, enemy3.speed);
		enemy4.speed = enemyDirection(enemy4.x, frameSize[0] - 4, enemy4.speed);
		ghost.speed = enemyDirection(ghost.x, frameSize[0] - 4, ghost.speed);


		// @@@ COLLITION DETECTION @@@
		// prevents the player from going out of bounds
		if(y > 19) y = 19;

		//what happens if enemies colides with the player
		if(enemy1.y == y){
			if (enemy1.x == x) {
				y = initialY;
				lives--;
			}
		}
		if(enemy2.y == y){
			if (enemy2.x > 18 && enemy2.x < 22) {
				y = initialY;
				lives--;
			}
		}
		if(enemy3.y == y){
			if (enemy3.x > 18 && enemy3.x < 22) {
				y = initialY;
				lives--;
			}
		}
		if(enemy4.y == y){
			if (enemy4.x > 18 && enemy4.x < 22) {
				y = initialY;
				lives--;
			}
		}

		// game over and beating the level conditions
		if (lives < 1) running = 0;
		if (level > 3) running = 0;

		// prevents ouyt of bounds
		if (y  < 4){
			level++;
			y = initialY;
		}




		// @@@ RENDER @@@
		// title
		gotoxy(1,1);
		printf("     .:|     crossy in C \t |:.");

		// display lives
		gotoxy(2, 3);
		printf(" Lives");
		gotoxy(3,4);
		for (int i = 0; i < lives; i++) {
			printf("%s ",hearts[i]);
		}

		// display level
		gotoxy(30, 3);
		printf("Level: %i", level);

		// display treasure
		treasure(20,3,"▲");
		frame(1,2,frameSize[0],frameSize[1]);

		//draw the player
		player(x ,y ,"☺");

		//draw enemies acording to level chamnge
		if(level < 2 ){
			enemy(enemy1.x, enemy1.y);
			enemy(enemy2.x, enemy2.y);
		}
		else if (level < 3) {
			enemy(enemy1.x, enemy1.y);
			enemy(enemy2.x, enemy2.y);
			enemy(enemy3.x, enemy3.y);
		}
		else if(level < 4){
			enemy(enemy1.x, enemy1.y);
			enemy(enemy2.x, enemy2.y);
			enemy(enemy3.x, enemy3.y);
			enemy(enemy4.x, enemy4.y);
			enemyGhost(ghost.x, ghost.y);
		}

		//controls menu
		gotoxy(1, frameSize[1] + 2);
		printf("controls:");
		gotoxy(1, frameSize[1] + 3);
		printf("up arrow, down arrow, q - quits the game");

		//updates the screen
 		update();
	}

	// Last messaages after the loop ends
	if (lives < 1){
		gotoxy(1,1);
		printf("GAME OVER!");
	}
	if (level > 3) {
		gotoxy(1,1);
		printf("CONGRATS!, YOU WON!");
	}

	printf("\n");
	showcursor();
	return 0;
}

void update(){
	gotoxy(50,40); // resets the position of the cursor, allows the character to move
	system("sleep 0.07s"); // time deleay
	clrscr(); // clears the scereen
}

void treasure(int x, int y, char* c) {
	textcolor(YELLOW);
	gotoxy(x,y);
	printf("%s", c);
	textcolor(GREEN);
}

void player(int x, int y, char* c){
	textcolor(WHITE);
	gotoxy(x,y);
	printf("%s", c);
	textcolor(GREEN);
}

void frame(int x, int y, int w, int h){
	gotoxy(x,y);
	// left and right walls
	for (int i = 2; i < h; i++) {
		gotoxy(x, i);
		printf("║");
		gotoxy(w, i);
		printf("║");

		// // road
		textcolor(YELLOW);
		gotoxy(x + 17, i);
		printf("║");
		gotoxy(w - 19, i);
		printf("║");
		textcolor(GREEN);
	}
	// top and bottom
	for (int j = 2; j < w; j++) {
		gotoxy(j, y);
		printf("═");
		gotoxy(j, h);
		printf("═");
	}

	// corners
	gotoxy(x, y);
	printf("╔");
	gotoxy(w, y);
	printf("╗");
	gotoxy(x, h);
	printf("╚");
	gotoxy(w, h);
	printf("╝");
}

void enemy(int x, int y){
	textcolor(RED);
	gotoxy(x,y);
	printf("♦");
	textcolor(GREEN);
}

void enemyGhost(int x, int y){
	textcolor(MAGENTA);
	gotoxy(x,y);
	printf("☼");
	textcolor(GREEN);
}

int moveEnemy(int x, int speed){
	x += speed;
	return x;
}

int enemyDirection(int x, int edge, int speed){
	if(x >= edge) speed = -abs(speed);
	else if(x <= 2) speed = abs(speed);
	return speed;
}
