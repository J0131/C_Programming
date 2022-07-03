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
enum BFS_PROCESS_STATUS { NOT_SELECTED, SELECTED }; // BFS ���� ����
class BreadthFirstSearch
{
protected:
	Graph& graph; // �׷���
	bool done;// �˻� �Ϸ� �÷���
	int** ppDistMtrx; // �Ÿ��� ��Ÿ���� 2�����迭
protected:
	void initialize(); // ����
	bool isValidvID(int vid) { return graph.isValidVrtxID(vid); } // ������ ID�� ��ȿ���� Ȯ��
	int getNumVertices() { return graph.getNumVertices(); } // ������ ���� �ҷ�����
public:
	BreadthFirstSearch(Graph& g) :graph(g) // ������
	{ 
		int num_nodes;
		num_nodes = g.getNumVertices(); // num_nodes�� �׷��� g�� ���������� ����
		// initialize DistMtrx
		for (int i = 0; i < num_nodes; i++)
			ppDistMtrx = new int* [num_nodes]; 
		for (int i = 0; i < num_nodes; i++)
			ppDistMtrx[i] = new int[num_nodes]; 
		for (int i = 0; i < num_nodes; i++) {
			for (int j = 0; j < num_nodes; j++)
			{
				ppDistMtrx[i][j] = PLUS_INF;
			} // �ʱ� ppDistMtrx�� ���ҵ��� ���Ѵ�� ����
		}
	}
	void initDistMtrx(); // �����鰣�� �Ÿ��� ��ķ� �����ϴ� �Լ�
	void fprintDistMtrx(ofstream& fout); // ����� ����ϴ� �Լ�
	void DijkstraShortestPathTree(ofstream& fout, Vertex& s, int* pPrev);
	void DijkstraShortestPath(ofstream& fout, Vertex& s, Vertex& t, VrtxList& path); // �׷������� �ִܰ�� ã�� �Լ�
	Graph& getGraph() { return graph; } // �׷����� ��ȯ�ϴ� �Լ�
	int** getppDistMtrx() { return ppDistMtrx; } //ppDistMtrx�� ��ȯ�ϴ� �Լ�
};
void BreadthFirstSearch::initialize() // �ʱ�ȭ �Լ�
{
	Vertex* pVrtx = getGraph().getpVrtxArray();
	VrtxList vrtxLst;
	graph.vertices(vrtxLst); // �׷����� �������� vrtxLs�� ���
	int num_vertices = graph.getNumVertices(); // �׷����� ���������� num_vertices�� ����
	for (int vID = 0; vID < num_vertices; vID++)
		pVrtx[vID].setVrtxStatus(UN_VISITED); // pVrtx[vID]�� ���¸� UN_VISITED�� �ʱ�ȭ
	EdgeList edges;
	graph.edges(edges); // edge���� edges�� �����
	for (EdgeItor pe = edges.begin(); pe != edges.end(); ++pe)
		pe->setEdgeStatus(EDGE_UN_VISITED); // edge���� EDGE_UN_VISITED���·� �ʱ�ȭ
}
void BreadthFirstSearch::initDistMtrx()
{
	int** ppDistMtrx;
	int* pLeaseCostMtrx;
	int num_nodes;
	Vertex* pVrtxArray; // vertex �迭
	EdgeList* pAdjLstArray; // edge����Ʈ�� �迭�� ��������Ʈ
	int curVID, vID;
	num_nodes = getNumVertices(); // ������ ����
	pVrtxArray = graph.getpVrtxArray(); // vertex �迭
	pAdjLstArray = graph.getpAdjLstArray(); // ��������Ʈ
	ppDistMtrx = getppDistMtrx(); // �������� �Ÿ��� ��Ÿ���� 2�����迭
	for (int i = 0; i < num_nodes; i++)
	{
		curVID = pVrtxArray[i].getID();
		EdgeItor pe = pAdjLstArray[curVID].begin();
		while (pe != pAdjLstArray[curVID].end())
		{
			vID = (*(*pe).getpVrtx_2()).getID();
			ppDistMtrx[curVID][vID] = (*pe).getDistance();
			pe++;
		} // ppDistMtrx�� ä���
		ppDistMtrx[curVID][curVID] = 0; // �ڽ��� �������� �ڱ��ڽ��� �������� �Ÿ��� 0���� ����
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
} // ��� �Լ�
void BreadthFirstSearch::DijkstraShortestPath(ofstream& fout, Vertex& start, Vertex& target,VrtxList& path)
{
	int** ppDistMtrx; // �������� �Ÿ� ���̺�
	int* pLeastCost; // ������� �ִܰ�� ID
	int num_nodes, num_selected; 
	int minID, minCost; // �ּ� ���� ID, �ּ� ����ġ
	BFS_PROCESS_STATUS* pBFS_Process_Stat; // ���� ����
	int* pPrev; // �������� ���� ���� ID�� ����Ű�� ����
	Vertex* pVrtxArray; // ������ �迭
	Vertex vrtx, * pPrevVrtx, v;
	Edge e; // EDGE
	int start_vID, target_vID, curVID, vID;
	EdgeList* pAdjLstArray; // ��������Ʈ
	pVrtxArray = graph.getpVrtxArray(); // vertex ����Ʈ
	pAdjLstArray = graph.getpAdjLstArray(); // ��������Ʈ 
	start_vID = start.getID(); // ���� vertex id
	target_vID = target.getID();// ������ vertex id
	num_nodes = getNumVertices();// vertex����
	ppDistMtrx = getppDistMtrx(); // �Ÿ����̺�
	pLeastCost = new int[num_nodes]; // �ִܰ�� ����Ǿ��ִ� �迭
	pPrev = new int[num_nodes]; // ���� ������ ID�� �����ϴ� �迭
	pBFS_Process_Stat = new BFS_PROCESS_STATUS[num_nodes]; // ������ ���¸� �����ϴ� �迭
	// initialize L(n) = w(start, n);
	for (int i = 0; i < num_nodes; i++)
	{
		pLeastCost[i] = ppDistMtrx[start_vID][i]; // pLeastCost�� �ʱ�ȭ
		pPrev[i] = start_vID; // pPrev[i]�� �ʱ⿡ start_vID���ʱ�ȭ
		pBFS_Process_Stat[i] = NOT_SELECTED; // pBFS_Process_Stat[i]�� �ʱ⿡ NOT_SELECTED�� �ʱ�ȭ
	}
	pBFS_Process_Stat[start_vID] = SELECTED; // ���������� SELECTED���·� ����
	num_selected = 1; // ������ �ϳ����õ�
	path.clear(); // path Ŭ����
	int round = 0; // round�� �ʱ⿡ 0���� ���� 
	int cost; // 
	string vName;
	fout << "Dijkstra::Least Cost from Vertex (" << start.getName() << ") at each round : " << endl;
	fout << "           |";
	for (int i = 0; i < num_nodes; i++)
	{
		vName = pVrtxArray[i].getName(); // �������� �̸��� �о� vName�� �����ϰ� ���
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
		round++; // round 1����
		fout << "round [" << setw(2) << round << "] |";
		minID = -1; // min_ID�� �ʱ⿡ -1�� ����
		minCost = PLUS_INF; // minCost�� �ʱ⿡ ���Ѵ�� ����
		for (int i = 0; i < num_nodes; i++) // find a node with LeastCost
		{
			if ((pLeastCost[i] < minCost) && (pBFS_Process_Stat[i] != SELECTED)) // pLeastCost[i] �� ���� minCost���� �۰� �ش������� ���õȰ��� �ƴ϶��
			{
				minID = i; // i�� minID�� ����
				minCost = pLeastCost[i]; // minCost�� pLeastCost[i]�� �ǰ��Ѵ�
			}
	    }
	    if (minID == -1) // ����� ������ ã����������
	    {
			fout << "Error in Dijkstra() -- found not connected vertex !!" << endl;
			break;
	    }
	    else
		{
			pBFS_Process_Stat[minID] = SELECTED; // pBFS_Process_Stat[minID]�� SELECTED ���·� ����
			num_selected++; // num_selected 1����
			if (minID == target_vID) // minID�� target_vID���
			{
				fout << endl << "reached to the target node ("<< pVrtxArray[minID].getName() << ") at Least Cost = " << minCost << endl;
				vID = minID;// vID�� minID�� �ǰ�����
				do {
					vrtx = pVrtxArray[vID]; // vID�� �ش��ϴ� vertex�� vrtx�θ����
					path.push_front(vrtx); // path�� vrtx�� �Ǿտ� �ִ´�
					vID = pPrev[vID]; // vID�� ������带 vID�� �������
				} while (vID != start_vID); // vID�� start_vID�� �ɶ����� �ݺ�
				vrtx = pVrtxArray[vID]; // ���� ����
				path.push_front(vrtx); // ���� ������ path�� ����
				break;
			}
		}
		/* Edge relaxation */
		int pLS, ppDistMtrx_i;
		for (int i = 0; i < num_nodes; i++)
		{
			pLS = pLeastCost[i]; // pLeastCost[i]�� pLS�� ����
			ppDistMtrx_i = ppDistMtrx[minID][i]; // ppDistMtrx[minID][i]�� ppDistMtrx_i�� ����
			if ((pBFS_Process_Stat[i] != SELECTED) && (pLeastCost[i] > (pLeastCost[minID] + ppDistMtrx[minID][i]))) // i�� ������ ���õ����ʾҰ� pLeastCost[i]�� pLeastCost[minID] + ppDistMtrx[minID][i]���� ũ�ٸ�
			{
				pPrev[i] = minID; // pPrev[i]�� ���� minID�� �ǰ��Ѵ�
				pLeastCost[i] = pLeastCost[minID] + ppDistMtrx[minID][i]; // pLeastCost[i]�� ����  pLeastCost[minID] + ppDistMtrx[minID][i]�� �ǰ��Ѵ�
			}
		}
		// print out the pLeastCost[] for debugging
		for (int i = 0; i < num_nodes; i++)
		{
			cost = pLeastCost[i]; // pLeastCost[i]�� ���� cost�� ����
			if (cost == PLUS_INF) // cost�� ���Ѵ���
				fout << "  +oo"; // ������ ���� �������� ���
			else
				fout << setw(5) << pLeastCost[i]; // cost�� ���Ѵ밡�ƴ϶�� pLeastCost[i]�� ���� ���
		}
		fout << " ==> selected vertex : " << pVrtxArray[minID] << endl;
	} // end while()
}  
#endif