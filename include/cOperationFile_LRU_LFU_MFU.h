#ifndef C_OPERATION_FILE_LRU_LFU_MFU
#define C_OPERATION_FILE_LRU_LFU_MFU

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
struct Page //przechowuje liczbe stron i zastosowan 
{
	int page;
	int used;
};
struct Result //wyniki
{
	int fault;
	int hit;
};
class cOperationFile_LRU_LFU_MFU
{
	std::ifstream mInputFile; //dane wejsciowe 
	std::ofstream mOutputResultFile; //wyniki
	std::ofstream mOutputLastTestFile; //dane, ostatnie testowane
	std::vector<Page>mDataStorageOneMesures; // zawiera dane dla jednego ciagu procesow
	std::vector<std::vector<Page>>mDataStorageTwoMesures; //zawiera dane dla dwoch ciagow procesow (100 ciagow / 100 procesow)
	int mOptionsNumber;
	int mProcess;
public:
	cOperationFile_LRU_LFU_MFU();
	//otwioeramy pliki, rezerwacja mejsca dla danych 
	~cOperationFile_LRU_LFU_MFU();
	//zamykanie plikow
	void dataSettings(int aOptions);
	//ustawiamy wybor uzytkownika
	void globalReadTestDataFile();
	//odczytanie danych z pliku wejsciowego
	void writeDateInLastTestFile();
	//zapisywanie danych do pliku z danymi, ostatnio przetestawanymi
	void gennerate100SetsAnd100Elements();
	//generator 100 ciagow o 100 procesah
	void writeResultsToFile(std::vector<Result>& aResult);
	//zapiwywanie wynikow
	int getOptionsNumber();
	//zwraca wybrana opcje
	std::vector<Page>& getDataStorageOneMesures();
	//zwraca dane dla jednego ciagu
	std::vector<std::vector<Page>>& gerDataStorageTwoMesures();
	//zwraca dane dla dwoch ciagow
	void gennerateUserData();
	//generator na zyczenie uzytkownika
};

#endif // !C_OPERATION_FILE_LRU_LFU_MFU