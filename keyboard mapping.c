#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <string.h>

void inits();
void init2D(float r, float g, float b);
void display(void);
void keyboard(unsigned char k,int x, int y);
void print(int x,int y,int z,char *);
void hit(int *);

float xc=0,yc=0,xc2=0,yc2=0; 
int hit11 = 0, hit12 =0, hlth2=0, won=0, i;

int resx = 1000, resy =1000;
typedef struct limb
{
  int x1,y1,x2,y2;
}limb;

typedef struct polygon{
  int x1,y1,x2,y2,x3,y3,x4,y4;
}polygon;

typedef struct bod{
  limb hnds1,hnds11,hnds2,hnds22,lgs1,lgs2,trunk; // hands and legs
  polygon hd1; //head and trunk 
}Body;

Body body,body2;

void main(int argc, char *argv)
{

   GLuint texture;
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(1000,1000);
  glutInitWindowPosition(200,200);
  glutCreateWindow("Point&lines");
  init2D(0.0,0.0,0.0);
  inits();
  //texture = LoadTexture("/home/akshat/program/Game(opengl)/Assets/lena512.bmp");
  //glBindTexture (GL_TEXTURE_2D, texture);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);   // call keyboard() when key is hit
  glutMainLoop();
}

void inits(){
  //initialising opponent 1
    body.hd1.x1 = 150;body.hd1.y1 = 750;
    body.hd1.x2 = 220;body.hd1.y2 = 750;
    body.hd1.x3 = 220;body.hd1.y3 = 670;
    body.hd1.x4 = 150;body.hd1.y4 = 670;

    body.trunk.x1 = 185;body.trunk.y1 = 670;
    body.trunk.x2 = 185;body.trunk.y2 = 550;

    body.hnds1.x1 = body.hnds2.x1 = 185;
    body.hnds1.y1 = body.hnds2.y1 = 640;

    body.hnds1.x2 = body.hnds11.x1 = 195;
    body.hnds1.y2 = body.hnds11.y1 = 580;
    body.hnds2.x2 = body.hnds22.x1 = 195;
    body.hnds2.y2 = body.hnds22.y1 = 580;

    body.hnds11.x2 = 210;body.hnds11.y2 = 630;
    body.hnds22.x2 = 210;body.hnds22.y2 = 630;

    body.lgs1.x1 = 185;body.lgs1.y1 = 550;
    body.lgs2.x1 = 185;body.lgs2.y1 = 550;

    body.lgs1.x2 = 175;body.lgs1.y2 = 500;
    body.lgs2.x2 = 195;body.lgs2.y2 = 500;


  // initialsing opponent 2
    body2.hd1.x1 = resx-150;body2.hd1.y1 = resy-750;
    body2.hd1.x2 = resx-220;body2.hd1.y2 = resy-750;
    body2.hd1.x3 = resx-220;body2.hd1.y3 = resy-670;
    body2.hd1.x4 = resx-150;body2.hd1.y4 = resy-670;

    body2.trunk.x1 = 185;body2.trunk.y1 = resy-670;
    body2.trunk.x2 = 185;body2.trunk.y2 = resy-550;

    body2.hnds1.x1 = body2.hnds2.x1 = resx-185;
    body2.hnds1.y1 = body2.hnds2.y1 = resx-640;

    body2.hnds1.x2 = body2.hnds11.x1 = resx-195;
    body2.hnds1.y2 = body2.hnds11.y1 = resy-580;
    body2.hnds2.x2 = body2.hnds22.x1 = resx-195;
    body2.hnds2.y2 = body2.hnds22.y1 = resy-580;

    body2.hnds11.x2 = resx-210;body2.hnds11.y2 = resy-630;
    body2.hnds22.x2 = resx-210;body2.hnds22.y2 = resy-630;

    body2.lgs1.x1 = resx-185;body2.lgs1.y1 = resy-550;
    body2.lgs2.x1 = resx-185;body2.lgs2.y1 = resy-550;

    body2.lgs1.x2 = resx-175;body2.lgs1.y2 = resy-500;
    body2.lgs2.x2 = resx-195;body2.lgs2.y2 = resy-500;
}
void init2D(float r, float g, float b)
{
  glClearColor(r,g,b,0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0,1000.0,0.0,1000.0);
}

void display(void)
{
  //sleep(100);
  int r;     
      glClear(GL_COLOR_BUFFER_BIT);
      glColor3f(1.0,0.0,0.0); 
      
      //opponent 1
      glBegin(GL_QUADS);
        //head
          glVertex2f(body.hd1.x1+xc,body.hd1.y1+yc);
          glVertex2f(body.hd1.x2+xc,body.hd1.y2+yc);
          glVertex2f(body.hd1.x3+xc,body.hd1.y3+yc);
          glVertex2f(body.hd1.x4+xc,body.hd1.y4+yc);
        //printf("whee i am running ");
      glEnd();

      
      glBegin(GL_LINES);
        //hands
          glVertex2f(body.hnds1.x1+xc,body.hnds1.y1+yc);
          glVertex2f(body.hnds1.x2+xc,body.hnds1.y2+yc+(hit11*(body.hnds1.y1 - body.hnds1.y2)));

          glVertex2f(body.hnds11.x1+xc,body.hnds11.y1+yc+(hit11*(body.hnds1.y1 - body.hnds1.y2)));
          glVertex2f(body.hnds11.x2+xc+(hit11*40),body.hnds11.y2+yc+(hit11*(body.hnds1.y1 - body.hnds11.y2)));

          glVertex2f(body.hnds2.x1+xc,body.hnds2.y1+yc);
          glVertex2f(body.hnds2.x2+xc,body.hnds2.y2+yc+(hit12*(body.hnds2.y1 - body.hnds2.y2)));

          glVertex2f(body.hnds22.x1+xc,body.hnds22.y1+yc+(hit12*(body.hnds2.y1 - body.hnds2.y2)));
          glVertex2f(body.hnds22.x2+xc+(hit12*40),body.hnds22.y2+yc+(hit12*(body.hnds2.y1 - body.hnds22.y2)));
        //legs
          glVertex2f(body.lgs1.x1+xc,body.lgs1.y1+yc);
          glVertex2f(body.lgs1.x2+xc,body.lgs1.y2+yc);

          glVertex2f(body.lgs2.x1+xc,body.lgs2.y1+yc);
          glVertex2f(body.lgs2.x2+xc,body.lgs2.y2+yc);

        //trunk  
          glVertex2f(body.trunk.x1+xc,body.trunk.y1+yc);
          glVertex2f(body.trunk.x2+xc,body.trunk.y2+yc);

      glEnd();
      
      glColor3f(0.0,0.0,1.0);

      //opponent 2
      glBegin(GL_QUADS);
        //head
          glVertex2f(body2.hd1.x1+xc,body2.hd1.y1+yc);
          glVertex2f(body2.hd1.x2+xc,body2.hd1.y2+yc);
          glVertex2f(body2.hd1.x3+xc,body2.hd1.y3+yc);
          glVertex2f(body2.hd1.x4+xc,body2.hd1.y4+yc);
        printf("whee i am running ");
      glEnd();

      
      glBegin(GL_LINES);
        //hands
          glVertex2f(body2.hnds1.x1+xc2,body2.hnds1.y1+yc2);
          glVertex2f(body2.hnds1.x2+xc2,body2.hnds1.y2+yc2+(hit11*(body2.hnds1.y1 - body2.hnds1.y2)));

          glVertex2f(body2.hnds11.x1+xc2,body2.hnds11.y1+yc2+(hit11*(body2.hnds1.y1 - body.hnds1.y2)));
          glVertex2f(body2.hnds11.x2+xc2+(hit11*40),body2.hnds11.y2+yc2+(hit11*(body2.hnds1.y1 - body2.hnds11.y2)));

          glVertex2f(body2.hnds2.x1+xc2,body2.hnds2.y1+yc2);
          glVertex2f(body2.hnds2.x2+xc2,body2.hnds2.y2+yc2+(hit12*(body2.hnds2.y1 - body2.hnds2.y2)));

          glVertex2f(body2.hnds22.x1+xc2,body2.hnds22.y1+yc2+(hit12*(body2.hnds2.y1 - body2.hnds2.y2)));
          glVertex2f(body2.hnds22.x2+xc2+(hit12*40),body2.hnds22.y2+yc2+(hit12*(body2.hnds2.y1 - body2.hnds22.y2)));
        //legs
          glVertex2f(body2.lgs1.x1+xc2,body2.lgs1.y1+yc2);
          glVertex2f(body2.lgs1.x2+xc2,body2.lgs1.y2+yc2);

          glVertex2f(body2.lgs2.x1+xc2,body2.lgs2.y1+yc2);
          glVertex2f(body2.lgs2.x2+xc2,body2.lgs2.y2+yc2);

        //trunk  
          glVertex2f(body2.trunk.x1+xc2,body2.trunk.y1+yc2);
          glVertex2f(body2.trunk.x2+xc2,body2.trunk.y2+yc2);

      glEnd();
      
      
      glColor3f(0.0,1.0,0.0);      
      
      //health meter opponent 1
      glBegin(GL_LINE_LOOP);
      
        glVertex2f(150,40);
        glVertex2f(300,40);
        glVertex2f(300,20);
        glVertex2f(150,20);

      glEnd();
      
      glColor3f(0.0,1.0,1.0);
      glBegin(GL_QUADS);
        glVertex2f(150,40);
        glVertex2f(300,40);
        glVertex2f(300,20);
        glVertex2f(150,20);
      glEnd();      
      
      //health meter opponent 2
      glColor3f(0.0,1.0,0.0);
      glBegin(GL_LINE_LOOP);
      
        glVertex2f(850,40);
        glVertex2f(700,40);
        glVertex2f(700,20);
        glVertex2f(850,20);

      glEnd();

      glColor3f(0.0,1.0,1.0);
      glBegin(GL_QUADS);
        glVertex2f(850-hlth2,40);
        glVertex2f(700,40);
        glVertex2f(700,20);
        glVertex2f(850-hlth2,20);
      glEnd();

      if(won==1){
        print(500,500,0,"player 1 won");

      }
      if(won ==2){
        print(500,00,0,"player 2 won");
      }
      glFlush();
}

void keyboard(unsigned char k, int x ,int y){
  switch(k){
    case 'w':
        yc += 20;
        break;
    case 's':
        yc -= 20;
        break;
    case 'a' :
        xc -= 20;
        break;
    case 'd' :
        xc += 20;
        break;
    case 'q':
        hit(&hit11);
      break;
    case 'e' :
        hit(&hit12);
      break;
    default : printf("wrong input\n");
      break;
  }
  glutPostRedisplay(); 
}

void hit(int *hit){
  if(*hit){
          *hit = 0;
        }
        else{
          *hit =1;
          
          //checking for punches from opponent 1
          short int punch1 = (body.hnds11.x2+xc+(hit11*40) > 580 && body.hnds11.x2+xc+(hit11*40) < 620);
          short int punch2 = (body.hnds22.x2+xc+(hit12*40) > 580 && body.hnds22.x2+xc+(hit12*40) < 620);
          //printf("hands = %d punch1 = %d and punch2  =%d\n",body.hnds11.x2 , punch1 , punch2);
          if(punch1*hit11 || punch2*hit12){
            hlth2 += 10;
            //printf("it was a hit\n");
            if (hlth2==150)
            {
              won = 1;
              printf("opponent 1 won\n");
            }
            return;
          }

          //checking for punches from opponent 2
          punch1 = (body.hnds11.x2+xc+(hit11*40) > 580 && body.hnds11.x2+xc+(hit11*40) < 620);
          punch2 = (body.hnds22.x2+xc+(hit12*40) > 580 && body.hnds22.x2+xc+(hit12*40) < 620);
        }
}

void print(int x, int y,int z, char *string)
{
  //set the position of the text in the window using the x and y coordinates
  glRasterPos2f(x,y);
  //get the length of the string to display
  int len = (int) strlen(string);

  //loop to display character by character
  for (i = 0; i < len; i++)
  {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
  }
};