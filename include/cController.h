#ifndef C_CONTROLLER_H
#define C_CONTROLLER_H
#include "cAlgorithm_FCFS_LCFS_SJF.h"
#include"cAlgorithm_LRU_LFU_MFU.h"
class cController
{
	cAlgorithm_FCFS_LCFS_SJF &FCFS_LCFS_SJF;
	cOperationFile_FCFS_LCFS_SJF &FILE_FCFS_LCFS_SJP;
	int mAlgorithmState; //zawiera wybor algorytmu dla 
	int mFileState; //zawiera wybor uzytkownika, czy chcemy korzystac z generatora, czy z odczytywania pliku
	
	cAlgorithm_LRU_LFU_MFU& LRU_LFU_MFU;
	cOperationFile_LRU_LFU_MFU& FILE_LRU_LFU_MFU;
	int mAlgorithmStateLLM; //zawiera wybor algorytmu dla 
	int mFileStateLLM; //zawiera wybor uzytkownika, czy chcemy korzystac z generatora, czy z odczytywania pliku

public:
	cController(cAlgorithm_FCFS_LCFS_SJF& aAlg, cOperationFile_FCFS_LCFS_SJF& aFile, cAlgorithm_LRU_LFU_MFU &aAlgLLM, cOperationFile_LRU_LFU_MFU &aFileLLM);
	int getAlgorithmState(); // zwraca stan programu dla algorytmow planowania przedzialu procesora
	int getAlgorithmStateLLM(); //zwraca stan programu dla algorytmow przetwarzania stron
	void draw(); //uruchamia program z menu 
};
#endif // !C_CONTROLLER_H



