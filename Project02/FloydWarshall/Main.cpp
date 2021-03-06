/*
* Main.cpp
*
*      Author: Kellison
*
*/

#include <iostream>
#include <stdio.h>
#include "./FloydWarshall.hpp" 

using namespace std;


int main(int argc, char* argv[]){
	vector<int> a;

	a.push_back(0);
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);

	Graph<int> g("new", a);
	g.setDirecionado(true);

	printf("\n %c%c%c%c%c%c%c TRABALHANDO COM GRAFOS - ALG. DE FloydWarshall %c%c%c%c%c%c%c \n\n",
		205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);

	g.showAllVertex();

	cout << endl << " Matriz de Adjacencias (com custos, grafo direcionado): " << endl << endl;

	g.setEdge(0, 1, 20);
	g.setEdge(0, 2, 10);
	g.setEdge(0, 4, 5);
	g.setEdge(2, 3, 10);
	g.setEdge(3, 1, 3);
	g.setEdge(4, 2, 2);
	g.setEdge(4, 3, 4);

	g.showMatriz();

	cout << endl << endl << " Algoritmo de FLOYD-WARSHALL" << endl << endl;

	FloydWarshall<int> dist;

	dist.graph = g;
	dist.getDistances();

	cout << " - Distancias minimas entre os pares de vertices: " << endl << endl;
	dist.print('d');

	cout << endl << " - Antecessores (caminho): " << endl << endl;
	dist.print('a');
	
	cout << endl << endl << " (Pressione <ENTER> para encerrar>" << endl;
	
	return 0;
}
