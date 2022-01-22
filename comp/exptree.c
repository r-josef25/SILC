tnode* makeLeafNode(int val){
  tnode *temp;
  temp = (tnode*)malloc(sizeof(tnode));
  temp->val = val;
  temp->op = NULL;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

tnode* makeOperatorNode(char c, tnode* left, tnode* right){
  tnode* temp;
  temp = (tnode*)malloc(sizeof(tnode));
  temp->val = 0;
  temp->op = (char*)malloc(sizeof(char));
  *(temp->op) = c;
  temp->left = left;
  temp->right = right;
  return temp;
}

int generateCode(tnode *node){
  if(node->op == NULL){
    int p = getReg();
    fprintf(tar_file, "MOV R%d, %d\n", p, node->val);
    return p;
  }
  else{
    int p = generateCode(node->left);
    int q = generateCode(node->right);
    switch (*(node->op)){
	case '+':
	  fprintf(tar_file, "ADD R%d, R%d\n", p, q);
	  break;
	case '-':
	  fprintf(tar_file, "SUB R%d, R%d\n", p, q);
	  break;
	case '*':
	  fprintf(tar_file, "MUL R%d, R%d\n", p, q);
	  break;
	case '/':
	  fprintf(tar_file, "DIV R%d, R%d\n", p, q);
	  break;
    }
    freeReg();
    return p;
  }
}

int getReg(void){
    if(lastReg < 20){
	return lastReg++;
    }
    printf("Out of Registers");
    exit(0);
}

void freeReg(void){
    lastReg--;
}
/*int getReg(void){
  for(int i = 0; i < 20; i++){
  if(regTable[i] == false){
  regTable[i] = true;
  return i;
  }
  }
  return -1;
  }

  void freeReg(void){
  for(int i = 20; i >= 0; i--){
  if(regTable[i] == true){
  regTable[i] = false;
  return;
  }
  }
  }*/ 
