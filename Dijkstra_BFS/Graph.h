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
enum VrtxStatus { UN_VISITED, VISITED, VRTX_NOT_FOUND }; // vertex 상태
enum EdgeStatus {
	DISCOVERY, BACK, CROSS, EDGE_UN_VISITED, EDGE_VISITED,
	EDGE_NOT_FOUND
}; // edge 상태
class Graph // 인접행렬 기반의 그래프
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
		friend ostream& operator<<(ostream& fout, Vertex v) // vertex 출력 연산자
		{
			fout << v.getName();
			return fout;
		}
	public:
		Vertex() : name(), ID(-1) {} // 기본생성자
		Vertex(string n, int id) : name(n), ID(id) { } // 생성자
		Vertex(int id) : ID(id) {} // 생성자
		string getName() { return name; } // name 받아오는 함수
		void setName(string c_name) { name = c_name; } // name 설정하는 함수
		int getID() { return ID; } // ID받아오는 함수
		void setID(int id) { ID = id; } // ID설정하는 함수
		void setVrtxStatus(VrtxStatus vs) { vrtxStatus = vs; } // vrtxStatus설정하는 함수
		VrtxStatus getvrtxStatus() { return vrtxStatus; } // vrtxStatus 받아오는 함수
		bool operator==(Vertex v) { return ((ID == v.getID()) && (name == v.getName())); } // 비교연산자
		bool operator!=(Vertex v) { return ((ID != v.getID()) || (name != v.getName())); } // 비교연산자
	private:
		string name; // 이름
		int ID; // ID
		VrtxStatus vrtxStatus; // Vertex 상태
	};
public:
	class Edge // Graph::Edge
	{
		friend ostream& operator<<(ostream& fout, Edge& e) // edge 출력 연산자 오버로딩
		{
			fout << "Edge(" << setw(2) << *e.getpVrtx_1() << ", " << setw(2)
				<< *e.getpVrtx_2() << ", " << setw(4) << e.getDistance() << ")";
			return fout;
		}
	public:
		Edge() : pVrtx_1(NULL), pVrtx_2(NULL), distance(PLUS_INF) {} // 기본생성자
		Edge(Vertex& v1, Vertex& v2, int d) :distance(d), pVrtx_1(&v1), pVrtx_2(&v2), edgeStatus(EDGE_UN_VISITED) { } // 생성자
		void endVertices(VrtxList& vrtxLst) // 정점삽입함수
		{
			vrtxLst.push_back(*pVrtx_1);
			vrtxLst.push_back(*pVrtx_2);
		}
		Vertex opposite(Vertex v) // 간선이 연결된 v의 반대쪽 정점을 반환하는 함수
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
		Vertex* getpVrtx_1() { return pVrtx_1; } // pVrtx_1 읽어오는 함수
		Vertex* getpVrtx_2() { return pVrtx_2; } // pVrtx_2 읽어오는 함수
		int getDistance() { return distance; } // 거리 읽어오는 함수
		void setpVrtx_1(Vertex* pV) { pVrtx_1 = pV; } // pVrtx_1 설정하는 함수
		void setpVrtx_2(Vertex* pV) { pVrtx_2 = pV; } // pVrtx_2 설정하는 함수
		void setDistance(int d) { distance = d; } // 거리 설정하는 함수
		bool operator!=(Edge e) {
			return ((pVrtx_1 != e.getpVrtx_1()) || (pVrtx_2 !=
				e.getpVrtx_2()));
		} // 비교연산자
		bool operator==(Edge e) {
			return ((pVrtx_1 == e.getpVrtx_1()) && (pVrtx_2 ==
				e.getpVrtx_2()));
		} // 비교연산자
		void setEdgeStatus(EdgeStatus es) { edgeStatus = es; } //  edgeStatus 설정하는 함수
		EdgeStatus getEdgeStatus() { return edgeStatus; } //  edgeStatus 읽어오는 함수
	private:
		Vertex* pVrtx_1;
		Vertex* pVrtx_2;
		int distance;
		EdgeStatus edgeStatus;
	}; 
public:
	Graph() : name(""), pVrtxArray(NULL), pAdjLstArray(NULL) {} // 기본생성자
	Graph(string nm, int num_nodes) : name(nm), pVrtxArray(NULL), pAdjLstArray(NULL) // 생성자
	{
		num_vertices = num_nodes;
		pVrtxArray = new Graph::Vertex[num_vertices]; // pVrtxArray생성 및 초기화
		for (int i = 0; i < num_nodes; i++)
			pVrtxArray[i] = NULL;
		pAdjLstArray = new EdgeList[num_vertices]; // pAdjLstArray생성 및 초기화
		for (int i = 0; i < num_vertices; i++)
			pAdjLstArray[i].clear();
	}
	string getName() { return name; } // name 읽어오는 함수
	void vertices(VrtxList& vrtxLst); // vrtxLst에 정점들을 삽입하는 함수
	void edges(EdgeList&); // edge들을 삽입하는 함수
	bool isAdjacentTo(Vertex v, Vertex w);
	void insertVertex(Vertex& v); // 정점 삽입하는 함수
	void insertEdge(Edge& e); // 간선 삽입하는 함수
	void eraseEdge(Edge e); // 간선 지우는 함수
	void eraseVertex(Vertex v); // 정점 삭제하는 함수
	int getNumVertices() { return num_vertices; } // 정점갯수 받아오는 함수
	void incidentEdges(Vertex v, EdgeList& edges); // v에 연결된 간선을 edges에 담는 함수
	Vertex* getpVrtxArray() { return pVrtxArray; } // pVrtxArray읽어오는 함수
	EdgeList* getpAdjLstArray() { return pAdjLstArray; } // pAdjLstArray읽어오는 함수
	void fprintGraph(ofstream& fout); // 그래프 출력 함수
	bool isValidVrtxID(int vid); // 정점의 id가 유효한지 확인
private:
	string name; // 이름
	Vertex* pVrtxArray; // vertex 배열
	EdgeList* pAdjLstArray; // 간선리스트의 배열
	int num_vertices; // 정점갯수
};

void Graph::insertVertex(Vertex& v)
{
	int vID;
	vID = v.getID();
	if (pVrtxArray[vID] == NULL) {
		pVrtxArray[vID] = v;
	} // v를 pVrtxArray[vID]에 삽입
}
void Graph::vertices(VrtxList& vrtxLst)
{
	vrtxLst.clear();
	for (int i = 0; i < getNumVertices(); i++)
		vrtxLst.push_back(pVrtxArray[i]);
} // 모든 정점들을 vrtxLst에 삽입
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
} // edge를 삽입하는 함수
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
} // 모든 edge들을 edges에 삽입하는 함수
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
} // v에 연결된 edge들을 edgeLst에 담는 함수
bool Graph::isValidVrtxID(int vid)
{
	if ((vid >= 0) && (vid < num_vertices))
		return true;
	else
	{
		cout << "Vertex ID (" << vid << ") is invalid for Graph (" << getName()
			<< ") with num_vertices (" << num_vertices << ")" << endl;
	}
} // vertex의 id가 유효한지 확인하는 함수
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
} // 그래프를 출력하는 함수
#endif

