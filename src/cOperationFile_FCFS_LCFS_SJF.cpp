#include "cOperationFile_FCFS_LCFS_SJF.h"
cOperationFile_FCFS_LCFS_SJF::cOperationFile_FCFS_LCFS_SJF()
{
	mOptionsNumber = 0;
	mInputFile.open("d:/Admin/Desktop/PWR/PWR 3 SEM/SO Trajdos/SO Lab Klikowski/SO_MAKSIM_FILATAU_projekt_koncowy/SO_MAKSIM_FILATAU/DaneFCFS_LCFS_SJF.txt");
	 //(../Dane
	if (!mInputFile.is_open())
	{
		std::cout << "Nie udalo sie otworzyc plik DaneFCFS_LCFS_SJF.txt\n";
		abort();
	}
	mOutputLastTestFile.open("d:/Admin/Desktop/PWR/PWR 3 SEM/SO Trajdos/SO Lab Klikowski/SO_MAKSIM_FILATAU_projekt_koncowy/SO_MAKSIM_FILATAU/DaneOstatnioTestowaneFCFS_LCFS_SJF.txt");
	if (!mOutputLastTestFile.is_open())
	{
		std::cout << "Nie udalo sie otworzyc plik DaneOstatnioTestowaneFCFS_LCFS_SJF.txt\n";
		abort();
	}
	mOutputResultFile.open("d:/Admin/Desktop/PWR/PWR 3 SEM/SO Trajdos/SO Lab Klikowski/SO_MAKSIM_FILATAU_projekt_koncowy/SO_MAKSIM_FILATAU/WynikiFCFS_LCFS_SJF.txt");
	if (!mOutputResultFile.is_open())
	{
		std::cout << "Nie udalo sie otworzyc plik WynikiFCFS_LCFS_SJF.txt\n";
		abort();
	}
	std::cout << "Wszystkie pliki zostalty poprawnie otworzone\n";
	mDataStorageTwoMesures.resize(100);
	for (auto& mDataStorageTwoMesures : mDataStorageTwoMesures)
	{
		mDataStorageTwoMesures.resize(100);
	}
}
void cOperationFile_FCFS_LCFS_SJF::dataSettings(int aOptions)
{
	mOptionsNumber = aOptions;
	if (aOptions == 1)
	{
		globalReadTestDataFile();
	}
	else if(aOptions == 2)
	{
		gennerate100SetsAnd100Elements();
	}
	else if (aOptions == 3)
	{
		gennerateUserData();
	}
}
void cOperationFile_FCFS_LCFS_SJF::globalReadTestDataFile()
{
	char ch;
	Process tempProcess{};
	std::string dataFromFile;
	std::string saveValue;

	while (mInputFile.get(ch))
	{
		dataFromFile += ch;
	}

	for (int i = 0; i < dataFromFile.size(); i++)
	{
		saveValue = "";
		if (dataFromFile[i] == 'P')
		{
			while (true)
			{
				i += 1;
				if (dataFromFile[i] == ':')
				{
					break;
				}
				saveValue += dataFromFile[i];
			}
			tempProcess.processName = stoi(saveValue);
		}
		if (dataFromFile[i] == 's')
		{
			saveValue = "";
			while (true)
			{
				i += 1;
				if (dataFromFile[i] == '=')
					continue;
				else if (dataFromFile[i] == ' ')
					break;
				saveValue += dataFromFile[i];
			}
			tempProcess.serviceTime = stoi(saveValue);
		}
		if (dataFromFile[i] == 'a')
		{
			saveValue = "";
			while (true)
			{
				i += 1;
				if (dataFromFile[i] == '=')
					continue;
				else if (dataFromFile[i] == '\n' || dataFromFile[i] == '\0')
					break;
				saveValue += dataFromFile[i];
			}
			tempProcess.arrivalTime = stoi(saveValue);
			mDataStorageOneMesures.push_back(tempProcess);
		}
	}
	//gdy rozmiar = 10 000, tro chcemy zbadac algorytm na 100 ciagach, zawierajacych 100 procesow, wiec generujemy wektor
	//dwuwymiarowy
		if (mDataStorageOneMesures.size() == 10000)
		{
			int dataStorageOneMesuresIndex = 0;
			for (auto i = 0; i < 100; i++)
			{
				for (auto j = 0; j < 100; j++)
				{
					mDataStorageTwoMesures[i][j] = mDataStorageOneMesures[dataStorageOneMesuresIndex];
					dataStorageOneMesuresIndex++;
				}
			}
			mOptionsNumber = 2;
		}
	
}
void cOperationFile_FCFS_LCFS_SJF::gennerate100SetsAnd100Elements()
{
	Process tempProcess{};
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			tempProcess.processName = j + 1;
			tempProcess.arrivalTime = rand() % 19 + 2;
			tempProcess.serviceTime = rand() % 19 + 2;
			mDataStorageTwoMesures[i][j] = tempProcess;
		}
	}
}
std::vector<Process>&cOperationFile_FCFS_LCFS_SJF::getDataStorageOneMesures()
{
	return mDataStorageOneMesures;
}
std::vector<std::vector<Process>>& cOperationFile_FCFS_LCFS_SJF::getDataStorageTwoMesures()
{
	return mDataStorageTwoMesures;
}
void cOperationFile_FCFS_LCFS_SJF::writeResultsToFile(std::vector<std::vector<float>> aResult)
{
	for (int i = 0; i < aResult.size(); i++)
	{
		mOutputResultFile << "Set: " << 1 + i;
		mOutputResultFile << "\nAverage Waiting Time: " << aResult[i][0];
		mOutputResultFile << "\nAverage Turanaround Time: " << aResult[i][1] << "\n";
	}
}
void cOperationFile_FCFS_LCFS_SJF::writeDateInLastTestFile()
{
	if (mOptionsNumber == 1 || mOptionsNumber==3)
	{
		for (auto& a : mDataStorageOneMesures)
		{
			mOutputLastTestFile << "P" << a.processName;
			mOutputLastTestFile << ": s=" << a.serviceTime;
			mOutputLastTestFile << " a=" << a.arrivalTime << "\n";
		}
	}
	else if (mOptionsNumber == 2)
	{
		for (int i = 0; i < mDataStorageTwoMesures.size(); i++)
		{
			for (int j = 0; j < mDataStorageTwoMesures[i].size(); j++)
			{
				mOutputLastTestFile << "P" << j + 1 << ": s=" << mDataStorageTwoMesures[i][j].serviceTime
					<< " a=" << mDataStorageTwoMesures[i][j].arrivalTime << "\n";
			}
		}
	}
}
int cOperationFile_FCFS_LCFS_SJF::getOptionsNumber()
{
	return mOptionsNumber;
}
void cOperationFile_FCFS_LCFS_SJF::gennerateUserData()
{
	Process tempProcess{};
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
		if (randMIN <= 1 || randMAX <=2)
		{
			goto writeRandMaxMin;
		}
		for (int i = 0; i < dataCount; i++)
		{
			tempProcess.processName = i + 1;
			tempProcess.arrivalTime = rand() % randMAX + randMIN;
			tempProcess.serviceTime = rand() % randMAX+randMIN;
			mDataStorageOneMesures[i] = tempProcess;
		}
	}

}
cOperationFile_FCFS_LCFS_SJF::~cOperationFile_FCFS_LCFS_SJF()
{
	mInputFile.close();
	mOutputResultFile.close();
	mOutputResultFile.close();
	std::cout << "Pliki zostaly poprawnie zamkniete!\n";
}