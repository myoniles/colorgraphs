#include <vector>
#include <queue>
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
		unsigned int edgeNum;
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
			edgeNum = 0;
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
						edgeNum++;
					}
				}
				nodes.push_back(newNode);
			}
		}

		void noColor(){
			for(std::vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it){
				(*it).setColor(-1);
			}
		}


		// r/notmyjob: I solved the graph boss!
		void randomize(){
			for(std::vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it){
				(*it).setColor(rand()%3);
			}
		}

		// BFS on graph starting at node 0
		// alternate colors each iteration,
		// if there is a conflict, either try to solve it by moving to the third color
		// if that does not work, leave it and hope nobody sees it
		// THIS WILL ONLY WORK ON UNCOLORED GRAPHS
		void bfsGuess(){
			// start at node 0
			std::queue<int> q;
			int currCol = 0;
			q.push(0);
			nodes[0].setColor(currCol++);

			// Starting current color as 1
			// We will guess wither color 0 or 1
			// if a node is pointed to by both, we swap to 2
			while( !q.empty() ){
				// for a node to be in here it should already be colored
				int nodeName = q.front();
				vector<int> con = nodes[nodeName].getConnections();
				// recolor connections
				for (std::vector<int>::iterator it = con.begin(); it != con.end(); ++it){
					// If the node has not been visited
					if (nodes[*it].getColor() == -1){
						// check if the node has conflicting connections
						vector<int> conj = nodes[*it].getConnections();
						for (std::vector<int>::iterator itj = conj.begin(); itj != conj.end(); ++itj){
							if ((currCol+1)%2 == nodes[*itj].getColor() && nodes[*itj].getColor() != 2  ){
								nodes[(*it)].setColor(2);
								q.push(*it);
								continue;
							}
						}
						nodes[(*it)].setColor(currCol);
						q.push(*it);
					}
					currCol =( currCol + 1 ) % 2;
				}
				q.pop();
			}
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

		// line 1: (Number of nodes) (number of edges)
		// line 2 - n+1: (node_1) (node_2)
		void saveGraph(std::string filename){
			ofstream fille;
			fille.open(filename);

			fille << nodes.size() << " ";
			fille << edgeNum << "\n";

			for ( int i = 0; i < nodes.size(); i++ ) {
				vector<int> con = nodes[i].getConnections();
				for (std::vector<int>::iterator it = con.begin(); it != con.end(); ++it){
						fille << i << " ";
						fille << *it << "\n";
					}
			}
		}

		// For N lines: (node_name) (color)
		void saveColoring(std::string filename){
			ofstream fille;
			fille.open(filename);

			for ( int i = 0; i < nodes.size(); i++ ) {
				fille << i << " ";
				fille << nodes[i].getColor() << "\n";
			}

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
