// A simple introductory program; its main window contains a static picture
// of a triangle, whose three vertices are red, green and blue.  The program
// illustrates viewing with default viewing parameters only.

#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

#define WIN_X 640
#define WIN_Y 480

struct vec2 {
	float x;
	float y;
	vec2(){}
	vec2(float x, float y) : x(x), y(y){}
};

struct Triangle {
	vec2 v_init[3];
	vec2 v_pos[3];
	int x_dir = 1;
	int y_dir = 1;

	Triangle(){}
	Triangle(float x1, float y1, float x2, float y2, float x3, float y3) { 
		v_pos[0].x = v_init[0].x = x1;
		v_pos[0].y = v_init[0].y = y1;
		v_pos[1].x = v_init[1].x = x2;
		v_pos[1].y = v_init[1].y = y2;
		v_pos[2].x = v_init[2].x = x3;
		v_pos[2].y = v_init[2].y = y3;
	}
	vec2 getCenter(){
		float x = (v_init[0].x + v_init[1].x + v_init[2].x)/3;
		float y = (v_init[0].y + v_init[1].y + v_init[2].y)/3;
	}
	void printCoords(){
		printf("(%f,%f)\n(%f,%f)\n(%f,%f)\n", v_init[0].x, v_init[0].y, v_init[1].x, v_init[1].y, v_init[2].x, v_init[2].y);
	}
};

Triangle tri = Triangle(-0.1f, -0.1f,
						0.0f, 0.1f,
						0.1f, -0.1f);

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {
	GLFWwindow* window;
	if (!glfwInit())
		return EXIT_FAILURE;
	window = glfwCreateWindow(WIN_X, WIN_Y, "Triangle", NULL, NULL);

	if (!window){
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK){
		cout << "glew error!\n";
	}

	float theta = 0.5f;

	// loop until user closes window
	while (!glfwWindowShouldClose(window)){

		// render here
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLES);

		glVertex2f(tri.v_init[0].x, tri.v_init[0].y);
		glVertex2f(tri.v_init[1].x, tri.v_init[1].y);
		glVertex2f(tri.v_init[2].x, tri.v_init[2].y);
		// glVertex2f(-0.5f, -0.5f);
		// glVertex2f(0.0f, 0.5f);
		// glVertex2f(0.5f, -0.5f);

		glEnd();
			
		// swap front & back buffers
		glfwSwapBuffers(window);
	
		// poll for and process events.
		glfwPollEvents();

		glTranslatef(0.1,0,0);
		// glRotatef(theta,0,0,1); 
		// }
		// Move Left Right
		for (vec2& v_init : tri.v_init){
			float& x = v_init.x;
			x += 0.01 * tri.x_dir;
			float& y = v_init.y;
			y += 0.01 * tri.y_dir;
		}

		 for (vec2 v_true : tri.v_true){
		 	if (v_true.x >= 1 || v_true.x <= -1)
		 		tri.x_dir *= -1;
		 	if (v_true.y >= 1 || v_true.y <= -1)
		 		tri.y_dir *= -1;
		 }
		 tri.printCoords();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
