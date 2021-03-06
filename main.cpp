#include<GL/glut.h>
#include<iostream>
#include<math.h>
#include"curve.h"

double zoomnum = 1;//how zoomed in it is. ya know.
double speed = 0.96;
int choice = 1;
char colorchoice = 's';
bool flip = false;
char direction[4] = {'l','d','r','u'};//uses counter to tell direction
bool pause = false;

struct color
{
	float num[3];
};
color c[4];

void print_controls(){
	std::cout << "1 : zoom out" << std::endl;
	std::cout << "2 : zoom in" << std::endl;
	std::cout << "3 : crazy out" << std::endl;
	std::cout << "4 : crazy in" << std::endl;
	std::cout << "s : steel ball run colors" << std::endl;
	std::cout << "r : tricolor rainbow " << std::endl;
	std::cout << "g : green and blue gradient colors" << std::endl;
	std::cout << "b : black and white gradient colors" << std::endl;
	std::cout << "t : tricolor blueish" << std::endl;
	std::cout << "p : pause" << std::endl;
	std::cout << "q : quit" << std::endl;
}

void ColorSel(int count)
{
	if (colorchoice == 'g'||colorchoice == 'b') //if gradient is selected
	{
		if(direction[count % 4] == 'l'|| direction[count % 4] == 'r')
		{
			glColor3f(c[0].num[0], c[0].num[1], c[0].num[2]);//color 1
		}//if r
		else if(direction[count % 4] == 'd' || direction[count % 4] == 'u')
		{
			glColor3f(c[1].num[0], c[1].num[1], c[1].num[2]);//color 2
		}//if d
		if(!pause)//also pauses the gradient from moving when paused
		{
			if(flip)
			{
				if(colorchoice == 'g')//green and blue
				{
					c[0].num[1] -= 0.000001;
					c[0].num[2] += 0.000001;
					c[1].num[1] += 0.000001;
					c[1].num[2] -= 0.000001;
				}//color green and blue
				else if(colorchoice == 'b')//black and white
				{
					c[0].num[0] -= 0.000001;
					c[0].num[1] -= 0.000001;
					c[0].num[2] -= 0.000001;
					c[1].num[0] += 0.000001;
					c[1].num[1] += 0.000001;
					c[1].num[2] += 0.000001;
				}//black and white

				if(c[0].num[1] <= 0)
				{
					flip = false;
				}// if == 0
			}//if flip
			else
			{
				if(colorchoice == 'g')
				{
					c[0].num[1] += 0.000001;
					c[0].num[2] -= 0.000001;
					c[1].num[1] -= 0.000001;
					c[1].num[2] += 0.000001;
				}//color green and blue
				else if(colorchoice == 'b')
				{
					c[0].num[0] += 0.000001;
					c[0].num[1] += 0.000001;
					c[0].num[2] += 0.000001;
					c[1].num[0] -= 0.000001;
					c[1].num[1] -= 0.000001;
					c[1].num[2] -= 0.000001;
				}//black and white

				if(c[0].num[1] >= 1)
				{
					flip = true;
				}// if == 1
			}//else
		}//if !pause
	}//else if gradient
	else if (colorchoice == 'r' || colorchoice == 't') //if tri-color is selected
	{
		if(count % 3 == 0)
		{
			glColor3f(c[0].num[0], c[0].num[1], c[0].num[2]);//color 1
		}//if 1
		else if (count % 3 == 1)
		{
			glColor3f(c[1].num[0], c[1].num[1], c[1].num[2]);//color 1
		}//else if 2
		else if (count % 3 == 2)
		{
			glColor3f(c[2].num[0], c[2].num[1], c[2].num[2]);//color 1
		}//else if 3
	}//else if tricolor
	else //default 4 color variant
	{
		if(colorchoice == 's')
		{
			c[0] = {0.486f, 0.988f, 0.0f};//color 1
			c[1] = {0.118f, 0.565f, 1.0f};//color 2
			c[2] = {1.0f, 0.0f, 1.0f};//color 3
			c[3] = {1.0f, 0.843f, 0.2f};//color 4
		}//if steel ball run

		//change color (R,G,B) values
		if(direction[count % 4] == 'l')
		{
			glColor3f(c[0].num[0], c[0].num[1], c[0].num[2]);//color 1
		}//if r
		else if(direction[count % 4] == 'd')
		{
			glColor3f(c[1].num[0], c[1].num[1], c[1].num[2]);//color 2
		}//if d
		else if(direction[count % 4] == 'r')
		{
			glColor3f(c[2].num[0], c[2].num[1], c[2].num[2]);//color 3
		}//if l
		else if(direction[count % 4] == 'u')
		{
			glColor3f(c[3].num[0], c[3].num[1], c[3].num[2]);//color 4
		}//if u
	}//else default 4 color varient
}//ColorSel

void HolQuad(coord point1, coord point2, coord point3, coord point4, int count)//print 4 lines in a quadralateral corrioding to the 4 points
{
	ColorSel(count);

	glBegin(GL_QUADS);//print colored quad
		glVertex2d(point1.x, point1.y);
		glVertex2d(point2.x, point2.y);
		glVertex2d(point3.x, point3.y);
		glVertex2d(point4.x, point4.y);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);//white	

	//print hollow quad
	glBegin(GL_LINES);
		glVertex2d(point1.x, point1.y);
		glVertex2d(point2.x, point2.y);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(point2.x, point2.y);
		glVertex2d(point3.x, point3.y);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(point3.x, point3.y);
		glVertex2d(point4.x, point4.y);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(point4.x, point4.y);
		glVertex2d(point1.x, point1.y);
	glEnd();
}//HolQuad

bool under1(coord arr[])
{
	for(int i = 0; i < 4; i++)
	{
		if(arr[i].x < 1 || arr[i].y < 1)
			return true;
	}//for i
return false;
}//under1

void DrawFib()
{
	double minlength;
	int counter = 1;//used to determine direction

	if(choice == 1)
	{
		minlength = 0.0005 * zoomnum;//side length of first triangle zoom in
	}//if 1
	else if((choice == 4 && (colorchoice == 'r'|| colorchoice == 't'))||(choice == 3 && (colorchoice == 'r' || colorchoice == 't')))
	{
		minlength = 0.0000005 / zoomnum;//side length of first triangle zoom out
	}//else if 
	else if (choice == 2 || choice == 3 || choice == 4)
	{
		minlength = 0.0005 / zoomnum;//side length of first triangle zoom out
	}//else if 2


	//starting square initial points
	coord point[4];
	point[0].x = minlength;
	point[0].y = minlength;
	point[1].x = -minlength;
	point[1].y = minlength;
	point[2].x = -minlength;
	point[2].y = -minlength;
	point[3].x = minlength;
	point[3].y = -minlength;

	//starting sequence
	double prevlength[3] = {0, minlength * 2, 0};
	const double N = (1.2/15.0);
	
	while(under1(point))
	{
		HolQuad(point[0], point[1], point[2], point[3],counter);
		
		//change position and size of square and also print curve
		if(direction[counter%4] == 'l')
		{
			coord mid = {point[0].x - N * point[0].x, point[0].y - N * point[0].y};//this point is used to make the bezier curve look more like a quarter circle
			curve(point[3], mid, point[1]);	
			for(int i = 0; i < 4; i++)
			{
				point[i].x -= prevlength[1];
			}//for i
			point[1].x -= prevlength[0];
			point[2].x -= prevlength[0];
			point[2].y -= prevlength[0];
			point[3].y -= prevlength[0];
		}//if r
		else if(direction[counter%4] == 'd')
		{
			coord mid = {point[1].x - N * point[1].x, point[1].y - N * point[1].y};//this point is used to make the bezier curve look more like a quarter circle
			curve(point[0], mid, point[2]);	
			for(int i = 0; i < 4; i++)
			{
				point[i].y -= prevlength[1];
			}//for i
			point[0].x += prevlength[0];
			point[3].x += prevlength[0];
			point[2].y -= prevlength[0];
			point[3].y -= prevlength[0];
		}//if d
		else if(direction[counter%4] == 'r')
		{
			coord mid = {point[2].x + N * point[2].x, point[2].y - N * point[2].y};//this point is used to make the bezier curve look more like a quarter circle
			curve(point[1], mid, point[3]);	
			for(int i = 0; i < 4; i++)
			{
				point[i].x += prevlength[1];
			}//for i
			point[0].x += prevlength[0];
			point[3].x += prevlength[0];
			point[0].y += prevlength[0];
			point[1].y += prevlength[0];
		}//if l
		else if(direction[counter%4] == 'u')
		{
			coord mid = {point[3].x - N * point[3].x, point[3].y + N * point[3].y};//this point is used to make the bezier curve look more like a quarter circle
			curve(point[2], mid, point[0]);	
			for(int i = 0; i < 4; i++)
			{
				point[i].y += prevlength[1];
			}//for i
			point[1].x -= prevlength[0];
			point[2].x -= prevlength[0];
			point[0].y += prevlength[0];
			point[1].y += prevlength[0];
		}//if u

		//set length of squares
		prevlength[2] = prevlength[0] + prevlength[1];
		prevlength[0] = prevlength[1];
		prevlength[1] = prevlength[2];
		counter++;//increment
	}//while(under1)

	if(!pause)
	{
		if(choice == 1|| choice == 2|| choice == 3)
		{
			zoomnum *= speed;
		}//if choice 1 2 or 3
		else if (choice == 4)
		{
			zoomnum /= speed;
		}//else if choice 4
	}//pause

	if(zoomnum <= 0.14705882352 && colorchoice != 'r' && colorchoice != 't')//if one square has become the same size as the next biggest of the same color
	{
		zoomnum = 1;// reset scale
	}//if
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	//This is done so instead of infinitely increasing the size of a set number of squares, it increases the
	//size to until it is smaller than that big decimal ((5/34) => square/next biggest of same color)
	else if (zoomnum <= 13.0/55.0/70 && (colorchoice == 'r' || colorchoice == 't'))//i don't even understand anything anymore
	{
		zoomnum = 1;//reset scale
	}//else if


	if(choice == 3 || choice == 4)
		speed += 0.0001;

}//DrawFib

void display()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//I do as the sample code says

	DrawFib();

	glutSwapBuffers();//I do as sample code commands
}//display

void kbin (unsigned char key, int x, int y)
{
	if (key == '1')
	{
		choice = 1;
		speed = 0.96;
		zoomnum = 1;
	}//if 1
	else if (key == '2')
	{
		choice = 2;
		speed = 0.96;
		zoomnum = 1;
	}//else if 2
	else if (key == '3')
	{
		choice = 3;
		speed = 0.96;
		zoomnum = 1;
	}//else if 3
	else if (key == '4')
	{
		choice = 4;
		speed = 0.96;
		zoomnum = 1;
	}//else if 4
	else if (key == 's')
	{
		colorchoice = 's';
	}//else if s
	else if (key == 'g')
	{
		colorchoice = 'g';
		c[0] = {0, 0, 1};
		c[1] = {0, 1, 0};
	}//else if g
	else if (key == 'r')
	{
		colorchoice = 'r';
		c[0] = {1, 0, 0};
		c[1] = {0, 1, 0};
		c[2] = {0, 0, 1};
	}//else if g
	else if (key == 'b')
	{
		colorchoice = 'b';
		c[0] = {1, 1, 1};
		c[1] = {0, 0, 0};
	}//else if b
	else if(key == 't')
	{
		colorchoice = 't';
		c[0] = {0, 0.502, 0.502};
		c[1] = {0, 1, 1};
		c[2] = {0.125, 0.698, 0.667};
	}//else if t
	else if (key == 'p')
	{
		if(pause) pause = false;
		else pause = true;
	}//else if p
	else if (key == 'q')//quit
	{
		exit(0);
	}//else if q
}//kbin 

int main(int argc, char *argv[])
{
	//initialize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition ( 0, 0 ) ;
	glutInitWindowSize ( 675, 675 ) ;
	glutCreateWindow( "Fibonacci Spiral" );

	//console screen
	print_controls();

	//functions
	glutDisplayFunc(display);
	glutKeyboardFunc(kbin);
	glutIdleFunc(display);

	//loop
	glutMainLoop();


	return 0;
}
