#define MAXWORD 50

int main(int argc, char** argv)
{
   /* Lexicon (dictionary) and Book Dictionaries */
   dict* dl;
   dict* db;
   FILE* fw, *fb;
   char str[MAXWORD];

   if(argc != 3){
      fprintf(stderr, "Usage : i%s <dictionary file> <file to spell-check>\n", argv[0]);
      exit(1);
   }

   dl = dict_init(MAXWORD);
   db = dict_init(MAXWORD);
   fw = fopen(argv[1], "r");
   fb = fopen(argv[2], "r");
   if(!fw || !fb){
      fprintf(stderr, "Can't open %s or %s\n", argv[1], argv[2]);
      exit(1);
   }

   /* Main spelling list read into dl */
   while(fscanf(fw, "%s", str) == 1){
      dict_insert(dl, str);
   }
   fclose(fw);

   /* Read in book - each spelling mistake stored into db
      so that you don't have to search for it again */
   while(fscanf(fb, "%s", str) == 1){
      if(!dict_isin(dl, str) && !dict_isin(db,str)){
         dict_insert(db, str);
         printf("%s\n", str);
      }
   }
   fclose(fb);

   dict_free(&dl);
   dict_free(&db);

   /*inOrderPrint(db); */
   /*inOrderPrint(dl); */

   return 0;
}
