#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

float degToRad(float f){
	return f * (M_PI/180.0f);
}

struct vec2f {
	float x;
	float y;
	vec2f(float x, float y) : x(x), y(y){}
};

struct Triangle {
	vec2f vec[2];
	float x1 = vec[0].x;
	float y1 = vec[0].y;
	float x2 = vec[1].x;
	float y2 = vec[0].y;
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
	// vector<float> x_vec = {-0.5f,0.0f,0.5f};
	// vector<float> y_vec = {-0.5f,0.5f,-0.5f};
	vector<pair<float, float>> tri_mat = {
		{-0.5f, -0.5f},
		{0.0f, 0.5f},
		{0.5f, -0.5f},
	};
	float theta = 3.0f;

	// loop until user closes window
	while (!glfwWindowShouldClose(window)){

		// render here
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLES);

		glVertex2f(tri_mat[0].first, tri_mat[0].second);
		glVertex2f(tri_mat[1].first, tri_mat[1].second);
		glVertex2f(tri_mat[2].first, tri_mat[2].second);

		glEnd();
			
		// swap front & back buffers
		glfwSwapBuffers(window);
	
		// poll for and process events.
		glfwPollEvents();
		// (dir > 0) ? glTranslatef(0.1,0,0) : glTranslatef(-0.1,0,0); // Maybe don't use this?
		// Move Left Right
		// for (float& vx : x_vec)
		// 	vx += 0.01 * dir;
		// print
		for (pair<float, float> vec : tri_mat){
			printf("(%f,%f)\n", vec.first, vec.second);
		}
		printf("---------------\n");

		// rotate (Do not forget to convert to radians before using trig functions)
		// Also, it is VERY important that a temp variable for x is stored (since we are calculating )
		for (pair<float, float>& vec : tri_mat){
			float temp = vec.first;
			vec.first = vec.first * cos(degToRad(theta)) - vec.second * sin(degToRad(theta));
			vec.second = temp * sin(degToRad(theta)) + vec.second * cos(degToRad(theta));
		}
		// glRotatef(theta,0,0,1); 

		// if (x_vec[2] >= 1 || x_vec[0] <= -1)
		// 	dir *= -1;
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
