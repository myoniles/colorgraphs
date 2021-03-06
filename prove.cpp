#include "graph.h"
#include "user.h"
#include <iostream>

int main(){
	//Map* m = new Map(10);
	//m->toFile("map1.txt", true);
	//m->toFile("serverMap.txt", false);

	User* prove = new User( 100);
	User* ver = new User(prove, USERTYPE::VERIFY);
	User* snoop = new User(prove, USERTYPE::SNOOP);

	Map* example = new Map(1000);

	for ( int i = 0; i < 10000; i ++ ) {
		if (!(ver->requestRound(prove))){
			std::cout<<"darn";
			return -1;
		} else {
			std::cout<< "round " << i << " passed!\n";
		}
	}

	cout << "All rounds passed!\n";

	Map* bfsExample= new Map(5);
	bfsExample->noColor();
	bfsExample->bfsGuess();
	bfsExample->saveGraph("bfs.map");
	bfsExample->saveColoring("bfs.coloring");
	bfsExample->toComprehensiveFile("bfs.comp", true);

	snoop->guess();
	for ( int i = 0; i < 10000; i ++ ) {
		if (!(ver->requestRound(snoop))){
			std::cout<<"SWIPER NO SWIPING!\n";
			return -1;
		} else {
			std::cout<< "round " << i << " passed!\n";
		}
	}

	cout << "All rounds passed!\n";
	return 0;
}
