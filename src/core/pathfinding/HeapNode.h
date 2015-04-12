#include <glm/glm.hpp>
using namespace std;

struct HeapNode
{
	glm::ivec2 Pos;		//2D position of the 'node'

	float DistTravelled;	//how far from the start the algoritm has travelled to reach this node
	float TotalCost;		//DistTravelled + best case distance to goal
	
	HeapNode()
	{
	
	};

	HeapNode(glm::ivec2 pos, float distTravelled, float totalCost)
		: Pos(pos), DistTravelled(distTravelled) , TotalCost(totalCost)
	{
	
	};
	
	bool operator < ( const HeapNode &rhs ) const
	{
			return this->TotalCost < rhs.TotalCost;
	}
};