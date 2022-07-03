#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;
#define PLUS_INF INT_MAX/2
enum VrtxStatus { UN_VISITED, VISITED, VRTX_NOT_FOUND }; // vertex ����
enum EdgeStatus {
	DISCOVERY, BACK, CROSS, EDGE_UN_VISITED, EDGE_VISITED,
	EDGE_NOT_FOUND
}; // edge ����
class Graph // ������� ����� �׷���
{
public:
	class Vertex; // vertex
	class Edge; // edge
	typedef std::list<Graph::Vertex> VrtxList; 
	typedef std::list<Graph::Edge> EdgeList;
	typedef std::list<Vertex>::iterator VrtxItor;
	typedef std::list<Edge>::iterator EdgeItor;
public:
	class Vertex // Graph::Vertex
	{
		friend ostream& operator<<(ostream& fout, Vertex v) // vertex ��� ������
		{
			fout << v.getName();
			return fout;
		}
	public:
		Vertex() : name(), ID(-1) {} // �⺻������
		Vertex(string n, int id) : name(n), ID(id) { } // ������
		Vertex(int id) : ID(id) {} // ������
		string getName() { return name; } // name �޾ƿ��� �Լ�
		void setName(string c_name) { name = c_name; } // name �����ϴ� �Լ�
		int getID() { return ID; } // ID�޾ƿ��� �Լ�
		void setID(int id) { ID = id; } // ID�����ϴ� �Լ�
		void setVrtxStatus(VrtxStatus vs) { vrtxStatus = vs; } // vrtxStatus�����ϴ� �Լ�
		VrtxStatus getvrtxStatus() { return vrtxStatus; } // vrtxStatus �޾ƿ��� �Լ�
		bool operator==(Vertex v) { return ((ID == v.getID()) && (name == v.getName())); } // �񱳿�����
		bool operator!=(Vertex v) { return ((ID != v.getID()) || (name != v.getName())); } // �񱳿�����
	private:
		string name; // �̸�
		int ID; // ID
		VrtxStatus vrtxStatus; // Vertex ����
	};
public:
	class Edge // Graph::Edge
	{
		friend ostream& operator<<(ostream& fout, Edge& e) // edge ��� ������ �����ε�
		{
			fout << "Edge(" << setw(2) << *e.getpVrtx_1() << ", " << setw(2)
				<< *e.getpVrtx_2() << ", " << setw(4) << e.getDistance() << ")";
			return fout;
		}
	public:
		Edge() : pVrtx_1(NULL), pVrtx_2(NULL), distance(PLUS_INF) {} // �⺻������
		Edge(Vertex& v1, Vertex& v2, int d) :distance(d), pVrtx_1(&v1), pVrtx_2(&v2), edgeStatus(EDGE_UN_VISITED) { } // ������
		void endVertices(VrtxList& vrtxLst) // ���������Լ�
		{
			vrtxLst.push_back(*pVrtx_1);
			vrtxLst.push_back(*pVrtx_2);
		}
		Vertex opposite(Vertex v) // ������ ����� v�� �ݴ��� ������ ��ȯ�ϴ� �Լ�
		{
			if (v == *pVrtx_1)
				return *pVrtx_2;
			else if (v == *pVrtx_2)
				return *pVrtx_1;
			else {
				//cout << "Error in opposite()" << endl;
				return Vertex(NULL);
			}
		}
		Vertex* getpVrtx_1() { return pVrtx_1; } // pVrtx_1 �о���� �Լ�
		Vertex* getpVrtx_2() { return pVrtx_2; } // pVrtx_2 �о���� �Լ�
		int getDistance() { return distance; } // �Ÿ� �о���� �Լ�
		void setpVrtx_1(Vertex* pV) { pVrtx_1 = pV; } // pVrtx_1 �����ϴ� �Լ�
		void setpVrtx_2(Vertex* pV) { pVrtx_2 = pV; } // pVrtx_2 �����ϴ� �Լ�
		void setDistance(int d) { distance = d; } // �Ÿ� �����ϴ� �Լ�
		bool operator!=(Edge e) {
			return ((pVrtx_1 != e.getpVrtx_1()) || (pVrtx_2 !=
				e.getpVrtx_2()));
		} // �񱳿�����
		bool operator==(Edge e) {
			return ((pVrtx_1 == e.getpVrtx_1()) && (pVrtx_2 ==
				e.getpVrtx_2()));
		} // �񱳿�����
		void setEdgeStatus(EdgeStatus es) { edgeStatus = es; } //  edgeStatus �����ϴ� �Լ�
		EdgeStatus getEdgeStatus() { return edgeStatus; } //  edgeStatus �о���� �Լ�
	private:
		Vertex* pVrtx_1;
		Vertex* pVrtx_2;
		int distance;
		EdgeStatus edgeStatus;
	}; 
public:
	Graph() : name(""), pVrtxArray(NULL), pAdjLstArray(NULL) {} // �⺻������
	Graph(string nm, int num_nodes) : name(nm), pVrtxArray(NULL), pAdjLstArray(NULL) // ������
	{
		num_vertices = num_nodes;
		pVrtxArray = new Graph::Vertex[num_vertices]; // pVrtxArray���� �� �ʱ�ȭ
		for (int i = 0; i < num_nodes; i++)
			pVrtxArray[i] = NULL;
		pAdjLstArray = new EdgeList[num_vertices]; // pAdjLstArray���� �� �ʱ�ȭ
		for (int i = 0; i < num_vertices; i++)
			pAdjLstArray[i].clear();
	}
	string getName() { return name; } // name �о���� �Լ�
	void vertices(VrtxList& vrtxLst); // vrtxLst�� �������� �����ϴ� �Լ�
	void edges(EdgeList&); // edge���� �����ϴ� �Լ�
	bool isAdjacentTo(Vertex v, Vertex w);
	void insertVertex(Vertex& v); // ���� �����ϴ� �Լ�
	void insertEdge(Edge& e); // ���� �����ϴ� �Լ�
	void eraseEdge(Edge e); // ���� ����� �Լ�
	void eraseVertex(Vertex v); // ���� �����ϴ� �Լ�
	int getNumVertices() { return num_vertices; } // �������� �޾ƿ��� �Լ�
	void incidentEdges(Vertex v, EdgeList& edges); // v�� ����� ������ edges�� ��� �Լ�
	Vertex* getpVrtxArray() { return pVrtxArray; } // pVrtxArray�о���� �Լ�
	EdgeList* getpAdjLstArray() { return pAdjLstArray; } // pAdjLstArray�о���� �Լ�
	void fprintGraph(ofstream& fout); // �׷��� ��� �Լ�
	bool isValidVrtxID(int vid); // ������ id�� ��ȿ���� Ȯ��
private:
	string name; // �̸�
	Vertex* pVrtxArray; // vertex �迭
	EdgeList* pAdjLstArray; // ��������Ʈ�� �迭
	int num_vertices; // ��������
};

void Graph::insertVertex(Vertex& v)
{
	int vID;
	vID = v.getID();
	if (pVrtxArray[vID] == NULL) {
		pVrtxArray[vID] = v;
	} // v�� pVrtxArray[vID]�� ����
}
void Graph::vertices(VrtxList& vrtxLst)
{
	vrtxLst.clear();
	for (int i = 0; i < getNumVertices(); i++)
		vrtxLst.push_back(pVrtxArray[i]);
} // ��� �������� vrtxLst�� ����
void Graph::insertEdge(Edge& e)
{
	Vertex vrtx_1, vrtx_2;
	Vertex* pVtx;
	int vID_1, vID_2;
	vrtx_1 = *e.getpVrtx_1(); vID_1 = vrtx_1.getID();
	vrtx_2 = *e.getpVrtx_2(); vID_2 = vrtx_2.getID();
	if (pVrtxArray[vID_1] == NULL) {
		pVrtxArray[vID_1] = vrtx_1;
	}
	if (pVrtxArray[vID_2] == NULL) {
		pVrtxArray[vID_2] = vrtx_2;
	}
	e.setpVrtx_1(&pVrtxArray[vID_1]);
	e.setpVrtx_2(&pVrtxArray[vID_2]);
	pAdjLstArray[vID_1].push_back(e);
} // edge�� �����ϴ� �Լ�
void Graph::edges(EdgeList& edges)
{
	EdgeItor eItor;
	Graph::Edge e;
	edges.clear();
	for (int i = 0; i < getNumVertices(); i++)
	{
		eItor = pAdjLstArray[i].begin();
		while (eItor != pAdjLstArray[i].end())
		{
			e = *eItor;
			edges.push_back(e);
			eItor++;
		}
	}
} // ��� edge���� edges�� �����ϴ� �Լ�
void Graph::incidentEdges(Vertex v, EdgeList& edgeLst)
{
	Graph::Edge e;
	EdgeItor eItor;
	int vID = v.getID();
	eItor = pAdjLstArray[vID].begin();
	while (eItor != pAdjLstArray[vID].end())
	{
		e = *eItor;
		edgeLst.push_back(e);
		eItor++;
	}
} // v�� ����� edge���� edgeLst�� ��� �Լ�
bool Graph::isValidVrtxID(int vid)
{
	if ((vid >= 0) && (vid < num_vertices))
		return true;
	else
	{
		cout << "Vertex ID (" << vid << ") is invalid for Graph (" << getName()
			<< ") with num_vertices (" << num_vertices << ")" << endl;
	}
} // vertex�� id�� ��ȿ���� Ȯ���ϴ� �Լ�
void Graph::fprintGraph(ofstream& fout)
{
	int i, j;
	EdgeItor eItor;
	Graph::Edge e;
	int numOutgoingEdges;
	fout << this->getName() << " with " << this->getNumVertices()
		<< " vertices has following connectivity :" << endl;
	for (i = 0; i < num_vertices; i++)
	{
		fout << " vertex (" << setw(3) << pVrtxArray[i].getName() << ") : ";
		numOutgoingEdges = pAdjLstArray[i].size();
		eItor = pAdjLstArray[i].begin();
		while (eItor != pAdjLstArray[i].end())
		{
			e = *eItor;
			fout << e << " ";
			eItor++;
		}
		fout << endl;
	}
} // �׷����� ����ϴ� �Լ�
#endif

