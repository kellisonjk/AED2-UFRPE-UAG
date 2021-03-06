/*
* Graph.cpp 
*
*  Created on: May 27, 2015
*      - Author: Kellison
*		- Descri��o:
*			Implementa��o de um Grafo.
*		- Detalhes:
*		  - Ser�o consideradas, na matriz de adjac�ncias, arestas n�o existentes aquelas que possuem custo INF
*		  - A implementa��o atual considera arestas duplas, ou seja:
*			->  (a,b, custo) != (b,a, custo)
*		   UPDATE: o grafo n�o est� considerando grafo direcional, apenas arestas simples ser�o consideradas, assim 
*				   sendo:  (a,b, custo) == (b,a, custo)
*		- Observa��o:
*			Por padr�o, o grafo � configurado como n�o direcional, assim, quando adiciona-se uma aresta
*			a mesma ganhar� um aresta simetrica. Para mudar essa configura��o, o grafo deve ser configurado 
*			para "true", usando o m�todo "setDirecionado(bool)" da classe Graph.
*
*/

#include "Graph.hpp"

template class Graph<int>;
using namespace std;


// Inicializadores da classe
template <class TVertex>
Graph<TVertex>::Graph(){}

template <class TVertex>
Graph<TVertex>::Graph(string f_op){
	// Para o arquivo "base de dados" das arestas
	this->openFile(f_op);
	this->edgeNumber = 0;
	this->direcionado = false;
}

template <class TVertex>
Graph<TVertex>::Graph(string f_op, vector<TVertex> vertex){
	// Para o arquivo "base de dados" das arestas
	this->openFile(f_op); 

	this->edgeNumber = 0;

	this->vertex = vertex;
	this->adjacencyMatriz.resize(vertex.size());
	for (int i = 0; i < (int) vertex.size(); i++){
		this->adjacencyMatriz[i].resize(vertex.size(),INF);
	}

	this->direcionado = false;
}

template <class TVertex>
TVertex Graph<TVertex>::getVertex(int ind){
	return this->vertex[ind];
}

template <class TVertex>
vector<TVertex> Graph<TVertex>::getVertex(){
	return this->vertex;
}

template <class TVertex>
vector< vector<TVertex> > Graph<TVertex>::getAdjacencyMatriz(){
	return this->adjacencyMatriz;
}

// Verifica qual a posi��o do v�rtice dentro do vetor de v�rtices
template <class TVertex>
int Graph<TVertex>::getIndex(TVertex vertex){
	for (int i = 0; i < (int) this->vertex.size(); i++){
		if (this->vertex.at(i) == vertex)
			return i;
	}

	throw out_of_range(" Vertice nao existente.");
}


// Retorna a aresta que est� entre u e v
template <class TVertex>
Edge<TVertex> Graph<TVertex>::getEdge(TVertex u, TVertex v)
{
	try{

		int ind_u = this->getIndex(u);
		int ind_v = this->getIndex(v);

		Edge<TVertex> result(this->vertex[ind_u], this->vertex[ind_v], this->adjacencyMatriz[ind_u][ind_v]);

		return result;
	}
	catch (const out_of_range& oor){
		cerr << endl << " Vertices: " << u << " e " << v << endl;
		cerr << " Aresta nao existente." << endl << endl;
	}
}

// Adiciona uma nova aresta, com seu custo, ao grafo
template <class TVertex>
void Graph<TVertex>::setEdge(TVertex u, TVertex v, double cost){

	try{

		int ind_u = this->getIndex(u);
		int ind_v = this->getIndex(v);

		this->adjacencyMatriz[ind_u][ind_v] = (double)cost;
		if (!(this->direcionado))
			this->adjacencyMatriz[ind_v][ind_u] = (double)cost;

		this->saveFile(ind_u, ind_v, cost);
		this->edgeNumber++;

	}
	catch (const out_of_range& oor){
		cerr << endl << " Vertices: " << u << " e " << v << endl;
		cerr << " Out of range error: " << oor.what() << endl << endl;
	}
}

// Retorna o n�mero de vetores
template <class TVertex>
int Graph<TVertex>::getNumberVertex(){
	return this->vertex.size();
}

// Retorna o n�mero de arestas salvas
template <class TVertex>
int Graph<TVertex>::getNumberEdge(){
	return this->edgeNumber;
}

// Salva uma aresta no arquivo
template <class TVertex>
void Graph<TVertex>::saveFile(TVertex u, TVertex v, double cost){
	this->outfile << u << "," << v << "," << cost << endl;
}


// Abre o arquivo que armazenar� as aresta/custos do grafo em modo de edi��o ou escrita
// O caminho para este arquivo est� setado na constate FILEOUTPUT
template <class TVertex>
void Graph<TVertex>::openFile(string f_op){
	// Caso a implementa��o seja definida como new, abre o arquivo como escrita
	if (f_op == "new"){
		cout << "NEW" << endl;
		this->outfile.open(FILEOUTPUT, ios::out | ios::trunc);
		this->outfile << "Node1,Node2,Cost" << endl;
	}
	// Abre como edi��o
	else{
		cout << "APP" << endl;
		this->outfile.open(FILEOUTPUT, ios::app);
	}
}

// Obt�m todos as arestas adjacentes ao vertice u, e as salva em um vetor (vector)
template <class TVertex>
vector< Edge<TVertex> > Graph<TVertex>::getAdjacents(TVertex u){
	try{
		vector< Edge<TVertex> > adj;
		int index = this->getIndex(u);

		for (int i = 0; i < (int) this->vertex.size(); i++){
			// == 0 implica em n�o exist�ncia da aresta
			if (this->adjacencyMatriz[index][i] != INF)
				adj.push_back(Edge<TVertex>(i, index, this->adjacencyMatriz[index][i]));
		}

		return adj;
	}
	catch (const out_of_range& oor){
		cerr << endl << " Vertex: " << u << endl;
		cerr << " Out of range error: " << oor.what() << endl << endl;
	}
}

// Retorna todas as arestas do grafos, de modo que desconsidera as duplicadas, considerando
// apenas os elementos da matriz abaixo da diagonal principal (ja que � simetrica)
template <class TVertex>
vector< Edge<TVertex> > Graph<TVertex>::getAllEdges(){
	int a;
	try{
		if (this->edgeNumber == 0)
			throw out_of_range(" O grafo nao possui nenhuma aresta.");

		vector< Edge<TVertex> > adj;

		for (int i = 0; i < (int) this->vertex.size(); i++){
			a = i;
			
			//vector< Edge<TVertex> > aux = this->getAdjacents(this->vertex.at(i));
			if (this->direcionado)
				a = 0;

			for (int j = a; j < (int) this->vertex.size(); j++){
				if (this->adjacencyMatriz[i][j] != INF){
					adj.push_back(Edge<TVertex>(this->vertex.at(i), this->vertex.at(j), this->adjacencyMatriz[i][j]));
				}
			}
		}

		return adj;
	}
	catch (const out_of_range& oor){
		cerr << " Out of range error: " << oor.what() << endl << endl;
	}
}


template <class TVertex>
void Graph<TVertex>::showMatriz(){
	cout << "  IND ";
	printf("%c", 186);
	for (int i = 0; i < (int) this->vertex.size(); i++)
	{
		if (i < 10)
			cout << "   " << i;
		else
			cout << "  " << i;
	}


	printf("\n %c%c%c%c%c%c", 205, 205, 205, 205, 205, 206);
	for (int i = 0; i < (int) this->vertex.size(); i++)
		printf("%c%c%c%c", 205, 205, 205, 205);

	cout << endl;

	for (int i = 0; i < (int) this->vertex.size(); i++)
	{
		if (i < 10)
			cout << "   " << i;
		else
			cout << "  " << i;

		printf("  %c", 186);
		for (int j = 0; j < (int) this->vertex.size(); j++)
		{
			if ((this->adjacencyMatriz[i][j] < 10) || (this->adjacencyMatriz[i][j] == INF))
				cout << "   ";
			else
				cout << "  ";

			if (this->adjacencyMatriz[i][j] != INF)
				cout << this->adjacencyMatriz[i][j];
			else
				cout << "-";
		}
		cout << endl;
	}
}


template <class TVertex>
void Graph<TVertex>::showAllVertex(){
	cout << endl << "  IND ";
	printf("%c", 186);
	cout << "  VERTICE ";

	printf("\n %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 205, 205, 205, 205, 205, 206, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	cout << endl;
	for (int i = 0; i < (int) this->vertex.size(); i++)
	{
		if (i < 10)
			cout << "   " << i;
		else
			cout << "  " << i;
		printf("  %c  ", 186);

		cout << this->vertex.at(i);
		cout << endl;
	}
}

template <class TVertex>
void Graph<TVertex>::setDirecionado(bool op){
	this->direcionado = op;
}

// M�todo respons�vel por abrir o arquivo html de visualiza��o do grafo
template <class TVertex>
void Graph<TVertex>::showGraphView(){
	//ShellExecute(NULL, "open", GRAPHVIEW, NULL, NULL, SW_SHOWNORMAL);
}

// Overload da do operador =
template <class TVertex>
void Graph<TVertex>::operator= (Graph<TVertex> &data){
	(*this).adjacencyMatriz = data.adjacencyMatriz;
	(*this).edgeNumber = data.edgeNumber;
	(*this).vertex = data.vertex;

	return;
}

template <class TVertex>
Graph<TVertex>::~Graph(){

	for (int i = 0; i < this->getNumberVertex(); i++){
		if (this->getAdjacents(this->vertex[i]).size() == 0)
			this->saveFile(this->getIndex(this->vertex[i]), this->getIndex(this->vertex[i]), INF);
	}

	this->outfile.close();
}