#include "graph.h"
#include <iostream>

enum USERTYPE{ PROVE, VERIFY, SNOOP };
int schemas[][3] = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};

class User{
	private:
		Map map;
		USERTYPE usertype;

	public:
		User(User u, USERTYPE user){
			// This option is used when the User is a verifier
			m;
			usertype = user;
		}

		User( int nodes ){
			// This option is used when User is a prover
			map.initialize( nodes );
			usertype = USERTYPE::PROVE;
		}

		USERTYPE getUserType(){
			return usertype;
		}

		bool requestRound(User* prover){
			if (prover->getUserType() == USERTYPE::PROVE){
				std::cout << "ERROR: Requesting another Verifier's information\n";
				return false;
			} else if (this->getUserType() != USERTYPE::VERIFY){
				std::cout <<"ERROR: We'll be asking the questions here!\n";
				return false;
			}

			//TODO: Either generate two random ints in here given size of n
			// Then return a bool if it goes well!
			Map* recol = prover->commitToRecolor();
			if (recol->getNodeColor() != recol->getNodeColor()) {
				return true;
			} else {
				std::cout << "ERROR: Round failed!\n";
				return false;
			}

		}

		Map* commitToRecolor(){
			int* scheme = schemas[rand() % 6];
			Map* recol = new Map( map , scheme );
			return recol;
		}

		Map* getNoColor(){
			Map newMap = new Map(map);
		}
};
