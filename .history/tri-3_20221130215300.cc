#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

#define WIN_X 640
#define WIN_Y 480

float degToRad(float f){
	return f * (M_PI/180.0f);
}

struct vec2f {
	float x;
	float y;
	vec2f(){}
	vec2f(float x, float y) : x(x), y(y){}
};

class Triangle {
private:
	vec2f mat[3];

	float x_vel;
	float y_vel;
	int x_dir;
	int y_dir;
public:
	Triangle(float x1, float y1, float x2, float y2, float x3, float y3){
		mat[0] = vec2f(x1, y1);
		mat[1] = vec2f(x2, y2);
		mat[2] = vec2f(x3, y3);
	}

	Triangle(float x1, float y1, float x2, float y2, float x3, float y3,
	float x_vel, float y_vel, int x_dir, int y_dir) : x_vel(x_vel), y_vel(y_vel), x_dir(x_dir), y_dir(y_dir) {
		mat[0] = vec2f(x1, y1);
		mat[1] = vec2f(x2, y2);
		mat[2] = vec2f(x3, y3);
	}
	~Triangle(){}
	// easy access variables for triangle matrix
	float x1 = mat[0].x, y1 = mat[0].y;
	float x2 = mat[1].x, y2 = mat[1].y;
	float x3 = mat[2].x, y3 = mat[2].y;

	// getters
	float getVelX(float x_vel){ return x_vel; }
	float getVelY(float y_vel){ return y_vel; }
	// setters
	void setVelX(float x_vel){ this->x_vel = x_vel; }
	void setVelY(float y_vel){ this->y_vel = y_vel; }

	void printPos(){
		for (vec2f vec : mat)
			printf("(%f,%f)\n", vec.x, vec.y);
		printf("-------------------\n");
	}

	void move(){


	}

	void rotate(float theta){
		for (vec2f& vec : mat){
			float temp_x = vec.x; // This temp_x here is very important, without it, the object will shrink.
			vec.x = vec.x * cos(degToRad(theta)) - vec.y * sin(degToRad(theta));
			vec.y = temp_x * sin(degToRad(theta)) + vec.y * cos(degToRad(theta));
		}
	}

	void draw(){
		glVertex2f(mat[0].x, mat[0].y);
		glVertex2f(mat[1].x, mat[1].y);
		glVertex2f(mat[2].x, mat[2].y);
	}
};

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
	
	int dir = 1;

	float theta = 3.0f;
	Triangle tri = Triangle(
		-0.5f, -0.5f, // x1, y1
		0.0f, 0.5f,   // x2, y2
		0.5f, -0.5f   // x3, y3
	);

	// loop until user closes window
	while (!glfwWindowShouldClose(window)){

		// render here
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLES);

		tri.draw();
		glEnd();
			
		// swap front & back buffers
		glfwSwapBuffers(window);
	
		// poll for and process events.
		glfwPollEvents();

		// print
		tri.printPos();

		// rotate
		tri.rotate(theta);
		// glRotatef(theta,0,0,1); 

		// if (x_vec[2] >= 1 || x_vec[0] <= -1)
		// 	dir *= -1;
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
