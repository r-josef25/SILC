//tnode* makeLeafNode(int val){
//  tnode *temp;
//  temp = (tnode*)malloc(sizeof(tnode));
//  temp->val = val;
//  temp->op = NULL;
//  temp->left = NULL;
//  temp->right = NULL;
//  return temp;
//}

tnode* makeNode(int ntype, char *c, int val, int type ,tnode* left, tnode* right){
  tnode* temp;
  temp = (tnode*)malloc(sizeof(tnode));
  temp->ntype = ntype;
  temp->left = left;
  temp->right= right;
  if(ntype == 0){
    if(c == NULL){
      temp->c = NULL;
      temp->val = val;
      temp->type = 0;
      return temp;
    }
    else{
      temp->c = (char*)malloc(sizeof(char));
      temp->type = type;
      *(temp->c) = *c;
      return temp;
    }
  }
  else {
    temp->val = 0;
    temp->type = 0;
    temp->c = NULL;
    return temp;
  }
  //  temp->val = 0;
  //  temp->op = (char*)malloc(sizeof(char));
  //  *(temp->op) = c;
  //  temp->left = left;
  //  temp->right = right;
  //  return temp;
}

int generateCode(tnode *node){
 //printf("\nentered next: %d\n", node->ntype);
  if(node->ntype == 0){
    //printf("leaf");
    if(node->c == NULL){
     //printf(" num\n");
	int p = getReg();
	fprintf(tar_file, "MOV R%d, %d\n", p, node->val);
	return p;
    }
    else {
     //printf(" id\n");
	int p = getReg();
	int q = getReg();
	fprintf(tar_file, "MOV R%d, SP\n", p);
	fprintf(tar_file, "MOV R%d, %d\n", q, (*(node->c) - 'a' + 1));
	fprintf(tar_file, "ADD R%d, R%d\n", p, q);
	if(in_read_asmnt)
	  fprintf(tar_file, "ADD R%d, [R%d]\n", p, p);
	freeReg();
	return p;
    }
  }
  else{
    if(node->ntype == 1){
        in_read_asmnt = true;
	int p = generateCode(node->left);
	int q = getReg();
	fprintf(tar_file, "MOV R%d, %s\n", q, "\"Read\"");
	fprintf(tar_file, "PUSH %d\n", q);
	fprintf(tar_file, "MOV R%d, %d\n", q, -1);
	fprintf(tar_file, "PUSH %d\n", q);
	fprintf(tar_file, "MOV R%d, R%d\n", q, p);
	fprintf(tar_file, "PUSH %d\n", q);
	fprintf(tar_file, "CALL 0\n");
	fprintf(tar_file, "POP R%d\n", q);
	fprintf(tar_file, "POP R%d\n", q);
	fprintf(tar_file, "POP R%d\n", q);
	fprintf(tar_file, "POP R%d\n", q);
	freeReg();
	freeReg();
        in_read_asmnt = false;
	return 0;
    }
    else if(node->ntype == 2){
	int p = generateCode(node->left);
	int q = getReg();
	fprintf(tar_file, "MOV R%d, %s\n", q, "\"Write\"");
	fprintf(tar_file, "PUSH %d\n", q); 
	fprintf(tar_file, "MOV R%d, %d\n", q, -2);
	fprintf(tar_file, "PUSH %d\n", q); 
	fprintf(tar_file, "MOV R%d, [R%d]\n", q, p);
	fprintf(tar_file, "PUSH %d\n", q); 
	fprintf(tar_file, "CALL 0\n");
	fprintf(tar_file, "POP R%d\n", q);
	fprintf(tar_file, "POP R%d\n", q);
	fprintf(tar_file, "POP R%d\n", q);
	fprintf(tar_file, "POP R%d\n", q);
	freeReg();
	freeReg();
	return 0;
    }
    else if(node->ntype == 3){
     //printf(" connector Node\n\n ");
     //printf(" %d %d \n ", node->left->ntype, node->right->ntype);
      node->val = generateCode(node->left);
      node->val = generateCode(node->right);
    }
    else if(node->ntype == 4){
   //printf("assignment");
	in_read_asmnt = true;
	int p = generateCode(node->left);
	in_read_asmnt = false;
	int q = generateCode(node->right);
	fprintf(tar_file, "MOV [R%d], R%d\n", p, q);
	freeReg();
	return p;
    }
    else if(node->ntype > 4 && node->ntype < 9){
	int p = generateCode(node->left);
	int q = generateCode(node->right);
	switch (node->ntype){
	    case 5:
	    fprintf(tar_file, "ADD R%d, R%d\n", p, q);
	    break;
	    case 6:
	    fprintf(tar_file, "SUB R%d, R%d\n", p, q);
	    break;
	    case 7:
	    fprintf(tar_file, "MUL R%d, R%d\n", p, q);
	    break;
	    case 8:
	    fprintf(tar_file, "DIV R%d, R%d\n", p, q);
	}
	freeReg();
	return p;
    }
    
  }
}

int getReg(void){
    if(lastReg < 20){
	return lastReg++;
    }
   //printf("Out of Registers");
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
