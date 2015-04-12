#include "AStar.h"

#include "../level/Level.h"

AStar::AStar()
{
	m_sqrt2 = 1.4f;
}


AStar::~AStar()
{

}


vector<glm::ivec2> AStar::findPath( const Level &map, const glm::ivec2 &start, const glm::ivec2 &goal )
{
	m_prioQueue = new MinHeap<HeapNode>( map.getWidth() );
	m_prevNode = new glm::ivec2[ map.getSize() ];
	m_visited = new bool[ map.getSize() ];

	for (int i = 0; i < map.getSize(); i++ )
		m_visited[i] = false;

	bool pathFound = false;

	//inserts the start node into the prioQueue
	m_prioQueue->insert( HeapNode( start,
		0,
		m_calcDist( start, goal ) ) );

	//marks that the start node have been added to prioQueue
	m_visited[ start.x + start.y * map.getWidth() ] = true;

	while ( pathFound == false  && m_prioQueue->empty() == false )
	{
		//Gets the node with lowest value out of prioQueue 
		HeapNode node = m_prioQueue->getMin();

		//Saves the nodes position(index) in arrays, so it doesn't have to get recalculated several times later on
		int arrayPos = node.Pos.x + node.Pos.y * map.getWidth();

		if ( node.Pos.x == goal.x && node.Pos.y == goal.y )
		{
			//the goal has been reached and the loop will end
			pathFound = true;
		}
		else
		{
			//These 2 for loops, loop through all neighbours to 'node'
			for ( int x = -1; x <= 1; x++ )
			{
				for ( int y = -1; y <= 1; y++ )
				{
					//Checks if it's an adjacent node and not just the node itself, and checks if the adjacent node is walkable
					if (( x != 0 || y != 0) && map.isWalkable( node.Pos.x + x, node.Pos.y + y ) )
					{
						//Saves the array position(index) of the adjacent node
						int adjArrayPos = arrayPos + x + y * map.getWidth();

						//Checks if the node has previuosly been added to the prioQueue (no node is entered more then once)
						if ( m_visited[adjArrayPos] == false )
						{
							if  ( x == 1 && y == 1 && ( map.isWalkable( node.Pos.x + 1, node.Pos.y ) == false || map.isWalkable( node.Pos.x, node.Pos.y + 1 ) == false ) )
							{
								//Do nothing (cutting corner)
							}
							else if ( x == 1 && y == -1 && ( map.isWalkable( node.Pos.x + 1, node.Pos.y ) == false || map.isWalkable( node.Pos.x, node.Pos.y - 1 ) == false ) )
							{
								//Do nothing (cutting corner)
							}
							else if  ( x == -1 && y == 1 && ( map.isWalkable( node.Pos.x - 1, node.Pos.y ) == false || map.isWalkable( node.Pos.x, node.Pos.y + 1 ) == false ) )
							{
								//Do nothing (cutting corner)
							}
							else if ( x == -1 && y == -1 && ( map.isWalkable( node.Pos.x - 1, node.Pos.y ) == false || map.isWalkable( node.Pos.x, node.Pos.y - 1 ) == false ) )
							{
								//Do nothing (cutting corner)
							}
							else 
							{
								float deltaDist = 1;	//Cost to walk from node to the adjacent node

								if (x != 0 && y != 0)	//changes the cost to sqrt(2) if it's a diagonal movement
									deltaDist = m_sqrt2;

								//Adds the adjacent node to prioQueue
								m_prioQueue->insert( HeapNode(
									glm::ivec2( node.Pos.x + x, node.Pos.y + y ),
									node.DistTravelled + deltaDist,
									node.DistTravelled + deltaDist + m_calcDist( glm::ivec2( node.Pos.x + x, node.Pos.y + y ), goal ) ) );
							
								m_visited[adjArrayPos] = true;	//marks that the adjacent node has been added to prioQueue

								m_prevNode[adjArrayPos] = node.Pos;		//adds node as the previous node to the adjacent node
							}
						}
					}
				}
			}
		}
	}

	vector<glm::ivec2> path;
	glm::ivec2 temp;

	if ( pathFound == false )
	{
		cout << "No path found" << endl;
	}
	else
	{
		//Everything in this region ("pathStraightener") is code that straightens the path to make it shorter.
		//This beacuse the path doesn't always take the shortest route (caused by nodes not being added more then once to prioQueue)
		//COMMENT OUT THE ENTIRE "pathStraightener" REGION IF SPEED IS MORE IMPORTANT THEN THE PATH BEING SLIGHTLY LONGER THEN NECCESAIRY
		#pragma region pathStraightener

		//resets m_visited do it can be used later to 'draw' the path
		for (int i = 0; i < map.getSize(); i++ )
			m_visited[i] = false;

		glm::ivec2 min = goal;	//will store the path's lowest value on x and y
		glm::ivec2 max = goal;	//will store the path's highest value on x and y

		//'Draws' the last node on m-visited array, with the value true
		temp = goal;
		m_visited[ temp.x + temp.y * map.getWidth() ] = true;

		//Draws the rest of the path, and sets the value to 'min' and 'max
		while ( temp.x != start.x || temp.y != start.y )
		{
			temp = m_prevNode[temp.x + temp.y * map.getWidth()];	//goes backwards 1 step from 'temp' along the path
			m_visited[ temp.x + temp.y * map.getWidth() ] = true;	//'Draws' the node

			if ( temp.x < min.x )
				min.x = temp.x;
			if ( temp.x > max.x )
				max.x = temp.x;
			if ( temp.y < min.y )
				min.y = temp.y;
			if ( temp.y > max.y )
				max.y = temp.y;
		}

		temp = goal;
		bool loop;

		while ( temp.x != start.x || temp.y != start.y )
		{
			int arrayPos = temp.x + temp.y * map.getWidth();	//Saves the array position of 'temp'
			int x = m_prevNode[arrayPos].x - temp.x;	//Calculates difference in x-axis betwenn temp and it's previous node
			int y = m_prevNode[arrayPos].y - temp.y;	// ----------||----------  y-axis  ---------------||-----------------

			if ( x != 0 && y != 0 )	//if the movement is diagonal
			{
				int xPos = temp.x;
				int yPos = temp.y;
				int tempArrayPos = arrayPos;
				loop = true;

				//while the x-axis search haven't reached a nonwalkable node or is outside the path's min and max x
				while ( loop && xPos >= min.x && xPos <= max.x && map.isWalkable( xPos + x, yPos ) )
				{
					//moves in x-axis from temp
					xPos += x;
					tempArrayPos += x;

					if ( m_visited[tempArrayPos] )	//if the search has reached the path again
					{
						//Creates a shortcut (between temp and the found part of the path) that the final path will follow
						int iArrayPos = arrayPos;
						for (int i = temp.x; i != xPos; i += x )
						{
							m_prevNode[iArrayPos] = glm::ivec2( i + x, yPos );
							iArrayPos += x;
						}

						loop = false;
					}
				}

				xPos = temp.x;
				yPos = temp.y;
				tempArrayPos = arrayPos;

				//while the y-axis search haven't reached a nonwalkable node or is outside the path's min and max y
				//Doesn't loop if a shortcut was made in x-axis
				while ( loop && yPos >= min.y && yPos <= max.y && map.isWalkable( xPos, yPos + y )  )
				{
					yPos += y;
					tempArrayPos += y * map.getWidth();

					if ( m_visited[tempArrayPos] )	//if the search has reached the path
					{
						//Creates a shortcut (between temp and the found part of the path) that the final path will follow
						int iArrayPos = arrayPos;
						for (int i = temp.y; i != yPos; i += y )
						{
							m_prevNode[iArrayPos] = glm::ivec2( xPos, i + y );
							iArrayPos += y * map.getWidth();
						}

						loop = false;
					}
				}
			}

			temp = m_prevNode[arrayPos];	//moves one step ahead on the path, looking for more shortcuts to take next loop
		}

		#pragma endregion

		path.push_back( goal );
		temp = goal;

		//reconstructs the path from goal to start
		while ( temp.x != start.x || temp.y != start.y )
		{
			temp = m_prevNode[temp.x + temp.y * map.getWidth()];
			path.push_back( temp );
		}
	}

	delete m_prioQueue;
	delete [] m_visited;
	delete [] m_prevNode;

	return path;
}


//Calculates best case distance from pos to goal
float AStar::m_calcDist( const glm::ivec2 &pos, const glm::ivec2 &goal )
{
	float x = abs( pos.x - goal.x );
	float y = abs( pos.y - goal.y );

	if ( x < y )
		return x * m_sqrt2 + y - x;
	else
		return y * m_sqrt2 + x - y;
}
