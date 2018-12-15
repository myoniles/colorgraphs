#include <vector>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <sstream>

#ifndef NODEMAP
#define NODEMAP
using namespace std;

class Node{
	private:
		// Color can range from 0 to 2 for normal colors, -1 denotes an uncolroed node
		int color;
		// Holds all connections to a given node
		// Undirected so edges will be repeated inbetween node
		vector<int> connections;

	public:
		Node(int color){
			this->color = color;
		}

		vector<int> getConnections(){
			return connections;
		}

		void setColor(int c){
			color = c;
		}

		int getColor(){
			return color;
		}

		void connect(int name){
			// pushed to the back to maintain ordering
			connections.push_back(name);
		}

		bool canConnect( Node n ){
			// used in map generation
			// returns true if the node in question has a color that is not the same
			return !(this->color == n.getColor());
		}

};


class Map{
	private:
		// list of nodes
		vector<Node> nodes;
		// requested denotes the number of nodes requested
		// this is important so that a recoloring cannot be reused
		int requested = 0;

	public:
		Map(){}

		Map(Map m, int* scheme){
			nodes = m.getNodes();
			requested = 2;

			// recolor every node
			for(std::vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it){
				(*it).setColor(scheme[(*it).getColor()]);
			}
		}

		Map(int n){
			initialize(n);
		}

		Map(Map arg, bool color){
			nodes = arg.getNodes();
			for(std::vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it){
				(*it).setColor(-1);
			}
		}

		Map(std::string filename, bool color){
			ifstream fille;
			fille.open(filename);

			std::string node;
			// for each line in the file, make a node
			// if applicable, give it a color
			// then add all connections until end of line
			while(getline(fille, node)){
				int name, c, connection;
				Node newNode(-1);
				stringstream con(node);
				if(color){
					con >> name >> c;
					newNode.setColor(c);
				} else {
					con >> name;
				}
				while (con >> connection){
					newNode.connect(connection);
				}
				nodes.push_back(newNode);
			}

			fille.close();
		}

		void initialize(int n){
			std::srand(time(NULL));
			for( int i = 0; i < n; i++) {
				Node newNode( std::rand() % 3 );
				for (int j = 0; j < nodes.size(); j++){
					if (newNode.canConnect(nodes[j]) && std::rand() % 2){
						newNode.connect(j);
						nodes[j].connect(i);
					}
				}
				nodes.push_back(newNode);
			}
		}


		// r/notmyjob: I solved the graph boss!
		void randomize(){
			for(std::vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it){
				(*it).setColor(rand()%3);
			}
		}

		// TODO: BFS on graph starting at node 0
		// alternate colors each iteration,
		// if there is a conflict, either try to solve it by moving to the third color
		// if that does not worl, leave it and hope nobody sees it
		void bfsGuess(){
		}

		int getSize(){
			return nodes.size();
		}

		// The comprehensive file format was one that I implemented before
		// I learned the general conventions for storing graphs
		// Thus it creates an N line file. Format is as follows:
		// (node name) (node color) (connection)+
		void toComprehensiveFile(std::string filename, bool includeColor){
			ofstream fille;
			fille.open(filename);

			// For node in map, write the color of the node and then all connected nodes in order
			for ( int i = 0; i < nodes.size(); i++ ) {
				fille << i << " ";
				if (includeColor){
					fille << nodes[i].getColor() << " ";
				}

				vector<int> con = nodes[i].getConnections();
				for (std::vector<int>::iterator it = con.begin(); it != con.end(); ++it){
						fille << *it << " ";
					}
				fille << "\n";
			}
			fille.close();
		}

		// TODO: implement a file writing function as follows:
		// line 1: (Number of nodes) (number of edges)
		// line 2 - n+1: (node_1) (node_2)
		void saveGraph(){

		}

		// TODO: implement a file writing function as follows:
		// For N lines: (node_name) (color)
		void saveColoring(){

		}

		int getNodeColor(int name){
			if (requested > 0 ){
				return nodes[name].getColor();
			} else {
				return -1;
			}
		}

		int size(){
			return nodes.size();
		}

		Node operator[] (int i){
			return nodes.at(i);
		}
		vector<Node> getNodes(){
			return nodes;
		}

};

#endif
