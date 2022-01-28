typedef struct tnode{
  int ntype; // type of node 0->leaf 1->read 2->write 3->connector 4->assignment 5->+ 6->- ....
  char *c; //operator or variable name
  int val; //value of NUM
  int type;//type of variable
  struct tnode *left, *right; 
}tnode;

#define TTSTYPE tnode*;

int getReg(void);
void freeReg(void);
int generateCode(tnode*);
tnode* makeNode(int, char*, int, int, tnode*, tnode*);
