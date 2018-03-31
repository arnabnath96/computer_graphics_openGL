#include<GL/glut.h>
#include<math.h>
#include<stdio.h>

#define WIDTH 600
#define HEIGHT 600
#define PIXEL 10

int k=1;
int X[3],Y[3];
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

void setEllipsePixel(GLint x1,GLint y1, GLint x, GLint y)
{
 setPixel(x1+x,y1+y);
 setPixel(x1-x,y1+y);
 setPixel(x1+x,y1-y);
 setPixel(x1-x,y1-y);
}

void drawEllipse(int xc,int yc, int r1,int r2)
{
//	  printf("%d %d",r1,r2);
	
  int rxs=r1*r1;
  int rys=r2*r2;
  int p, x=0,y=r2,px=0,py=2*rxs*y;

  setEllipsePixel(xc,yc,x,y);

  p=round(rys- rxs*r2 + 0.25*(float)(rxs));
  while(px<py)
  {
    x++;
    px+=2*rys;
    if(p<0)
      p+=rys+px;
    else
    {
      y--;
      py-=2*rxs;
      p+=rys+px-py;
    }
    setEllipsePixel(xc,yc,x,y);
  }

  p=round(rys*(x+0.5)*(x+0.5)+rxs*(y-1)*(y-1)-rxs*rys);
  while(y>0)
  {
    y--;
    py-=2*rxs;
    if(p>0)
      p+=rxs-py;
    else
    {
      x++;
      px+=2*rys;
      p+=rxs-py+px;
    }
    setEllipsePixel(xc,yc,x,y);
  }

}


void mouseClick(int button, int state, int x, int y)
{
 switch(button)
 {
    case GLUT_LEFT_BUTTON:
     if (state == GLUT_DOWN)
     {   
      temp=temp%3;
      X[temp]=x/PIXEL+1;
      Y[temp]=HEIGHT/PIXEL-y/PIXEL;
      setPixel(X[0],Y[0]);
      temp++;
      if(temp%3==0)
      {
       float r1=sqrt((X[0]-X[1])*(X[0]-X[1]) + (Y[0]-Y[1])*(Y[0]-Y[1]));
       float r2=sqrt((X[0]-X[2])*(X[0]-X[2]) + (Y[0]-Y[2])*(Y[0]-Y[2]));
       drawEllipse(X[0],Y[0],r1,r2);
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