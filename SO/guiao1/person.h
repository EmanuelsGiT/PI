#define FILENAME "file_pessoas"

typedef struct Person{
    char name[200];
    int age;
} Person;

//API
int new_person(char *name, int age);
int person_change_age(char *name, int age);
int person_change_age_v2(char *name, int age);


//se fizesse char*name e depos malloc(200) poderia fazer strcpy mas quando fizesse o write &p iria escrever o endereço
//sou dono dessa mem ate fazer free ou ser libertada
//se ler do disco e tentar ser usado em outro contexto, ha de ter lixo ou coisas q n consigo ler