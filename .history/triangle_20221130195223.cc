// A simple introductory program; its main window contains a static picture
// of a triangle, whose three vertices are red, green and blue.  The program
// illustrates viewing with default viewing parameters only.

#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

struct vec2 {
	float x;
	float y;
	vec2(){}
	vec2(float x, float y) : x(x), y(y){}
};

struct Triangle {
	vec2 v[3];

	Triangle(){}
	Triangle(float x1, float y1, float x2, float y2, float x3, float y3) { 
		v[0].x = x1, v[0].y = y1;
		v[1].x = x2, v[1].y = y2;
		v[2].x = x2, v[2].y = y2;
	}
};

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {
	GLFWwindow* window;
	if (!glfwInit())
		return EXIT_FAILURE;
	const int win_x = 640;
	const int win_y = 480;
	window = glfwCreateWindow(win_x, win_y, "Triangle", NULL, NULL);

	if (!window){
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK){
		cout << "glew error!\n";
	}
	
	int dir = 1;
	Triangle tri = Triangle(-0.5f, -0.5f,
							0.0f, -0.5f,
							0.5f, -0.5f);

	float theta = 0.5f;

	// loop until user closes window
	while (!glfwWindowShouldClose(window)){

		// render here
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLES);

		glVertex2f(tri.v[0].x, tri.v[0].y);
		glVertex2f(tri.v[1].x, tri.v[1].y);
		glVertex2f(tri.v[2].x, tri.v[2].y);

		glEnd();
			
		// swap front & back buffers
		glfwSwapBuffers(window);
	
		// poll for and process events.
		glfwPollEvents();

		glRotatef(theta,0,0,1); 
		// glTranslatef(-5,-10,5);
		// }
		// Move Left Right
		for (vec2 v : tri.v){
			for (int i = 0; i < v.size(); i++){
				x += 0.01 * dir;
			}
		}
		cout << x_vec[0] << " " << x_vec[2] << "\n";

		if (x_vec[2] >= 1 || x_vec[0] <= -1)
			dir *= -1;
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
