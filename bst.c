
#define MAXWORD 50

struct dic
{
   char* word;
   struct dic* left;
   struct dic* right;
};

dic* dic_init(int size)
{
   dic* node = (dic*)malloc(sizeof(dic));
   node->word = (char*)calloc(size, sizeof(char));
   node->left = NULL;
   node->right = NULL;
   return node;
}

void dic_insert(dic* s, char* v)
{
   dic* leaf;
   if(s == NULL || (strcmp(v, s->word) == 0))
   {
      return;
   }
   if(strcmp(v,s->word) < 0)
   {
      if(s->left == NULL)
      {
         leaf = dic_init(MAXWORD);
         strcpy(leaf->word, v);
         s->left = leaf;
      }
      else
      {
      dic_insert(s->left, v);
      }
   }
   else
   {
      if(s->right == NULL)
      {
         leaf = dic_init(MAXWORD);
         strcpy(leaf->word, v);
         s->right = leaf;
      }
      else
      {
         dic_insert(s->right, v);
      }
   }
}

bool dic_isin(dic* s, char* v)
{
   bool done = false;
   bool found = false;
   dic* leaf = s;
   while(!done && leaf)
   {
      if(strcmp(v,leaf->word) == 0)
      {
         done = true;
         found = true;
      }
      else if(strcmp(v,leaf->word) < 0)
      {
         leaf = leaf->left;
      }
      else if(strcmp(v,leaf->word) > 0)
      {
         leaf = leaf->right;
      }
   }
   return found;
}

void inOrderPrint(dic* node)
{
	if (node == NULL)
   {
      return;
   }
   inOrderPrint(node->left);
   if(node)
   {
      printf("%s\n", node->word);
   }
   inOrderPrint(node->right);
}

void deleteTree(dic* leaf)
{
   if (leaf == NULL)
   {
      return;
   }
   deleteTree(leaf->left);
   deleteTree(leaf->right);
   free(leaf->word);
   free(leaf);
}

void dic_free(dic** s)
{
   deleteTree(*s);
   *s = NULL;
}
