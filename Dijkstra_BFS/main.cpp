/*****************************
* 파일목적 : 그래프를 넓이우선탐색방식으로 탐색하여 최단경로를 찾는 프로그램
* 작성자 : 최범준
* 2020.12.04
******************************/
#include <iostream>
#include <fstream>
#include <string> 
#include "Graph.h" 
#include "BFS_Dijkstra.h"
#define NUM_NODES 7
#define NUM_EDGES 26
#define GRAPH_SIMPLE_USA_7_NODES

using namespace std;
void main()
{
	ofstream fout; 
	fout.open("output.txt"); // 출력파일 설정
	if (fout.fail())
	{
		cout << "Failed to open output.txt file !!" << endl;
		exit;
	}

	Vertex v[NUM_NODES] = { Vertex("SF", 0), Vertex("LA", 1), Vertex("DLS", 2), Vertex("CHG", 3), Vertex("MIA", 4), Vertex("NY", 5), Vertex("BOS", 6) }; // Vertex배열 v초기화
	Graph::Edge edges[NUM_EDGES] = // Edge배열 edges선언
	{
	Edge(v[0], v[1], 337), Edge(v[1], v[0], 337),
	Edge(v[0], v[2], 1464), Edge(v[2], v[0], 1464),
	Edge(v[0], v[3], 1846), Edge(v[3], v[0], 1846),
	Edge(v[0], v[6], 2704), Edge(v[6], v[0], 2704),
	Edge(v[1], v[2], 1235), Edge(v[2], v[1], 1235),
	Edge(v[1], v[4], 2342), Edge(v[4], v[1], 2342),
	Edge(v[2], v[3], 802), Edge(v[3], v[2], 802),
	Edge(v[2], v[4], 1121), Edge(v[4], v[2], 1121),
	Edge(v[3], v[5], 740), Edge(v[5], v[3], 740),
	Edge(v[3], v[6], 867), Edge(v[6], v[3], 867),
	Edge(v[5], v[4], 1090), Edge(v[4], v[5], 1090),
	Edge(v[5], v[6], 187), Edge(v[6], v[5], 187),
	Edge(v[4], v[6], 1258), Edge(v[6], v[4], 1258),
	};
	int test_start = 1; // 시작정점을 vertex1으로 설정
	int test_end = 6; // 목적정점을 vertex6으로 설정
	Graph simpleGraph("GRAPH_SIMPLE_USA_7_NODES", NUM_NODES); // Graph simpleGraph생성
	fout << "Inserting vertices .." << endl;
	for (int i = 0; i < NUM_NODES; i++) {
		simpleGraph.insertVertex(v[i]); // simpleGraph에 vertex를 차례로 삽입
	}
	VrtxList vtxLst;
	simpleGraph.vertices(vtxLst); // vtxLst에 그래프의 vertex들을 담아줌
	int count = 0;
	fout << "Inserted vertices: ";
	for (VrtxItor vItor = vtxLst.begin(); vItor != vtxLst.end(); ++vItor)
	{
		fout << *vItor << ", ";
	}
	fout << endl;
	fout << "Inserting edges .." << endl;
	for (int i = 0; i < NUM_EDGES; i++)
	{
		simpleGraph.insertEdge(edges[i]); // simpleGraph에 edge를 차례로 삽입
	}
	fout << "Inserted edges: " << endl;
	count = 0;
	EdgeList egLst;
	simpleGraph.edges(egLst); // egLst에 그래프의 edge들을 담아줌
	for (EdgeItor p = egLst.begin(); p != egLst.end(); ++p)
	{
		count++;
		fout << *p << ", ";
		if (count % 5 == 0)
			fout << endl;
	} // 모든 edge출력
	fout << endl;
	fout << "Print out Graph based on Adjacency List .." << endl;
	simpleGraph.fprintGraph(fout); // 그래프 파일에 출력
	/* ==========================================*/
	BreadthFirstSearch bfsGraph(simpleGraph);
	fout << "\nTesting Breadth First Search with Dijkstra Algorithm" << endl;
	bfsGraph.initDistMtrx(); // 정점간의 거리를 나타내는 행렬 만들기
	bfsGraph.fprintDistMtrx(fout); // 정점간의 거리를 나타내는 행렬출력
	VrtxList path;
	path.clear();
	fout << "\nDijkstra Shortest Path Finding from " << v[test_start].getName() << " to " << v[test_end].getName() << " .... " << endl;
	bfsGraph.DijkstraShortestPath(fout, v[test_start], v[test_end], path); // test_start부터 test_end로 가는 최단거리경로를 path에 저장
	fout << "Path found by DijkstraShortestPath from " << v[test_start] << " to " << v[test_end] << " : ";
	for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
		fout << *vItor << " -> ";
	fout << endl;
	fout.close();
}