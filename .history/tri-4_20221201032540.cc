#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
using namespace std;

#define WIN_X 640
#define WIN_Y 480

#define OG_X1 0.0f
#define OG_Y1 0.0f
#define OG_X2 1.0f
#define OG_Y2 0.0f
#define OG_X3 0.5f
#define OG_Y3 0.866f

float degToRad(float f) { return f * (M_PI / 180.0f); }

struct vec2f {
    float x;
    float y;
    vec2f(){}
    vec2f(float x, float y) : x(x), y(y) {}
};

class Triangle {
private:
    vec2f mat[3];

    // TODO: Need a buffer so that rotating & movement can happen concurrently
    vec2f mat_buf[3];
    float x1_buf, y1_buf;
    float x2_buf, y2_buf;
    float x3_buf, y3_buf;

    float x_vel;
    float y_vel;
    int x_dir;
    int y_dir;
    float rot_vel;
    float rot_dir;

public:

    Triangle(float scalar) : x_vel(0), y_vel(0), x_dir(0), y_dir(0), rot_vel(0), rot_dir(0) {
        mat[0] = vec2f(OG_X1 * scalar, OG_Y1 * scalar);
        mat[1] = vec2f(OG_X2 * scalar, OG_Y2 * scalar);
        mat[2] = vec2f(OG_X3 * scalar, OG_Y3 * scalar);
    }

    ~Triangle() {}

    // easy access variables for triangle matrix
    float &x1 = mat[0].x, &y1 = mat[0].y;
    float &x2 = mat[1].x, &y2 = mat[1].y;
    float &x3 = mat[2].x, &y3 = mat[2].y;

    /* Getter functions */
    float getVelX() { return x_vel; }
    float getVelY() { return y_vel; }
    int getDirX() { return x_dir; }
    int getDirY() { return y_dir; }
    vec2f getCenter() { return vec2f((x1+x2+x3)/3, (y1+y2+y3)/3); }

    /* Setter functions */
    void setDirX(int dir) {
        assert(dir == -1 || dir == 0 ||
               dir == 1 && "Error: direction variable must be -1, 0, or 1");
        x_dir = dir;
    }

    // in OpenGL, -y is up and +y is down, so we flip the setter.
    void setDirY(int dir) {
        assert(dir == -1 || dir == 0 ||
               dir == 1 && "Error: direction variable must be -1, 0, or 1");
        y_dir = -dir;
    }

    void setVelX(float vel) { x_vel = vel; }
    void setVelY(float vel) { y_vel = vel; }

    void setVelRot(float vel) { rot_vel = vel; }
    void setVelDir(int dir) { 
		assert(dir == -1 || dir == 0 ||
               dir == 1 && "Error: direction variable must be -1, 0, or 1");
		rot_dir = dir; 
	}

    /* Movement functions */
    void move() {
        for (vec2f& vec : mat) {
            vec.x += x_vel * x_dir;
            vec.y += y_vel * y_dir;
        }
    }

    void rotate() {
        vec2f center = getCenter();
        // trans to point

        for (int i = 0; i < 3; i++) {
            vec2f& vec = mat[i];
            float theta = rot_vel * rot_dir;
			// printf("%f %f %f\n", rot_vel, rot_dir, theta);
            float nx = vec.x * cos(degToRad(theta)) - vec.y * sin(degToRad(theta));
            float ny = vec.x * sin(degToRad(theta)) + vec.y * cos(degToRad(theta));
            vec.x = nx, vec.y = ny;
        }

        // trans back
    }

    // Update movement direction based on position
    void update() {
        vector<float> x_vec = {x1, x2, x3};
        vector<float> y_vec = {y1, y2, y3};

        float max_x = *max_element(x_vec.begin(), x_vec.end());
        float max_y = *max_element(y_vec.begin(), y_vec.end());
        float min_x = *min_element(x_vec.begin(), x_vec.end());
        float min_y = *min_element(y_vec.begin(), y_vec.end());

        if (max_x >= 1 || min_x <= -1) x_dir *= -1;
        if (max_y >= 1 || min_y <= -1) y_dir *= -1;
    }

    /* Drawing */
    void draw() {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    }

    /* Debugging */
    void printPos() {
        int i = 1;
        for (vec2f vec : mat) printf("v[%i]: (%f,%f)\n", i++, vec.x, vec.y);
        printf("-------------------\n");
    }
};

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {
    GLFWwindow* window;
    if (!glfwInit()) return EXIT_FAILURE;

    window = glfwCreateWindow(WIN_X, WIN_Y, "Triangle", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);


    if (glewInit() != GLEW_OK) {
        cout << "glew error!\n";
    }

    Triangle tri(0.5);
    // tri.setDirX(1);
    // tri.setVelX(0.01f);

    // tri.setDirY(1);
    // tri.setVelY(0.01f);

	tri.setVelRot(1);
	tri.setVelDir(1);

    // Run event loop loop until user closes window
    while (!glfwWindowShouldClose(window)) {
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
        // move
        tri.move();
        // rotate
        tri.rotate();
        tri.update();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
