#include "Rendering.h"
//vertex arrays needed for drawing
unsigned int vbo;
unsigned int cbo;
unsigned int nbo;
unsigned int ibo;

//attributes
unsigned int positionLocation = 0;
unsigned int colorLocation = 1;
unsigned int normalLocation = 2;

//uniforms
unsigned int u_lightPosLocation;
unsigned int u_modelMatrixLocation;
unsigned int u_projMatrixLocation;
	
//needed to compile and link and use the shaders
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;


//Vertex buffers. Hard initialized for now

//4 vertex positions
glm::vec3 vertices[4] = {
		vec3(-0.5,-0.5, 0.0),
		vec3( 0.5,-0.5, 0.0),
		vec3(-0.5, 0.5, 0.0),
		vec3( 0.5, 0.5, 0.0)};

//4 normals (one per vertex)
glm::vec3 normals[4] = {
		vec3(0.0, 0.0, 1.0), 
		vec3(0.0, 0.0, 1.0),
		vec3(0.0, 0.0, 1.0),
		vec3(0.0, 0.0, 1.0)};

//4 Colors (one per vertex)
glm::vec3 colors[4] = {
		 vec3(1.0, 0.0, 0.0), 
		 vec3(0.0, 1.0, 0.0),
		 vec3(0.0, 0.0, 1.0),
		 vec3(1.0, 1.0, 1.0)};

//6 indecies (2 triangles)
unsigned short indices[6] = {0, 1, 2,  2, 1, 3};


//Animation/transformation stuff
clock_t old;
float rotation = 0.0f;

void initOpenGL(int argc, char** argv, int width, int height)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow("Sandbox");

	glewInit();

	//Setup clear color, enable depth test, and other setup stuff
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);

}

void initVBOs(void)
{
	//Create the VBOs and IBO we'll be using to render images in OpenGL
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &cbo);
	glGenBuffers(1, &nbo);
	glGenBuffers(1, &ibo);

	
}

void initShaders() {
	
	const char* fragFile = "diffuseFrag.frag";
	const char* vertFile = "diffuseVert.vert";
	Utility::shaders_t shaders = Utility::loadShaders(vertFile, fragFile);

	shaderProgram = glCreateProgram();
	
	//set the attribute locations for our shaders
	glBindAttribLocation(shaderProgram, positionLocation, "vs_position");
	glBindAttribLocation(shaderProgram, normalLocation, "vs_normal");
	glBindAttribLocation(shaderProgram, colorLocation, "vs_color");

	Utility::attachAndLinkProgram(shaderProgram,shaders);
	
	//Get the uniform locations for our shaders, unfortunately they can not be set by us, we have
	//to ask OpenGL for them
	u_lightPosLocation = glGetUniformLocation(shaderProgram, "u_lightPos");
	u_modelMatrixLocation = glGetUniformLocation(shaderProgram, "u_modelMatrix");
	u_projMatrixLocation = glGetUniformLocation(shaderProgram, "u_projMatrix");
}


void cleanup() {
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &cbo);
	glDeleteBuffers(1, &nbo);
	glDeleteBuffers(1, &ibo);

	//Tear down the shader program in reverse of building it
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(shaderProgram);
}



void resize(int width, int height) {
	//set the viewport, more boilerplate
	glViewport(0, 0, width, height);

	//
	glm::mat4 projection = glm::perspective(60.0f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 30.0f);
	glm::mat4 camera = glm::lookAt(glm::vec3(2.5, 2, 10), glm::vec3(2.5, 2, 0), glm::vec3(0, 1, 0));
	projection = projection * camera;
	vec3 lightPos = vec3(5.0, 5.0, 10.0);

	//set the projection matrix here, it only needs to be changed if the screen is resized otherwise it can stay the same
	glUniformMatrix4fv(u_projMatrixLocation, 1, GL_FALSE, &projection[0][0]);
	glUniform3fv(u_lightPosLocation, 1, &lightPos[0]);

	glutPostRedisplay();
}


//from swiftless.com
char* textFileRead(const char* fileName) {
    char* text;
    
    if (fileName != NULL) {
        FILE *file = fopen(fileName, "rt");
        
        if (file != NULL) {
            fseek(file, 0, SEEK_END);
            int count = ftell(file);
            rewind(file);
            
            if (count > 0) {
                text = (char*)malloc(sizeof(char) * (count + 1));
                count = fread(text, sizeof(char), count, file);
                text[count] = '\0';	//cap off the string with a terminal symbol, fixed by Cory
            }
            fclose(file);
        }
    }
    return text;
}

void printLinkInfoLog(int prog) 
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLogLen);

	// should additionally check for OpenGL errors here

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];
		// error check for fail to allocate memory omitted
		glGetProgramInfoLog(prog,infoLogLen, &charsWritten, infoLog);
		std::cout << "InfoLog:" << std::endl << infoLog << std::endl;
		delete [] infoLog;
	}
}

void printShaderInfoLog(int shader)
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

	// should additionally check for OpenGL errors here

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];
		// error check for fail to allocate memory omitted
		glGetShaderInfoLog(shader,infoLogLen, &charsWritten, infoLog);
		std::cout << "InfoLog:" << std::endl << infoLog << std::endl;
		delete [] infoLog;
	}

	// should additionally check for OpenGL errors here
}