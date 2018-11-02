// $Id: memory.c,v 1.22 2001/12/18 10:52:39 andy Exp $
//blib!
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

//func prototypes

void displayboard(char *,WINDOW *); /* displays playing board */
void displaymenu(WINDOW *);         /* displays menu... */
void initsystemboard(char *);       /* inits board of symbols */
void initplayingboard(char *);      /* inits playing board */
void playgame(char *, char *, WINDOW *); /* play game function */
int  getnum(int, WINDOW *);         /* gets and checks input */
void checkmove(char *,int,int,int,int, WINDOW *); /* check if move is a match */
int  checkwon(char *);              /* check if game is over */
int  movenok(char *,int,int,WINDOW *); /* check if move is ok */

// main

int main()
{
	WINDOW *w;
	char menuchar, *systemboard, *playingboard; 
	int playing=1;

	playingboard = (char *) malloc (sizeof(char)*4*6);
	systemboard  = (char *) malloc (sizeof(char)*4*6);

	w = (WINDOW *) initscr(); /* ncurses stuff */
	cbreak(); /* so you don't have to press enter */
	displaymenu(w);

	while (playing) {
		scanf("%c", &menuchar);

		switch(menuchar) {

		case 'n':
			playgame(systemboard,playingboard,w);
			break;
		case 'h':
			break;
		case 'q':
			playing=0;
			break;
		}
	}
	return 1;
}

void playgame(char *systemboard, char *playingboard, WINDOW *w) {
	char z;
	int coorx,coory,coorx2,coory2,turn=1,moves=0;

	clear();


	initsystemboard(systemboard);
	initplayingboard(playingboard);

	wrefresh(w);

	while (turn) {
		displayboard(playingboard,w);

		mvprintw(10,10, "Enter column then row: ");
		mvprintw(0,40, "( , ) and ( , )");
		wrefresh(w);

		coorx=0; coory=0; coorx2=0; coory2=0;

		while (movenok(playingboard,coorx,coory,w)) {
		    	coorx=getnum(6,w);
			mvprintw(0,40, "(%d, ) and ( , )",coorx); wrefresh(w);
			coory=getnum(4,w);
			mvprintw(0,40, "(%d,%d) and ( , )",coorx,coory); wrefresh(w);
		}

		playingboard[(coory-1)*6+coorx-1]=systemboard[(coory-1)*6+coorx-1];
		displayboard(playingboard,w);

		while (movenok(playingboard,coorx2,coory2,w)) {
		    coorx2=getnum(6,w);
			mvprintw(0,40, "(%d,%d) and (%d, )",coorx,coory,coorx2); wrefresh(w);
			coory2=getnum(4,w);
			mvprintw(0,40, "(%d,%d) and (%d,%d)",coorx,coory,coorx2,coory2); wrefresh(w);
		}

		playingboard[(coory2-1)*6+coorx2-1]=systemboard[(coory2-1)*6+coorx2-1];
		displayboard(playingboard,w);

		moves++;
		mvprintw(2,40,"Moves: %d",moves);
		wrefresh;

		checkmove(playingboard,coorx,coory,coorx2,coory2,w);

		if (checkwon(playingboard)) {
			mvprintw(10,10,"You won!");
			mvprintw(12,0,"");
			wrefresh(w);
			exit(0);
		}
	}
}

void checkmove(char *array,int x, int y, int x2, int y2,WINDOW *w) {

        if (array[(y-1)*6+x-1] != array[(y2-1)*6+x2-1]) {
			// no match...bad luck.
			mvprintw(10,10,"No match, bad luck. Now press a key.");
			wrefresh(w);
			mvprintw(10,10,"                                    ");
			array[(y-1)*6+x-1] = array[(y2-1)*6+x2-1] = '*';
			cbreak(); scanf("%c",&x);

        } else {
			beep();
		}

}

int checkwon(char *array) {
	int i,j,won=1;

	for (i=0; i<4; i++) { 
		for (j=0; j<6; j++) {
			if (array[i*6+j]=='*') {won=0;}
		}
	}

	return won;
}

void displaymenu(WINDOW *w) {
	mvprintw(0,0,"Memory 1.0");
	mvprintw(2,0,"N\nH\nQ\n");
	mvprintw(2,1,"ew Game");
	mvprintw(3,1,"elp");
	mvprintw(4,1,"uit");
	wrefresh(w);
}

void displayboard(char *array,WINDOW *w) {
	int i,j;

	for (i=0; i<4; i++) { 
		for (j=0; j<6; j++) {
		//	if (array[i*6+j]=='*') attron(WA_DIM);
		//	if (array[i*6+j]!='*') attron(WA_STANDOUT);

			mvprintw(i, j*2, "%c", array[i*6+j]);

			//if (array[i*6+j]=='*') attroff(WA_DIM);
			//if (array[i*6+j]!='*') attroff(WA_STANDOUT);

		}
		mvprintw(i,j*2,"%d",i+1);
	}
	mvprintw(i,0,"1 2 3 4 5 6");

	wrefresh(w);

}

int getnum(int max, WINDOW *w) {
        //gets a number between one and value passed in
        int val=0;

        while (!val) {
			cbreak(); scanf("%c", &val);
			if (val>48 && val<(49+max)) {val-=48;}
			else { mvprintw(10,10,"Number must be between 1 and %d",max); val=0; }
            wrefresh(w);
			mvprintw(10,10,"                               ");
        }

		wrefresh(w);

		return val;
}

void initplayingboard(char *array) { // fill playingboard array with *s
	int i,j;

			for(i=0; i<4; i++)
			{	
				for(j=0; j<6; j++)
				{
					array[i*6+j] = '*';
				}
			}                                           
}

void initsystemboard(char *array) {
	int i,j,x,y,k=0;
	char z,symbolrange[]=("~#@$%&=?!:-+"); /* symbol stuff */

	srand(time(NULL)); // seed random number generator

	for (i=0; i<4; i++) {
		for (j=0; j<6; j++) {
			array[i*6+j] = symbolrange[k];
			k++; k = k > 11 ? 0 : k; 
		}
	}

	for (i=0; i<4; i++) {
		for (j=0; j<6; j++) {
			x=(int) ((float) 3.0*rand()/(RAND_MAX+1.0));
			y=(int) ((float) 5.0*rand()/(RAND_MAX+1.0));

			z=array[i*6+j];
			array[i*6+j] = array[x*6+y];
			array[x*6+y] = z;
		}
	}
}

int movenok(char *array,int x, int y, WINDOW *w) {
	if (x==0 || y==0) { return 1; }
	if (array[(y-1)*6+x-1]!='*') {
			mvprintw(10,0,"Cell already flipped or same coords twice. Press a key, then enter coords again");
			wrefresh(w);
			mvprintw(10,0,"                                                                               ");
			cbreak(); scanf("%c");
			return 1;
	}
	return 0;
}
