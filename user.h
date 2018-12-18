#ifndef USERS
#define USERS

#include "graph.h"
#include <iostream>

enum USERTYPE{ PROVE, VERIFY, SNOOP };


class User{
	private:
		Map map;
		USERTYPE usertype;

	public:
		User(User* u, USERTYPE user){
			// This option is used when the User is a verifier
			map = *(u->getNoColor());
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
			if (prover->getUserType() == USERTYPE::VERIFY){
				std::cout << "ERROR: Requesting another Verifier's information\n";
				return false;
			} else if (this->getUserType() != USERTYPE::VERIFY){
				std::cout <<"ERROR: We'll be asking the questions here!\n";
				return false;
			}

			//TODO: Either generate two random ints in here given size of n
			// Then return a bool if it goes well!
			Map* recol = prover->commitToRecolor();
			int checkNode1 =  rand() % map.size();
			int checkNode2 = map[checkNode1].getConnections()[ rand() % map[checkNode1].getConnections().size()];
			if (recol->getNodeColor(checkNode1) != recol->getNodeColor(checkNode2)) {
				return true;
			} else {
				std::cout << "ERROR: Round failed!\n";
				return false;
			}

		}

        bool requestRound(User* prover, int checkNode1, int checkNode2){
            if (prover->getUserType() == USERTYPE::VERIFY){
                std::cout << "ERROR: Requesting another Verifier's information\n";
                return false;
            } else if (this->getUserType() != USERTYPE::VERIFY){
                std::cout <<"ERROR: We'll be asking the questions here!\n";
                return false;
            }

            Map* recol = prover->commitToRecolor();
            if (recol->getNodeColor(checkNode1) != recol->getNodeColor(checkNode2)) {
                return true;
            } else {
                std::cout << "ERROR: Round failed!\n";
                return false;
            }

        }

		Map* commitToRecolor(){
            int schemas[][3]= {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};
			int* scheme = schemas[rand() % 6];
			Map* recol = new Map( map , scheme );
			return recol;
		}

		int getSize(){
			return map.getSize();
		}

		Map* getNoColor(){
			Map* newMap = new Map(map, false);
			return newMap;
		}

		void guess(){
			map.bfsGuess();
		}
};

#endif
