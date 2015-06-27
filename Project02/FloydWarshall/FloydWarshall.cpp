/*
* FloydWarshall.cpp
*
*  Created on: Jun 06, 2015
*      - Author: Kellison
*		- Descri��o:
*			Implementa��o do algoritmo de FloydWarshall aplicado junto com a classe Graph.
*		- Observa��es:
*			Diferente do Kruskal, essa implementa��o � funciona apenas para grafos n�o direcionais
*
*/

#include "FloydWarshall.hpp"

template class FloydWarshall<int>;
using namespace std;

template <class TVertex>
FloydWarshall<TVertex>::FloydWarshall(){}

template <class TVertex>
void FloydWarshall<TVertex>::getDistances(){
	int number_vertices = this->graph.getNumberVertex();

	this->distanceMatriz = this->graph.getAdjacencyMatriz();

	for (int i = 0; i < number_vertices; i++)
		this->distanceMatriz[i][i] = 0;

	for (int k = 0; k < number_vertices; k++){
		for (int i = 0; i < number_vertices; i++){
			for (int j = 0; j < number_vertices; j++){
				
				if (distanceMatriz[i][j] > distanceMatriz[i][k] + distanceMatriz[k][j]){
					distanceMatriz[i][j] = distanceMatriz[i][k] + distanceMatriz[k][j];
						//antecessorMatriz[i][j] = antecessorMatriz[k][j];					
				}
				
			}
		}
	}

}

template <class TVertex>
void FloydWarshall<TVertex>::print(){
	cout << "  IND ";
	printf("%c", 186);
	for (int i = 0; i < (int) this->graph.getNumberVertex(); i++)
	{
		if (i < 10)
			cout << "   " << i;
		else
			cout << "  " << i;
	}


	printf("\n %c%c%c%c%c%c", 205, 205, 205, 205, 205, 206);
	for (int i = 0; i < (int) this->graph.getNumberVertex(); i++)
		printf("%c%c%c%c", 205, 205, 205, 205);

	cout << endl;

	for (int i = 0; i < (int) this->graph.getNumberVertex(); i++)
	{
		if (i < 10)
			cout << "   " << i;
		else
			cout << "  " << i;

		printf("  %c", 186);
		for (int j = 0; j < (int) this->graph.getNumberVertex(); j++)
		{
			if (this->distanceMatriz[i][j] < 0)
				cout << "  ";
			else if ((this->distanceMatriz[i][j] < 10) || (this->distanceMatriz[i][j] == INF))
				cout << "   ";
			else
				cout << "  ";

			if (this->distanceMatriz[i][j] != INF)
				cout << this->distanceMatriz[i][j];
			else
				cout << "-";
		}
		cout << endl;
	}
}

template <class TVertex>
FloydWarshall<TVertex>::~FloydWarshall(){}
