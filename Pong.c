#include <string>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>


using namespace std;

int main()
{

	start:


	bool quit = false;

	int level=0;


	int c=6;
	int d=5;


	int max_points;

	int ch;

	int life=3;

	int ai_life=3;

	int player_points=0;
	int ai_points=0;

	int player_direct=0;
	int x=0;
	int y=6;

	int rock_direct=0;
	int rock_x=14;
	int rock_y=5;

	int ai_direct=0;
	int ai_x=29;
	int ai_y=6;



	int clock_1=0;

	int clock_2=0;


	srand(time(NULL));
	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	timeout(75);  




	//initiate color function


	start_color();

	bkgd(COLOR_PAIR(1));

	//multiple color pairs to use

	init_pair(1, COLOR_WHITE, COLOR_BLACK);

	init_pair(2, COLOR_CYAN, COLOR_BLACK);

	init_pair(3, COLOR_BLUE, COLOR_CYAN);

	init_pair(4, COLOR_WHITE, COLOR_RED);

	init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);

	init_pair(6, COLOR_CYAN, COLOR_BLACK);

	init_pair(7, COLOR_RED, COLOR_BLACK);

	init_pair(8, COLOR_BLACK, COLOR_RED);


	while (!quit){



		ch = getch();


		switch (ch)
		{
			case KEY_UP: player_direct=1; break;
			case KEY_DOWN: player_direct=2; break;

			case 'q': quit = true;
			break;
			case '0': timeout(55555); break;
			case 'p': timeout(75);
			break;

		}

		//player hits rock

		if (rock_x<=x && rock_y==y)
		rock_direct=2;


		if (rock_x<=x && rock_y==y-1)
		rock_direct=3;

		if (rock_x<=x && rock_y==y+1)
		rock_direct=5;


		//a.i. hits rock...sometimes doesn't have time to hit rock:-)

		if (rock_x>=ai_x && rock_y==ai_y)
		rock_direct=1;


		if (rock_x>=ai_x && rock_y==ai_y-1)
		rock_direct=6;

		if (rock_x>=ai_x && rock_y==ai_y+1)
		rock_direct=8;



		clock_1++;


		if (clock_1==5){ rock_direct=1+rand()%2;
	}



erase();



switch (player_direct)
{

	case 1: y--; break;
	case 2: y++; break;
}

switch(ai_direct)
{
	case 1: ai_y--; break;
	case 2: ai_y++; break;
}




switch (rock_direct){

	case 1: rock_x--; break;
	case 2: rock_x++;  break;
	case 3: rock_x++; rock_y--; break;
	case 4: rock_x++; break;
	case 5: rock_x++; rock_y++; break;
	case 6: rock_x--; rock_y--; break;
	case 7: rock_x--; break;
	case 8: rock_x--; rock_y++; break;



}

//ai (computer) hits target...

if (rock_x>=18+rand()%10 && rock_y<=ai_y-1) ai_direct=1;

if (rock_x>=18+rand()%10 && rock_y>=ai_y+1) ai_direct=2;


if (ai_y<1) ai_y=1;

if (ai_y>10) ai_y=10;







if (rock_x<0) {
	rock_x=14;
	rock_y=3+rand()%5;
	rock_direct=0;
	ai_points++;
	clock_1=0;

}

if (rock_x>29) {
	rock_x=14;
	rock_y=3+rand()%5;
	player_points++;
	clock_1=0;
	rock_direct=0;

}





if ( rock_direct==1 || rock_direct==2 || rock_direct==4 || rock_direct==7) timeout(60);

if ( rock_direct==3 || rock_direct==5 || rock_direct==6 || rock_direct==8) timeout(100);


if (ch=='0') timeout(55555);


if (rock_y<0 && rock_direct==3) rock_direct=5;

if (rock_y>10 && rock_direct==5) rock_direct=3;

if (rock_y<0 && rock_direct==6) rock_direct=8;

if (rock_y>10 && rock_direct==8) rock_direct=6;




if (y<1) y=1;

if (y>10) y=10;

//start screen
if (level==0  ){


	attrset(COLOR_PAIR(8));
	mvprintw(0,0,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

	attrset(COLOR_PAIR(1));
	  mvprintw(2,12,"PONG");
	  mvprintw(5,9,"20-Point Game");
	  mvprintw(6,9,"50-Point Game");

	attrset(COLOR_PAIR(2));
	  mvprintw(d,c,"==[");

	attrset(COLOR_PAIR(8));
	mvprintw(11,0,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	clock_1=0;
}


if (level==0 && ch==' ') {
	d++;

}

if (level==0 && d>6 ) d=5;

if (level==0 && d==5 && ch==10) {
	level=1;
	max_points=20;



}


if (level==0 && d==6 && ch==10){
	level=1;
	max_points=50;
}


if (level==1){

	attrset(COLOR_PAIR(1));
	for (int a=1; a<12; a++){
		mvprintw(a,14,":");}

//player

	attrset(COLOR_PAIR(3));
	mvprintw(y,x,"0");
	mvprintw(y-1,x,"]");
	mvprintw(y+1,x,"]");

//rock

	attrset(COLOR_PAIR(5));
	mvprintw(rock_y,rock_x,"O");
	attrset(COLOR_PAIR(4));
	mvprintw(ai_y,ai_x,"#");
	mvprintw(ai_y-1,ai_x,"0");
	mvprintw(ai_y+1,ai_x,"0");

	attrset(COLOR_PAIR(6));
	mvprintw(0,1,"Player");
	mvprintw(0,8,"%i", player_points);

	attrset(COLOR_PAIR(7));
	mvprintw(0,20,"A.I.:");
	mvprintw(0,26,"%i", ai_points);


	attrset(COLOR_PAIR(1));
	mvprintw(0,14,"%i", max_points);

}


if (player_points==max_points || ai_points==max_points) quit=true;


}//while (!quit) bracket. Do not delete this bracket


//The area below here is for when quit=true, which stops the program.

timeout(-1);
//erase();// clears screen

if (player_points>=max_points) mvprintw(5, 9, "Player Won");

if (ai_points>=max_points) mvprintw(5, 9, "A.I. Won");




refresh();
getch();
endwin();

goto start;

}
