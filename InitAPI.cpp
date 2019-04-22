// InitAPI.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "include/GLFW/glfw3.h"
#include "include/GLFW/glfw3native.h"
#include <iostream>
#include <string>
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include <vector>
#include <thread>
#include <Windows.h>
#include "PhysicPoint.h"
#include "Keyboard.h"


using namespace std;

bool physic = true;
PhysicPoint point(glm::vec2(0.02, 0.02));
PhysicPoint point2(glm::vec2(0.52, 0.52));
PhysicPoint point3(glm::vec2(0.57, 0.57));
glm::vec2 Forces(0.0,0.0);
glm::vec2 Forces2(0.0, 0.0);
glm::vec2 PrevForces2(0.0, 0.0);

glm::vec2 Wall_normal_left(-1,1);
glm::vec2 Wall_normal_rigth(-1, 1);
glm::vec2 Wall_normal_up(1, -1);
glm::vec2 Wall_normal_down(1, -1);
glm::vec3 Colors(1,0,0);


glm::vec2 A(0.0,0.0);
glm::vec2 B(0.5,0.0);
glm::vec2 C(0.5,0.5);
glm::vec2 D(0.5, 0.5);

glm::vec2 A1(0.5, 0.5);
glm::vec2 B1(0.5, 0.5);
glm::vec2 C1(0.5, 0.5);


glm::vec2 A2(0.5, 0.5);
glm::vec2 B2(0.5, 0.5);

glm::vec2 result3;
float lambda = 0;




Grid* grid;
string point1s, point2s;
int colis = 0;
float zoom = 0.01;




inline bool Collision2Circe(glm::vec2 p1,glm::vec2 p2,float Radius1,float Radius2) {
	return glm::length(p2 - p1) > Radius1 + Radius2 ? true : false;
}
void PhysicProcess() {
	

	while (true)
	{
		if (Keys.w)
		{
			Forces += glm::vec2(0,0.001);
		}
		if (Keys.s)
		{
			Forces -= glm::vec2(0, 0.001);
		}
		if (Keys.a)
		{
			Forces -= glm::vec2(0.001,0);
		}
		if (Keys.d)
		{
			Forces += glm::vec2(0.001,0);
		}/////
		/*
		if (point.Position.x > 1)
		{
			Forces *= Wall_normal_left;
		
		    Colors =glm::vec3(1,0.5,0.2);
	//		cout << Forces.x << endl;
		}
		if (point.Position.x < -1)
		{
			Forces *= Wall_normal_left;
			
			Colors = glm::vec3(.8, .8, .8);

		//	cout << Forces.x << endl;
		}
		if (point.Position.y > 1)
		{
			Forces *= Wall_normal_up;
		
			Colors = glm::vec3(0.5, 0.5, 1);
	//		cout << Forces.x << endl;
		}
		if (point.Position.y < -1)
		{
			Forces *= Wall_normal_down;
			
			Colors = glm::vec3(0.2, 1, 0.2);
		//	cout << Forces.x << endl;
		}
		////
		if (point2.Position.x > 1)
		{
			Forces2 *= Wall_normal_left;

			
			//cout << Forces2.x << endl;
		}
		if (point2.Position.x < -1)
		{
			Forces2 *= Wall_normal_left;

			

		//	cout << Forces2.x << endl;
		}
		if (point2.Position.y > 1)
		{
			Forces2 *= Wall_normal_up;
		//	cout << Forces2.x << endl;
		}
		if (point2.Position.y < -1)
		{
			Forces2 *= Wall_normal_down;

			cout << Forces2.x << endl;
		}
		*/
		if (Keys.v)
		{
			zoom += 0.01;
		}	
		if (Keys.c)
		{
			zoom -= 0.01;
		}

		if (point1s == point2s) {
			if (!Collision2Circe(point.Position, point2.Position, 0.03, 0.03))
			{


				PrevForces2 = Forces2;
				Forces2 += Forces * glm::vec2(0.5, 0.5);
				Forces *= PrevForces2;


				//colis++;
				cout << "yes" << endl;
			}
		}
		point.AddForce(Forces);
		point2.AddForce(Forces2);

		
		Forces *= glm::vec2(0.9);
		Forces2 *= glm::vec2(0.99);


		
		A1 = A * lambda + (1 - lambda)*B;
		B1 = B * lambda + (1 - lambda)*C;
		C1 = C * lambda + (1 - lambda)*D;
		
		A2 = A1 * lambda + (1 - lambda)*B1;
		B2 = B1 * lambda + (1 - lambda)*C1;


		result3 = A2 * lambda + (1 - lambda)*B2;

		lambda += 0.005;

		if (lambda > 1)
		{
			lambda = 0;
		}

		Sleep(30);
	}

}


int main()
{
	grid = new Grid(glm::vec2(0, 0), 4);
	grid->depth = 6;
	grid->AddInGrid(*grid, grid->depth);
	std::thread* Keyboard = new thread(keyboard_time);
	std::thread* Physic = new thread(PhysicProcess);
	
	//grid->GetValueInPos(*grid,grid->depth,glm::vec2(1.1,1.1));

	GLFWwindow *window;
	if (!glfwInit())
	{
		return -1;
	}
	window = glfwCreateWindow(800, 600, "Program", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	



	//glClearColor((GLclampf)1, (GLclampf)1, (GLclampf)1, (GLclampf)0);
	glPointSize(20);
	glLineWidth(6);
	while (!glfwWindowShouldClose(window))
	{
		

		if (Keys.ESC)
		{
			
			delete Physic;
			delete Keyboard;
			return 0;
		}

		
		glLoadIdentity();

		glLoadMatrixf(glm::value_ptr(glm::lookAt(glm::vec3(point.Position.x,point.Position.y,zoom),glm::vec3(point.Position.x,point.Position.y,-1),glm::vec3(0,1,0))));

		glPushMatrix();

		

		glPushMatrix();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glColor3f(1, 1, 0.5);
		
		grid->GetValueInPos(*grid, grid->depth, point2.Position);
		point2s = grid->number;
		grid->ClearIndex();


		glColor3f(1, 0.5, 0.5);
		grid->GetValueInPos(*grid, grid->depth, point.Position);
		point1s = grid->number;
		grid->ClearIndex();
		glPopMatrix();
		if (point1s == point2s) {
			glBegin(GL_LINES);
			glColor3f(1, 0, 0);
			glVertex2fv(glm::value_ptr(point.Position));
			glVertex2fv(glm::value_ptr(point2.Position));
			glEnd();
		}
		glBegin(GL_POINTS);
		glColor3fv(glm::value_ptr(Colors));
		glVertex2fv(glm::value_ptr(point.Position));
		glEnd();
		glBegin(GL_POINTS);
		glColor3f(0,1,0);
		glVertex2fv(glm::value_ptr(point2.Position));
		glEnd();

		
		glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(A.x,A.y,0);
		glVertex3f(B.x,B.y,0);
		glColor3f(1, 0, 1);
		glVertex3f(B.x, B.y, 0);
		glVertex3f(C.x, C.y, 0);
		glColor3f(1, 1, 0);
		glVertex3f(C.x, C.y, 0);
		glVertex3f(D.x, D.y, 0);

		glColor3f(1, 0.5, 0);
		glVertex3f(A1.x, A1.y, 0);
		glVertex3f(B1.x, B1.y, 0);
		glColor3f(1, 0, 0.5);
		glVertex3f(B1.x, B1.y, 0);
		glVertex3f(C1.x, C1.y, 0);
		glColor3f(0, 0.5, 0);
		glVertex3f(A2.x, A2.y, 0);
		glVertex3f(B2.x, B2.y, 0);

		glEnd();
		glColor3f(0, 1, 0);
		glBegin(GL_POINTS);
		glVertex3f(result3.x, result3.y, 0);
		glEnd();

		glPopMatrix();
		

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwTerminate();
	
	
	return 0;
}
