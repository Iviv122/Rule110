#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 1000
#define HEIGHT 1000
 
 

 float scale= (float)1/WIDTH;

 int** matrix;
 int iteration = HEIGHT-1;	

int main(void)
{


	matrix = (int**)calloc(WIDTH,sizeof(int*));

	for(int i=0;i<WIDTH;i++){
	matrix[i] = (int*)calloc(HEIGHT,sizeof(int));	
	}

	matrix[WIDTH-1][HEIGHT-1] =1;

	GLFWwindow* window;

	if (!glfwInit())
	return -1;

	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
    
	if (!window)
	{
	glfwTerminate();
	return -1;
	}

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window) || iteration >= 0)
    {
        glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	glScalef(scale*2,scale*2,scale*2);
	glBegin(GL_POINTS);

	for(int x=0;x<WIDTH;++x){
	for(int y=HEIGHT-1;y>0;--y){
	if(matrix[x][y]!=0)glVertex2f(x-(WIDTH/2),y-(HEIGHT/2));	
	}
	}
	glEnd();

	for(int i=0;i<WIDTH;i++){
	if(i-1 <0 || i+1 >= WIDTH) {continue;}
	if(matrix[i][iteration]==1 && matrix[i-1][iteration]==1 && matrix[i+1][iteration]==1){  // if cell and neighbors are 1 -> 0
		matrix[i][iteration-1] = 0;
	}else if(matrix[i][iteration]==0 && matrix[i-1][iteration]==0 && matrix[i+1][iteration]==0){ // if cell and neighbours are 0 -> 0
		matrix[i][iteration-1] = 0;	
	}else if(matrix[i][iteration]==0 && matrix[i-1][iteration]==1&& matrix[i+1][iteration]==0){ // if cell and right are 0 but left is 1 -> 0
		matrix[i][iteration-1] = 0;
	}else{
		matrix[i][iteration-1] = 1;
	}}
	if(iteration == 0) getchar();		
	iteration--;
	glfwSwapBuffers(window);
	glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


