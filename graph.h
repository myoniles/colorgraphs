#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <random>

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

		void setColor(int color){
			this->color = color;
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

	public:
		Map(){}

		Map(Map m, int* scheme){
			nodes = m.getNodes();

			for(std::vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it){
				(*it).setColor(scheme[(*it).getColor()]);
			}
		}

		Map(int n){
			initialize(n);
		}

		void initialize(int n){
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

		vector<Node> getNodes(){
			return nodes;
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

};
