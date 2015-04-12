#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "MinHeap.h"
#include "HeapNode.h"
using namespace std;

class Level;

class AStar
{
private:
	float m_sqrt2;	//holds the value of the square root of 2
	MinHeap<HeapNode> * m_prioQueue;	//Min heap where the 'node' along the path will be added 
	glm::ivec2 * m_prevNode;	//Array used to reconstruct the path the algoritm took
	bool * m_visited;		//Array used to check if a node has already been added to prioQueue
	float m_calcDist( const glm::ivec2 &pos, const glm::ivec2 &goal );		//Function that calculates and returns the best case distance between 'pos' and 'goal'

public:
	AStar();
	~AStar();
	//Function that calculates a path between 'start' and 'goal' on 'map', returns the path if found
	vector<glm::ivec2> findPath( const Level &map, const glm::ivec2 &start, const glm::ivec2 &goal  );
};

