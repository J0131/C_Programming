#ifndef BFS_DIJKSTRA_H
#define BFS_DIJKSTRA_H
#include "Graph.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <list>
#include <algorithm>
using namespace std;
typedef Graph::Vertex Vertex;
typedef Graph::Edge Edge;
typedef std::list<Graph::Vertex> VrtxList;
typedef std::list<Graph::Edge> EdgeList;
typedef std::list<Graph::Vertex>::iterator VrtxItor;
typedef std::list<Graph::Edge>::iterator EdgeItor;
enum BFS_PROCESS_STATUS { NOT_SELECTED, SELECTED }; // BFS 정점 상태
class BreadthFirstSearch
{
protected:
	Graph& graph; // 그래프
	bool done;// 검색 완료 플래그
	int** ppDistMtrx; // 거리를 나타내는 2차원배열
protected:
	void initialize(); // 시작
	bool isValidvID(int vid) { return graph.isValidVrtxID(vid); } // 정점이 ID가 유효한지 확인
	int getNumVertices() { return graph.getNumVertices(); } // 정점의 갯수 불러오기
public:
	BreadthFirstSearch(Graph& g) :graph(g) // 생성자
	{ 
		int num_nodes;
		num_nodes = g.getNumVertices(); // num_nodes를 그래프 g의 정점갯수로 설정
		// initialize DistMtrx
		for (int i = 0; i < num_nodes; i++)
			ppDistMtrx = new int* [num_nodes]; 
		for (int i = 0; i < num_nodes; i++)
			ppDistMtrx[i] = new int[num_nodes]; 
		for (int i = 0; i < num_nodes; i++) {
			for (int j = 0; j < num_nodes; j++)
			{
				ppDistMtrx[i][j] = PLUS_INF;
			} // 초기 ppDistMtrx의 원소들을 무한대로 설정
		}
	}
	void initDistMtrx(); // 정점들간의 거리를 행렬로 구성하는 함수
	void fprintDistMtrx(ofstream& fout); // 행렬을 출력하는 함수
	void DijkstraShortestPathTree(ofstream& fout, Vertex& s, int* pPrev);
	void DijkstraShortestPath(ofstream& fout, Vertex& s, Vertex& t, VrtxList& path); // 그래프에서 최단경로 찾는 함수
	Graph& getGraph() { return graph; } // 그래프를 반환하는 함수
	int** getppDistMtrx() { return ppDistMtrx; } //ppDistMtrx를 반환하는 함수
};
void BreadthFirstSearch::initialize() // 초기화 함수
{
	Vertex* pVrtx = getGraph().getpVrtxArray();
	VrtxList vrtxLst;
	graph.vertices(vrtxLst); // 그래프의 정점들을 vrtxLs에 담기
	int num_vertices = graph.getNumVertices(); // 그래프의 정점갯수를 num_vertices에 저장
	for (int vID = 0; vID < num_vertices; vID++)
		pVrtx[vID].setVrtxStatus(UN_VISITED); // pVrtx[vID]의 상태를 UN_VISITED로 초기화
	EdgeList edges;
	graph.edges(edges); // edge들을 edges에 담아줌
	for (EdgeItor pe = edges.begin(); pe != edges.end(); ++pe)
		pe->setEdgeStatus(EDGE_UN_VISITED); // edge들을 EDGE_UN_VISITED상태로 초기화
}
void BreadthFirstSearch::initDistMtrx()
{
	int** ppDistMtrx;
	int* pLeaseCostMtrx;
	int num_nodes;
	Vertex* pVrtxArray; // vertex 배열
	EdgeList* pAdjLstArray; // edge리스트의 배열인 인접리스트
	int curVID, vID;
	num_nodes = getNumVertices(); // 정점의 갯수
	pVrtxArray = graph.getpVrtxArray(); // vertex 배열
	pAdjLstArray = graph.getpAdjLstArray(); // 인접리스트
	ppDistMtrx = getppDistMtrx(); // 정점간의 거리를 나타내는 2차원배열
	for (int i = 0; i < num_nodes; i++)
	{
		curVID = pVrtxArray[i].getID();
		EdgeItor pe = pAdjLstArray[curVID].begin();
		while (pe != pAdjLstArray[curVID].end())
		{
			vID = (*(*pe).getpVrtx_2()).getID();
			ppDistMtrx[curVID][vID] = (*pe).getDistance();
			pe++;
		} // ppDistMtrx를 채우기
		ppDistMtrx[curVID][curVID] = 0; // 자신의 정점에서 자기자신의 정점까지 거리는 0으로 설정
	}
}
void BreadthFirstSearch::fprintDistMtrx(ofstream& fout)
{
	int** ppDistMtrx;
	Vertex* pVrtxArray;
	int num_nodes;
	int dist;
	int vID;
	string vName;
	pVrtxArray = graph.getpVrtxArray();
	num_nodes = getNumVertices();
	ppDistMtrx = getppDistMtrx();
	fout << "\nDistance Matrix of Graph (" << graph.getName() << ") :" << endl;
	fout << "      |";
	for (int i = 0; i < num_nodes; i++) {
		vName = pVrtxArray[i].getName();
		fout << setw(5) << vName;
	}
	fout << endl;
	fout << "-------+";
	for (int i = 0; i < num_nodes; i++) {
		fout << "-----";
	}
	fout << endl;
	for (int i = 0; i < num_nodes; i++) {
		vName = pVrtxArray[i].getName();
		fout << setw(5) << vName << " |";
		for (int j = 0; j < num_nodes; j++) {
			dist = ppDistMtrx[i][j];
			if (dist == PLUS_INF)
				fout << "  +oo";
			else
				fout << setw(5) << dist;
		}
		fout << endl;
	}
	fout << endl;
} // 출력 함수
void BreadthFirstSearch::DijkstraShortestPath(ofstream& fout, Vertex& start, Vertex& target,VrtxList& path)
{
	int** ppDistMtrx; // 정점간의 거리 테이블
	int* pLeastCost; // 현재까지 최단경로 ID
	int num_nodes, num_selected; 
	int minID, minCost; // 최소 정점 ID, 최소 가중치
	BFS_PROCESS_STATUS* pBFS_Process_Stat; // 정점 상태
	int* pPrev; // 현재경로의 이전 정점 ID를 가르키는 변수
	Vertex* pVrtxArray; // 정점의 배열
	Vertex vrtx, * pPrevVrtx, v;
	Edge e; // EDGE
	int start_vID, target_vID, curVID, vID;
	EdgeList* pAdjLstArray; // 인접리스트
	pVrtxArray = graph.getpVrtxArray(); // vertex 리스트
	pAdjLstArray = graph.getpAdjLstArray(); // 인접리스트 
	start_vID = start.getID(); // 시작 vertex id
	target_vID = target.getID();// 목적지 vertex id
	num_nodes = getNumVertices();// vertex갯수
	ppDistMtrx = getppDistMtrx(); // 거리테이블
	pLeastCost = new int[num_nodes]; // 최단경로 저장되어있는 배열
	pPrev = new int[num_nodes]; // 이전 정점의 ID를 저장하는 배열
	pBFS_Process_Stat = new BFS_PROCESS_STATUS[num_nodes]; // 정점의 상태를 저장하는 배열
	// initialize L(n) = w(start, n);
	for (int i = 0; i < num_nodes; i++)
	{
		pLeastCost[i] = ppDistMtrx[start_vID][i]; // pLeastCost를 초기화
		pPrev[i] = start_vID; // pPrev[i]를 초기에 start_vID로초기화
		pBFS_Process_Stat[i] = NOT_SELECTED; // pBFS_Process_Stat[i]를 초기에 NOT_SELECTED로 초기화
	}
	pBFS_Process_Stat[start_vID] = SELECTED; // 시작정점을 SELECTED상태로 변경
	num_selected = 1; // 정점이 하나선택됨
	path.clear(); // path 클리어
	int round = 0; // round를 초기에 0으로 설정 
	int cost; // 
	string vName;
	fout << "Dijkstra::Least Cost from Vertex (" << start.getName() << ") at each round : " << endl;
	fout << "           |";
	for (int i = 0; i < num_nodes; i++)
	{
		vName = pVrtxArray[i].getName(); // 정점들의 이름을 읽어 vName에 저장하고 출력
		fout << setw(5) << vName;
	}
	fout << endl;
	fout << "-----------+";
	for (int i = 0; i < num_nodes; i++)
	{
		fout << setw(5) << "-----";
	}
	fout << endl;
	while (num_selected < num_nodes)
	{
		round++; // round 1증가
		fout << "round [" << setw(2) << round << "] |";
		minID = -1; // min_ID는 초기에 -1로 설정
		minCost = PLUS_INF; // minCost는 초기에 무한대로 설정
		for (int i = 0; i < num_nodes; i++) // find a node with LeastCost
		{
			if ((pLeastCost[i] < minCost) && (pBFS_Process_Stat[i] != SELECTED)) // pLeastCost[i] 가 현재 minCost보다 작고 해당정점이 선택된것이 아니라면
			{
				minID = i; // i를 minID로 설정
				minCost = pLeastCost[i]; // minCost를 pLeastCost[i]가 되게한다
			}
	    }
	    if (minID == -1) // 연결된 정점을 찾지못했을때
	    {
			fout << "Error in Dijkstra() -- found not connected vertex !!" << endl;
			break;
	    }
	    else
		{
			pBFS_Process_Stat[minID] = SELECTED; // pBFS_Process_Stat[minID]를 SELECTED 상태로 변경
			num_selected++; // num_selected 1증가
			if (minID == target_vID) // minID가 target_vID라면
			{
				fout << endl << "reached to the target node ("<< pVrtxArray[minID].getName() << ") at Least Cost = " << minCost << endl;
				vID = minID;// vID를 minID게 되게해줌
				do {
					vrtx = pVrtxArray[vID]; // vID에 해당하는 vertex를 vrtx로만들고
					path.push_front(vrtx); // path에 vrtx를 맨앞에 넣는다
					vID = pPrev[vID]; // vID의 이전노드를 vID로 만들어줌
				} while (vID != start_vID); // vID가 start_vID가 될때까지 반복
				vrtx = pVrtxArray[vID]; // 시작 정점
				path.push_front(vrtx); // 시작 정점을 path에 저장
				break;
			}
		}
		/* Edge relaxation */
		int pLS, ppDistMtrx_i;
		for (int i = 0; i < num_nodes; i++)
		{
			pLS = pLeastCost[i]; // pLeastCost[i]를 pLS에 저장
			ppDistMtrx_i = ppDistMtrx[minID][i]; // ppDistMtrx[minID][i]를 ppDistMtrx_i에 저장
			if ((pBFS_Process_Stat[i] != SELECTED) && (pLeastCost[i] > (pLeastCost[minID] + ppDistMtrx[minID][i]))) // i의 정점이 선택되지않았고 pLeastCost[i]가 pLeastCost[minID] + ppDistMtrx[minID][i]보다 크다면
			{
				pPrev[i] = minID; // pPrev[i]의 값은 minID가 되게한다
				pLeastCost[i] = pLeastCost[minID] + ppDistMtrx[minID][i]; // pLeastCost[i]의 값은  pLeastCost[minID] + ppDistMtrx[minID][i]가 되게한다
			}
		}
		// print out the pLeastCost[] for debugging
		for (int i = 0; i < num_nodes; i++)
		{
			cost = pLeastCost[i]; // pLeastCost[i]의 값을 cost에 저장
			if (cost == PLUS_INF) // cost가 무한대라면
				fout << "  +oo"; // 다음과 같은 형식으로 출력
			else
				fout << setw(5) << pLeastCost[i]; // cost가 무한대가아니라면 pLeastCost[i]의 값을 출력
		}
		fout << " ==> selected vertex : " << pVrtxArray[minID] << endl;
	} // end while()
}  
#endif