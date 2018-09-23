#include <phyzle/PhyGame.h>

PhyGame::PhyGame()
{
	m_Window = nullptr;
}

PhyGame::~PhyGame()
{
}

bool PhyGame::init()
{
	if (!glfwInit())
	{
	
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_Window = glfwCreateWindow(800, 600, "Phyzle", nullptr, nullptr);
	if (!m_Window)
	{
		glfwTerminate();	
		return false;
	}

	glfwMakeContextCurrent(m_Window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();	
		return false;
	}
	initOpenGL();

	return true;
}

void PhyGame::run()
{
	if (!init())
		return;

	while(!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();
	
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_Window);
	}
}

void PhyGame::initOpenGL()
{
	glViewport(0, 0, 800, 600);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
