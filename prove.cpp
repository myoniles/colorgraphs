#include "graph.h"

int main(){
	Map* m = new Map(10000);
	m->toFile("map1.txt", true);
	m->toFile("serverMap.txt", false);
	delete m;
}
