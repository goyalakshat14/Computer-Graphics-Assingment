#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void inits();
void init2D(float r, float g, float b);
void display(void);
void keyPressed(unsigned char k,int x, int y);
void print(int x,int y,int z,char *);
void hit(int *);
void updatecol1();
void updatecol2();
void update();
void keyRelease(unsigned char k,int x, int y);

float xc=0,yc=-250,xc2=0,yc2=-250;

time_t seconds;
int second;
int hit11 = 0, hit12 =0, hit21=0, hit22=0, hlth=0, hlth2=0, won=-3, i;
//bool* keyStates = new bool[256];


char opponent1[50],opponent2[50];
int op1,op2;

char keypressed;
//collision boundries of opponent 1
float oppo1ColsnBndryx1 = 0 ,oppo1ColsnBndryy1 = 0, oppo1ColsnBndryx2 = 0,oppo1ColsnBndryy2 = 0;

//collision boundries of opponent 2
float oppo2ColsnBndryx1 = 0 ,oppo2ColsnBndryy1 = 0, oppo2ColsnBndryx2 = 0,oppo2ColsnBndryy2 = 0;

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

int main(int argc, char *argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(1000,1000);
  glutInitWindowPosition(-1,-1);
  glutCreateWindow("Point&lines");
  init2D(0.0,0.0,0.0);
  inits();
  //texture = LoadTexture("/home/akshat/program/Game(opengl)/Assets/lena512.bmp");
  //glBindTexture (GL_TEXTURE_2D, texture);
  glutDisplayFunc(display);
  
  glutIdleFunc(update);
  glutKeyboardUpFunc(keyRelease);
  glutKeyboardFunc(keyPressed);   // call keyboard() when key is hit
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

    updatecol1();

  // initialsing opponent 2
    body2.hd1.x1 = resx-150;body2.hd1.y1 = 750;
    body2.hd1.x2 = resx-220;body2.hd1.y2 = 750;
    body2.hd1.x3 = resx-220;body2.hd1.y3 = 670;
    body2.hd1.x4 = resx-150;body2.hd1.y4 = 670;

    body2.trunk.x1 = resx-185;body2.trunk.y1 = 670;
    body2.trunk.x2 = resx-185;body2.trunk.y2 = 550;

    body2.hnds1.x1 = body2.hnds2.x1 = resx-185;
    body2.hnds1.y1 = body2.hnds2.y1 = 640;

    body2.hnds1.x2 = body2.hnds11.x1 = resx-195;
    body2.hnds1.y2 = body2.hnds11.y1 = 580;
    body2.hnds2.x2 = body2.hnds22.x1 = resx-195;
    body2.hnds2.y2 = body2.hnds22.y1 = 580;

    body2.hnds11.x2 = resx-210;body2.hnds11.y2 = 630;
    body2.hnds22.x2 = resx-210;body2.hnds22.y2 = 630;

    body2.lgs1.x1 = resx-185;body2.lgs1.y1 = 550;
    body2.lgs2.x1 = resx-185;body2.lgs2.y1 = 550;

    body2.lgs1.x2 = resx-175;body2.lgs1.y2 = 500;
    body2.lgs2.x2 = resx-195;body2.lgs2.y2 = 500;

    updatecol2();
}
void init2D(float r, float g, float b)
{
  glClearColor(r,g,b,0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0,1000.0,0.0,1000.0);
}

void update(){
    second = 90-time(NULL)+seconds;
    if(!second){
      if(hlth<hlth2){
        won=1;
      }
      else{
        won=2;
      }
    }
    //printf("%d %d\n", seconds);
    
    glutTimerFunc(600,glutPostRedisplay,0);
}

void display(void)
{   
    //keyOperation();

    glClear(GL_COLOR_BUFFER_BIT);
       
  
    if(won==-3){
      print(400,800,0,"enter name of opponent 1");
      print(400,750,0,opponent1);
    }
    else if(won==-2){
      print(400,800,0,"enter name of opponent 2");
      print(400,750,0,opponent2); 
    }
    else if(won==-1){
      glColor3f(0.0,1.0,0.0);
      print(430,800,0,"Instruction");
      glColor3f(0.0,0.5,1.0);
      print(100,750,0,"opponent 1 use w/a/s/d to move around");
      print(150,700,0,"opponent 1 use q/e to punch");
      print(500,750,0,"opponent 2 use 8/5/4/6 to move around");
      print(500,700,0,"opponent 2 use 7/9 to punch");
      glColor3f(1.0,0.5,0.5);
      print(380,650,0,"use ENTER to continue");
      print(415,600,0,"use ESC to exit");
    }
    else if(won==0){
      //clock
    char buffer[20];
    sprintf(buffer,"%d",second);
    print(480,800,0,buffer);
      //opponent 1
      glColor3f(1.0,0.0,0.0); 
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
          glVertex2f(body2.hd1.x1+xc2,body2.hd1.y1+yc2);
          glVertex2f(body2.hd1.x2+xc2,body2.hd1.y2+yc2);
          glVertex2f(body2.hd1.x3+xc2,body2.hd1.y3+yc2);
          glVertex2f(body2.hd1.x4+xc2,body2.hd1.y4+yc2);
       // printf("whee i am running ");
      glEnd();

      
      glBegin(GL_LINES);
        //hands
          glVertex2f(body2.hnds1.x1+xc2,body2.hnds1.y1+yc2);
          glVertex2f(body2.hnds1.x2+xc2,body2.hnds1.y2+yc2+(hit21*(body2.hnds1.y1 - body2.hnds1.y2)));

          glVertex2f(body2.hnds11.x1+xc2,body2.hnds11.y1+yc2+(hit21*(body2.hnds1.y1 - body.hnds1.y2)));
          glVertex2f(body2.hnds11.x2+xc2-(hit21*40),body2.hnds11.y2+yc2+(hit21*(body2.hnds1.y1 - body2.hnds11.y2)));

          glVertex2f(body2.hnds2.x1+xc2,body2.hnds2.y1+yc2);
          glVertex2f(body2.hnds2.x2+xc2,body2.hnds2.y2+yc2+(hit22*(body2.hnds2.y1 - body2.hnds2.y2)));

          glVertex2f(body2.hnds22.x1+xc2,body2.hnds22.y1+yc2+(hit22*(body2.hnds2.y1 - body2.hnds2.y2)));
          glVertex2f(body2.hnds22.x2+xc2-(hit22*40),body2.hnds22.y2+yc2+(hit22*(body2.hnds2.y1 - body2.hnds22.y2)));
        //legs
          glVertex2f(body2.lgs1.x1+xc2,body2.lgs1.y1+yc2);
          glVertex2f(body2.lgs1.x2+xc2,body2.lgs1.y2+yc2);

          glVertex2f(body2.lgs2.x1+xc2,body2.lgs2.y1+yc2);
          glVertex2f(body2.lgs2.x2+xc2,body2.lgs2.y2+yc2);

        //trunk  
          glVertex2f(body2.trunk.x1+xc2,body2.trunk.y1+yc2);
          glVertex2f(body2.trunk.x2+xc2,body2.trunk.y2+yc2);

      glEnd();
      //health meter opponent 1
        glColor3f(0.0,1.0,0.0);  
        
        //name of opponent 1
        print(100,765,0,opponent1);
        
        glBegin(GL_LINE_LOOP);
        
          glVertex2f(100,810);
          glVertex2f(300,810);
          glVertex2f(300,790);
          glVertex2f(100,790);

        glEnd();
        
        glColor3f(0.0,1.0,1.0);
        glBegin(GL_QUADS);
          glVertex2f(100+hlth,810);
          glVertex2f(300,810);
          glVertex2f(300,790);
          glVertex2f(100+hlth,790);
        glEnd();      
      
      
      //health meter opponent 2
        glColor3f(0.0,1.0,0.0);
        
        //name of opponent 2
        print(700,765,0,opponent2);
        glBegin(GL_LINE_LOOP);
        
          glVertex2f(900,810);
          glVertex2f(700,810);
          glVertex2f(700,790);
          glVertex2f(900,790);

        glEnd();

        glColor3f(0.0,1.0,1.0);
        glBegin(GL_QUADS);
          glVertex2f(900-hlth2,810);
          glVertex2f(700,810);
          glVertex2f(700,790);
          glVertex2f(900-hlth2,790);
        glEnd();
    }else{
    	glColor3f(1.0,1.0,0.0);
    	print(425,550,0,"And the Winner is");
      if(won==1){
        print(465,500,0,opponent1);

      }
      if(won ==2){
        print(450,500,0,opponent2);
      }
      print(430,450,0,"press ESC to quit");

    }
      glFlush();
}

void keyPressed(unsigned char k, int x ,int y){
  //keyStates[k] = true;
if(k==27){
  exit(0);
}

if(won==-3){
  switch(k){
    case 8:
      op1--;
      opponent1[op1]='\0';
      break;
    case 13:
      won++;
      break; 
    default:
      opponent1[op1]=k;
      op1++;
      break;

  }
}
else if(won==-2){
  switch(k){
    case 8:
      op2--;
      opponent2[op2]='\0';
      break;
    case 13:
      won++;
      break; 
    default:
      opponent2[op2]=k;
      op2++;
      break;

  }
}
else if(won==-1){
  if(k==13){
    seconds =time(NULL);
      won++;
      glClearColor(0,0,0,0);
    }
  }
else if(won==0){
  switch(k){
    //keyboard binding for opponent 1
      case 'w':
          yc += 20;
          updatecol1();
          break;
      case 's':
          yc -= 20;
          updatecol1();
          break;
      case 'a' :
          xc -= 20;
          updatecol1();
          break;
      case 'd' :
          xc += 20;
          updatecol1();
          break;
      case 'q':
      //beep();
          hit(&hit11);
          updatecol1();
        break;
      case 'e' :
      //beep();
          hit(&hit12);
          updatecol1();
        break;

    //keyboard binding for opponent 2
      case '8':
          yc2 += 20;
          updatecol2();
          break;
      case '5':
          yc2 -= 20;
          updatecol2();
          break;
      case '4' :
          xc2 -= 20;
          updatecol2();
          break;
      case '6' :
          xc2 += 20;
          updatecol2();
          break;
      case '7':
          hit(&hit21);
        break;
      case '9' :
          hit(&hit22);
        break;

    default : printf("wrong input\n");
      break;
  }
}
  glutPostRedisplay();
  
}

void keyRelease(unsigned char k,int x, int y){

if(won==0){
  switch(k){
    case 'q':
          hit(&hit11);
          updatecol1();
        break;
    case 'e' :
          hit(&hit12);
          updatecol1();
        break;

    case '7':
          hit(&hit21);
          updatecol2();
        break;
    case '9' :
          hit(&hit22);
          updatecol2();
        break;

    }
  glutPostRedisplay();
  }
}

void hit(int *hit){
  if(*hit){
     *hit = 0;
     glClearColor(0,0,0,0);
  }
  else{
    *hit =1;
    //checking for punches from opponent 1
    short int punch1 = (body.hnds11.x2+xc+(hit11*40) > oppo2ColsnBndryx2 && body.hnds11.x2+xc+(hit11*40) < oppo2ColsnBndryx1);
    short int punch2 = (body.hnds22.x2+xc+(hit12*40) > oppo2ColsnBndryx2 && body.hnds22.x2+xc+(hit12*40) < oppo2ColsnBndryx1);
    //printf("hands = %d punch1 = %d and punch2  =%d\n",body.hnds11.x2 , punch1 , punch2);
    if(punch1*hit11 || punch2*hit12){
      hlth2 += 10;
      glClearColor(0.53,0.027,0.027,0.2f);
      //printf("it was a hit\n");
      if (hlth2==200)
      {
        won = 1;
        printf("opponent 1 won\n");

          //return;
        }
      }

    //checking for punches from opponent 2
    punch1 = (body2.hnds11.x2+xc2-(hit21*40) > oppo1ColsnBndryx1 && body2.hnds11.x2+xc2-(hit21*40) < oppo1ColsnBndryx2);
    punch2 = (body2.hnds22.x2+xc2-(hit22*40) > oppo1ColsnBndryx1 && body2.hnds22.x2+xc2-(hit22*40) < oppo1ColsnBndryx2);
    printf("%f %f\n", body2.hnds11.x2+xc2+(hit21*40),oppo1ColsnBndryx2);
    if(punch1*hit21 || punch2*hit22){
      hlth += 10;
      glClearColor(0.53,0.027,0.027,0.2f);
      //printf("it was a hit\n");
      if (hlth==200)
      {
        won = 2;
        printf("opponent 2 won\n");
      }
      //return;
    }
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
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
  }
};

//update collision boundries of opponent 1
void updatecol1(){
  oppo1ColsnBndryx1 = body.hd1.x1+xc;
  oppo1ColsnBndryy1 = body.hd1.y1+yc;
  oppo1ColsnBndryx2 = body.hd1.x3+xc;
  oppo1ColsnBndryy2 = body.hd1.y3+xc;
}

//updates collision boundries of opponent 2
void updatecol2(){
  oppo2ColsnBndryx1 = body2.hd1.x1+xc2;
  oppo2ColsnBndryy1 = body2.hd1.y1+yc2;
  oppo2ColsnBndryx2 = body2.hd1.x3+xc2;
  oppo2ColsnBndryy2 = body2.hd1.y3+yc2;
}