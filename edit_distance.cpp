#include <iostream>
#include <string>
#include "string.h"
using namespace std;
using std::string;

struct node{
	int value;
	node* insertion_p = NULL;
	node* deletion_p = NULL;
	node* mismatch_p = NULL;
};typedef struct node node;

int edit_distance(const string &str1, const string &str2) {
  int rows = str1.size() ;
  int columns = str2.size();
  char a[rows];
  char b[columns];
  strcpy(a, str1.c_str());
  strcpy(b, str2.c_str());
  int edit_distance = 0;
  int x = rows - 1;
  int y = columns - 1;
  node D[rows][columns];
  for(int i = 0 ; i < rows ; i++){
  	D[i][0].value = i;
	if(i != 0){
		D[i-1][0].deletion_p = &D[i][0];
	}
  }
  for(int j = 0 ; j < columns ; j++){
  	D[0][j].value = j;
  	if(j != 0){
		D[0][j-1].insertion_p = &D[j][0];
	}
  }
  for(int j = 1 ; j < columns ; j++ ){
  	for(int i = 1 ; i < rows ; i++){
  		int insertion = D[i][j-1].value + 1;
  		int deletion = D[i-1][j].value + 1;
  		int match = D[i-1][j-1].value;
  		int mismatch = D[i-1][j-1].value + 1;
  		if(a[i] == b[j]){
  			D[i][j].value = min(min(insertion,deletion),match);
		  }
		else{
			D[i][j].value = min(min(insertion,deletion),mismatch);
			if(D[i][j].value == insertion){
				D[i][j-1].insertion_p = &D[i][j];
			}
			else if(D[i][j].value == deletion){
				D[i-1][j].deletion_p = &D[i][j];
			}
			else if(D[i][j].value == mismatch){
				D[i-1][j-1].deletion_p = &D[i][j];
			}
		}
	  }
  }
  while( x != 0 || y!= 0){
  	if(a[x] == b[y]){
  		x = x-1;
  		y = y-1;

	  }
	else{
  	if(x > 0 && D[x][y].value == D[x-1][y].value + 1){
  		edit_distance++;
  		x = x-1;
  		y = y;

	  }
	else if(y > 0 && D[x][y].value == D[x][y-1].value + 1){
		x= x;
		y = y-1;
		edit_distance++;

	}
	else{
		x = x-1;
		y = y-1;
		edit_distance++;

		}
	}
  }
  return edit_distance;
}

int main() {
  string str3;
  string str4;
  std::cin >> str3 >> str4;
  string str1 = "0" + str3;
  string str2 = "0" + str4;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
