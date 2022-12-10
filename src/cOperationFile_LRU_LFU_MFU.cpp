#include "cOperationFile_LRU_LFU_MFU.h"
cOperationFile_LRU_LFU_MFU::cOperationFile_LRU_LFU_MFU()
{
	mOptionsNumber = 0;
	mProcess = 20;
	mInputFile.open("d:/Admin/Desktop/PWR/PWR 3 SEM/SO Trajdos/SO Lab Klikowski/SO_MAKSIM_FILATAU_projekt_koncowy/SO_MAKSIM_FILATAU/DaneLRU_LFU_MFU.txt");
	if (!mInputFile.is_open())
	{
		std::cout << "Nie udalo sie otworzyc plik DaneLRU_LFU_MFU.txt!\n";
		abort();	
	}
	mOutputLastTestFile.open("d:/Admin/Desktop/PWR/PWR 3 SEM/SO Trajdos/SO Lab Klikowski/SO_MAKSIM_FILATAU_projekt_koncowy/SO_MAKSIM_FILATAU/DaneOstatnioTestowaneLRU_LFU_MFU.txt");
	if (!mOutputLastTestFile.is_open())
	{
		std::cout << "Nie udalo sie otworzyc plik DaneOstatnieTestowaneLRU_LFU_MFU.txt!\n ";
		abort();
	}
	mOutputResultFile.open("d:/Admin/Desktop/PWR/PWR 3 SEM/SO Trajdos/SO Lab Klikowski/SO_MAKSIM_FILATAU_projekt_koncowy/SO_MAKSIM_FILATAU/WynikiLRU_LFU_MFU.txt");
	if (!mOutputResultFile.is_open())
	{
		std::cout << "Nie udalo sie otworzyc plik WynikiLRU_LFU_MFU.txt!\n";
		abort();
	}
	std::cout << "Wszystkie pliki dla algorytmow LRU_LFU_MFU zostaly poprawnie otworzone!\n";
	mDataStorageTwoMesures.resize(100);
	for (auto& mDataStorageTwoMesures : mDataStorageTwoMesures)
	{
		mDataStorageTwoMesures.resize(100);
	}
}
void cOperationFile_LRU_LFU_MFU::dataSettings(int aOptions)
{
	mOptionsNumber = aOptions;
	if (aOptions == 1)
	{
		globalReadTestDataFile();
	}
	else if (aOptions == 2)
	{
		gennerate100SetsAnd100Elements();
	}
	else if (aOptions == 3)
	{
		gennerateUserData();
	}
}
void cOperationFile_LRU_LFU_MFU::globalReadTestDataFile()
{
	char ch;
	Page tempPage;
	std::string dataFromFile;
	std::string saveValue;
	while (mInputFile.get(ch))
	{
		dataFromFile += ch;
	}
	for (int i = 0; i < dataFromFile.size(); i++)
	{
		saveValue = "";
		while (i < dataFromFile.size())
		{
			if (dataFromFile[i] == ' ' || dataFromFile[i] == '\n')
			{
				break;
			}
			saveValue += dataFromFile[i];
			i++;
		}
		tempPage.page = stoi(saveValue);
		tempPage.used = 0;
		mDataStorageOneMesures.push_back(tempPage);
	}
	if (mDataStorageOneMesures.size() == 10000)
	{
		int index = 0;
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				mDataStorageTwoMesures[i][j] = mDataStorageOneMesures[index];
				index++;
			}
		}
		mOptionsNumber = 2;
	}
}
void cOperationFile_LRU_LFU_MFU::gennerate100SetsAnd100Elements()
{
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			mDataStorageTwoMesures[i][j].page = rand() % mProcess + 1;
			mDataStorageTwoMesures[i][j].used = 0;
		}
	}
	std::cout << "";
}
std::vector<Page>& cOperationFile_LRU_LFU_MFU::getDataStorageOneMesures()
{
	return mDataStorageOneMesures;
}
std::vector<std::vector<Page>>& cOperationFile_LRU_LFU_MFU::gerDataStorageTwoMesures()
{
	return mDataStorageTwoMesures;
}
void cOperationFile_LRU_LFU_MFU::gennerateUserData()
{
	Page tempPage{};
	int dataCount;
	int randMAX;
	int randMIN;
	std::cout << "Napisz, ile danych chcesz wygenerowac(100/200/.../9900)!\n";
	std::cin >> dataCount;
	if (dataCount >= 100 && dataCount <= 9900 && dataCount % 100 == 0)
	{
		mDataStorageOneMesures.resize(dataCount);
	writeRandMaxMin:
		std::cout << "Wybierz przedzial losowania!, wartosc minimalna ma byc > 1, max > 2\nMinimalna wartosc: ";
		std::cin >> randMIN;
		std::cout << "Max wartosc: ";
		std::cin >> randMAX;
		if (randMIN <= 1 || randMAX <= 2)
		{
			goto writeRandMaxMin;
		}
		for (int i = 0; i < dataCount; i++)
		{
			tempPage.page = rand() % randMAX + randMIN;
			tempPage.used = 0;
			mDataStorageOneMesures[i] = tempPage;
		}
	}

}
void cOperationFile_LRU_LFU_MFU::writeResultsToFile(std::vector<Result>& aResult)
{
	for (int i = 0; i < aResult.size(); ++i)
	{
		mOutputResultFile << "Hit:" << aResult[i].hit << "  ";
		mOutputResultFile << "Fault:" << aResult[i].fault << "\n";
	}
}
void  cOperationFile_LRU_LFU_MFU::writeDateInLastTestFile()
{
	if (mOptionsNumber == 1||mOptionsNumber==3)
	{
		for (auto& i : mDataStorageOneMesures)
		{
			mOutputLastTestFile << i.page << " ";
		}
	}
	else if (mOptionsNumber==2)
	{
		for (int i = 0; i < mDataStorageTwoMesures.size(); ++i)
		{
			for (int j = 0; j < mDataStorageTwoMesures[i].size(); ++j)
			{
				mOutputLastTestFile << mDataStorageTwoMesures[i][j].page << " ";
			}
				
		}	
	}
}
int cOperationFile_LRU_LFU_MFU::getOptionsNumber()
{
	return mOptionsNumber;
}
cOperationFile_LRU_LFU_MFU::~cOperationFile_LRU_LFU_MFU()
{
	mInputFile.close();
	mOutputLastTestFile.close();
	mOutputResultFile.close();
}