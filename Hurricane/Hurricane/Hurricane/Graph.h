//*******************************//
//
// Name:			Graph.h
// Description:		
//
// Author:			JP  Amore
// Created:			Mar 14, 2016
// Last updated:	Nov 07, 2016
//
//*******************************//

#ifndef GRAPHS_H
#define GRAPHS_H

#include "Macro.h"

using namespace std;

template<typename T>
class Graph
{
	template<typename T>
	class GraphVertex
	{
		friend Graph;

	public:
		GraphVertex(T node) : m_node(node) {}

		T GetNode() {
			return m_node;
		}

	private:
		T m_node;
	};

public:
	Graph(hINT numVerts) : m_maxVerts(numVerts), m_adjMatrix(NULL)
	{
		assert(numVerts > 0);

		m_vertices.reserve(m_maxVerts);

		m_adjMatrix = new hCHAR*[m_maxVerts];
		assert(m_adjMatrix != NULL);

		m_vertVisits = new hCHAR[m_maxVerts];
		assert(m_vertVisits != NULL);

		memset(m_vertVisits, 0, m_maxVerts);

		for (hINT i = 0; i < m_maxVerts; i++)
		{
			m_adjMatrix[i] = new hCHAR[m_maxVerts];

			assert(m_adjMatrix[i] != NULL);

			memset(m_adjMatrix[i], 0, m_maxVerts);
		}
	}

	~Graph()
	{
		if (m_adjMatrix != NULL)
		{
			for (hINT i = 0; i < m_maxVerts; i++)
			{
				if (m_adjMatrix[i] != NULL)
				{
					delete[] m_adjMatrix[i];

					m_adjMatrix[i] = NULL;
				}
			}

			delete[] m_adjMatrix;

			m_adjMatrix = NULL;
		}

		if (m_vertVisits != NULL)
		{
			delete[] m_vertVisits;

			m_vertVisits = NULL;
		}
	}

	hBOOL push(T node)
	{
		if ((hINT)m_vertices.size() >= m_maxVerts)
			return false;

		m_vertices.push_back(GraphVertex<T>(node));

		return true;
	}


	void attachEdge(hINT index1, hINT index2)
	{
		assert(m_adjMatrix != NULL);

		m_adjMatrix[index1][index2] = 1;
		m_adjMatrix[index2][index1] = 1;
	}

	void attachDirectedEdge(hINT index1, hINT index2)
	{
		assert(m_adjMatrix != NULL);

		m_adjMatrix[index1][index2] = 1;
	}

	hINT getNextUnvisitedVertex(hINT index)
	{
		assert(m_adjMatrix != NULL);
		assert(m_vertVisits != NULL);

		for (hINT i = 0; i < (hINT)m_vertices.size(); i++)
			if (m_adjMatrix[index][i] == 1 && m_vertVisits[i] == 0)
				return i;

		return -1;
	}

	//Depth First Traversal
	hBOOL DepthFirstSearch(hINT startIndex, hINT endIndex)
	{
		//Assert whether the adjacency matrix exists and is not NULL
		assert(m_adjMatrix != NULL);
		//Assert whether the vertices visited exists and is not NULL
		assert(m_vertVisits != NULL);

		//Begin the traversal at the starting index
		m_vertVisits[startIndex] = 1;

		//PrhINT the value at the start index
		cout << m_vertices[startIndex].GetNode();

		//Declare a stack for searching
		stack<hINT> searchStack;
		//Declare and initialize a starting vertex pohINT to 0
		hINT startVertexPohINT = 0;

		//Push start index hINTo stack
		searchStack.push(startIndex);

		//Loop while stack is not empty
		while (!searchStack.empty()) {
			//Assign end pohINT vertex to the next unvisited vertex - use getNextUnvisitedVertex method
			startVertexPohINT = getNextUnvisitedVertex(searchStack.top());

			//If vertex is -1 pop from stack
			// -1 means that the node has already been visited
			if (startVertexPohINT == -1) {
				searchStack.pop();
			}
			//If vertex is not -1
			else {
				m_vertVisits[startVertexPohINT] = 1;

				//PrhINT the value of the current node visited
				cout << m_vertices[startVertexPohINT].GetNode();

				//Push vertex index hINTo stack
				searchStack.push(startVertexPohINT);
			}

			//If vertex reach end pohINT
			if (startVertexPohINT == endIndex) {

				// Use memset to reset vertices visited to NULL
				// 0 is the same thing as NULL
				memset(m_vertVisits, 0, m_maxVerts);

				//Return true
				return true;
			}
		}


		//Use memset to reset vertices visited to NULL
		memset(m_vertVisits, 0, m_maxVerts);

		//Return false
		return false;
	}

	hBOOL BreadthFirstSearch(hINT startIndex, hINT endIndex)
	{
		assert(m_adjMatrix != NULL);
		assert(m_vertVisits != NULL);

		m_vertVisits[startIndex] = 1;

		cout << m_vertices[startIndex].GetNode();

		queue<hINT> searchQueue;
		hINT vert1 = 0, vert2 = 0;

		searchQueue.push(startIndex);

		while (searchQueue.empty() != true)
		{
			vert1 = searchQueue.front();
			searchQueue.pop();

			if (vert1 == endIndex)
			{
				memset(m_vertVisits, 0, m_maxVerts);
				return true;
			}

			while ((vert2 = getNextUnvisitedVertex(vert1)) != -1)
			{
				m_vertVisits[vert2] = 1;

				cout << m_vertices[vert2].GetNode();

				searchQueue.push(vert2);
			}
		}

		memset(m_vertVisits, 0, m_maxVerts);

		return false;
	}

	//Topological Sort
	hBOOL topologicalSort(list<T> &output)
	{
		//Flag to record cycles
		hBOOL hasCycles = false;

		//Temp vector of vertices
		vector<GraphVertex<T> > tempVerts(m_vertices);

		//Temp size of vertices
		hINT tempSize = (hINT)tempVerts.size();

		//Array of characters to record vertex labels
		hCHAR **tempAdjMat = new hCHAR*[m_maxVerts];

		//Assert if temp is null
		assert(tempAdjMat != NULL);

		//Iterate through all vertices
		for (hINT i = 0; i < m_maxVerts; i++)
		{
			//Create new character
			tempAdjMat[i] = new hCHAR[m_maxVerts];

			//Assert if null
			assert(tempAdjMat[i] != NULL);

			//Copy memory from adjacency matrix to temp
			memcpy(tempAdjMat[i], m_adjMatrix[i], m_maxVerts);
		}

		//If size greater than 0
		while (tempSize > 0)
		{
			//Fine vertices with no successor
			hINT v = GetVertNoSuccessor(tempAdjMat, tempSize);

			//If no cycles exit
			if (v == -1)
			{
				hasCycles = true;
				break;
			}

			//Store node in output
			output.push_front(tempVerts[v].GetNode());

			//If successor cannot be found, delete vertex from list and matrix
			if (v != (tempSize - 1))
			{
				//Erase all vertices from from temp
				tempVerts.erase(tempVerts.begin() + v);

				//Delete from rows in adjacency matrix
				for (hINT row = v; row < tempSize - 1; row++)
				{
					for (hINT c = 0; c < tempSize; c++)
					{
						tempAdjMat[row][c] = tempAdjMat[row + 1][c];
					}
				}

				//Delete from columns in adjacency matrix
				for (hINT col = v; col < tempSize - 1; col++)
				{
					for (hINT r = 0; r < tempSize; r++)
					{
						tempAdjMat[r][col] = tempAdjMat[r][col + 1];
					}
				}
			}

			//Decrease size
			tempSize--;
		}

		//If temp adjacency matrix is null delete
		if (tempAdjMat != NULL)
		{
			for (hINT i = 0; i < m_maxVerts; i++)
			{
				if (tempAdjMat[i] != NULL)
				{
					delete[] tempAdjMat[i];
					tempAdjMat[i] = NULL;
				}
			}

			delete[] tempAdjMat;
			tempAdjMat = NULL;
		}

		//Return whether has cycles
		return !hasCycles;
	}
private:
	vector<GraphVertex<T>> m_vertices;
	hINT m_maxVerts;

	hCHAR **m_adjMatrix;
	hCHAR *m_vertVisits;

	//Find the vetices with no successors
	hINT GetVertNoSuccessor(hCHAR **adjMat, hINT size)
	{
		//Set flag to determine whether successor exists
		hBOOL edgeFound = false;

		//Traverse all edges and find vertices with no successor
		//End traversal when found
		//Traverse Rows
		for (hINT row = 0; row < size; row++)
		{
			//Set flag to false
			edgeFound = false;

			//Traverse Columns
			for (hINT col = 0; col < size; col++)
			{
				//If cell is not null
				//Edge is found
				if (adjMat[row][col] != 0)
				{
					edgeFound = true;
					break;
				}
			}

			//If edge not found
			//Return row
			if (edgeFound == false)
				return row;
		}

		//Return
		return -1;
	}
};

#endif