#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<GL/glut.h>
#include <cmath>
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
using namespace std;



class Ball/*class to create coins and sticker*/
{
	public:
		float x;
		float y;
		float rad;
		float velx;
		float vely;
		float color;
		float mass;
		void drawball()//function to draw coins and sticker
		{
			glPushMatrix();
			glTranslatef(this->x,this->y, 0.0f);
			if(color==0)
				glColor3f(1.0f,0.85f,0.725f);
			else if(color==1)
				glColor3f(1.0f,0.0f,0.0f);
			else if(color==2)
				glColor3f(0.96f,0.87f,0.70f);
			else if(color==3)
				glColor3f(0.0f,0.0f,0.0f);
			glBegin(GL_TRIANGLE_FAN);
			for(int i=0 ; i<360 ; i++)
			{
				glVertex2f(this->rad * cos(DEG2RAD(i)), this->rad * sin(DEG2RAD(i)));
			}
			glEnd();
			glPopMatrix();

		}
};

/*declaring all global flags*/
Ball ball[10];
int take=0;
float hole_rad = 0.05f;
float rad1 = 0.025f;
float rad2 = rad1-0.004f;
float main_rad=0.25f;
float main_rad1=main_rad-0.004f;
float theta =90.0f; 
float vel=0.0;
float box_len = 1.4f;
int score=30;
int ord_hol[10];
int hc=0;
int cflgs[10][10]={0};
int arrowflag=0;
int release=0;
int take1=0;
int choosen = 2;
int hole[10];
float dis[10]={10};
int flag=0;
int finish=0;
int restart =0 ;
int check =0 ;

/*function to display characters on window*/
void renderBitmapString(
		float x,
		float y,
		float z,
		void *font,
		char *string) {

	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}


/*function to assign values to coins and carroms*/
void assign(int i,float x,float y,float rad,float vel_x,float vel_y, float color)
{
	ball[i].x=x;
	ball[i].y=y;
	ball[i].rad=rad;
	ball[i].velx=vel_x;
	ball[i].vely=vel_y;
	ball[i].color=color;
	ball[i].drawball();
}



/*function to check whether coin is at hole or not */
void checkhole()
{
	float z,x,y,x1,y1;
	int i;
	for(i=0;i<10;i++)
	{
		if(hole[i]==0)
		{
			x1=ball[i].x;
			y1=ball[i].y;

			if(x1>0 && y1 >0)
			{
				x=0.7f-hole_rad;
				y=0.7f-hole_rad;
				z = ((x-x1)*(x-x1))+((y-y1)*(y-y1))-((hole_rad*hole_rad));
				if(z<=0)
				{
					hole[i]=1;
					ball[i].velx=0;
					ball[i].vely=0;
				}
			}
			if(x1<0 && y1 >0)
			{
				x=-0.7f+hole_rad;
				y=0.7f-hole_rad;
				z = ((x-x1)*(x-x1))+((y-y1)*(y-y1))-((hole_rad*hole_rad));
				if(z<=0)
				{
					hole[i]=1;
					ball[i].velx=0;
					ball[i].vely=0;
				}
			}
			if(x1<0 && y1 <0)
			{
				x=-0.7f+hole_rad;
				y=-0.7f+hole_rad;
				z = ((x-x1)*(x-x1))+((y-y1)*(y-y1))-((hole_rad*hole_rad));
				if(z<=0)
				{
					hole[i]=1;
					ball[i].velx=0;
					ball[i].vely=0;
				}
			}
			if(x1>0 && y1 <0)
			{
				x=0.7f-hole_rad;
				y=-0.7f+hole_rad;
				z = ((x-x1)*(x-x1))+((y-y1)*(y-y1))-((hole_rad*hole_rad));
				if(z<=0)
				{
					hole[i]=1;
					ball[i].velx=0;
					ball[i].vely=0;
				}
			}
			if(hole[i]==1)//if hole is 1 updates the score according to coin
			{
				if(i==0)
					vel=0;
				if(i!=0)
				{
					ord_hol[hc]=i;
					hc++;
				}
				if(i==1)
					score =score+50;
				else if(i==0)
					score=score-1;
				else if((i==2 || i==3 ||i==4 ||i==5 )&& choosen ==2)
					score=score+5;
				else if((i==6 || i==7 ||i==8 ||i==9 ) && choosen ==2)
					score=score-5;
				else if((i==2 || i==3 ||i==4 ||i==5 )&& choosen ==1)
					score=score-5;
				else if((i==6 || i==7 ||i==8 ||i==9 )&& choosen ==1)
					score=score+5;
			}
		}
	}
}
//to add background color
void initRendering()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.75f,0.75f,0.75f,0.0f);
}
//to resize the window
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}







/* timer function to update score*/
void updatescore(int value)
{
	score -= 1;
	if(choosen==2)
	{
		if(hole[2]+hole[3]+hole[4]+hole[5]+hole[1]!=5)
			glutTimerFunc(1000,updatescore,0);
		else
			finish=1;	
	}
	if(choosen==1)
	{
		if(hole[6]+hole[7]+hole[8]+hole[9]+hole[1]!=5)
			glutTimerFunc(1000,updatescore,0);
		else
			finish=1;	
	}

}
void update(int value);
//function to check collision
void update1()
{
	int i,j;
	float x1,x2,y1,y2,r1,r2,co,si,u1,u2,v1,v2,m1,m2,u1x,u1y,u2x,u2y,dis;
	for(i=0;i<10;i++)
	{
		if(hole[i]==0)
		{
			for(j=i+1;j<10;j++)
			{
				if(hole[j]==0)
				{
					r1=ball[i].rad;
					r2=ball[j].rad;
					x1=ball[i].x;
					y1=ball[i].y;
					x2=ball[j].x;
					y2=ball[j].y;
					dis = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
					if(dis<=(r1+r2+0.001))
					{
						if(cflgs[i][j]==0 && cflgs[j][i]==0)
						{
							co=((x2-x1)/dis);
							si=((y2-y1)/dis);
							m1=ball[i].mass;
							m2=ball[j].mass;
							u1x=ball[i].velx;
							u1y=ball[i].vely;
							u2x=ball[j].velx;
							u2y=ball[j].vely;
							u1=(u1x*co)+(u1y*si);
							u2=(u2x*co)+(u2y*si);
							v1=(((m1-m2)*u1)+(2*m2*u2))/(m1+m2);
							v2=(((m1-m2)*u2)+(2*m1*u1))/(m1+m2);
							ball[i].vely=(u1y*co-u1x*si)*co+v1*si;
							ball[i].velx=-(u1y*co-u1x*si)*si+v1*co;
							ball[j].vely=(u2y*co-u2x*si)*co+v2*si;
							ball[j].velx=-(u2y*co-u2x*si)*si+v2*co;
							cflgs[i][j]=1;
							cflgs[j][i]=1;
						}
					}
					else
					{
						cflgs[i][j]=cflgs[j][i]=0;
					}


				}
			}
		}
	}

}

//function to check collision with wall
void update2()
{

	checkhole();
	int i;
	for(i=0;i<10;i++)
	{
		if(hole[i]==0)
		{
			if(ball[i].velx>0)
			{
				if(ball[i].x + ball[i].velx + ball[i].rad < 0.7)
				{
					ball[i].x += ball[i].velx;
				}
				else
				{
					ball[i].x = 0.7-ball[i].rad;
					ball[i].velx *= -0.90;
				}
			}
			else if(ball[i].velx<0)
			{
				if(ball[i].x+ball[i].velx-ball[i].rad>-0.7)
				{
					ball[i].x += ball[i].velx;
				}
				else
				{
					ball[i].x=-0.7+ball[i].rad;
					ball[i].velx *= -0.90;
				}
			}
			if(ball[i].vely>0)
			{
				if(ball[i].y + ball[i].vely + ball[i].rad < 0.7)
				{
					ball[i].y += ball[i].vely;
				}
				else
				{
					ball[i].y = 0.7-ball[i].rad;
					ball[i].vely *= -0.90;
				}
			}
			else if(ball[i].vely<0)
			{
				if(ball[i].y+ball[i].vely-ball[i].rad>-0.7)
				{
					ball[i].y += ball[i].vely;
				}
				else
				{
					ball[i].y=-0.7+ball[i].rad;
					ball[i].vely *= -0.90;
				}
			}



			checkhole();
			if((ball[i].velx*ball[i].velx)+(ball[i].vely*ball[i].vely)<0.000025)
			{
				ball[i].velx=0;
				ball[i].vely=0;
			}
			float temp=sqrt((ball[i].velx*ball[i].velx)+(ball[i].vely*ball[i].vely));
			if(temp!=0)
			{
				ball[i].velx -=fabs(0.0000001*ball[i].velx)/temp; 
				ball[i].vely -=fabs(0.0000001*ball[i].vely)/temp;
			}
		}
	}

}

/*timer function to call update1 and update2 function*/
void update(int value)
{
	update1();
	update2();
	glutTimerFunc(10,update,0);
}

/*function to draw circle*/
void drawBall(float rad) 
{
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++)
	{
		glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
	}
	glEnd();
}

/*function to check buttons pressed*/
void handleKeypress1(unsigned char key, int x, int y) {

	if (key == 27) {
		exit(0);     // escape key is pressed
	}
	else if(key == 32) // spacebar key
	{
		release=1;
		if(release==1)
		{
			ball[0].velx = vel * cos(DEG2RAD(theta));
			ball[0].vely = vel * sin(DEG2RAD(theta));
		}
		flag=1;
		check=1;
		arrowflag=1;
		glutTimerFunc(10, update, 0);

	}
	else if(key == 65 || key == 97) //a key
	{
		if(theta<180)
			theta += 1;

	}
	else if(key == 67 || key ==99)//c key
	{
		if(theta>0)
			theta -= 1;



	}
	else if(key== 66|| key == 98)
	{
		choosen=1;
	}
	else if(key==87 ||key== 119)
	{
		choosen=2;
	}
	else if(key == 114)
	{
		release=0;
		hole[0]=0;
		theta=90;
		finish=0;
		ball[0].x= 0.0f;
		ball[0].y= -0.5f+0.04f;
		ball[0].rad=0.04;
		restart=0;
		vel = 0;
		score=30;
		check=0;
		hc=0;
		arrowflag=0;
		release=0;
		take1=0;
		take=0;
		choosen = 2;
		int i ;

		for(i=0;i<10;i++)
		{
			ord_hol[i]=0;
			cout << "qq";
			hole[i]=0;
		}
		int j;
		for(i=0;i<10;i++)
			for(j=0;j<10;j++)
				cflgs[i][j]=10;
	}
}

int isDragging;
double ox,oy,oz;
void mouseMove(int x, int y)
{
	if (isDragging ==1) {

		GLint viewport[4];
		GLdouble modelview[16],projection[16];
		GLfloat wx=x,wy,wz;


		glGetIntegerv(GL_VIEWPORT,viewport);
		y=viewport[3]-y;
		wy=y;
		glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
		glGetDoublev(GL_PROJECTION_MATRIX,projection);
		glReadPixels(x,y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&wz);
		gluUnProject(wx,wy,wz,modelview,projection,viewport,&ox,&oy,&oz);

		oy*=2.5;
		ox*=2.5;


		if((ox>-0.5+0.04) && (ox<0.5-0.04))
			ball[0].x = ox;

	}
}



void mouseButton(int button, int state, int x, int y)
{
	float slope;
	GLint viewport[4];
	GLdouble modelview[16],projection[16];
	GLfloat wx=x,wy,wz;


	glGetIntegerv(GL_VIEWPORT,viewport);
	y=viewport[3]-y;
	wy=y;
	glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
	glGetDoublev(GL_PROJECTION_MATRIX,projection);
	glReadPixels(x,y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&wz);
	gluUnProject(wx,wy,wz,modelview,projection,viewport,&ox,&oy,&oz);

	oy*=2.5;
	ox*=2.5;

	if (button == GLUT_RIGHT_BUTTON) {

		if (state == GLUT_DOWN) { // left mouse button pressed

			float d=sqrt(pow((ball[0].x-ox),2)+pow((ball[0].y-oy),2));
			if(d < ball[0].rad)
				isDragging = 1; // start dragging
		}
		else  {
			isDragging = 0;
		}
	}
	if(button == GLUT_LEFT_BUTTON)
	{
		if(state==GLUT_DOWN)
		{
			if(oy<0.5 and oy >-0.5)
				vel = (oy+0.5)*0.05;
			else
			{
				if(oy>0.5)
				{
					vel=(0.5+0.5)*0.1;
				}
				else
					vel=0;
			}

			if(fabs(ox-ball[0].x)>0.00000000001f){

				slope=(oy-ball[0].y)/(ox-ball[0].x);
				if(slope>=0)
				{
					if(slope>0)
					{
						cout << "aa";
						theta = atan(slope)*180/PI;
					}
					else
					{
						if(ox-ball[0].x<0)
						{
							cout <<"bB";
							theta=180;
						}
						else
						{
							cout << "cc";
							theta=0;
						}
					}
				}
				else
				{
					theta =180 + atan(slope)*180/PI;

				}
			}

			else
			{
				if(oy-ball[0].y>0.000000000001)
					theta=90;
				else
					theta=180;
			}
			if(theta >180)
				theta=180;
			if(theta<0)
				theta=0;
		}
		if(state==GLUT_UP)
		{
			release=1;
			if(release==1)
			{
				ball[0].velx = vel * cos(DEG2RAD(theta));
				ball[0].vely = vel * sin(DEG2RAD(theta));
			}
			flag=1;
			check=1;
			arrowflag=1;
			glutTimerFunc(10, update, 0);
		}
	}

}


//function to check button pressed
void handleKeypress2(int key, int x, int y) {

	if (key == GLUT_KEY_LEFT)
		if(ball[0].x>=-0.5+0.05)
			ball[0].x -= 0.01;
	if (key == GLUT_KEY_RIGHT)
		if(ball[0].x<=0.5-0.05)
			ball[0].x += 0.01;
	if (key == GLUT_KEY_UP)
		if(vel<=0.05-0.005)
			vel += 0.005;
	if (key == GLUT_KEY_DOWN)
		if(vel>=0.005)
			vel -= 0.005;

}

//function to draw circle
void drawTriangle() {

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glEnd();
}

//function to draw lines
void drawlines()
{
	glBegin(GL_LINES);
	glColor3f(0.6f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.05f,0.0f,0.0f);
	glEnd();
}

//function to display board
void display()
{
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, win_width, 0.0, win_height);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glLoadIdentity();

	glPushMatrix();

	glTranslatef(0.0f,0.0f,-2.5f);

	//outer square
	glBegin(GL_QUADS);
	glColor3f(0.6f,0.29f,0.0f);
	glVertex3f(0.75,0.75f,0.0f);
	glVertex3f(-0.75f,0.75f,0.0f);
	glVertex3f(-0.75f,-0.75f,0.0f);
	glVertex3f(0.75f,-0.75f,0.0f);
	glEnd();

	//innersquare
	glBegin(GL_QUADS);
	glColor3f(1.0f,0.69f,0.4f);
	glVertex3f(0.7f,0.7f,0.0f);
	glVertex3f(-0.7f,0.7f,0.0f);
	glVertex3f(-0.7f,-0.7f,0.0f);
	glVertex3f(0.7f,-0.7f,0.0f);
	glEnd();

	//inner line1
	glBegin(GL_LINES);
	glColor3f(0.6f,0.0f,0.0f);
	glVertex3f(0.5f-rad1,0.5f,0.0f);
	glVertex3f(-0.5f+rad1,0.5f,0.0f);
	glEnd();

	//innerline2
	glBegin(GL_LINES);
	glColor3f(0.6f,0.0f,0.0f);
	glVertex3f(-0.5,-0.5f+rad1,0.0f);
	glVertex3f(-0.5f,0.5f-rad1,0.0f);
	glEnd();

	//innerline3
	glBegin(GL_LINES);
	glColor3f(0.6f,0.0f,0.0f);
	glVertex3f(0.5-rad1,-0.5f,0.0f);
	glVertex3f(-0.5f+rad1,-0.5f,0.0f);
	glEnd();

	//innerline4
	glBegin(GL_LINES);
	glColor3f(0.6f,0.0f,0.0f);
	glVertex3f(0.5,0.5f-rad1,0.0f);
	glVertex3f(0.5f,-0.5f+rad1,0.0f);
	glEnd();

	//triangle for hole circle1
	glBegin(GL_TRIANGLES);
	glColor3f(0.6f,0.29f,0.0f);
	glVertex3f(0.7f, 0.7f, 0.0f);
	glVertex3f(0.7f-hole_rad, 0.7f, 0.0f);
	glVertex3f(0.7f, 0.7f-hole_rad, 0.0f);
	glEnd();

	//holecircle1
	glPushMatrix();
	glTranslatef(0.7f-hole_rad,0.7f-hole_rad, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	drawBall(hole_rad);
	glPopMatrix();

	//triangle for hole circle2
	glBegin(GL_TRIANGLES);
	glColor3f(0.6f,0.29f,0.0f);
	glVertex3f(-0.7f, 0.7f, 0.0f);
	glVertex3f(-0.7f+hole_rad, 0.7f, 0.0f);
	glVertex3f(-0.7f, 0.7f-hole_rad, 0.0f);
	glEnd();

	//holecircle2
	glPushMatrix();
	glTranslatef(-0.7f+hole_rad,0.7f-hole_rad, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	drawBall(hole_rad);
	glPopMatrix();

	//triangle for hole circle3
	glBegin(GL_TRIANGLES);
	glColor3f(0.6f,0.29f,0.0f);
	glVertex3f(-0.7f,-0.7f, 0.0f);
	glVertex3f(-0.7f+hole_rad, -0.7f, 0.0f);
	glVertex3f(-0.7f, -0.7f+hole_rad, 0.0f);
	glEnd();

	//holecircle3
	glPushMatrix();
	glTranslatef(-0.7f+hole_rad,-0.7f+hole_rad, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	drawBall(hole_rad);
	glPopMatrix();

	//triangle for hole circle4
	glBegin(GL_TRIANGLES);
	glColor3f(0.6f,0.29f,0.0f);
	glVertex3f(0.7f, -0.7f, 0.0f);
	glVertex3f(0.7f-hole_rad, -0.7f, 0.0f);
	glVertex3f(0.7f, -0.7f+hole_rad, 0.0f);
	glEnd();

	//holecircle4
	glPushMatrix();
	glTranslatef(0.7f-hole_rad,-0.7f+hole_rad, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	drawBall(hole_rad);
	glPopMatrix();


	//innercirle1
	glPushMatrix();
	glTranslatef(0.5f-rad1,0.5f-rad1, 0.0f);
	glColor3f(0.6f,0.0f,0.0f);
	drawBall(rad1);
	glPopMatrix();

	//innerinner1
	glPushMatrix();
	glTranslatef(0.5f-rad1,0.5f-rad1, 0.0f);
	glColor3f(1.0f,0.69f,0.4f);
	drawBall(rad2);
	glPopMatrix();

	//innercirle2
	glPushMatrix();
	glTranslatef(-0.5f+rad1,0.5f-rad1, 0.0f);
	glColor3f(0.6f,0.0f,0.0f);
	drawBall(rad1);
	glPopMatrix();

	//innerinner2
	glPushMatrix();
	glTranslatef(-0.5f+rad1,0.5f-rad1, 0.0f);
	glColor3f(1.0f,0.69f,0.4f);
	drawBall(rad2);
	glPopMatrix();

	//innercirle3
	glPushMatrix();
	glTranslatef(-0.5f+rad1,-0.5f+rad1, 0.0f);
	glColor3f(0.6f,0.0f,0.0f);
	drawBall(rad1);
	glPopMatrix();

	//innerinner3
	glPushMatrix();
	glTranslatef(-0.5f+rad1,-0.5f+rad1, 0.0f);
	glColor3f(1.0f,0.69f,0.4f);
	drawBall(rad2);
	glPopMatrix();

	//innercirle4
	glPushMatrix();
	glTranslatef(0.5f-rad1,-0.5f+rad1, 0.0f);
	glColor3f(0.6f,0.0f,0.0f);
	drawBall(rad1);
	glPopMatrix();

	//innerinner4
	glPushMatrix();
	glTranslatef(0.5f-rad1,-0.5f+rad1, 0.0f);
	glColor3f(1.0f,0.69f,0.4f);
	drawBall(rad2);
	glPopMatrix();


	//maininnercircle
	glPushMatrix();
	glTranslatef(0.0f,0.0, 0.0f);
	glColor3f(0.6f,0.0f,0.0f);
	drawBall(main_rad);
	glPopMatrix();

	//main inner innercircle
	glPushMatrix();
	glTranslatef(0.0f,0.0, 0.0f);
	glColor3f(1.0f,0.69f,0.4f);
	drawBall(main_rad1);
	glPopMatrix();

	//to display sticker and coins 
	int i;
	int check1=0;
	for( i=0;i<10;i++)
		if(ball[i].velx !=0|| ball[i].vely !=0)
		{
			check1=1;
			break;
		}

	if(check1==0 and take ==1 and take1==1 and release==1) 
	{
		hole[0]=0;
		take1=0;
		check=0;
		release=0;
	}

	if(take==0)
	{
		take=1;
		ball[0].x= 0.0f;;
		ball[0].y= -0.5f+0.04f;;
		ball[0].rad = 0.04f;
		ball[0].velx = vel * cos(DEG2RAD(theta));
		ball[0].vely = vel * sin(DEG2RAD(theta));
		int m=0;
		ball[0].mass=2;
		for (m=1;m<10;m++)
		{
			ball[m].velx=ball[m].vely=0;
			ball[m].rad=0.03f;
			ball[m].mass=1;
			if(m==1)
				ball[m].color=1;
			else if(m<=5)
				ball[m].color=2;
			else
				ball[m].color=3;
		}
		ball[1].x=0.0f;		 ball[1].y=0.0f;
		float rr=0.25-0.04;
		float ang=0;
		for(m=2;m<10;m++)
		{
			ball[m].x=rr*cos(DEG2RAD(ang));
			ball[m].y=rr*sin(DEG2RAD(ang));
			ang=ang+90;
			if(ang==360)
				ang=45;
		}
	}
	if(take1==0)
	{
		take1=1;
		theta=90;
		vel=0;
		ball[0].x= 0.0f;;
		ball[0].y= -0.5f+0.04;;
		ball[0].rad = 0.04f;
	}


	//to display all coins that are not in hole
	int mn=1;
	for(mn=1;mn<10;mn++)
		if(hole[mn]==0)
			assign(mn,ball[mn].x,ball[mn].y,ball[mn].rad,ball[mn].velx,ball[mn].vely,ball[mn].color);

	//to display sticker
	if(release == 0 and check==0)
	{ 
		assign(0,ball[0].x,ball[0].y,0.04,0,0,0);	

		//sticker triangle
		glPushMatrix();
		glColor3f(0.6f,0.0f,0.0f);
		glTranslatef(ball[0].x, ball[0].y, 0.0f);
		glRotatef(theta, 0.0f, 0.0f, 1.0f);
		glScalef(5, 5, 5);
		drawlines();
		glPopMatrix();
		//stickerarrow
		glPushMatrix();
		glTranslatef(ball[0].x, ball[0].y, 0.0f);
		glRotatef(theta, 0.0f, 0.0f, 1.0f);
		glScalef(0.02f, 0.02f, 0.02f);
		drawTriangle();
		glPopMatrix();

	}
	else if(hole[0]==0 and release==1)
	{
		assign(0,ball[0].x,ball[0].y,0.04,ball[0].velx,ball[0].vely,0);

	}


	//speedo meter frame
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_QUADS);
	glColor3f(0.0f,0.0f,0.0f);
	glVertex3f(0.9,-0.5f,0.0f);
	glVertex3f(1.0f,-0.5f,0.0f);
	glVertex3f(1.0f,0.5f-0.01,0.0f);
	glVertex3f(0.9f,0.5f-0.01,0.0f);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	//speedo meter 
	glBegin(GL_QUADS);
	glColor3f(0.6f,0.29f,0.0f);
	glVertex3f(0.9,-0.5f,0.0f);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(1.0f,-0.5f,0.0f);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(1.0f,20*vel-0.5,0.0f);
	glColor3f(1.0f,0.27f,0.0f);
	glVertex3f(0.9f,20*vel-0.5,0.0f);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	//coins pocked frame
	glBegin(GL_QUADS);
	glColor3f(0.0f,0.0f,0.6f);
	glVertex3f(1.25,-0.5f,0.0f);
	glVertex3f(1.35f,-0.5f,0.0f);
	glVertex3f(1.35f,0.5f,0.0f);
	glVertex3f(1.25f,0.5f,0.0f);
	glEnd();


	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	//to display coins pocked
	int z1=0;
	float z2=-0.5+0.05;
	for(z1=0;z1<10;z1++)
	{
		if(ord_hol[z1]!=0)
		{      

			glPushMatrix();
			glTranslatef(1.25+0.05,z2 , 0.0f);
			if(ball[ord_hol[z1]].color==1)
				glColor3f(1.0f,0.0f,0.0f);
			else if(ball[ord_hol[z1]].color==2)
				glColor3f(1.0f,1.0f,1.0f);
			else if(ball[ord_hol[z1]].color==3)
				glColor3f(0.0f,0.0f,0.0f);
			drawBall(0.04);
			glPopMatrix();
			z2=z2+0.1;
		}
	}



	char scbuf[100];
	glColor3f(0.0f,0.0f,0.0f);
	//to print game over and score
	if(choosen==1) // if black chosen
	{
		sprintf(scbuf,"%s","Your Coin Blacks ");
		renderBitmapString(-0.3,-0.85,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,scbuf);
		if(finish==1)
		{
			glBegin(GL_QUADS);
			glColor3f(1.0f,1.0f,1.0f);
			glVertex3f(0.75,0.75f,0.0f);
			glVertex3f(-0.75f,0.75f,0.0f);
			glVertex3f(-0.75f,-0.75f,0.0f);
			glVertex3f(0.75f,-0.75f,0.0f);
			glEnd();
			glColor3f(0.0f,0.0f,0.0f);
			sprintf(scbuf,"%s","Game Finished Your Score ");
			renderBitmapString(-0.4,0.0,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,scbuf);
			sprintf(scbuf,"%d",score);
			renderBitmapString(0.5,0.0,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,scbuf);
			sprintf(scbuf,"%s","To Restart Game Press R ");
			renderBitmapString(-0.4,-0.2,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,scbuf);
		}

	}
	if(choosen==2) // if white chosen
	{
		sprintf(scbuf,"%s","Your Coin Whites ");
		renderBitmapString(-0.3,-0.85,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,scbuf);
		if(finish==1)
		{
			glBegin(GL_QUADS);
			glColor3f(1.0f,1.0f,1.0f);
			glVertex3f(0.75,0.75f,0.0f);
			glVertex3f(-0.75f,0.75f,0.0f);
			glVertex3f(-0.75f,-0.75f,0.0f);
			glVertex3f(0.75f,-0.75f,0.0f);
			glEnd();
			glColor3f(0.0f,0.0f,0.0f);
			sprintf(scbuf,"%s","Game Finished Your Score ");
			renderBitmapString(-0.4,0.0,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,scbuf);
			sprintf(scbuf,"%d",score);
			renderBitmapString(0.5,0.0,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,scbuf);
			sprintf(scbuf,"%s","To Restart Game Press R ");
			renderBitmapString(-0.4,-0.2,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,scbuf);
		}

	}
	sprintf(scbuf,"%s","sticker");
	renderBitmapString(0.90,-0.65,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,scbuf);
	sprintf(scbuf,"%s","speed");
	renderBitmapString(0.90,-0.75,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,scbuf);

	//to print coins pocked
	sprintf(scbuf,"%s","coins");
	renderBitmapString(1.25,-0.65,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,scbuf);
	sprintf(scbuf,"%s","Pocked");
	renderBitmapString(1.25,-0.75,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,scbuf);
	//to print score	
	sprintf(scbuf,"%s","score : ");
	renderBitmapString(0.80,0.75,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,scbuf);
	//to print score
	sprintf(scbuf,"%d",score);
	renderBitmapString(1.0,0.75,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,scbuf);
	glPopMatrix();
	glutSwapBuffers();
}



int main(int argc,char **argv)
{
	glutInit( &argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	//glutInitWindowPosition(400,50);
	glutInitWindowSize(1500,750);
	glutCreateWindow("My Window");

	initRendering();


	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(handleResize);	
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	glutTimerFunc(10,update,0);
	glutTimerFunc(1000,updatescore,0);
	glutMainLoop();

}
