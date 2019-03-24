/*---------------------------------------------------------*/
/* ----------------   Práctica 7 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*---------------------Grupo : 04--------------------------*/
/*------------- Alumno:  Zagoya Mellado Roberto Uriel ---------------*/
/*--------------------Version de visual : 2017-----------------------*/
/* LOS MOVIMIENTOS DE LA LUZ SON:

   O --> MOVIMIENTO NEGATIVO EN Z
   U --> MOVIMIETNO POSITIVO EN Z
   I --> MOVIMIENTO POSITIVO EN Y
   K --> MOVIMIENTO NEGATIVO EN Y
   L --> MOVIMIENTO POSITIVO EN X
   J --> MOVIMIENTO NEGATIVO EN X

*/
#include "esfera.h"
#include "camera.h"

Esfera my_sphere(1.0);

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, lightVAO;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
double	lastX = 0.0f,
		lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

float mlx = 0.0f,
mly = 0.0f,
mlz = 0.0f;

//Lighting
glm::vec3 lightPos(mlx, mly, mlz);

void myData(void);
void display(void);
void getResolution(void);
void animate(void);

//For Keyboard
float	movX = 0.0f,
		movY = 0.0f,
		movZ = -5.0f,
		rotX = 0.0f;

float	sol = 0.0f,
year = 0.0f,
day = 0.0f,
moon = 0.0f,
mars_year = 0.0f,
jupiter_year = 0.0f,
e1 = 0.0f,
e2 = 0.0f,
e3 = 0.00,
e4 = 0.0,
e5 = 0.0,
e6 = 0.0,
e7 = 0.0,
e8 = 0.0;



void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void myData()
{	
		GLfloat vertices[] = {
		//Position				//Normals
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,//
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//To configure Second Objecto to represet Light
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void animate(void)
{
	sol += 0.5f;
	e1 += 0.15f;
	e2 += 0.1f;
	e3 += 0.09;
	e4 += 0.08;
	e5+= 0.07;
	e6 += 0.06;
	e7 += 0.05;
	e8 += 0.04;
}

void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	//Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");
	Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//Shader projectionShader("shaders/shader_light_Gouraud.vs", "shaders/shader_light_Gouraud.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");
	
	//To Use Lighting
	projectionShader.use();
	glm::vec3 lightPos(mlx, mly, mlz);
	projectionShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("lightPos", lightPos);

	// create transformations and Projection
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 temp01= glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 temp02 = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to inlcude Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();

	// pass them to the shaders}
	projectionShader.setVec3("viewPos", camera.Position);
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);


	//proton y neutrones 
	model = glm::mat4(1.0f);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(e6), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0, 0, 0));
	model = glm::rotate(model, glm::radians(e6), glm::vec3(0.0f, 1.0f, 0.0f));
	temp02 = model;
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 0.0f, 0.0f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();	//Sphere	//mercurio

	//e1
	model = temp02;
	model = glm::rotate(model, glm::radians(e1), glm::vec3(1.0f, 0.5f, 0.5f));
	model = glm::translate(model, glm::vec3(3.0f, 3.0f, 3.0f));
	model = glm::rotate(model, glm::radians(e1), glm::vec3(1.0f, 0.5f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.5843f, 0.372549f, 0.1254f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();	//Sphere
	//glDrawArrays(GL_TRIANGLES, 0, 36);	//Light


	//e2
	model = temp02;
	model = glm::rotate(model, glm::radians(-e2), glm::vec3(1, 5, 2));
	model = glm::translate(model, glm::vec3(3.5f, 3.5f, 3.5f));
	model = glm::rotate(model, glm::radians(-e2), glm::vec3(1, 5, 2));
	//temp01 = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 0.0f, 0.0f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();	//Sphere	//mercurio


	//e3
	model = temp02;
	model = glm::rotate(model, glm::radians(e3), glm::vec3(-2, 5, 2));
	model = glm::translate(model, glm::vec3(4, 0, 0));
	model = glm::rotate(model, glm::radians(e3), glm::vec3(-2, 5, 2));
	//temp01 = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.0f, 1.0f, 0.0f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();	//Sphere
	
	//e4
	model = temp02;
	model = glm::rotate(model, glm::radians(-e4), glm::vec3(-2, 5, 2));
	model = glm::translate(model, glm::vec3(4.5f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-e4), glm::vec3(-2, 5, 2));
	//temp01 = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();	//Sphere	//mercurio

	//e5
	model = temp02;
	model = glm::rotate(model, glm::radians(e5), glm::vec3(-2, 7, 2));
	model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(e5), glm::vec3(-2, 7, 2));
	//temp01 = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 0.2f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();	//Sphere	//mercurio
	

	//e6
	model = temp02;
	model = glm::rotate(model, glm::radians(-e6), glm::vec3(1, 5, 1));
	model = glm::translate(model, glm::vec3(5.5f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-e6), glm::vec3(1, 5, 1));
	//temp01 = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.4f, 0.2f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();	//Sphere	//mercurio
	
	//e7
	model = temp02;
	model = glm::rotate(model, glm::radians(e7), glm::vec3(1, 5, 1));
	model = glm::translate(model, glm::vec3(6.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(e7), glm::vec3(1, 5, 1));
	//temp01 = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.5f, 0.1f, 0.1f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();	//Sphere	//mercurio
	

	//e8
	model = temp02;
	model = glm::rotate(model, glm::radians(-e8), glm::vec3(-1, 5, 1));
	model = glm::translate(model, glm::vec3(6.5f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-e8), glm::vec3(-1, 5, 1));
	//temp01 = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.1058f, 0.3333f, 0.5137f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();	//Sphere	//mercurio
	

	

	//Luz
	lampShader.use();//esto es para indicar que shader se va a usar y poder cambiar entre shaders
	lampShader.setMat4("projection", projection);
	lampShader.setMat4("view", view);
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.5f));
	lampShader.setMat4("model", model);
	my_sphere.render();	//Sphere

	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light


	//glBindVertexArray(0);

}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 7", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	my_sphere.init();
	glEnable(GL_DEPTH_TEST);

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        // input
        // -----
        my_input(window);
		animate();

        // render
        // Backgound color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		display();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		mlx+=0.2;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		mlx-=0.2;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		mly+=0.2;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		mly -= 0.2;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		mlz -= 0.2;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		mlz += 0.2;
	

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}


