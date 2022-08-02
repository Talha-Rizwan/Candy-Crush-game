//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Centipede...
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include <iostream>
#include<fstream>//for file handling
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include<cstdlib>
#include<ctime>
using namespace std;

//making the player class to store all the required information of player for showing and loading the game again

//bool set=0;

//bool hs=0;

class player{

string name;
int highest;

public:
player(){


name='\0';
highest=0;
}

player(string n,int h){

name=n;
highest=h;

}


void set_name(string n){

name=n;
}

string get_name(){
return name;
}


void set_highest(int h){
highest=h;
}

int get_highest(){
return highest;
}


void change_highest();
};

//making pure abstract class of gems having common members and functions to be used in all gems

class shape{
string name;
int xcoor;
int ycoor;
int id;

public:
shape(){

name="\0";
xcoor=0;
ycoor=0;
id=0;

}

shape(string n,int x,int y,int d){

name=n;
xcoor=x;
ycoor=y;
id=d;
}


string get_name(){
return name;
}

void set_name(string n){
name=n;
}

void set_xcoor(int x){
xcoor=x;
}

int get_xcoor(){
return xcoor;
}

void set_ycoor(int y){
ycoor=y;
}

int get_ycoor(){
return ycoor;
}

void set_id(int d){
id=d;
}

int get_id(){
return id;
}


virtual void make(int x,int y)=0;



};


//making the child shape classes inherited by the parent shape class.


class squ_w: public shape{

public:



squ_w():shape(){
}


squ_w(string n,int x,int y,int d)	: shape( n, x, y, d){

}


virtual void make(int x, int y){

	DrawSquare( x , y ,40,colors[WHITE]); 



}

~squ_w(){

}
};




class squ_r: public shape{

public:

squ_r():shape(){
}


squ_r(string n,int x,int y,int d)	: shape( n, x, y, d){

}


virtual void make(int x, int y){

	DrawSquare( x , y ,40,colors[RED]); 


}


~squ_r(){

}
};



class squ_y: public shape{

public:

squ_y():shape(){
}


squ_y(string n,int x,int y,int d)	: shape( n, x, y, d){

}


virtual void make(int x, int y){

	DrawSquare( x , y ,40,colors[YELLOW]); 


}


~squ_y(){

}
};



class squ_o: public shape{

public:

squ_o():shape(){
}


squ_o(string n,int x,int y,int d)	: shape( n, x, y, d){

}


virtual void make(int x, int y){

	DrawSquare( x , y ,40,colors[ORANGE]); 


}


~squ_o(){

}
};


class squ_b: public shape{

public:

squ_b():shape(){
}


squ_b(string n,int x,int y,int d)	: shape( n, x, y, d){

}


virtual void make(int x, int y){

	DrawSquare( x , y ,40,colors[SKY_BLUE]); 


}


~squ_b(){
}
};


player p;

int arr[700][700];
void setter(){			//function to make randon shapes after destruction
srand(time(0));
for(int i=100;i<700;){

	for(int j=100;j<700;){
		if(arr[i][j]==0){
		arr[i][j]=rand()%5+1;
		}	
	j+=50;
	}	
i+=50;
}

}


int checker()	// function to check if any of the gems are destroying due to same color and returning score of that move
{
int sc=0;
while(true){
bool q=0;
for(int i=100;i<700;){

	for(int j=100;j<700;){
	
	if(i<600){

	if(arr[i][j]!=0 && arr[i][j]==arr[i+50][j] && arr[i][j]==arr[i+100][j])
	{
	arr[i][j]=0;
	arr[i+50][j]=0;
	arr[i+100][j]=0;
	q=1;
	sc++;
//	cout<<'\7';
//	cout<<'\a';
	}
	}
	if(j<600){
	
	if((arr[i][j]!=0 && arr[i][j]==arr[i][j+50] && arr[i][j]==arr[i][j+100]))
	{
	arr[i][j]=0;
	arr[i][j+50]=0;
	arr[i][j+100]=0;
	q=1;
	sc++;
//	cout<<'\7';
//	cout<<'\a';

	}
	}
	
	
	j+=50;
	}
i+=50;


}

setter();

if(q==0){
break;
}
}

return sc;
}


// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */

void GameDisplay()/**/{
	

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	

//declaring few veriables to be used in the game display

static int mega_sc=0;
	
bool menu;	
	
ifstream m;
m.open("menu.txt");

m>>menu;
m.close();	
	
		
bool help;	
	
ifstream h;
h.open("help.txt");

h>>help;
h.close();	
	




		
bool set;	
	
h.open("sett.txt");

h>>set;
h.close();	
	
bool hs;	
h.open("hhs.txt");
h>>hs;
h.close();	
	
bool pa;	
	
h.open("pause.txt");

h>>pa;
h.close();	
	
bool mode;	
	
h.open("mode.txt");

h>>mode;
h.close();		
			
bool start;	
	
h.open("start.txt");

h>>start;
h.close();		
	
		
int ti;	
	
h.open("time.txt");

h>>ti;
h.close();		
		
static int level=1;	
	
if(start==1){	
if(pa==0){
if (menu==0){

//static int ti=200;

string t=Num2Str(ti);
string str="time : ";
string st=str+t;


// making objects of different square classes

squ_w s1("white",1,1,1);
squ_r s2("red",2,2,2);	
squ_y s3("yellow",3,3,3);
squ_o s4("orange",4,4,4);
squ_b s5("blue",5,5,5);


static int q=0;
// randomly generating for the first time in the grid
if(q==0){
srand(time(0));

for(int i=0;i<700;)
{
	for(int j=0;j<700;)
	{
	arr[i][j]=rand()%5+1;	
	j+=50;
	}
i+=50;
}	
	
}
	
q++;	

static int score=0;
int sc;
sc=checker();

if(sc<20){
score=score+sc;
}


if(sc<20){
ti=ti+sc*2;
}


//condition for normal game mode
if(mode==0){

DrawString( 800, 400, "NORMAL Mode" , colors[MISTY_ROSE]);
DrawLine( 50 , 200 , 50 , (score*2)+200 , 80 , colors[ORANGE] );

if(score%2==0){
DrawLine( 50 , 200 , 50 , (score*2)+200 , 80 , colors[BLUE] );
}
else if(score%3==0){
DrawLine( 50 , 200 , 50 , (score*2)+200 , 80 , colors[WHITE] );

}


}

//condition for time trail mode
else if(mode==1){
DrawString( 800, 400, st , colors[MISTY_ROSE]);
DrawLine( 50 , 200 , 50 , ti+200 , 80 , colors[ORANGE] );

if(ti%2==0){
DrawLine( 50 , 200 , 50 , ti+200 , 80 , colors[RED] );
}

else if(ti%3==0){
DrawLine( 50 , 200 , 50 , ti+200 , 80 , colors[GREEN] );
}

}

DrawString(10,170, "food bar ",colors[YELLOW]);	

//displaying of different statements in bottom left corner of game time to time



if( q==1 || q==2 || q==3 ||q==4 || q==5 || q==6 || q==7 || q==8){
DrawString(40,60, "WELCOME !  ",colors[YELLOW]);
DrawString(20,20, "TO THE GAME OF MIND ",colors[WHITE]);
}


else if(ti%15==0){
DrawString(20,60, "HIT HINT.  ",colors[ORANGE]);
DrawString(20,20, "IF GOT CONFUSED !  ",colors[RED]);
}



else if(ti%10==0){
DrawString(30,50, "HUPPY UP !  ",colors[YELLOW]);
}



else if(ti%5==0 && ti!=5){
DrawString(20,50, "SWAP THE BOXES !  ",colors[WHITE]);
}

//displaying the important figures and points of game and increasing the game beauty	
	
	if(ti%5==0){
	DrawLine( 770 , 600 ,  950 , 600 , 20 , colors[ORANGE] );
	DrawLine( 770 , 680 ,  950 , 680 , 20 , colors[SKY_BLUE] );
	DrawLine( 770 , 590 ,  770 , 690 , 20 , colors[WHITE] );
	DrawLine( 950 , 590 ,  950 , 690 , 10 , colors[YELLOW] );
	DrawString(800,630, "candy crush ",colors[RED]);
	}
	
	else if(ti%4==0){
	DrawLine( 770 , 600 ,  950 , 600 , 20 , colors[SKY_BLUE] );
	DrawLine( 770 , 680 ,  950 , 680 , 20 , colors[WHITE] );
	DrawLine( 770 , 590 ,  770 , 690 , 20 , colors[YELLOW] );
	DrawLine( 950 , 590 ,  950 , 690 , 10 , colors[RED] );
	DrawString(800,630, "candy crush ",colors[ORANGE]);
	}
	
	else if(ti%3==0){
	DrawLine( 770 , 600 ,  950 , 600 , 20 , colors[WHITE] );
	DrawLine( 770 , 680 ,  950 , 680 , 20 , colors[YELLOW] );
	DrawLine( 770 , 590 ,  770 , 690 , 20 , colors[RED] );
	DrawLine( 950 , 590 ,  950 , 690 , 10 , colors[ORANGE] );
	DrawString(800,630, "candy crush ",colors[SKY_BLUE]);
	}
	
	else if(ti%2==0){
	DrawLine( 770 , 600 ,  950 , 600 , 20 , colors[YELLOW] );
	DrawLine( 770 , 680 ,  950 , 680 , 20 , colors[RED] );
	DrawLine( 770 , 590 ,  770 , 690 , 20 , colors[ORANGE] );
	DrawLine( 950 , 590 ,  950 , 690 , 10 , colors[SKY_BLUE] );
	DrawString(800,630, "candy crush ",colors[WHITE]);
	}
	
	else if(ti%1==0){
	DrawLine( 770 , 600 ,  950 , 600 , 20 , colors[RED] );
	DrawLine( 770 , 680 ,  950 , 680 , 20 , colors[ORANGE] );
	DrawLine( 770 , 590 ,  770 , 690 , 20 , colors[SKY_BLUE] );
	DrawLine( 950 , 590 ,  950 , 690 , 10 , colors[WHITE] );
	DrawString(800,630, "candy crush ",colors[YELLOW]);	
	}
	
	string l=Num2Str(level);
	string lv="level : ";
	string lvl=lv+l;
	
	
	string sco=Num2Str(mega_sc);
	string ss="game score = ";
	string scor=ss+sco;
	


	string ll=" level score = ";
	string ssc=Num2Str(score);
	string ll_sc=ll+ssc;

	DrawRectangle( 750,0, 100, 50,colors[RED] );
	DrawRectangle( 600,0, 100, 50,colors[BLUE] );
	DrawRectangle( 450,0, 100, 50,colors[GREEN] );
		
	DrawString(800,500, lvl ,colors[MISTY_ROSE]);
	DrawString(800,300, ll_sc,colors[MISTY_ROSE]);
	DrawString(800,100, "name ",colors[MISTY_ROSE]);
	DrawString(800,200, scor ,colors[MISTY_ROSE]);
	DrawString(780,20, "hint ",colors[MISTY_ROSE]);
	DrawString(620,20, "menu ",colors[MISTY_ROSE]);
	DrawString(470,20, "pause ",colors[MISTY_ROSE]);

	
	if(ti%3==0){
	
	DrawRectangle( 750,0, 100, 50,colors[ORANGE] );
	DrawString(780,20, "hint ",colors[BLACK]);
	}
	
	
		
//calling functions of different classes and making random boxes on grid
	
	
for(int i=100;i<700; )
{	
	for(int j=100;j<700; )
	{
	
	
	
	if(arr[i][j]==1)
	{
	
	s1.make(i,j);
	}
	
	else if(arr[i][j]==2)
	{
	
	s2.make(i,j);
	
	}
	
	else if(arr[i][j]==3){
	
	s3.make(i,j);
	
	
	}
	
	else if(arr[i][j]==4){
	
	s4.make(i,j);
	
	
	}
	
	else if(arr[i][j]==5){
	
	s5.make(i,j);
	
	
	}
	else if(arr[i][j]==8)
	{
	DrawSquare( i , j ,50,colors[BLACK]);
	}
	
	else if(arr[i][j]==0)
	{
	DrawSquare( i , j ,50,colors[BLUE]);
	}
	
	j=j+50;
	}
i=i+50;	

}


//making grid

	/*	for(int j=100;j<=700;)
		{
		DrawLine( j, 100, j, 700, 3,  colors[BLUE]);
		j=j+50;
		}
		
		for(int j=100;j<=700;)
		{
		DrawLine( 100, j, 700, j, 3,  colors[BLUE]);
		j=j+50;
		}
	*/
checker();

// moving to the new level

static int bb=10000;

if(score>=50){
bb=ti;
mega_sc=mega_sc+score;
score=0;
level++;
DrawSquare( 0 , 0 ,700,colors[BLACK]); 
DrawString( 300, 500, "LEVEL COMPLETED !" , colors[MISTY_ROSE]);
DrawString( 300, 400, "taking to you next level" , colors[MISTY_ROSE]);
}

if( ti==bb || ti==bb-1 || ti==bb-2 || ti==bb-3  ){
DrawSquare( 0 , 0 ,700,colors[BLACK]); 
DrawString( 300, 500, "LEVEL COMPLETED !" , colors[MISTY_ROSE]);
DrawString( 100, 400, "taking you to next level" , colors[MISTY_ROSE]);
}


else if(ti==bb-4){
DrawSquare( 0 , 0 ,700,colors[BLACK]);
DrawString( 300, 500, "LEVEL COMPLETED !" , colors[MISTY_ROSE]);
DrawString( 300, 400, "taking you to next level" , colors[MISTY_ROSE]);

bb=10000;
}

if(ti<1 && mode==1){
DrawRectangle( 0,0, 1050, 700,colors[BLACK] );
DrawString( 300, 550, "GAME OVER  !" , colors[MISTY_ROSE]);
DrawString( 300, 480, " your score has been saved. " , colors[MISTY_ROSE]);
DrawString( 300, 400, "TRY AGAIN" , colors[YELLOW]);
DrawRectangle( 600,0, 100, 50,colors[BLUE] );
DrawString(620,20, "menu ",colors[MISTY_ROSE]);
}


ofstream v;
v.open("high.txt");
v<<mega_sc;
v.close();


}

else{

if(help==0 && set==0 && hs==0){
			//making the general menu			
DrawSquare( 170 , 0 ,700,colors[GREEN]); 
DrawRectangle( 500,400, 100, 50,colors[BLUE] );

DrawString( 500, 600, "MUNU" , colors[MISTY_ROSE]);

DrawLine( 480 , 580 ,  600 , 580 , 20 , colors[ORANGE] );
DrawLine( 480 , 640 ,  600 , 640 , 20 , colors[SKY_BLUE] );
DrawLine( 480 , 640 ,  480 , 580 , 20 , colors[WHITE] );
DrawLine( 600 , 640 ,  600 , 580 , 10 , colors[GOLD] );

DrawRectangle( 500,300, 100, 50,colors[BLACK] );
DrawRectangle( 500,0, 100, 50,colors[RED] );
DrawRectangle( 500,100, 170, 50,colors[YELLOW] );
DrawRectangle( 500,200, 170, 50,colors[BLUE] );


DrawString( 500, 420, "RESUME" , colors[MISTY_ROSE]);
DrawString( 500, 320, "HELP" , colors[MISTY_ROSE]);
DrawString( 500, 220, "HIGH SCORES" , colors[MISTY_ROSE]);
DrawString( 500, 120, "PLAYER PROF" , colors[MISTY_ROSE]);
DrawString( 500, 20, "EXIT" , colors[MISTY_ROSE]);


for(int i=0;i<700;i+=150){
if(ti%3==0){
DrawRoundRect(0,i,50,100,colors[WHITE],70);
DrawRoundRect(940,i,50,100,colors[WHITE],70);
}
else if(ti%2==0){
DrawRoundRect(0,i,50,100,colors[RED],70);
DrawRoundRect(940,i,50,100,colors[RED],70);
}
else{
DrawRoundRect(0,i,50,100,colors[GREEN],70);
DrawRoundRect(940,i,50,100,colors[GREEN],70);
}

}
ti++;
}

else if(help==1 && set==0 && hs==0){
			// showing the general instructions to play
DrawString( 500, 600, " HELP " , colors[BLUE]);

DrawLine( 480 , 580 ,  600 , 580 , 20 , colors[ORANGE] );
DrawLine( 480 , 640 ,  600 , 640 , 20 , colors[SKY_BLUE] );
DrawLine( 480 , 640 ,  480 , 580 , 20 , colors[WHITE] );
DrawLine( 600 , 640 ,  600 , 580 , 10 , colors[YELLOW] );

DrawString( 300, 550, "THIS GAME IS OF COMBINATIONS. " , colors[SKY_BLUE]);
DrawString( 50, 500, "Only wise moves can take you to next levels." , colors[YELLOW]);
DrawString( 400, 400, "HOW TO PLAY" , colors[RED]);
DrawString( 50, 350, "To move a box and swap it with other boxes,you need to click the mouse left botton and drag", colors[GREEN]);
DrawString( 50, 300, "it with any of the adjecent boxes in any of the 4 directions. Whenever you'ld be able to make" , colors[MISTY_ROSE]);
DrawString( 50, 250, "atleast three same color consecutive boxes, you'll get increement in your score. " , colors[BLUE]);
DrawString( 500, 150, "CONFUSED !" , colors[ORANGE]);
DrawString( 50, 100, "You can also hit the RED hint button or press 'h' if you get confused but with panelty" , colors[BROWN]);
DrawString( 200, 50, "Press the back button at bottom left corner to go back to main MENU" , colors[RED]);

DrawRectangle( 0,0, 100, 50,colors[BLUE] );
DrawString( 20, 20, "back" , colors[ORANGE]);

ti++;
}


else if(help==0 && set==1 && hs==0){
DrawString( 500, 600, "PLAYER PROFILE " , colors[BLUE]);

DrawLine( 480 , 580 ,  730 , 580 , 20 , colors[ORANGE] );
DrawLine( 480 , 640 ,  730 , 640 , 20 , colors[SKY_BLUE] );
DrawLine( 480 , 640 ,  480 , 580 , 20 , colors[WHITE] );
DrawLine( 730 , 640 ,  730 , 580 , 10 , colors[YELLOW] );

DrawString( 100, 500, "player's name :" , colors[ORANGE]);
DrawString( 130, 470, p.get_name() , colors[WHITE]);	//showing the name of player at screen

DrawString( 300, 350, "PAST SCORES" , colors[WHITE]);	//showing the name of player at screen






ifstream f;
	string s,t;
	
	f.open("highscore.txt");
	
	int i=250;
	while(!f.eof()){
	if(f.eof()==true)
	{break;}
	getline(f,s);
	if(s==p.get_name()){
		f>>t;
		
		DrawString( 350, i, t , colors[WHITE]);	//showing the name of player at screen
		i-=50;
		}
		
	}
	
f.close();






DrawRectangle( 0,0, 100, 50,colors[BLUE] );
DrawString( 20, 20, "back" , colors[ORANGE]);



}


else if(help==0 && set==0 && hs==1){
DrawString( 500, 600, "HIGHSCORES " , colors[BLUE]);

DrawLine( 480 , 580 ,  730 , 580 , 20 , colors[ORANGE] );
DrawLine( 480 , 640 ,  730 , 640 , 20 , colors[SKY_BLUE] );
DrawLine( 480 , 640 ,  480 , 580 , 20 , colors[WHITE] );
DrawLine( 730 , 640 ,  730 , 580 , 10 , colors[YELLOW] );


ifstream f;
	string s;
	
	f.open("highscore.txt");
	
	int i=350;
	while(!f.eof()){
	
	if(f.eof()==true){
	break;}
	
	getline(f,s);
			
	DrawString( 400, i, s , colors[WHITE]);	//showing the name of player at screen
		i-=50;
	}
	
f.close();

DrawRectangle( 0,0, 100, 50,colors[BLUE] );
DrawString( 20, 20, "back" , colors[ORANGE]);

}


}

}
else{
		//	giving option to pause the game
static int r=0;

DrawString( 300, 550, " GAME PAUSED !  " , colors[SKY_BLUE]);
DrawRectangle( 300,300, 250, 50,colors[WHITE] );
DrawString( 320, 320, " RESUME AGAIN" , colors[BLACK]);

for(int i=0;i<1050;i+=100){
if(r%3==0){
DrawRoundRect(i,0,50,100,colors[DARK_SEA_GREEN],70);
DrawRoundRect(i,600,50,100,colors[DARK_SEA_GREEN],70);
}
else if(r%2==0){
DrawRoundRect(i,0,50,100,colors[RED],70);
DrawRoundRect(i,600,50,100,colors[RED],70);
}

else{
DrawRoundRect(i,0,50,100,colors[SKY_BLUE],70);
DrawRoundRect(i,600,50,100,colors[SKY_BLUE],70);
}

}
r++;
ti++;
}

}

else {
//making the very starting of the game

DrawString( 120, 270, " YOUR NAME :" , colors[WHITE]);

if(ti%4==0){
DrawLine( 100 , 250 ,  350 , 250 , 20 , colors[YELLOW] );
DrawLine( 100 , 200 ,  350 , 200 , 20 , colors[ORANGE] );
DrawLine( 100 , 250 ,  100 , 200 , 20 , colors[SKY_BLUE] );
DrawLine( 350 , 250 ,  350 , 200 , 10 , colors[WHITE] );
}


else if(ti%3==0){
DrawLine( 100 , 250 ,  350 , 250 , 20 , colors[ORANGE] );
DrawLine( 100 , 200 ,  350 , 200 , 20 , colors[SKY_BLUE] );
DrawLine( 100 , 250 ,  100 , 200 , 20 , colors[WHITE] );
DrawLine( 350 , 250 ,  350 , 200 , 10 , colors[YELLOW] );
}

else if(ti%2==0){
DrawLine( 100 , 250 ,  350 , 250 , 20 , colors[SKY_BLUE] );
DrawLine( 100 , 200 ,  350 , 200 , 20 , colors[WHITE] );
DrawLine( 100 , 250 ,  100 , 200 , 20 , colors[YELLOW] );
DrawLine( 350 , 250 ,  350 , 200 , 10 , colors[ORANGE] );
}

else{
DrawLine( 100 , 250 ,  350 , 250 , 20 , colors[WHITE] );
DrawLine( 100 , 200 ,  350 , 200 , 20 , colors[YELLOW] );
DrawLine( 100 , 250 ,  100 , 200 , 20 , colors[ORANGE] );
DrawLine( 350 , 250 ,  350 , 200 , 10 , colors[SKY_BLUE] );
}


DrawString( 650, 350, " select a MODE to play :" , colors[RED]);

DrawRectangle( 650,250, 250, 50,colors[BLUE] );
DrawString( 670, 270, " NORMAL MODE  " , colors[WHITE]);
DrawString( 690, 230, " (amature)" , colors[WHITE]);

DrawRectangle( 650,150, 250, 50,colors[RED] );
DrawString( 670, 170, " TIME TRAIL" , colors[WHITE]);
DrawString( 690, 130, " (advance)" , colors[WHITE]);

for(int i=0;i<1050;i+=100){
if(ti%3==0){
DrawRoundRect(i,0,50,100,colors[WHITE],70);
DrawRoundRect(i,600,50,100,colors[GREEN],70);
}

else if(ti%2==0){
DrawRoundRect(i,0,50,100,colors[RED],70);
DrawRoundRect(i,600,50,100,colors[YELLOW],70);
}

else{
DrawRoundRect(i,0,50,100,colors[BLUE],70);
DrawRoundRect(i,600,50,100,colors[ORANGE],70);
}

}

DrawString( 120, 220, p.get_name() , colors[WHITE]);	//showing the name of player at screen

ti++;
}


ofstream a;
a.open("time.txt");
a<<ti;
a.close();

	glutSwapBuffers(); // do not modify this line..

}

 
 
 
 
 
 
		// a function to give the player just one hint by blinking the boxes to be moved 
void hint(){

for(int i=100;i<700;){
int s=0;
	for(int j=100;j<700;){
	
	if( j<600){
	if(i<650 && arr[i][j]==arr[i][j+50] && arr[i][j]==arr[i+50][j+100]){
	
	int temp=arr[i][j];
	arr[i][j]=8;
	arr[i][j+50]=8;
	arr[i+50][j+100]=8;
	
	
GameDisplay();
GameDisplay();
GameDisplay();
	
	arr[i][j]=temp;
	arr[i][j+50]=temp;
	arr[i+50][j+100]=temp;
	
	s=1;
	break;
	
	}
	


	else if(i>100 && arr[i][j]==arr[i][j+50] && arr[i][j]==arr[i-50][j+100]){
	
	
	int temp=arr[i][j];
	arr[i][j]=8;
	arr[i][j+50]=8;
	arr[i-50][j+100]=8;
	
	
GameDisplay();
GameDisplay();
GameDisplay();

	
	arr[i][j]=temp;
	arr[i][j+50]=temp;
	arr[i-50][j+100]=temp;
	
	s=1;
	break;
	
	
	}
	}
	

	if(i<600){
	if(j<650 && arr[i][j]==arr[i+50][j] && arr[i][j]==arr[i+100][j+50]){
	
	int temp=arr[i][j];
	arr[i][j]=8;
	arr[i+50][j]=8;
	arr[i+100][j+50]=8;
		
GameDisplay();
GameDisplay();
GameDisplay();

	
	arr[i][j]=temp;
	arr[i+50][j]=temp;
	arr[i+100][j+50]=temp;
	s=1;
	break;

	
	}
	
	
	else if(j>100 && arr[i][j]==arr[i+50][j] && arr[i][j]==arr[i+100][j-50]){
	
		
	int temp=arr[i][j];
	arr[i][j]=8;
	arr[i+50][j]=8;
	arr[i+100][j-50]=8;
		
GameDisplay();
GameDisplay();
GameDisplay();

	
	arr[i][j]=temp;
	arr[i+50][j]=temp;
	arr[i+100][j-50]=temp;
	
	s=1;
	break;
	
	}
	
	}
	
	j+=50;

	}


if(s==1){
break;
}	
	
i+=50;
}



}
 
 // no use of arrow keys due to most usage of mouse

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {



bool menu;
bool pau;

ifstream m;
m.open("menu.txt");
m>>menu;
m.close();

m.open("pause.txt");
m>>pau;
m.close();


	if (key == 27/* Escape key ASCII*/) {

	string sc;	
	ifstream v;
	v.open("high.txt",ios::in);
	v>>sc;
	v.close();
		
	ofstream z;		//saving the score to keep record
	z.open("highscore.txt",ios::app);
	
	z<<sc<<endl;
	z.close();	
		exit(1); // exit the program when escape key is pressed.
	}

	if ((key == 'h' || key == 'H') && menu==0 && pau==0) 	//except for clicking , user can also press the h key for hint
			{
		hint();
	}
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
 
 
void Timer(int m) {
GameDisplay();
	// implement your functionality here
static int rr=0;

static int t=200;	// a variable of time for game

if(rr!=0){

ifstream h;	

h.open("time.txt");
h>>t;
h.close();
}	
	
t--;	


ofstream a;
a.open("time.txt");
a<<t;
a.close();


rr++;
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);



}

 



 
int clikx(int x){	//to bring the random x-coordinate to a mod of 50

while(true){
if(x%50==0){
break;
}
x--;
}
return x;
}




int cliky(int y){	//to correct y's position and bring the random y-coordinate to a mod of 50

int z=700-y;
y=z;
while(true){
if(y%50==0){
break;
}
y--;
}

return y;

}


 
 
 
void MousePressedAndMoved(int x, int y) {// used when the user is dragging the mouse for swapping

int xx1;
int yy1;
ifstream p;
p.open("x.txt");
p>>xx1;
p.close();

ifstream q;
q.open("y.txt");
q>>yy1;
q.close();




bool menu;

ifstream m;
m.open("menu.txt");
m>>menu;
m.close();


bool he;
ifstream h;
h.open("help.txt");
h>>he;
h.close();




bool pu;

h.open("pause.txt");
h>>pu;
h.close();

bool start;

h.open("start.txt");
h>>start;
h.close();



if(x<701 && menu==0 && pu==0 && start==1 && he==0){

x=clikx(x);
y=cliky(y);

if(x-xx1>=50 && xx1!=0){
int temp;
temp=arr[xx1][yy1];
arr[xx1][yy1]=arr[x][y];
arr[x][y]=temp;


int aa=0;
			
ofstream a;
a.open("x.txt");
a<<aa;
a.close();

}

else if(xx1-x>=50 && xx1!=0){
int temp;
temp=arr[xx1][yy1];
arr[xx1][yy1]=arr[x][y];
arr[x][y]=temp;



int aa=0;
			
ofstream a;
a.open("x.txt");
a<<aa;
a.close();


}


else if(y-yy1>=50 && xx1!=0){

int temp;
temp=arr[xx1][yy1];
arr[xx1][yy1]=arr[x][y];
arr[x][y]=temp;



int aa=0;
			
ofstream a;
a.open("x.txt");
a<<aa;
a.close();


}



else if(yy1-y>=50 && xx1!=0){

int temp;
temp=arr[xx1][yy1];
arr[xx1][yy1]=arr[x][y];
arr[x][y]=temp;



int aa=0;
			
ofstream a;
a.open("x.txt");
a<<aa;
a.close();

}
}

	glutPostRedisplay();

}
void MouseMoved(int x, int y) {

	//cout << x << " " <<700- y << endl;
//	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // making of different options for player to click the left button on certain positions
			{
	
			int xx=clikx(x);
			int yy=cliky(y);
			
ofstream s;
s.open("x.txt");
s<<xx;
s.close();

ofstream t;
t.open("y.txt");
t<<yy;
t.close();



int men;
ifstream me;
me.open("menu.txt");
me>>men;
me.close();

int help;
ifstream h;
h.open("help.txt");
h>>help;
h.close();


bool set;

h.open("sett.txt");
h>>set;
h.close();


bool hs;

h.open("hhs.txt");
h>>hs;
h.close();

int pa;

h.open("pause.txt");
h>>pa;
h.close();


bool start;

h.open("start.txt");
h>>start;
h.close(   );


			if((xx==750 && yy==0) ||(xx==800 && yy==0)){
			hint();
			}
			
			if((xx==600 || xx==650) && yy==0 && men==0){
			
			ofstream m;
			m.open("menu.txt");
			m<<1;
			m.close();
			}
			
			if((xx==500 || xx==550) && yy==400 && men==1 && help==0 && set==0 && hs==0){
			
			ofstream m;
			m.open("menu.txt");
			m<<0;
			m.close();		
			}
			
			if((xx==500 || xx==550) && yy==300 && men==1 && set==0 && hs==0){
			ofstream he;
			he.open("help.txt");
			he<<1;
			he.close();
			}
			
			
			if((xx==0 || xx==50) && yy==0 && men==1 && set==0 && help==1 && hs==0){
			
			ofstream he;
			he.open("help.txt");
			he<<0;
			he.close();
			}
			
			if((xx==0 || xx==50) && yy==0 && men==1 && set==1 && help==0 && hs==0){
			
			ofstream he;
			he.open("sett.txt");
			he<<0;
			he.close();
			}
			
			if((xx==500 || xx==550) && yy==0 && men==1 && help==0 && set==0 && hs==0){
			
			string sc;		
	
	ifstream v;
	v.open("high.txt",ios::in);
	v>>sc;
	v.close();
		
	ofstream z;		//saving the score to keep record
	z.open("highscore.txt",ios::app);
	
	z<<sc<<endl;
	z.close();	
			
			exit(1);
			}
			
			if((xx==500 || xx==550 || xx==600) && yy==100 && men==1 && help==0 && set==0 && hs==0){
			ofstream he;
			he.open("sett.txt");
			he<<1;
			he.close();
			}
			
			
			if((xx==0 || xx==50) && yy==0 && men==1 && set==0 && help==0 && hs==1){
			
			ofstream he;
			he.open("hhs.txt");
			he<<0;
			he.close();
			}
			
			if((xx==500 || xx==550 || xx==600) && yy==200 && men==1 && help==0 && set==0 && hs==0){
			
			ofstream he;
			he.open("hhs.txt");
			he<<1;
			he.close();
		
			}
			
			
			if((xx==450 || xx==500 ) && yy==0 && men==0){	
			
			ofstream pp;
			pp.open("pause.txt");
			pp<<1;
			pp.close();
			}
			
			
			if((xx==300 || xx==350 || xx==400 || xx==450 || xx==500) && yy==300 && pa==1){		

			ofstream pp;
			pp.open("pause.txt");
			pp<<0;
			pp.close();				
			}
			
			if((xx==650 || xx==700 || xx==750 || xx==800 || xx==850) && yy==250 && start==0){
			
			ofstream r;
			r.open("mode.txt");
			r<<0;
			r.close();
			
			r.open("start.txt");
			r<<1;
			r.close();	

			ofstream m;
			m.open("menu.txt");
			m<<1;
			m.close();
						
			ofstream hel;
			hel.open("help.txt");
			hel<<0;
			hel.close();
			
			
			hel.open("sett.txt");
			hel<<0;
			hel.close();				
			
			
			hel.open("hhs.txt");
			hel<<0;
			hel.close();				
			
			}
			
			if((xx==650 || xx==700 || xx==750 || xx==800 || xx==850) && yy==150 && start==0){
			
			ofstream r;
			r.open("mode.txt");
			r<<1;
			r.close();			
			
			r.open("start.txt");
			r<<1;
			r.close();	
			
			ofstream m;
			m.open("menu.txt");
			m<<1;
			m.close();
			
			ofstream hel;
			hel.open("help.txt");
			hel<<0;
			hel.close();				
			
			hel.open("sett.txt");
			hel<<0;
			hel.close();				
			
			
			hel.open("hhs.txt");
			hel<<0;
			hel.close();				
			
			
			
			
			}
			
		//cout << GLUT_DOWN << " " << GLUT_UP << endl;
	
	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
	}
	glutPostRedisplay();
}

int main(int argc, char*argv[]) {


ofstream st;
st.open("start.txt");
st<<0;
st.close();



string name;

cout<<"please enter your full name to start the game :"<<endl;
getline(cin,name);		//taking name of player before the starting of game

p.set_name(name);

	ofstream z;		//saving the name to keep record
	z.open("highscore.txt", ios::app);
	
	z<<name<<endl;
	z.close();	




	int width = 1020, height = 700; // i have set my window size to be 1020 x 700

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Project"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...

	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
