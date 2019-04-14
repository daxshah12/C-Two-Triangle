#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include "Shader.h"


// gluint is same as unsigned int

#define print(x) std::cout << x << std::endl;




////////////////////////////////////////////////////////////////////////////////////
//Just uncomment the main function;
///////////////////////////////////////////////////////////////////////////////////

int main()
{
	GLFWwindow *window;

	if (!glfwInit())

	{
		print("Error");
		glfwTerminate();
		return - 1;
	}

	window = glfwCreateWindow(800, 800, "Hello Window", NULL, NULL);

	if (!window)
	{

		print("Error window is not created");
		return -1;
	}
	

	glfwMakeContextCurrent(window);


		if(glewInit() != GLEW_OK)
		{
		   std::cout << "Error" << std::endl;
		}

		
	std::cout << glGetString(GL_VERSION) << std::endl;

	Shader ourShader("Vertex1.glsl", "Fragment1.glsl");

	float Attribute[] =
	{

		 -0.9f, -0.5f, 0.0f,  // left 
		  0.0,   0.0,  1.0f,

		 0.0f, -0.5f, 0.0f,  // right
		 0.0,   0.0,  1.0f,

		-0.5f, 0.5f, 0.0f,  // top 
		 0.0,   1.0,  1.0f,

		// second triangle
		 0.0f, -0.5f, 0.0f,  // left
		 0.0,   1.0,  1.0f,

		 0.9f, -0.5f, 0.0f,  // right
		 0.0,   1.0,  0.0f,

		 0.5f, 0.5f, 0.0f, //  top 
		 0.0,   1.0,  1.0f
	

	};




	unsigned int VBO, VAO, VBO2;

	glGenVertexArrays(1, &VAO);
	{

		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);


		glBufferData(GL_ARRAY_BUFFER, sizeof(Attribute), Attribute, GL_STATIC_DRAW);

		// first triangle
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0 * sizeof(float)));

		//for color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f,0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
	


		ourShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteProgram(shaderVertex);
	//glDeleteProgram(shaderFragment);

	glfwTerminate();
	
	return 0;
}