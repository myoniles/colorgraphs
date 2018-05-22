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
		int color;
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
			connections.push_back(name);
		}

		bool canConnect( Node n ){
			return !(this->color == n.getColor());
		}

};


class Map{
	private:
		vector<Node> nodes;
		int requested = 0;

	public:
		Map(){}

		Map(Map m, int* scheme){
			nodes = m.getNodes();
			requested = 2;

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
			while(getline(fille, node)){
				int name, c, connection;
				Node newNode(-1);
				stringstream con(node);
				if(color){
					con >> name >> c;
					//std::sscanf(node, "%d %d ", name, color);
					newNode.setColor(c);
				} else {
					con >> name;
					//std::sscanf(node, "%d ", name);
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

		void randomize(){
			for(std::vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it){
				(*it).setColor(rand()%3);
			}
		}

		int getSize(){
			return nodes.size();
		}

		void toFile(std::string filename, bool includeColor){
			ofstream fille;
			fille.open(filename);

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

		int getNodeColor(int name){
            if (requested >= 0 ){
                return nodes.at(name).getColor();
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
