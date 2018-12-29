
#define MAXWORD 50

struct dict
{
   char* word;
   struct dict* left;
   struct dict* right;
};

dict* dict_init(int size)
{
   dict* node = (dict*)malloc(sizeof(dict));
   node->word = (char*)calloc(size, sizeof(char));
   node->left = NULL;
   node->right = NULL;
   return node;
}

void dict_insert(dict* s, char* v)
{
   dict* leaf;
   if(s == NULL || (strcmp(v, s->word) == 0))
   {
      return;
   }
   if(strcmp(v,s->word) < 0)
   {
      if(s->left == NULL)
      {
         leaf = dict_init(MAXWORD);
         strcpy(leaf->word, v);
         s->left = leaf;
      }
      else
      {
      dict_insert(s->left, v);
      }
   }
   else
   {
      if(s->right == NULL)
      {
         leaf = dict_init(MAXWORD);
         strcpy(leaf->word, v);
         s->right = leaf;
      }
      else
      {
         dict_insert(s->right, v);
      }
   }
}

bool dict_isin(dict* s, char* v)
{
   bool done = false;
   bool found = false;
   dict* leaf = s;
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

void inOrderPrint(dict* node)
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

void deleteTree(dict* leaf)
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

void dict_free(dict** s)
{
   deleteTree(*s);
   *s = NULL;
}
