
#define MAXWORD 50
#define INITIAL 23
#define HASHSTART 5381
#define HASHMULTIPLIER 33
#define EXPAND 2
#define FULL .6
#define JUMP 1

struct dic
{
   int strSize;
   unsigned int elements;
   unsigned int arraySize;
   double loadFactor;
   char** words;
};

dic* initialise(int arraySize, int strSize);
unsigned int hash(unsigned int size, char *v);
int checkPrime(unsigned int i);
unsigned int nextPrime(unsigned int num);
void swapPtr(dic* one, dic* two);
dic* expandArray(dic* s);

dic* dic_init(int size)
{
   dic* n;
   n = initialise(INITIAL, size);
   return n;
}

dic* initialise(int arraySize, int strSize)
{
   int i;
   dic* ptr = (dic*)malloc(sizeof(dic));
   if(ptr == NULL){
      printf("Couldn't allocate memory for ptr\n");
      exit(1);
   }
   ptr->arraySize = arraySize;
   ptr->elements = 0;
   ptr->loadFactor = 0;
   ptr->words = (char**)malloc(arraySize * sizeof(char*));
   if(ptr->words == NULL){
      printf("Couldn't allocate memory for ptr->words\n");
      exit(1);
   }
   for (i=0; i<arraySize; i++)
   {
      ptr->words[i] = (char*)calloc(strSize, sizeof(char));
      if(ptr->words[i] == NULL){
         printf("Couldn't allocate memory for ptr->words[%d]\n", i);
         exit(1);
      }
   }
   return ptr;
}

unsigned int hash(unsigned int size, char* v)
{
   unsigned int hash = HASHSTART;
   int c;
   while((c = (*v++)))
   {
      hash = HASHMULTIPLIER * (hash^c);
   }
   return (unsigned int)(hash % size);
}

int checkPrime(unsigned int i)
{
   unsigned int n, prime=0;

   for (n=2; n<i; n++)
   {
      if(i % n == 0 )
      {
         return prime;
      }
   }
   if(i == n)
   {
      prime = 1;
   }
   return prime;
}

unsigned int nextPrime(unsigned int num)
{
   unsigned int prime = num;
   while(checkPrime(prime)==0)
   {
      prime += 1;
   }
   return prime;
}

dic* expandArray(dic* s)
{
   unsigned int i, newSize;
   dic* tempPtr;
   newSize = nextPrime(s->arraySize * EXPAND);
   tempPtr = initialise(newSize, MAXWORD);

   for(i=0; i<s->arraySize; i++)
   {
      if(strlen(s->words[i]) != 0){
         dic_insert(tempPtr, s->words[i]);
      }
   }
   return tempPtr;
}

void swapPtr(dic* one, dic* two)
{
   dic temp;
   temp = *one;
   *one = *two;
   *two = temp;
}

void dic_insert(dic* s, char* v)
{
   unsigned int address;
   dic* temp;
   if((s->loadFactor) >= FULL)
   {
      temp = expandArray(s);
      swapPtr(temp, s);
      dic_free(&temp);
   }
   address = hash(s->arraySize, v);
   while(strlen(s->words[address]) != 0)
   {
      address = (address+JUMP) % s->arraySize;
   }
   strcpy(s->words[address], v);
   s->elements += 1;
   s->loadFactor = (double)(s->elements)/s->arraySize;
}

bool dic_isin(dic* s, char* v)
{
   unsigned int address = hash(s->arraySize, v);
   while(strlen(s->words[address]) != 0)
   {
      if(strcmp(s->words[address], v) == 0){
         return true;
      }
      address = (address + 1) % s->arraySize;
   }
   return false;
}

void dic_free(dic** s)
{
   dic* d = *s;
   unsigned int i;
   for(i=0; i<d->arraySize; i++)
   {
      free(d->words[i]);
   }
   free(d->words);
   free(d);
   d = NULL;
}
