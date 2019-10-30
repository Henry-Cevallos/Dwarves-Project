/*
Henry Cevallos
CSCI 135
INstuctor: Genady Maryash
Project 3B

This program makes the dwarves collect the closest trees next to them
then once they have 300 lumber they will build fences

*/

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
#include "bot.h"

using namespace std;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;

int ROWS;  // global variables
int COLS;
int NUM;
bool buildQuota;

void moveToTree( Dwarf &dwarf, int r, int c, ostream &log);
string isNextToFence(Dwarf & dwarf, int r, int c);
bool willSpotBuildAdjacentFence(Dwarf & dwarf, int r, int c);
int directionToBuild(Dwarf & dwarf, int r, int c);
bool adjFence(Dwarf & dwarf, int r, int c);
void buildFence(Dwarf & dwarf, int r, int c, string dir, ostream &log);
/* onStart: 
An Initialization procedure called at the start of the game.
You can use it to initialize certain global variables, or do 
something else before the actual simulation starts.
Parameters:
    rows: number of rows
    cols: number of columns
    num:  number of dwarfs
    log:  a cout-like log */

void onStart(int rows, int cols, int num, std::ostream &log) {
	log << "Start!" << endl; // Print a greeting message

	ROWS = rows; // Save values in global variables
 	COLS = cols;
 	NUM = num;
	buildQuota = false;
}

/* onAction: 
A procedure called each time an idle dwarf is choosing 
their next action.
Parameters:
    dwarf:   dwarf choosing an action
    day:     day (1+)
    hours:   number of hours in 24-hour format (0-23)
    minutes: number of minutes (0-59)
    log:     a cout-like log  */


bool isNextToATree(Dwarf & dwarf, int r, int c){
    if( dwarf.look(r, c+1) == PINE_TREE || dwarf.look(r, c+1) == APPLE_TREE){
		return true;
    }
    else if( dwarf.look(r, c-1) == PINE_TREE || dwarf.look(r, c-1) == APPLE_TREE){
		return true;
	}
    else if( dwarf.look(r-1, c) == PINE_TREE || dwarf.look(r-1, c) == APPLE_TREE){
		return true;
	}
    else if( dwarf.look(r+1, c) == PINE_TREE || dwarf.look(r+1, c) == APPLE_TREE){
		return true;
	}
	
	return false;
}

void chopTree(Dwarf &dwarf, int r, int c, ostream &log);
void moveToTree(Dwarf &dwarf, int r, int c, ostream &log);

void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log) {
  // Get current position of the dwarf
	int r = dwarf.row();
	int c = dwarf.col();
	
	
		if(dwarf.lumber() < 360 && buildQuota==false){
			
			if(isNextToATree(dwarf, r, c)){
				chopTree(dwarf, r, c, log);
				return;
			}
			
			else{
			
				moveToTree(dwarf, r, c, log);
				return;
			}
		}
		
		if(buildQuota==false && dwarf.name()==3){
			
			
			if(dwarf.look(r-1, c)== EMPTY ) { //first pass dwarf
				log<<" FIRST to build!"<<endl ;
				dwarf.start_build(NORTH);
				buildQuota=true;
				//return;
		
			}

			else if(dwarf.look(r+1, c)== EMPTY ) { //first pass dwarf
				log<<"First to build";
				dwarf.start_build(SOUTH);
				buildQuota=true;
				//return;
		
			}

			else if(dwarf.look(r, c+1)== EMPTY ) { //first pass dwarf
				log<< "First to Build" <<endl;
				dwarf.start_build(EAST);
				buildQuota=true;
				//return;
		
			}

			else if(dwarf.look(r, c-1)== EMPTY ) { //first pass dwarf
				log<< "First to build!" <<endl;
				
				dwarf.start_build(WEST);
				buildQuota=true;
				//return;

			}
			
			
			return;
		}
		
		if(buildQuota == true){
			string dir = isNextToFence(dwarf, r, c);
			log << dwarf.name() << " " << dir << endl;
			buildFence(dwarf, r, c, dir, log);
		}
		return;
			
		
		
}  //end On Action
void chopTree(Dwarf &dwarf, int r, int c, ostream &log){
	if( dwarf.look(r, c+1) == PINE_TREE || dwarf.look(r, c+1) == APPLE_TREE){
				log<<"Gonna Chop!"<<endl;
				dwarf.start_chop(EAST);
				return;
			}
			else if( dwarf.look(r, c-1) == PINE_TREE || dwarf.look(r, c-1) == APPLE_TREE){
				log<<"Gonna Chop!"<<endl;
				dwarf.start_chop(WEST);
				return;
			}
			else if( dwarf.look(r-1, c) == PINE_TREE || dwarf.look(r-1, c) == APPLE_TREE){
				log<<"Gonna Chop!"<<endl;
				dwarf.start_chop(NORTH);
				return;
			}
			else if( dwarf.look(r+1, c) == PINE_TREE || dwarf.look(r+1, c) == APPLE_TREE){
				log<<"Gonna Chop!"<<endl;
				dwarf.start_chop(SOUTH);
				return;
			}

}

void moveToTree( Dwarf &dwarf, int r, int c, ostream &log){
				int optCol = -1;
				int optRow = -1;
				int optDistance = 10000000;
				
				for(int searchRow = 0; searchRow < ROWS; searchRow++){
				
					for(int searchCol = 0; searchCol < COLS; searchCol++){
					
							if(	(dwarf.look(searchRow, searchCol+1) == PINE_TREE || dwarf.look(searchRow, searchCol+1) == APPLE_TREE)
							
								|| (dwarf.look(searchRow, searchCol -1) == PINE_TREE  || dwarf.look(searchRow, searchCol -1) == APPLE_TREE)
								
									|| (dwarf.look(searchRow+1, searchCol) == PINE_TREE  || dwarf.look(searchRow+1, searchCol) == APPLE_TREE)
									
										|| (dwarf.look(searchRow-1, searchCol ) == PINE_TREE  || dwarf.look(searchRow-1, searchCol) == APPLE_TREE)  ){
							
								
											int currentDistance = pow(searchCol-c, 2) +  pow(searchRow-r, 2);
								
											if( (optCol < 0 && optRow < 0) || (currentDistance < optDistance) ){
									
												optCol = searchCol;
												optRow = searchRow;
												optDistance = currentDistance;
									
											}
							
							}
					
					}
				
				}
				
				log << "Walking to "<< optRow << " " << optCol << endl;
				dwarf.start_walk(optRow, optCol);
				return;
			

}

string isNextToFence(Dwarf & dwarf, int r, int c) {
  if (adjFence(dwarf, r, c+1)) {
    return "EAST";
  } else if (adjFence(dwarf, r, c-1)) {
    return "WEST";
  } else if (adjFence(dwarf, r+1, c)) {
    return "SOUTH";
  } else if (adjFence(dwarf, r-1, c)) {
    return "NORTH";
  } else {
    return "NONE";
  }
}

bool adjFence(Dwarf & dwarf, int r, int c) {
  if (dwarf.look(r,c)==EMPTY) {
		if((dwarf.look(r, c+1) == FENCE ||
            dwarf.look(r, c-1) == FENCE ||
            dwarf.look(r+1, c) == FENCE ||
            dwarf.look(r-1, c) == FENCE)){
			
				return true;
			}
  }
  return false;
}


bool willSpotBuildAdjacentFence(Dwarf & dwarf, int r, int c){

	if( isNextToFence(dwarf, r-1, c) == "NORTH"){

		return true; //North
	}

	else if( isNextToFence(dwarf, r+1, c)  == "SOUTH"){

		return true; //SOUTH
	}

	else if( isNextToFence(dwarf, r, c+1) == "EAST" ){

		return true; //EaST
	}

	else if( isNextToFence(dwarf, r, c-1) == "WEST" ){

		return true; //WEST
	}
	
	return false;
	

}

int directionToBuild(Dwarf & dwarf, int r, int c){


	if(dwarf.look(r-1, c+1)== FENCE){
		
		if(dwarf.look(r-1,c) ==EMPTY){
			return 0; //NORTH
		}

		else if (dwarf.look(r, c+1) ==EMPTY){

			return 2; //EAST
		}

	}

	else if(dwarf.look(r-1, c-1)== FENCE){
		
		if(dwarf.look(r-1,c) == EMPTY){
			return 0; //NORTH
		}

		else if (dwarf.look(r, c-1) ==EMPTY){

			return 3; //WEST
		}

	}

	else if(dwarf.look(r+1, c-1)== FENCE){
		
		if(dwarf.look(r+1,c) == EMPTY){
			return 1; //SOUTH
		}

		else if (dwarf.look(r, c-1) ==EMPTY){

			return 3; //WEST
		}

	}

	else if(dwarf.look(r+1, c+1)== FENCE){
		
		if(dwarf.look(r+1,c+1) == EMPTY){
			return 1; //SOUTH
		}

		else if (dwarf.look(r, c+1) ==EMPTY){

			return 2; //EAST
		}

	}


	return 0; //garbage

}

void moveToClosestFence(Dwarf & dwarf, int r, int c, ostream &log) {
				
				int optCol = -1;
				int optRow = -1;
				int optDistance = 10000000;
				
				for(int searchRow = 0; searchRow < ROWS; searchRow++){
				
					for(int searchCol = 0; searchCol < COLS; searchCol++){
      
							if (adjFence(dwarf, searchRow, searchCol) 
									&&  (isNextToFence(dwarf, searchRow, searchCol+1)!="NONE"   || isNextToFence(dwarf, searchRow, searchCol-1)!="NONE"
										|| isNextToFence(dwarf, searchRow+1, searchCol)!="NONE" || isNextToFence(dwarf, searchRow-1, searchCol)!="NONE")) {
								
								// Check if distance is less than current min distance
								int currentDistance = pow(searchCol-c, 2) +  pow(searchRow-r, 2);
								
											if( (optCol < 0 && optRow < 0) || (currentDistance < optDistance) ){
									
												if((isNextToFence(dwarf, searchRow, searchCol+1)!="NONE")){
													optCol = searchCol+1;
													optRow = searchRow;
													optDistance = currentDistance;
												}
												
												if((isNextToFence(dwarf, searchRow, searchCol-1)!="NONE")){
													optCol = searchCol-1;
													optRow = searchRow;
													optDistance = currentDistance;
												}
												
												if((isNextToFence(dwarf, searchRow+1, searchCol)!="NONE")){
													optCol = searchCol;
													optRow = searchRow+1;
													optDistance = currentDistance;
												}
												
												if((isNextToFence(dwarf, searchRow-1, searchCol)!="NONE")){
													optCol = searchCol;
													optRow = searchRow-1;
													optDistance = currentDistance;
												}
											}
							}
					}
				}

	log << "Walking to "<< optRow << " " << optCol << endl;
	dwarf.start_walk(optRow, optCol);
	return;
}


void buildFence(Dwarf & dwarf, int r, int c, string dir, ostream &log) {
  if (dir == "EAST") {
    log << "Build fence" << endl;
    dwarf.start_build(EAST);
    return;
  } else if (dir == "WEST") {
    log << "Build fence" << endl;
    dwarf.start_build(WEST);
    return;
  } else if (dir == "SOUTH") {
    log << "Build fence" << endl;
    dwarf.start_build(SOUTH);
    return;
  } else if (dir == "NORTH") {
    log << "Build fence" << endl;
    dwarf.start_build(NORTH);
    return;
  } 
  
  else {
    // Otherwise, move to the closest fence
    moveToClosestFence(dwarf, r, c, log);
    return;
  }
}