int controller_loadFromText(char* path , LinkedList* pArrayListPassenger);
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger);
int controller_addPassenger(LinkedList* pArrayListPassenger);
int controller_editPassenger(LinkedList* pArrayListPassenger);
int controller_removePassenger(LinkedList* pArrayListPassenger);
int controller_ListPassenger(LinkedList* pArrayListPassenger);
int controller_sortPassenger(LinkedList* pArrayListPassenger);
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger);
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger);

int controller_BuscarPasajeroPorID(LinkedList* pArrayListPassenger, int id);
int controller_buscarUltimoID(LinkedList* pArrayListPassenger);

int controller_generadorID(LinkedList* pArrayListPassenger);
int controller_buscarUltimoID(LinkedList* pArrayListPassenger);

