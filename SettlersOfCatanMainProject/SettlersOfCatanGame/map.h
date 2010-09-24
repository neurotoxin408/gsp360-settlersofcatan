#pragma once

#include <iostream>
#include <ctime>
#include <windows.h>
#include "edge.h"
#include "node.h"
#include "center.h"

using namespace std;

class map
{
private:
public:
	Edge myEdges[144];
	Node myNodes[54];
	Center myCenters[19];
	map::map();
	Node * getNode(Node * population, int popCount, int ID);
	int getEdge(Edge * population, int popCount, int start, Node * from);
	int getEdgeFromCount(Edge * population, int popCount, Node * from);
	int randomHarbor(int resource[]);
	void setHarbor(Node* harbor);
	void initializeCenters(void);
};

////set cursor to location
//void gotoxy(int x, int y)
//{
//	COORD position = {x, y};
//	SetConsoleCursorPosition(
//		GetStdHandle(STD_OUTPUT_HANDLE),
//		position);
//}


//
//
//#pragma once
//
//#include <iostream>
//#include <ctime>
//#include <windows.h>
//
//#include "player.h"
//
//using namespace std;
//
////set cursor to location
//void gotoxy(int x, int y)
//{
//	COORD position = {x, y};
//	SetConsoleCursorPosition(
//		GetStdHandle(STD_OUTPUT_HANDLE),
//		position);
//}
//
//struct harborType;
//
//struct Edge;
//
//struct Node
//{
//	int ID, harborType, x, y, numOfEdges;
//	char icon;
//	Edge ** edges;
//
//	Node(int a_x, int a_y, int a_ID)
//	{
//		x = a_x * scale;
//		y = a_y * scale;
//		icon = '@';
//		edges = 0;
//		numOfEdges = 0;
//		ID = a_ID;
//	}
//
//	void print()
//	{
//		gotoxy(x, y);
//		cout << 'N' << ID;
//	}
//
//	void setEdgeCount(int a_numOfEdges)
//	{
//		if(edges)
//			delete edges;
//		numOfEdges = a_numOfEdges;
//		edges = new Edge * [numOfEdges];
//	}
//
//	void setEdge(int a_index, Edge * e)
//	{
//		edges[a_index] = e;
//	}
//};
//
//struct Edge
//{
//	Node * from;
//	Node * to;
//	//player * whoHasARoadHere;
//	Edge(){}
//	//constructor
//	Edge(Node * a_from, Node * a_to)
//	{
//		from = a_from;
//		to = a_to;
//	}
//
//	//prints edge to screen
//	void print()
//	{
//						//set midpoint
//		/*
//		int avgX = (from->x*2 + to->x)/3,
//			avgY = (from->y*2 + to->y)/3;
//			*/
//		int avgX = (from->x + to->x) / 2,
//			avgY = (from->y + to->y) / 2;
//
//		gotoxy(avgX, avgY);
//		cout << from->icon << to->icon;
//	}
//	void setEdgeFromAndTo(Node * a_from, Node * a_to)
//	{
//		this->from = a_from;
//		this->to = a_to;
//	}
//};
//
//struct Center
//{
//	int x, y, ID;
//	char resource;
//
//	Center(Node * from, Node * to, int a_ID)
//	{
//		x = (from->x + to->x) / 2;
//		y = (from->y + to->y) / 2;
//		ID = a_ID;
//	}
//	void print()
//	{
//		gotoxy(x, y);
//		cout << 'C' << ID;
//	}
//};
//
//Node * getNode(Node * population, int popCount, int ID)
//{
//	for(int i = 0; i < popCount; i++)
//		if(population[i].ID == ID)
//			return &population[i];
//	return 0;
//}
//
//int getEdge(Edge * population, int popCount, int start, Node * from)
//{
//	for(int i = start; i < popCount; ++i)
//		if(population[i].from == from)
//			return i;
//	return -1;
//}
//
//int getEdgeFromCount(Edge * population, int popCount, Node * from)
//{
//	int count =0;
//	for(int i = 0; i < popCount; ++i)
//		if(population[i].from == from)
//			count++;
//	return count;
//}
//
//int randomHarbor(int resource[])
//{
//	srand(0);
//	int num;
//	bool acceptable = false;
//
//	//determine if the harbor has already been placed
//	while(acceptable != true)
//	{
//		num = (rand() % 6);
//		if(num < 5)
//		{
//			if(resource[num] < 1)
//			{
//				acceptable = true;
//				resource[num]++;
//			}
//			else
//			{
//				acceptable = false;
//			}
//		}
//		else
//		{
//			if(resource[num] < 5)
//			{
//				resource[num]++;
//				acceptable = true;
//			}
//			else
//			{
//				acceptable = false;
//			}
//		}
//	}
//	return num;
//}
//
//void setHarbor(Node* harbor)
//{
//	int num, resource[6] = {0, 0, 0, 0, 0, 0};
//
//	for(int i = 0; i < 54; i++)
//	{
//		//places harbor on pre-determined nodes
//		switch(i)
//		{
//		case 2:
//			num = randomHarbor(resource);
//			harbor[i].harborType = num;
//			break;
//		case 3:
//			harbor[i].harborType = harbor[2].harborType;
//			break;
//		case 4:
//			num = randomHarbor(resource);
//			harbor[i].harborType = num;
//			break;
//		case 5:
//			harbor[i].harborType = harbor[4].harborType;
//			break;
//		case 6:
//			num = randomHarbor(resource);
//			harbor[i].harborType = num;
//			break;
//		case 12:
//			harbor[i].harborType = harbor[6].harborType;
//			break;
//		case 11:
//			num = randomHarbor(resource);
//			harbor[i].harborType = num;
//			break;
//		case 17:
//			harbor[i].harborType = harbor[11].harborType;
//			break;
//		case 24:
//			num = randomHarbor(resource);
//			harbor[i].harborType = num;
//			break;
//		case 30:
//			harbor[i].harborType = harbor[24].harborType;
//			break;
//		case 29:
//			num = randomHarbor(resource);
//			harbor[i].harborType = num;
//			break;
//		case 35:
//			harbor[i].harborType = harbor[29].harborType;
//			break;
//		case 43:
//			num = randomHarbor(resource);
//			harbor[i].harborType = num;
//			break;
//		case 49:
//			harbor[i].harborType = harbor[43].harborType;
//			break;
//		case 46:
//			num = randomHarbor(resource);
//			harbor[i].harborType = num;
//			break;
//		case 51:
//			harbor[i].harborType = harbor[46].harborType;
//			break;
//		case 52:
//			num = randomHarbor(resource);
//			harbor[i].harborType = num;
//			break;
//		case 53:
//			harbor[i].harborType = harbor[52].harborType;
//			break;
//		default:
//			harbor[i].harborType = NULL;
//		}
//	}
//}
//
//#define _EDGE(c,d) Edge(getNode(myNodes, count, c),\
//							getNode(myNodes, count, d))
//
//#define _CENTER(c,d,e) Center(getNode(myNodes, count, c),\
//							getNode(myNodes, count, d), e)
//// GLOBAL VARIABLES
//Node myNodes[] = 
//{
//					 		 Node(8,1,1),Node(10,1,2),
//				 Node(5,2,3),Node(7,2,4),Node(11,2,5),Node(13,2,6),
//	 Node(2,3,7),Node(4,3,8),Node(8,3,9),Node(10,3,10),Node(14,3,11),Node(16,3,12),
//	Node(1,4,13),Node(5,4,14),Node(7,4,15),Node(11,4,16),Node(13,4,17),Node(17,4,18),
//	 Node(2,5,19),Node(4,5,20),Node(8,5,21),Node(10,5,22),Node(14,5,23),Node(16,5,24),
//	Node(1,6,25),Node(5,6,26),Node(7,6,27),Node(11,6,28),Node(13,6,29),Node(17,6,30),
//	 Node(2,7,31),Node(4,7,32),Node(8,7,33),Node(10,7,34),Node(14,7,35),Node(16,7,36),
//	Node(1,8,37),Node(5,8,38),Node(7,8,39),Node(11,8,40),Node(13,8,41),Node(17,8,42),
//	 Node(2,9,43),Node(4,9,44),Node(8,9,45),Node(10,9,46),Node(14,9,47),Node(16,9,48),
//				 Node(5,10,49),Node(7,10,50),Node(11,10,51),Node(13,10,52),
//							 Node(8,11,53),Node(10,11,54),
//};
////find number of nodes
//const int count = sizeof(myNodes) / sizeof(Node);
//Center myCenters[] =
//{
//					_CENTER(4, 5, 1),
//			_CENTER(8, 9, 2),_CENTER(10, 11, 3),
//	_CENTER(13, 14, 4),_CENTER(15, 16, 5),_CENTER(17, 18, 6),
//			_CENTER(20, 21, 7),_CENTER(22, 23, 8),
//	_CENTER(25, 26, 9),_CENTER(27, 28, 10),_CENTER(29, 30, 11),
//			_CENTER(32, 33, 12),_CENTER(34, 35, 13),
//	_CENTER(37, 38, 14),_CENTER(39, 40, 15),_CENTER(41, 42, 16),
//			_CENTER(44, 45, 17),_CENTER(46, 47, 18),
//					_CENTER(50, 51, 19),
//};
//
//void graph()
//{ //22 + 32 = 54
//	//set node values
////	Node myNodes[] = 
////	{
////							 	 Node(8,1,1),Node(10,1,2),
////					 Node(5,2,3),Node(7,2,4),Node(11,2,5),Node(13,2,6),
////		 Node(2,3,7),Node(4,3,8),Node(8,3,9),Node(10,3,10),Node(14,3,11),Node(16,3,12),
////		Node(1,4,13),Node(5,4,14),Node(7,4,15),Node(11,4,16),Node(13,4,17),Node(17,4,18),
////		 Node(2,5,19),Node(4,5,20),Node(8,5,21),Node(10,5,22),Node(14,5,23),Node(16,5,24),
////		Node(1,6,25),Node(5,6,26),Node(7,6,27),Node(11,6,28),Node(13,6,29),Node(17,6,30),
////		 Node(2,7,31),Node(4,7,32),Node(8,7,33),Node(10,7,34),Node(14,7,35),Node(16,7,36),
////		Node(1,8,37),Node(5,8,38),Node(7,8,39),Node(11,8,40),Node(13,8,41),Node(17,8,42),
////		 Node(2,9,43),Node(4,9,44),Node(8,9,45),Node(10,9,46),Node(14,9,47),Node(16,9,48),
////					 Node(5,10,49),Node(7,10,50),Node(11,10,51),Node(13,10,52),
////								 Node(8,11,53),Node(10,11,54),
////	};
//
//	////find number of nodes
//	//const int count = sizeof(myNodes) / sizeof(Node);
//
//	//print each node
//	for(int i = 0; i < count; ++i)
//	{
//		myNodes[i].print();
//	}
//
//	//=================EDGEFINDER==============================================================
//
//	int amountEdges = 0;
//
//	Edge * tempEdges;
//
//	tempEdges = new Edge [1000];
//
//	Edge * myEdges;
//
//	for(int i = 0; i < count; ++i)
//	{
//		for(int j = 0; j < count; ++j)
//		{
//			if(j != i)
//			{
//
//				if ((myNodes[i].y / scale) == (myNodes[j].y / scale) ||
//					(myNodes[i].y / scale) + 1 == (myNodes[j].y / scale) ||
//					(myNodes[i].y / scale) - 1 == (myNodes[j].y / scale) )
//				{
//					if( (myNodes[i].x / scale) + 2 == (myNodes[j].x / scale) ||
//						(myNodes[i].x / scale) + 1 == (myNodes[j].x / scale) ||
//						(myNodes[i].x / scale) - 2 == (myNodes[j].x / scale) ||
//						(myNodes[i].x / scale) - 1 == (myNodes[j].x / scale) )
//					{
//						getNode(myNodes,count, i + 1)->numOfEdges++;
//						tempEdges[amountEdges].from = getNode(myNodes, count, i + 1);
//						tempEdges[amountEdges].to = getNode(myNodes, count, j + 1);
//						amountEdges++;
//					}
//				}
//			}
//		}
//	}
//
//	//cout << endl << "Amount of Edges Found: " << amountEdges << endl; // USED TO SEE HOW MANY EDGES TOTAL THERE ARE (STANDARD = 144 including overlap)
//
//	myEdges = new Edge [amountEdges];
//
//	const int eCount = amountEdges;
//
//	for (int i = 0; i < eCount; ++i)
//	{
//		myEdges[i].setEdgeFromAndTo(tempEdges[i].from, tempEdges[i].to);
//	}
//
//	delete tempEdges;
//
//	//=============================================END OF EDGEFINDER=================================
//
//	for(int i = 1; i < eCount; ++i)
//	{
//		myEdges[i].print();
//	}
//
//	setHarbor(myNodes);
//
//	/*
//	for (int i = 0; i < 24; i++)
//	{
//		//myEdges[i].setEdgeFromAndTo(getNode(myNodes, count, myStoredEdgeAs[i]), getNode(myNodes, count, myStoredEdgeBs[i]));
//		cout << myStoredEdgeAs[i] << " and " << myStoredEdgeBs[i] << endl;	
//	}
//	*/
//
//	//Center myCenters[] =
//	//{
//	//					_CENTER(4, 5, 1),
//	//			_CENTER(8, 9, 2),_CENTER(10, 11, 3),
//	//	_CENTER(13, 14, 4),_CENTER(15, 16, 5),_CENTER(17, 18, 6),
//	//			_CENTER(20, 21, 7),_CENTER(22, 23, 8),
//	//	_CENTER(25, 26, 9),_CENTER(27, 28, 10),_CENTER(29, 30, 11),
//	//			_CENTER(32, 33, 12),_CENTER(34, 35, 13),
//	//	_CENTER(37, 38, 14),_CENTER(39, 40, 15),_CENTER(41, 42, 16),
//	//			_CENTER(44, 45, 17),_CENTER(46, 47, 18),
//	//					_CENTER(50, 51, 19),
//	//};
//
//	const int Ccount = sizeof(myCenters) / sizeof(Center);
//
//
//	for(int i = 0; i < Ccount; ++i)
//	{
//		myCenters[i].print();
//	}
//
//	gotoxy(1,50);
//	cout << endl << endl;
//}
//
//
//
//	/* NON DELETION PATHFINDER
//	//=================EDGEFINDER==============================================================
//
//	int myStoredEdgeAs[1000], myStoredEdgeBs[1000], amountEdges = 0;
//
//	Edge * myEdges;
//
//	for(int i = 0; i < count; ++i)
//	{
//		for(int j = 0; j < count; ++j)
//		{
//			if(j != i)
//			{
//
//				if ((myNodes[i].y / scale) == (myNodes[j].y / scale) ||
//					(myNodes[i].y / scale) + 1 == (myNodes[j].y / scale) ||
//					(myNodes[i].y / scale) - 1 == (myNodes[j].y / scale) )
//				{
//					if( (myNodes[i].x / scale) + 2 == (myNodes[j].x / scale) ||
//						(myNodes[i].x / scale) + 1 == (myNodes[j].x / scale) ||
//						(myNodes[i].x / scale) - 2 == (myNodes[j].x / scale) ||
//						(myNodes[i].x / scale) - 1 == (myNodes[j].x / scale) )
//					{
//						getNode(myNodes,count, i + 1)->numOfEdges++;
//						myStoredEdgeAs[amountEdges] = i + 1;
//						myStoredEdgeBs[amountEdges] = j + 1;
//						amountEdges++;
//					}
//				}
//			}
//		}
//	}
//
//	cout << endl << "Amount of Edges Found: " << amountEdges << endl;
//
//	myEdges = new Edge [amountEdges];
//
//	const int eCount = amountEdges;
//
//	for (int i = 0; i < eCount; ++i)
//	{
//		myEdges[i].setEdgeFromAndTo(getNode(myNodes, count, myStoredEdgeAs[i]), getNode(myNodes, count, myStoredEdgeBs[i]));
//	}
//
//	//=============================================END OF EDGEFINDER=================================
//	*/
//
////void main()
////{
////	graph();
////}