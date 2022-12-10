#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H
#pragma warning(disable : 4996)
#include<iostream>
#include <algorithm>
#include<vector>
#include<fstream>
#include<string>
#include <cstdlib>

struct Process
{
	float arrivalTime; //czas przebycia
	float serviceTime; //czas obslugi
	int processName; //imie processu
	float waitingTime; // czas oczekiwania
	float turnArroudTime; //czas wykanania
	float startedTime; //czas, kiedy process rozpoczal obsluge
	float competedTime; // kiedy skonczyl obsluge

}; 
class cOperationFile_FCFS_LCFS_SJF
{

	std::ifstream mInputFile; //plik z danymi wejsciowymi
	std::ofstream mOutputResultFile; // plik z wynikami
	std::ofstream mOutputLastTestFile; // plik dla zapisywania wartosci, ostatnio przetestawanymi
	std::vector<Process>mDataStorageOneMesures; // zawiera dane dla jednego ciagu procesow
	std::vector<std::vector<Process>>mDataStorageTwoMesures; //zawiera dane dla dwoch ciagow procesow (100 ciagow / 100 procesow)
	int mOptionsNumber;
public:
	cOperationFile_FCFS_LCFS_SJF();
	//otwioeramy pliki, rezerwacja mejsca dla danych 
	~cOperationFile_FCFS_LCFS_SJF();\
	//zamykanie plikow
	void dataSettings(int aOptions);
	//ustawiamy wybor uzytkownika
	void globalReadTestDataFile();
	//odczytanie danych z pliku wejsciowego
	void writeDateInLastTestFile();
	//zapisywanie danych do pliku z danymi, ostatnio przetestawanymi
	void gennerate100SetsAnd100Elements();
	//generator processow
	std::vector<Process>& getDataStorageOneMesures();
	//zwraca wektor procesow dla jednego ciagu
	std::vector<std::vector<Process>>& getDataStorageTwoMesures();
	//zwraca wektor procesow dla dwoch ciagow
	void writeResultsToFile(std::vector<std::vector<float>> aResult);
	//zapisywanie wynikow testow
	int getOptionsNumber();
	//zwraca wybrana opcje przez uzytkownika
	void gennerateUserData();
	//generator danych wedlug zyczen uzytkownika


};

#endif