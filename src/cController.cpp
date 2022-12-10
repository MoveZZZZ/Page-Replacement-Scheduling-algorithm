#include "cController.h"
cController::cController(cAlgorithm_FCFS_LCFS_SJF& aAlg, cOperationFile_FCFS_LCFS_SJF& aFile, cAlgorithm_LRU_LFU_MFU& aAlgLLM, cOperationFile_LRU_LFU_MFU& aFileLLM)
	: FCFS_LCFS_SJF(aAlg), FILE_FCFS_LCFS_SJP(aFile), LRU_LFU_MFU(aAlgLLM), FILE_LRU_LFU_MFU(aFileLLM)
{
	mAlgorithmState = 1;
	mAlgorithmStateLLM = 1;
};
int cController::getAlgorithmState()
{
	return mAlgorithmState;
}
int cController::getAlgorithmStateLLM()
{
	return mAlgorithmStateLLM;
}
void cController::draw()
{
	int FLSoptions;
	int LLMoptions;
	int algorithmNumber;
	int fileOptions;
	int fileOptionsLLM;
	bool writeResult = false;
	bool writeResultLLM = false;
	algorithmChoise:
	std::cout << "Podaj, na ktorych algorytmach chcesz pracowac\n";
	std::cout << "1: FCFS, LCFS, SJF\n";
	std::cout << "2: LRU, LFU, MFU\n";
	std::cin >> algorithmNumber; // prosimy uczytkowanika o tym, z czym chce pracowac
	if (algorithmNumber < 0 || algorithmNumber>2)
	{
		std::cout << "Wybierz liczbe od 1 do 2\n"; // gdy wybor znajduje sie poza 
		//zakresem, pytamy jescze raz i wypisujemy komunikat o bledzie
		goto algorithmChoise;
	}
	mAlgorithmState = algorithmNumber;
	if (algorithmNumber == 1)
	{
		FLSchoise:
		std::cout << "Wybierz algorytm\n";
		std::cout << "1) FCFS\n2) LCFS\n3)SJF\n";
		std::cin >> FLSoptions; //prosimy o algorytm
		if (FLSoptions < 0 || FLSoptions>3) //sprawdzamy, czy podana liczba w zakresie
		{
			std::cout << "Wybierz liczbe od 1 do 3\n";
			goto FLSchoise;
		}
		std::cout << "Wybrales algorytm :" << FLSoptions << std::endl;
		fileOptionsChoise:
		std::cout << "Wybierz, skad chcesz wziac dane dla testowania\n1) Z pliku\n2)Wygenerowac 100 ciagow, zawierajacych 100 procesow\n3)Wygenerowac dowolne liczbe procesow\n";
		std::cin >> fileOptions; //pytamy o dane 
		if (fileOptions < 0 || fileOptions>3)
		{
			std::cout << "Wybierz liczbe od 1 do 3\n";
			goto fileOptionsChoise;
		}
		FILE_FCFS_LCFS_SJP.dataSettings(fileOptions);
		fileOptions = FILE_FCFS_LCFS_SJP.getOptionsNumber();
		FILE_FCFS_LCFS_SJP.writeDateInLastTestFile();
		if (FLSoptions == 1 && fileOptions == 1)
		{
			FCFS_LCFS_SJF.AlgorithmFCFS(FILE_FCFS_LCFS_SJP.getDataStorageOneMesures());
			writeResult = true;
		}
		if (FLSoptions == 1 && fileOptions == 2)
		{
			FCFS_LCFS_SJF.AlgorithmFCFStwoMeasures(FILE_FCFS_LCFS_SJP.getDataStorageTwoMesures());
			writeResult = true;
		}
		if (FLSoptions == 1 && fileOptions == 3)
		{
			FCFS_LCFS_SJF.AlgorithmFCFS(FILE_FCFS_LCFS_SJP.getDataStorageOneMesures());
			writeResult = true;
		}
		if (FLSoptions == 2 && fileOptions == 1)
		{
			FCFS_LCFS_SJF.AlgorithmLCFS(FILE_FCFS_LCFS_SJP.getDataStorageOneMesures());
			writeResult = true;
		}
		if (FLSoptions == 2 && fileOptions == 2)
		{
			FCFS_LCFS_SJF.AlgorithmLCFStwoMeasures(FILE_FCFS_LCFS_SJP.getDataStorageTwoMesures());
			writeResult = true;
		}
		if (FLSoptions == 2 && fileOptions == 3)
		{
			FCFS_LCFS_SJF.AlgorithmLCFS(FILE_FCFS_LCFS_SJP.getDataStorageOneMesures());
			writeResult = true;
		}
		if (FLSoptions == 3 && fileOptions == 1)
		{
			FCFS_LCFS_SJF.AlgorithmSJF(FILE_FCFS_LCFS_SJP.getDataStorageOneMesures());
			writeResult = true;
		}
		if (FLSoptions == 3 && fileOptions == 2)
		{
			FCFS_LCFS_SJF.AlgorithmSJFtwoMeasures(FILE_FCFS_LCFS_SJP.getDataStorageTwoMesures());
			writeResult = true;
		}
		if (FLSoptions == 3 && fileOptions == 3)
		{
			FCFS_LCFS_SJF.AlgorithmSJF(FILE_FCFS_LCFS_SJP.getDataStorageOneMesures());
			writeResult = true;
		}
		if (writeResult)
		{
			FILE_FCFS_LCFS_SJP.writeResultsToFile(FCFS_LCFS_SJF.getResult());
			writeResult = false;
			mAlgorithmState = 0;
		}
	}
	else if (algorithmNumber == 2)
	{
		LLMchoise:
		std::cout << "Wybierz algorytm\n";
		std::cout << "1) LRU\n2) LFU\n3) MFU\n";
		std::cin >> LLMoptions;
		if (LLMoptions < 0 || LLMoptions>3)
		{
			std::cout << "Wybierz liczbe od 1 do 3\n";
			goto LLMchoise;
		}
		std::cout << "Wybrales algorytm :" << LLMoptions << std::endl;
		fileOptionsChoiseLLM:
		std::cout << "Wybierz, skad chcesz wziac dane dla testowania\n1) Z pliku\n2)Wygenerowac 100 ciagow, zawierajacych 100 procesow\n3)Wygenerowac dowolne liczbe procesow\n";
		std::cin >> fileOptionsLLM;
		if (fileOptionsLLM < 0 || fileOptionsLLM>3)
		{
			std::cout << "Wybierz liczbe od 1 do 3\n";
			goto fileOptionsChoiseLLM;
		}
		FILE_LRU_LFU_MFU.dataSettings(fileOptionsLLM);
		fileOptionsLLM = FILE_LRU_LFU_MFU.getOptionsNumber();
		LRU_LFU_MFU.reserve(fileOptionsLLM);
		FILE_LRU_LFU_MFU.writeDateInLastTestFile();
		if (LLMoptions == 1 && fileOptionsLLM == 1)
		{
			LRU_LFU_MFU.LRU_OneMesure(FILE_LRU_LFU_MFU.getDataStorageOneMesures());
			writeResultLLM = true;
		}
		if (LLMoptions == 1 && fileOptionsLLM == 2)
		{
			LRU_LFU_MFU.LRU_TwoMesure(FILE_LRU_LFU_MFU.gerDataStorageTwoMesures());
			writeResultLLM = true;
		}
		if (LLMoptions == 1 && fileOptionsLLM == 3)
		{
			LRU_LFU_MFU.LRU_OneMesure(FILE_LRU_LFU_MFU.getDataStorageOneMesures());
			writeResultLLM = true;
		}
		if (LLMoptions == 2 && fileOptionsLLM == 1)
		{
			LRU_LFU_MFU.LFU_MFU_OneMesure(FILE_LRU_LFU_MFU.getDataStorageOneMesures(), '-');
			writeResultLLM = true;
		}
		if (LLMoptions == 2 && fileOptionsLLM == 2)
		{
			LRU_LFU_MFU.LFU_MFU_TwoMesure(FILE_LRU_LFU_MFU.gerDataStorageTwoMesures(), '-');
			writeResultLLM = true;
		}
		if (LLMoptions == 2 && fileOptionsLLM == 3)
		{
			LRU_LFU_MFU.LFU_MFU_OneMesure(FILE_LRU_LFU_MFU.getDataStorageOneMesures(), '-');
			writeResultLLM = true;
		}
		if (LLMoptions == 3 && fileOptionsLLM == 1)
		{
			LRU_LFU_MFU.LFU_MFU_OneMesure(FILE_LRU_LFU_MFU.getDataStorageOneMesures(), '+');
			writeResultLLM = true;
		}
		if (LLMoptions == 3 && fileOptionsLLM == 2)
		{
			LRU_LFU_MFU.LFU_MFU_TwoMesure(FILE_LRU_LFU_MFU.gerDataStorageTwoMesures(), '+');
			writeResultLLM = true;
		}
		if (LLMoptions == 3 && fileOptionsLLM == 3)
		{
			LRU_LFU_MFU.LFU_MFU_OneMesure(FILE_LRU_LFU_MFU.getDataStorageOneMesures(), '+');
			writeResultLLM = true;
		}
		if (writeResultLLM)
		{
			FILE_LRU_LFU_MFU.writeResultsToFile(LRU_LFU_MFU.getResul());
			writeResultLLM = false;
			mAlgorithmStateLLM = 0;
		}
	}
}
