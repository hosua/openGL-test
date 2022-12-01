#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
using namespace std;

#define WIN_X 640
#define WIN_Y 480

// Number of vertices on a square
#define NUM_V 4

// Constants used to construct a square
#define OG_X1 0.0f
#define OG_Y1 0.0f

#define OG_X2 0.0f
#define OG_Y2 1.0f

#define OG_X3 1.0f
#define OG_Y3 1.0f

#define OG_X4 1.0f
#define OG_Y4 0.0f

// For random GLfloats
std::default_random_engine rng(time(0));
std::uniform_real_distribution<GLfloat> dist(0.0, 1.0);

GLfloat degToRad(float f) { return f * (M_PI / 180.0f); }

struct vec2f {
    GLfloat x;
    GLfloat y;
    vec2f() {}
    vec2f(GLfloat x, float y) : x(x), y(y) {}
};

// Note: openGL uses 0.0-1.0 scaling, not 0.0-255.0
struct rgb {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    rgb() : r(1.0f), g(1.0f), b(1.0f){}
    rgb(GLfloat r, float g, float b) : r(r), g(g), b(b){}
};

ostream& operator<<(ostream& out, const vec2f& vec) {
    out << "(" << vec.x << "," << vec.y << ")";
    return out;
}

ostream& operator<<(ostream& out, const rgb& color) {
    out << "(" << color.r << "," << color.g << "," << color.b << ")";
    return out;
}

class Square {
private:
    vec2f mat[4];
    rgb color;

    GLfloat x_vel, y_vel;
    int x_dir, y_dir;
    GLfloat rot_vel, rot_dir;

public:
    Square(GLfloat scalar)
        : x_vel(0), y_vel(0), x_dir(0), y_dir(0), rot_vel(0), rot_dir(0) {
        mat[0] = vec2f(OG_X1 * scalar, OG_Y1 * scalar);
        mat[1] = vec2f(OG_X2 * scalar, OG_Y2 * scalar);
        mat[2] = vec2f(OG_X3 * scalar, OG_Y3 * scalar);
        mat[3] = vec2f(OG_X4 * scalar, OG_Y4 * scalar);
    }
    Square(GLfloat scalar, float x_vel, float y_vel, int x_dir, int y_dir, float rot_vel, int rot_dir){
        : x_vel(0), y_vel(0), x_dir(0), y_dir(0), rot_vel(0), rot_dir(0) {
        mat[0] = vec2f(OG_X1 * scalar, OG_Y1 * scalar);
        mat[1] = vec2f(OG_X2 * scalar, OG_Y2 * scalar);
        mat[2] = vec2f(OG_X3 * scalar, OG_Y3 * scalar);
        mat[3] = vec2f(OG_X4 * scalar, OG_Y4 * scalar);
    }

    ~Square() {}

    // Easy access variables for square matrix
    GLfloat &x1 = mat[0].x, &y1 = mat[0].y; // bottom-left
    GLfloat &x2 = mat[1].x, &y2 = mat[1].y; // top-left
    GLfloat &x3 = mat[2].x, &y3 = mat[2].y; // top-right
    GLfloat &x4 = mat[3].x, &y4 = mat[3].y; // bottom-right

    /* Getter functions */
    GLfloat getVelX() { return x_vel; }
    GLfloat getVelY() { return y_vel; }
    int getDirX() { return x_dir; }
    int getDirY() { return y_dir; }
    vec2f getCenter() { return vec2f((x1 + x2 + x3) / 3, (y1 + y2 + y3) / 3); }

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
    void setVelDir(int dir) {
        assert(dir == -1 || dir == 0 ||
               dir == 1 && "Error: direction variable must be -1, 0, or 1");
        rot_dir = dir;
    }

    void setVelX(GLfloat vel) { x_vel = vel; }
    void setVelY(GLfloat vel) { y_vel = vel; }
    void setVelRot(GLfloat vel) { rot_vel = vel; }

    /* Movement functions */
    void move() {
        for (vec2f& vec : mat) {
            vec.x += x_vel * x_dir;
            vec.y += y_vel * y_dir;
        }
    }

    void rotate() {
        vec2f center = getCenter();
        // translate to point of rotation
        for (vec2f& vec : mat) {
            vec.x -= center.x;
            vec.y -= center.y;
        }

        // Perform rotation
        for (vec2f& vec : mat) {
            GLfloat theta = rot_vel * rot_dir;
            // printf("%f %f %f\n", rot_vel, rot_dir, theta);
            GLfloat nx =
                vec.x * cos(degToRad(theta)) - vec.y * sin(degToRad(theta));
            GLfloat ny =
                vec.x * sin(degToRad(theta)) + vec.y * cos(degToRad(theta));
            vec.x = nx, vec.y = ny;
        }

        // translate back to origin
        for (vec2f& vec : mat) {
            vec.x += center.x;
            vec.y += center.y;
        }
    }

    // Update movement direction based on position
    void update() {
        vector<GLfloat> x_vec = {x1, x2, x3, x4};
        vector<GLfloat> y_vec = {y1, y2, y3, y4};

        GLfloat max_x = *max_element(x_vec.begin(), x_vec.end());
        GLfloat max_y = *max_element(y_vec.begin(), y_vec.end());
        GLfloat min_x = *min_element(x_vec.begin(), x_vec.end());
        GLfloat min_y = *min_element(y_vec.begin(), y_vec.end());

        if (max_x >= 1 || min_x <= -1) {
            x_dir *= -1;
            // If a point goes off screen, flip rotation to keep the triangle
            // inside
            if (max_x > 1.01 || min_x < -1.01) rot_dir *= -1;
            randomizeColor();
        }
        if (max_y >= 1 || min_y <= -1) {
            y_dir *= -1;
            // If a point goes off screen, flip rotation to keep the triangle
            // inside
            if (max_y > 1.01 || min_y < -1.01) rot_dir *= -1;
            randomizeColor();
        }
    }

    /* Drawing */
    void draw() {
        glColor3f(color.r, color.g, color.b);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glVertex2f(x4, y4);
    }

    void randomizeColor(){
        color.r = dist(rng);
        color.g = dist(rng);
        color.b = dist(rng);
        cout << color << endl;
    }

    /* Debugging */
    void printPos() {
        int i = 1;
        for (vec2f vec : mat) cout << "v[" << i++ << "]: " << vec << "\n";
        printf("-------------------\n");
    }
};

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {
    srand(time(0));
    GLFWwindow* window;
    if (!glfwInit()) return EXIT_FAILURE;

    window = glfwCreateWindow(WIN_X, WIN_Y, "Square", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        cout << "glew error!\n";
    }

    Square sq(0.25);
    sq.setDirX(1);
    sq.setVelX(0.01f);
    sq.setDirY(1);
    sq.setVelY(0.008f);

    sq.setVelRot(0.5);
    sq.setVelDir(-1);
    sq.randomizeColor();

    vector<Square> sq_vec;
    int sq_count = 10;

    for (int i = 0; i < sq_count; i++){
        Square s = Square(0.25);
        sq_vec.push_back(s);

    }

    // Run event loop until user closes window
    while (!glfwWindowShouldClose(window)) {
        // render here
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_QUADS);

        sq.draw();
        // sq.printPos();
        sq.rotate();
        sq.move();
        sq.update();

        glEnd();

        // swap front & back buffers
        glfwSwapBuffers(window);

        // poll for and process events.
        glfwPollEvents();
        // cout << sq.getCenter() << endl;
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}