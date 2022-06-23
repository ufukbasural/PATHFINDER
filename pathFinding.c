#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
typedef struct node {
  int i;
  int j;
  int adjNum;
}node;



node* create_node(int a, int b) {
  node* newNode = malloc(sizeof(node));
  newNode->i = a;
  newNode->j = b;
  newNode->adjNum = 0;
  return newNode;
}

void printMatris(char table[31][44]){
  int k,j;
  for(k = 0; k < 31; k++){
        for(j = 0; j < 44; j++) {
            printf("%c", table[k][j]);
        }
        printf("\n");
    }
}
int currScore = 0;
void DFS(int adjlist[31][44][4][2], bool visited[31][44], node* d, char table[31][44], node* nodeMatris[31][44]){
  _sleep(200);

  bool isDead = false;
  int di = d->i;
  int dj = d->j;
  if(table[di][dj] == 'c') {
    printf("Exit found..");
    exit(0);
    }
  if(table[di][dj+1] == ' ' && (table[di][dj+2] == ' ' || table[di][dj+2] == 'O')) isDead = true;
  else if(table[di+1][dj] == ' ' && (table[di+2][dj] == ' ' || table[di+2][dj] == 'O')) isDead = true;
  else if(table[di][dj-1] == ' ' && (table[di][dj-2] == ' ' || table[di][dj-2] == 'O')) isDead = true;
  else if(table[di-1][dj] == ' ' && (table[di-2][dj] == ' ' || table[di-2][dj] == 'O')) isDead = true;
  else currScore-=5;
  if(table[di][dj] == 'O') currScore+=10;
  
  int a;
  visited[di][dj] = true;
  table[di][dj] = '*';
  printMatris(table);
  if(table[di+2][dj] == 'c') printf("Score: %d\n", currScore+5);
  else printf("Score: %d\n", currScore);
  for(a = 0; a < d->adjNum; a++)
    if(visited[adjlist[di][dj][a][0]][adjlist[di][dj][a][1]] == false)
      {
        DFS(adjlist, visited, nodeMatris[adjlist[di][dj][a][0]][adjlist[di][dj][a][1]], table, nodeMatris);
        table[adjlist[di][dj][a][0]][adjlist[di][dj][a][1]] = ' ';
      }
  /*for(a = d->adjNum-1; a >= 0; a--){
  	table[adjlist[di][dj][a][0]][adjlist[di][dj][a][1]] = ' ';
  }*/
  }

int random(){
  return rand() % 100;
}


int main(){
    FILE* fp;
    srand(time(NULL));
    char numstr1[4],numstr2[4], str1[2], str2[2];
    int i = 0, j, ctr = 0, k, len;
    int bufferLength = 255;
    fp = fopen("maze.txt", "r");
    char buffer[bufferLength];
    char table[31][44];
    int randNum;
    node* nodeMatris[31][44];
    int adjlist[31][44][4][2];
    bool visited[31][44];
    int appleNum = 10;
    int currAppleNum = 0;
    int currScore = 0;
    
    for(k = 0; k < 31; k++)
        for(j = 0; j < 44; j++)
          visited[k][j] = false;
    while(fgets(buffer, bufferLength, fp)){
        for(j = 0; j < bufferLength; j++){
            if(buffer[j] == '\n'){
                memcpy(table[i], &buffer[0], j);
                table[i++][j] = '\0';
            }
        }
        
    }
    fclose(fp);
    char str[] = "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+";
    //table[30] = str;
    memcpy(table[30], &str[0], 44);
    //printf("%d",ctr);
    while(currAppleNum <= appleNum){
      for(k = 1; k < 30; k+=2){
        for(j = 1; j < 42; j+=2){
          randNum = random();
            if(randNum <= 20) {
              table[k][j] = 'O';
              currAppleNum++;
            }
        }
      }
        
    }
    table[29][41] = 'c';
    table[29][1] = 'b';
    for(k = 0; k < 31; k++){
        for(j = 0; j < 44; j++) {
            printf("%c", table[k][j]);
        }
        printf("\n");
    }
    for(i = 0; i < 31; i++){
    	for(j = 0; j < 44; j++){
    		if(table[i][j] == ' ' || table[i][j] == 'b' || table[i][j] == 'c' || table[i][j] == 'O'){
    			node* n = create_node(i,j);
            	nodeMatris[i][j] = n;
			}
		}		
	}
    //size = 315
    //node* n = create_node(29,1);
    //nodeMatris[29][1] = n;

    for(i = 1; i < 30; i = i+2){
      for(j = 1; j < 43; j = j+2){
        if(table[i][j] == ' ' || table[i][j] == 'b' || table[i][j] == 'c' || table[i][j] == 'O'){
          node* n = nodeMatris[i][j];
          if (table[i][j+1] == ' ')
          {
            node* komsu = nodeMatris[i][j+2];
            adjlist[i][j][n->adjNum][0] = i;
            adjlist[i][j][n->adjNum++][1] = j+2;
            adjlist[i][j+2][komsu->adjNum][0] = i;
            adjlist[i][j+2][komsu->adjNum++][1] = j;
          }
          if (table[i+1][j] == ' ')
          {
            node* komsu = nodeMatris[i+2][j];
            adjlist[i][j][n->adjNum][0] = i+2;
            adjlist[i][j][n->adjNum++][1] = j;
            adjlist[i+2][j][komsu->adjNum][0] = i;
            adjlist[i+2][j][komsu->adjNum++][1] = j;
          }
        }
      }
    }
	node* d;
    // baslangic 29 3
    for(i = 0; i < 31; i++)
    	for(j = 0; j < 44; j++)
    		if(table[i][j] == 'b')
    			d = nodeMatris[i][j];
			
	
    DFS(adjlist, visited, d, table, nodeMatris);
    
    //printMatris(table);
    
    return 0;
}
