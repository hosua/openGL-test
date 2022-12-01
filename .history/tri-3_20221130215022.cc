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
	vec2f vec[3];

	float x_vel;
	float y_vel;
	int x_dir;
	int y_dir;
public:
	Triangle(float x1, float y1, float x2, float y2, float x3, float y3){
		vec[0] = vec2f(x1, y1);
		vec[1] = vec2f(x2, y2);
		vec[2] = vec2f(x3, y3);
	}

	Triangle(float x1, float y1, float x2, float y2, float x3, float y3,
	float x_vel, float y_vel, int x_dir, int y_dir) : x_vel(x_vel), y_vel(y_vel), x_dir(x_dir), y_dir(y_dir) {
		vec[0] = vec2f(x1, y1);
		vec[1] = vec2f(x2, y2);
		vec[2] = vec2f(x3, y3);
	}
	~Triangle(){}

	float x1 = vec[0].x, y1 = vec[0].y;
	float x2 = vec[1].x, y2 = vec[1].y;
	float x3 = vec[2].x, y3 = vec[2].y;

	void setVelX(float x_vel){

	}

	void setVelY(float y_vel){

	}

	void printPos(){
		for (vec2f v : vec)
			printf("(%f,%f)\n", v.x, v.y);
		printf("-------------------\n");
	}

	void move(){


	}

	void rotate(float theta){
		for (vec2f& v : vec){
			float temp_x = v.x; // This temp_x here is very important, without it, the object will shrink.
			v.x = v.x * cos(degToRad(theta)) - v.y * sin(degToRad(theta));
			v.y = temp_x * sin(degToRad(theta)) + v.y * cos(degToRad(theta));
		}
	}

	void draw(){
		glVertex2f(vec[0].x, vec[0].y);
		glVertex2f(vec[1].x, vec[1].y);
		glVertex2f(vec[2].x, vec[2].y);
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
	// vector<float> x_vec = {-0.5f,0.0f,0.5f};
	// vector<float> y_vec = {-0.5f,0.5f,-0.5f};
	vector<pair<float, float>> tri_mat = {
		{-0.5f, -0.5f},
		{0.0f, 0.5f},
		{0.5f, -0.5f},
	};

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
