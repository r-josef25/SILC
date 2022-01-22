typedef struct tnode{
  int val;
  char *op;
  struct tnode *left, *right;
}tnode;

#define TTSTYPE tnode*;

int getReg(void);
void freeReg(void);
int generateCode(tnode*);
tnode* makeLeafNode(int);
tnode* makeOperatorNode(char, tnode*, tnode*);
