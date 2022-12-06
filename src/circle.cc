#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WIN_X 640
#define WIN_Y 480

#define BORDER_X 1.0f
#define BORDER_Y 1.0f

using std::vector;
using std::cout;
using std::endl;

// For random GLfloats
std::default_random_engine rng(time(0));
std::uniform_real_distribution<GLfloat> col_dist(0.0, 1.0);

const GLfloat M_PI_DOUBLE = M_PI*2.0f;

// Note: openGL uses 0.0-1.0 scaling, not 0.0-255.0
struct rgb {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    rgb() : r(1.0f), g(1.0f), b(1.0f) {}
    rgb(GLfloat r, GLfloat g, GLfloat b) : r(r), g(g), b(b) {}
};

struct vec2f {
    GLfloat x;
    GLfloat y;
    vec2f() {}
    vec2f(GLfloat x, GLfloat y) : x(x), y(y) {}
};

GLfloat degToRad(float f) { return f * (M_PI / 180.0f); }

class Circle {
private:
    rgb color;
	GLint num_triangles;
	GLfloat radius;
    GLfloat x_vel, y_vel;
    GLint x_dir, y_dir;
	vec2f pos;
	GLfloat &x = pos.x;
	GLfloat &y = pos.y;

    void randomizeColor() {
        color.r = col_dist(rng);
        color.g = col_dist(rng);
        color.b = col_dist(rng);
    }

public:
    Circle(GLfloat radius, GLint num_triangles, 
			GLfloat x_vel, GLfloat y_vel,
			GLfloat x_dir, GLfloat y_dir,
			GLfloat x=0, GLfloat y=0) : radius(radius), num_triangles(num_triangles),
										x_vel(x_vel), y_vel(y_vel),
										x_dir(x_dir), y_dir(y_dir) {
		this->x = x, this->y = y;
    }

	void setPos(GLfloat x, GLfloat y){ pos.x = x, pos.y = y; }
    void setVelX(GLfloat vel) { x_vel = vel; }
    void setVelY(GLfloat vel) { y_vel = vel; }

    void move() {
		x += x_vel * x_dir;
		y += y_vel * y_dir;
    }

	void draw(){
        glColor3f(color.r, color.g, color.b);
		glVertex2f(x, y);
		for (int i = 0; i <= num_triangles; i++){
			GLfloat px = x + radius * cos(i * M_PI_DOUBLE/20.0f);
			GLfloat py = y + radius * sin(i * M_PI_DOUBLE/20.0f);
			glVertex2f(px, py);
		}
	}

    // Update movement direction based on position
    void bounce() {

        GLfloat max_x = x + radius;
        GLfloat max_y = y + radius;
        GLfloat min_x = x - radius;
        GLfloat min_y = y - radius;
	
		// bounce
        if (max_x >= BORDER_X || min_x <= -BORDER_X) {
            x_dir *= -1;
            randomizeColor();
        }

        if (max_y >= BORDER_Y || min_y <= -BORDER_Y) {
            y_dir *= -1;
            randomizeColor();
        }
    }
};


int main(){
    GLFWwindow* window;
    if (!glfwInit()) return EXIT_FAILURE;
    window = glfwCreateWindow(WIN_X, WIN_Y, "Square", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
        cout << "glew error!\n";

	Circle* c = new Circle(0.15f, // scale 
							20,  // num triangles to draw circle
							0.01f, 0.02f, // x_vel, y_vel
							1, -1); // x_dir, y_dir	

    while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLE_FAN);

		c->draw();	
		c->move();
		c->bounce();

		glEnd();

        // swap front & back buffers
        glfwSwapBuffers(window);

        // poll for and process events.
        glfwPollEvents();
	}
	glfwTerminate();
}
