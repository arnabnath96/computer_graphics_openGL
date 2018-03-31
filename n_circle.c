#include<GL/glut.h>
#include<math.h>

#define WIDTH 600
#define HEIGHT 600
#define PIXEL 10

int k=1;
int X[2],Y[2];
int temp =0;

void init()
{
 glClearColor (1.0f,1.0f,1.0f,0.0f);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0,WIDTH,0,HEIGHT); 
}

void setPixel(GLint x1,GLint y1)
{
 glColor3f(0.0f,0.0f,0.0f);
 glBegin(GL_POLYGON);
        glVertex2i(x1*10-10,round(y1)*10-10);
        glVertex2i(x1*10,round(y1)*10-10);
        glVertex2i(x1*10, round(y1)*10);
        glVertex2i(x1*10-10,round(y1)*10);
 glEnd();
}

void setCirclePixel(GLint x1,GLint y1, GLint x, GLint y)
{
 setPixel(x1+x,y1+y);
 setPixel(x1-x,y1+y);
 setPixel(x1+x,y1-y);
 setPixel(x1-x,y1-y);
 setPixel(x1+y,y1+x);
 setPixel(x1-y,y1+x);
 setPixel(x1+y,y1-x);
 setPixel(x1-y,y1-x);    
}

void drawCircle(int xc,int yc, int rad)
{
  int x=0;
  int y=rad;
  int p=1-rad;

  setCirclePixel(xc,yc,x,y);
  while(x<y)
  {
    x++;
    if(p<0)
      p+=2*x+1;
    else
    {
      y--;
      p+=2*(x-y)+1;
    }
    setCirclePixel(xc,yc,x,y);
  }
}


void mouseClick(int button, int state, int x, int y)
{
 switch(button)
 {
    case GLUT_LEFT_BUTTON:
     if (state == GLUT_DOWN)
     {   
      temp=temp%2;
      X[temp]=x/PIXEL+1;
      Y[temp]=HEIGHT/PIXEL-y/PIXEL;
      setPixel(X[0],Y[0]);
      temp++;
      if(temp%2==0)
      {
       float r=sqrt((X[0]-X[1])*(X[0]-X[1]) + (Y[0]-Y[1])*(Y[0]-Y[1]));
       drawCircle(X[0],Y[0],r);
       temp=0;
      }

      glutSwapBuffers();

     }
     break;
  case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        temp=0;
   default:
     break;
   }
                            // Force output to stdout
}
void drawGrid()
{
  glColor3f(0.0f,100.0f,0.0f);
  glBegin(GL_LINES);
  int i;
  for(i=0;i<HEIGHT;i+=10)
    {
      glVertex2i(0,i);
      glVertex2i(WIDTH,i);
    }

  for(i=0;i<WIDTH;i+=10)
    {
      glVertex2i(i,0);
      glVertex2i(i,HEIGHT);
    }   
  glEnd();
}

void Display()
{
 glClearColor(1,1,1,0);   //WHITE
 glClear(GL_COLOR_BUFFER_BIT);
 drawGrid();
 glFlush();
}

void main(int argc,char** argv)
{
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowPosition(50,50);
 glutInitWindowSize(WIDTH,HEIGHT);
 glutCreateWindow("Circle Drawing Algorithm");
 
 init();
 glutDisplayFunc(Display);
 glutMouseFunc(mouseClick);
 glutMainLoop();
}