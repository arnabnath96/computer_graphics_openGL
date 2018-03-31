#include<GL/glut.h>
#include<math.h>

#define WIDTH 600
#define HEIGHT 600
#define PIXEL 10

int k=1;
int X[2],Y[2];
int temp =0;
float r=0.0f, g=0.0f, b=0.0f;
int sign(int x)
{
if(x>0)
 return 1;
else if(x<0)
 return -1;
else
 return 0;
}

void init()
{
 glClearColor (1.0f,1.0f,1.0f,0.0f);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0,WIDTH+50,0,HEIGHT); 
}

void setPixel(GLint x1,GLint y1)
{
 glColor3f(r,g,b);
 glBegin(GL_POLYGON);
        glVertex2i(x1*10-10,round(y1)*10-10);
        glVertex2i(x1*10,round(y1)*10-10);
        glVertex2i(x1*10, round(y1)*10);
        glVertex2i(x1*10-10,round(y1)*10);
 glEnd();
}

void setPixel2(GLint x1,GLint y1)
{
 glBegin(GL_POLYGON);
        glVertex2i(x1*10-10,round(y1)*10-10);
        glVertex2i(x1*10+40,round(y1)*10-10);
        glVertex2i(x1*10+40, round(y1)*10+40);
        glVertex2i(x1*10-10,round(y1)*10+40);
 glEnd();
}


/* DDA ALgorithm */
void LineWithDDA(int x0,int y0,int x1,int y1)
{
 int dy=y1-y0;
 int dx=x1-x0;
 int steps,i;
 float xinc,yinc,x=x0,y=y0;
 if(abs(dx)>abs(dy))
    steps=abs(dx);
 else
    steps=abs(dy);

 xinc=(float)dx/(float)steps;
 yinc=(float)dy/(float)steps;

 setPixel(x,y);
 for(i=0;i<steps;i++)
 {
  x+=xinc;
  y+=yinc;
  setPixel(x,y);
 }
 glutSwapBuffers();
}

/* Bresenham's Line-Drawing Algorithm */
void LineWithBresenham(int x1,int y1,int x2,int y2)
{
int x,y,dx,dy,swap,temp,s1,s2,p,i;

x=x1;
y=y1;
dx=abs(x2-x1);
dy=abs(y2-y1);
s1=sign(x2-x1);
s2=sign(y2-y1);
swap=0;
setPixel(x1,y1);
if(dy>dx)
 {
 temp=dx;
 dx=dy;
 dy=temp;
 swap=1;
 }
p=2*dy-dx;
for(i=0;i<dx;i++)
 {
 setPixel(x,y);
 while(p>=0)
  {
  p=p-2*dx;
  if(swap)
   x+=s1;
  else
   y+=s2;
  }
 p=p+2*dy;
 if(swap)
  y+=s2;
 else
  x+=s1;
 }
setPixel(x2,y2);
}

void drawGrid()
{
  glColor3f(0.0f,1.0f,0.0f);
  glBegin(GL_LINES);
  int i;
  for(i=0;i<=HEIGHT;i+=10)
    {
      glVertex2i(0,i);
      glVertex2i(WIDTH,i);
    }

  for(i=0;i<=WIDTH;i+=10)
    {
      glVertex2i(i,0);
      glVertex2i(i,HEIGHT);
    }   
  glEnd();

  glBegin(GL_LINES);
  //int i;
  for(i=540;i<=HEIGHT+50;i+=4)
    {
      glVertex2i(600,i);
      glVertex2i(650,i);
    }

  for(i=WIDTH;i<=WIDTH+50;i+=4)
    {
      glVertex2i(i,540);
      glVertex2i(i,600);
    }   
  glEnd();
  

  glColor3f(1.0f,0.0f,0.0f);
  setPixel2(61,1);
  glColor3f(0.0f,1.0f,0.0f);
  setPixel2(61,6);
  glColor3f(0.0f,0.0f,1.0f);
  setPixel2(61,11);
  glColor3f(0.0f,1.0f,1.0f);
  setPixel2(61,16);
  glColor3f(1.0f,0.0f,1.0f);
  setPixel2(61,21);
  glColor3f(1.0f,1.0f,0.0f);
  setPixel2(61,26);
  glColor3f(1.0f,1.0f,1.0f);
  setPixel2(61,31);
  glColor3f(0.0f,0.0f,0.0f);  
  setPixel2(61,36);
  
  glColor3f(1.0f,0.5f,0.0f);
  setPixel2(61,41);
  glColor3f(0.5f,1.0f,0.5f);
  setPixel2(61,46);
  glColor3f(0.5f,0.5f,0.5f);
  setPixel2(61,51);
  

}


void mouseClick(int button, int state, int x, int y)
{
	printf("%d %d\n",x,y);

 if(x<600)
 {switch(button)
 {
    case GLUT_LEFT_BUTTON:
     if (state == GLUT_DOWN)
     {   
      temp=temp%2;
      X[temp]=x/PIXEL+1;
      Y[temp]=HEIGHT/PIXEL-y/PIXEL;
      temp++;
      if(temp%2==0)
      {
       LineWithBresenham(X[0],Y[0],X[1],Y[1]);
       X[0]=X[1];
       Y[0]=Y[1];
       temp++;
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
 }
 else if( x>=600 && y>50)
 {
 	unsigned char pick_col[3];
	glReadPixels(x , 600-y , 1 , 1 , GL_RGBA , GL_UNSIGNED_BYTE , pick_col);
	r = pick_col[0]/255.0;
	g = pick_col[1]/255.0;
	b = pick_col[2]/255.0;
	//printf("r:%f g:%f b:%f\n",r,g,b);
 }
 else
 { 
  
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor (1.0f,1.0f,1.0f,0.0f);
  drawGrid();
  glFlush();
 }
                            // Force output to stdout
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
 glutInitWindowSize(WIDTH+50,HEIGHT);
 glutCreateWindow("Line Drawing Algorithm");
 
 init();
 glutDisplayFunc(Display);
 glutMouseFunc(mouseClick);
 glutMainLoop();
}
