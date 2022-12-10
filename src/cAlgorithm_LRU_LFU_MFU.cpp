#include "cAlgorithm_LRU_LFU_MFU.h"
cAlgorithm_LRU_LFU_MFU::cAlgorithm_LRU_LFU_MFU(std::vector<Page>& aDataStorageOneMesures, std::vector<std::vector<Page>>& aDataStorageTwoMesures)
	:mDataStorageOneMesures(aDataStorageOneMesures), mDataStorageTwoMesures(aDataStorageTwoMesures)
{
}
void cAlgorithm_LRU_LFU_MFU::LFU_MFU_OneMesure(std::vector<Page>& aPageArr, char aOptions)
{
	int freeElofFrame = mFrameNumber;
	int hit = 0; 
	int fault = 0;
	bool isSwap = false;
	for (int i = 0; i < mStringLen; i++)
	{
		for (int j = 0; j < mFrameNumber; j++) //iteracja po ramce 
		{
			// jeżeli równa -1, wiemy ze nie stosowaliśmy tego pola
			if (mTable[i][j] == -1)  //1) puste mejsce w ramce 
			{
				fault+=1;       
				isSwap = true;
				chekManyUsed(aPageArr[i].page);
			}
			else if (mTable[i][j] == aPageArr[i].page) //2)taka sama strona w ramce
			{
				hit+=1;
				isSwap = false;
				chekManyUsed(aPageArr[i].page);
			}
			else if (mTable[i][j] != aPageArr[i].page && j == mFrameNumber - 1) //3)jestesmy na koncu w ramce(ostatni elemnt)
				//i nie mamy takiej samej strony
			{
				fault+=1;
				isSwap = true;
				chekManyUsed(aPageArr[i].page);
			}
			if (isSwap)
			{
				int temp = aPageArr[i].page;
				mTable[i].erase(mTable[i].begin() + minOrMaxManyUsedOptions(i, freeElofFrame, aOptions)); //usuwanie strony
				//minOrMaxManyUsedOptions dacyduje, jaka strone mamy usunac 
				mTable[i].push_front(temp);
				freeElofFrame -= 1;
				isSwap = false;
				break;
			}
		}
		if (i < mStringLen - 1) //przepisujemy strony do nastepnej ramki
		{
			for (int j = 0; j < mFrameNumber; j++)
			{
				mTable[i + 1][j] = mTable[i][j];
			}
		}
	}
	Result tempDataResult;
	tempDataResult.fault = aPageArr.size()-hit;
	tempDataResult.hit = hit;
	mResult.push_back(tempDataResult);

}
void cAlgorithm_LRU_LFU_MFU::LFU_MFU_TwoMesure(std::vector<std::vector<Page>>& aPageArrTwo, char aOptions)
{
	for (int i = 0; i < aPageArrTwo.size(); i++)
	{
		LFU_MFU_OneMesure(aPageArrTwo[i], aOptions);
	}
}
void cAlgorithm_LRU_LFU_MFU::LRU_OneMesure(std::vector<Page>& aPageArr)
{
	int hit = 0, fault = 0;
	bool isSwap = false;
	for (int i = 0; i < mStringLen; i++)
	{
		for (int j = 0; j < mFrameNumber; j++) //iteracja po ramce
		{
			if (mTable[i][j] == -1) // gdy = -1, znaczy nie stosowalismy tego pola 
			{
				fault += 1;
				isSwap = true;
			}
			else if (mTable[i][j] == aPageArr[i].page) //gdzy w ramce juz sie znajduje liczba ktora
				//jest nasteona w ciagu, zwiekszamy liczbe trafien,
				///zmienimy kolejnosc numerow w taki sposob zeby ta liczba byla na 1 mejscu
			{
				hit += 1;
				isSwap = true;
			}
			else if (mTable[i][j] != aPageArr[i].page && j == mFrameNumber - 1)//gdy jestesmy na ostatnej ramce i nie znalazlismy liczbe 
				//w ramce
			{
				fault += 1;
				isSwap = true;
			}
			if (isSwap)
			{
				int tempPage = aPageArr[i].page;
				mTable[i].erase(mTable[i].begin() + j);
				mTable[i].push_front(tempPage);
				isSwap = false;
				break;
			}
		}
		if (i < mStringLen - 1) //wpisujemy stan aktualnej ramki
		{
			for (int j = 0; j < mFrameNumber; j++)
			{
				mTable[i + 1][j] = mTable[i][j];
			}
		}
	}
	Result tempDataResult;
	tempDataResult.fault = fault;
	tempDataResult.hit = hit;
	mResult.push_back(tempDataResult);
}
void cAlgorithm_LRU_LFU_MFU::LRU_TwoMesure(std::vector<std::vector<Page>>& aPageArrTwo)
{
	for (int i = 0; i < aPageArrTwo.size(); i++)
	{
		LRU_OneMesure(aPageArrTwo[i]);
	}
}
void cAlgorithm_LRU_LFU_MFU::chekManyUsed(int aPage)
{
	//iterujemy sie po wszystkim elementam i szukamy liczbe stron, jezeli 
	//znalazlismy, zwiekszamy liczbe used i wychodzimy, jezeli nie - tworzymy 
	//taki element
	for (int i = 0; i < mFrequency.size(); ++i)
	{
		if (mFrequency[i].page == aPage)
		{
			mFrequency[i].used += 1;
			return;
		}
	}
	Frequency tempFreq;
	tempFreq.page = aPage;
	tempFreq.used = 1;
	mFrequency.push_front(tempFreq);
}
int cAlgorithm_LRU_LFU_MFU::minOrMaxManyUsedOptions(int aStep, int aFreeElOfFrame, char aOptions)
{
   if (aFreeElOfFrame > 0)
	{
		return aStep;
	}
	std::vector<IndexRepetition> repIndexVector; //przechowuje index i liczbe zastosowan wartosci pod tym samym indexem
	int index = 0;
	for (int i = 0; i < mTable[aStep].size(); i++) //iteracja po ramce
	{
		for (int j = 0; j < mFrequency.size(); j++) //iteracja po elementam structury z liczba zastosowan kazdej ze stron
		{
			if (mFrequency[j].page == mTable[aStep][i]) //jezeli mamy taki element, zwiekszmy licznik i wpisujemy dane do repIndexVector
			{
				IndexRepetition tempRepIndex;
				tempRepIndex.used = mFrequency[j].used;
				tempRepIndex.index = i;
				repIndexVector.push_back(tempRepIndex);
				break;
			}
		}
	}
	int tempRep = repIndexVector[0].used;
	if (aOptions == '-')
	{
		for (int j = 0; j < repIndexVector.size() - 1; j++) //dostajemy index elementu o najmnejszej liczbie zastosowan
		{
			if (tempRep >= repIndexVector[j + 1].used)
			{
				index = j + 1;
				tempRep = repIndexVector[index].used;
			}
		}
	}
	else
	{
		for (int j = 0; j < repIndexVector.size() - 1; j++)  //dostajemy index elementu o najwiekszej liczbie zastosowan
		{
			if (tempRep <= repIndexVector[j + 1].used)
			{
				index = j + 1;
				tempRep = repIndexVector[index].used;
			}
		}
	}
	return repIndexVector[index].index;
	

}
void cAlgorithm_LRU_LFU_MFU::reserve(int aOptions)
{
	mFrameNumber = 7; //aktualna liczba ramek pamieci fizycznej 
	if (aOptions == 1)
	{
		mStringLen = mDataStorageOneMesures.size();
	}
	else
	{
		mStringLen = mDataStorageTwoMesures.size();
	}
	//wpisujemy -1 zeby sprawdzic czy po raz pierwszy korzystamy z ramki
	std::deque<int> temp(mFrameNumber, -1);
	for (int i = 0; i < mStringLen; ++i)
	{
		mTable.push_back(temp);
	}
} 
std::vector<Result>& cAlgorithm_LRU_LFU_MFU::getResul()
{
	return mResult;
}
