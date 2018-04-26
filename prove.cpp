#include "graph.h"

int main(){
	Map* m = new Map(10);
	m->toFile("map1.txt", true);


	delete m;
}
