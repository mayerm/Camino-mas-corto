#include <iostream>
#include <array>
#include <vector>
#include <queue>
using namespace std;
#define Node pair< int , int > //definimos el nodo como un par( prim , seg ) donde prim es el vertice adyacente y seg el peso de la arista
#define INF 1<<30 //definimos un valor grande que represente la distancia infinita inicial, basta conque sea superior al maximo valor del peso en alguna de las aristas

//La cola de prioridad de C++ por default es un max-Heap (elemento de mayor valor en el tope)
//por ello es necesario realizar nuestro comparador para que sea un min-Heap
struct cmp {
	bool operator() (const Node &a, const Node &b) {
		return a.second > b.second;
	}
};

vector< Node > ady[10]; //lista de adyacencia
priority_queue< Node, vector<Node>, cmp > Q; //priority queue propia del c++, usamos el comparador definido para que el de menor valor este en el tope

array <int, 10> distancia;
array <bool, 10> visitado; //para vértices visitados   
int V;                     //numero de vertices
array <int, 10>previo; //para la impresion de caminos


//función de inicialización
void init(){
	for (int i = 0; i <= V; ++i){
		distancia.at(i) = INF;  //inicializamos todas las distancias con valor infinito
		visitado.at(i) = false; //inicializamos todos los vértices como no visitados
		previo.at(i) = -1;      //inicializamos el previo del vertice i con -1
	}
}

//Paso de relajacion
void relajacion(int actual, int adyacente, int peso){
	//Si la distancia del origen al vertice actual + peso de su arista es menor a la distancia del origen al vertice adyacente
	if (distancia.at(actual) + peso < distancia.at(adyacente)){
		distancia.at(adyacente) = distancia.at(actual) + peso;  //relajamos el vertice actualizando la distancia
		previo.at(adyacente) = actual;                         //a su vez actualizamos el vertice previo
		Q.push(Node(adyacente, distancia.at(adyacente))); //agregamos adyacente a la cola de prioridad
	}
}

//Impresion del camino mas corto desde el vertice inicial y final ingresados
void print(int destino){
	if (previo.at(destino) != -1)    //si aun poseo un vertice previo
		print(previo.at(destino));  //recursivamente sigo explorando
	cout << destino;                //terminada la recursion imprimo los vertices recorridos
}

// Recorro los nodos
void distmcort(int inicial){
	init(); //inicializamos nuestros arreglos
	Q.push(Node(inicial, 0)); //Insertamos el vértice inicial en la Cola de Prioridad
	distancia.at(inicial) = 0;      //inicializamos la distancia del inicial como 0
	int actual, adyacente, peso;

	while (!Q.empty()){                   //Mientras cola no este vacia
		actual = Q.top().first;            //Obtengo de la cola el nodo con menor peso, en un comienzo será el inicial
		Q.pop();                           //Sacamos el elemento de la cola
		if (visitado.at(actual)) continue; //Si el vértice actual ya fue visitado entonces sigo sacando elementos de la cola
		visitado.at(actual) = true;         //Marco como visitado el vértice actual

		for (int i = 0; i < ady[actual].size(); ++i){ //reviso sus adyacentes del vertice actual
			adyacente = ady[actual][i].first;   //id del vertice adyacente
			peso = ady[actual][i].second;        //peso de la arista que une actual con adyacente ( actual , adyacente )
			if (!visitado[adyacente]){        //si el vertice adyacente no fue visitado
				relajacion(actual, adyacente, peso); //realizamos el paso de relajacion
			}
		}
	}

	cout << "Ingrese vertice destino: ";
	int destino;
	cin >> destino;
	print(destino);
	cout << "\n";
}

// Funcion principal ,ingreso de valores e inicion de la funcion 
int main(){
	int A, origen, destino, peso, inicial;
	cout << "Ingrese numero de vertices:";
	cin >> V;
	cout << "Ingrese numero de aristas:";
	cin >> A;
	while (A--){
		cout << "Arista: " << A + 1 << "\n";
		cout << "ingrese origen: "; cin >> origen;
		cout << "ingrese destino: "; cin >> destino;
		cout << "ingrese peso de la arista: "; cin >> peso;
		ady[origen].push_back(Node(destino, peso)); // grafo dirigido

	}
	cout << "Ingrese el vertice inicial: ";
	cin >> inicial;
	distmcort(inicial);
	return 0;
}

