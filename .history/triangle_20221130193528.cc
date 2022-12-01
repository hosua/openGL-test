// A simple introductory program; its main window contains a static picture
// of a triangle, whose three vertices are red, green and blue.  The program
// illustrates viewing with default viewing parameters only.

#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

struct vec2 {
	float x[2];
	float y[2];
};

class Triangle {
		

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
	vector<float> x_vec = {-0.5f,0.0f,0.5f};
	vector<float> y_vec = {-0.5f,0.5f,-0.5f};
	float theta = 0.5f;

	// loop until user closes window
	while (!glfwWindowShouldClose(window)){

		// render here
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		glVertex2f(x_vec[0], y_vec[0]);
		glVertex2f(x_vec[1], y_vec[1]);
		glVertex2f(x_vec[2], y_vec[2]);

		glEnd();
			
		// swap front & back buffers
		glfwSwapBuffers(window);
	
		// poll for and process events.
		glfwPollEvents();

		glRotatef(theta,0,0,1); 
		// glTranslatef(-5,-10,5);
		// }
		// Move Left Right
		for (float& vx : x_vec)
			vx += 0.01 * dir;
		cout << x_vec[0] << " " << x_vec[2] << "\n";

		if (x_vec[2] >= 1 || x_vec[0] <= -1)
			dir *= -1;
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
