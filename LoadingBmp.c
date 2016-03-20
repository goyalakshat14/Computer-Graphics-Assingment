#include<stdio.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<stdlib.h>

void init2D(float r, float g, float b);
void display(void);

GLuint LoadTexture( const char * filename )
{

  GLuint texture;

  int width, height,i;

  unsigned char * data;

  FILE * file;

  file = fopen( filename, "rb" );

  if ( file == NULL ) return 0;
  width = 1024;
  height = 512;
  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );

 for(i = 0; i < width * height ; ++i)
{
   int index = i*3;
   unsigned char B,R;
   B = data[index];
   R = data[index+2];

   data[index] = R;
   data[index+2] = B;

}


glGenTextures( 1, &texture );
glBindTexture( GL_TEXTURE_2D, texture );
glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
free( data );
return texture;
}



void main(int argc, char *argv)
{
   GLuint texture;
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Point&lines");
  init2D(0.0,0.0,0.0);
  texture = LoadTexture("/home/akshat/program/Game(opengl)/Assets/lena512.bmp");
  glBindTexture (GL_TEXTURE_2D, texture);
  //glutDisplayFunc(display);
  //glutMainLoop();
}

void init2D(float r, float g, float b)
{
  glClearColor(r,g,b,0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0,200.0,0.0,250.0);
}

/*
void display(void)
{
  //sleep(100);
  int r;
  float i=0;
  for(r=1;r<100000;r++)
  { 
    i = i+.0005;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0); 
    glBegin(GL_LINES);
    
    glVertex2f(10*i,10*i);
    glVertex2f(10*i,20*i);

    glVertex2f(10*i,10*i);
    glVertex2f(20*i,10*i);
    
    glVertex2f(20*i,10*i);
    glVertex2f(20*i,20*i);
    
    glVertex2f(10*i,20*i);
    glVertex2f(20*i,20*i);
    
    glVertex2f(20*i,20*i);
    glVertex2f(15*i,30*i);

    glVertex2f(10*i,20*i);
    glVertex2f(15*i,30*i);

    printf("whee i am running %f\n",i);
    glEnd();
    glFlush();
    //sleep(1);
  }
}*/
