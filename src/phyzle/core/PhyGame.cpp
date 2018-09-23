#include <phyzle/core/PhyGame.h>
#include <phyzle/core/PhyClock.h>
#include <iostream>

PhyGame::PhyGame()
{
	m_Window = nullptr;
}

PhyGame::~PhyGame()
{
}

bool PhyGame::init()
{
	PhyClockInst->init();
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

	initCallbacks();

	return true;
}

void PhyGame::run()
{
	if (!init())
		return;


	phyFloat lastFrameTime = PhyClockInst->now();

	while(!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_Window);
		
		{
			phyFloat now = PhyClockInst->now();
			phyFloat delta = now - lastFrameTime;
			lastFrameTime = now;
			update(delta);
		}
	}
}


void PhyGame::update(phyFloat deltaTime)
{
	std::cout << deltaTime << std::endl;
}

void PhyGame::initOpenGL()
{
	glViewport(0, 0, 800, 600);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void PhyGame::initCallbacks()
{
	glfwSetFramebufferSizeCallback(m_Window, &PhyGame::framebufferSizeCB);
}


void PhyGame::framebufferSizeCB(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
