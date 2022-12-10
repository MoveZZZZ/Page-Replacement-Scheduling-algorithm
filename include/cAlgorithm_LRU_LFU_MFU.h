#ifndef C_ALGORITHM_LRU_LFU_MFU_H
#define C_ALGORITHM_LRU_LFU_MFU_H
#include"cOperationFile_LRU_LFU_MFU.h"
#include<deque>
struct Frequency 
{
	int page; 
	int used;
};
struct IndexRepetition 
{
	int used;
	int index;
};
class cAlgorithm_LRU_LFU_MFU
{

	std::deque<Frequency> mFrequency; // pamieta ile razy uzylismy kazda ze stron
	std::vector<std::deque<int>> mTable;
	std::vector<Result> mResult; //wyniki algorytmow dla zapisywania do plikow
	std::vector<Page> &mDataStorageOneMesures; // wektor dla jednego ciagu procesow
	std::vector<std::vector<Page>>& mDataStorageTwoMesures;
	int mFrameNumber;
	int mStringLen;
public:
	cAlgorithm_LRU_LFU_MFU(std::vector<Page>& aDataStorageOneMesures, std::vector<std::vector<Page>>& aDataStorageTwoMesures);
	void LFU_MFU_OneMesure(std::vector<Page>& aPageArr, char aOptions);
	void LFU_MFU_TwoMesure(std::vector<std::vector<Page>>& aPageArrTwo, char aOptions);
	void LRU_OneMesure(std::vector<Page>& aPageArr);
	void LRU_TwoMesure(std::vector<std::vector<Page>>& aPageArrTwo);
	void chekManyUsed(int aPage);
	//sprawdza, czy strona w argumencie znajduje sie w strukturze
	//ktora przechowuje dane o uzyciu stron (mFrequency)
	//pamieta ile razy kazda ze stron uzylismy
	// jezeli znajdzie -> zwieksza licznik
	//tworzy nowy objekt Frequency
	int minOrMaxManyUsedOptions(int aStep, int aFreeElOfFrame, char aOptions);
	//zwraca index o najmnejszej\najwiekszej liczby powtorzen (zalezy od parametru aOptions)
	// + - najwieksza liczba powtrorzen (dla MFU)
	// - - najmnejsza liczba powtorzen (dla LFU)
	void reserve(int aOptions);
	//ustalia liczbe ramek i dlugosc ciagu odwolan 
	std::vector<Result>& getResul();
	//zwraca wyniki

};
#endif // !C_ALGORITHM_LRU_LFU_MFU_H
