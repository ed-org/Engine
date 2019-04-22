#pragma once
#include "include/glm/vec2.hpp"
#include <vector>
#include <iostream>
#include "include/GLFW/glfw3.h"
#include <string>

using namespace std;



class PhysicPoint
{
public:
	PhysicPoint(glm::vec2 position) { this->Position = position; };
	~PhysicPoint();
	bool onCollisionWall();
    void AddForce(glm::vec2 Force);

	glm::vec2 PrevPosition;
	glm::vec2 Position;
	
	//float Radius;

};

struct Grid
{
	std::string number;
	int depth;
	float quads[4];
	glm::vec2 position;
	float size;
	Grid() {};
	Grid(glm::vec2 pos,float sizes) :Grid() {
		this->position = pos;
		this->size = sizes;
	};
	void quad() {
		quads[0] = this->position.x - this->size;
		quads[1] = this->position.x + this->size;

		quads[2] = this->position.y + this->size;
		quads[3] = this->position.y - this->size;
	}
	void AddGrid() {
		float sz = this->size*0.5;
		this->one = new Grid(glm::vec2(this->position.x - sz, this->position.y + sz),sz);
		this->two = new Grid(glm::vec2(this->position.x + sz, this->position.y + sz), sz);
		this->three = new Grid(glm::vec2(this->position.x - sz, this->position.y - sz), sz);
		this->four = new Grid(glm::vec2(this->position.x + sz, this->position.y - sz), sz);
	
	}
	void AddInGrid(Grid &grid,int num) {
	
		if (num < 1)
		{
			return;
		}
		grid.AddGrid();
		grid.quad();
		AddInGrid(*grid.one,num - 1);
		AddInGrid(*grid.two,num - 1);
		AddInGrid(*grid.three,num - 1);
		AddInGrid(*grid.four,num - 1);
	
	}
	void GetValueInPos(Grid& grid,int depths,glm::vec2 pos) {
		
		if (depths < 1)
		{
		//	cout << "no" << endl;
			return;
		}
		else {
			
			if (Col_in_quad(grid.one->quads, pos))
			{
				//cout << '1';
				DrawsQuads(grid.one->position,grid.one->size);
				number += '1';
				return GetValueInPos(*grid.one, depths - 1, pos);
			}
			if (Col_in_quad(grid.two->quads, pos))
			{
				//cout << '2';
				DrawsQuads(grid.two->position, grid.two->size);
				number += '2';
				return GetValueInPos(*grid.two, depths - 1, pos);
			}
			if (Col_in_quad(grid.three->quads, pos))
			{
				//cout << '3';
				DrawsQuads(grid.three->position, grid.three->size);
				number += '3';
				return GetValueInPos(*grid.three, depths - 1, pos);
			}
			if (Col_in_quad(grid.four->quads, pos))
			{
				//cout << '4';
				DrawsQuads(grid.four->position, grid.four->size);
				number += '4';
				return GetValueInPos(*grid.four, depths - 1, pos);
			}
		}
	}
	void ClearIndex() {
		number.clear();
	}
	void DrawsQuads(glm::vec2 pos, float size) {

		glBegin(GL_LINES);

		glVertex3f(pos.x + size, pos.y + size,0);
		glVertex3f(pos.x - size, pos.y + size,0);

		glVertex3f(pos.x + size, pos.y - size,0);
		glVertex3f(pos.x - size, pos.y - size,0);

		glVertex3f(pos.x - size, pos.y + size,0);
		glVertex3f(pos.x - size, pos.y - size,0);

		glVertex3f(pos.x + size, pos.y + size,0);
		glVertex3f(pos.x + size, pos.y - size,0);

		glEnd();

	}
	Grid* one;
	Grid* two;
	Grid* three;
	Grid* four;

private:
	bool Col_in_quad(float mass[4], glm::vec2& pos) {

		if ((pos.x >= mass[0] && pos.x <= mass[1]) && (pos.y <= mass[2] && pos.y >= mass[3]))
		{
			return true;
		}

		return false;
	}
};