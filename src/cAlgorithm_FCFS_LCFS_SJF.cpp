#include "cAlgorithm_FCFS_LCFS_SJF.h"
cAlgorithm_FCFS_LCFS_SJF::cAlgorithm_FCFS_LCFS_SJF()
{
}
void cAlgorithm_FCFS_LCFS_SJF::FCFSvectorSort(std::vector<Process>& aVectorMeasureProcess)
{
	//std::sort(aVectorMeasureProcess.begin(), aVectorMeasureProcess.end(),
		//[](const Process& f, const Process& s) {return f.arrivalTime < s.arrivalTime; });

	bool isSwap;
	for (int i = 0; i < aVectorMeasureProcess.size() - 1; i++)
	{
		isSwap = false;
		for (int j = 0; j < aVectorMeasureProcess.size() - i - 1; j++)
		{
			if (aVectorMeasureProcess[j].arrivalTime > aVectorMeasureProcess[j + 1].arrivalTime)
			{
				std::swap(aVectorMeasureProcess[j], aVectorMeasureProcess[j + 1]);
				isSwap = true;
			}
		}
		if (!isSwap)
		{
			break;
		}
	}
	
}
void cAlgorithm_FCFS_LCFS_SJF::LCFSvectorSort(std::vector<Process>& aVectorMeasureProcess)
{
	//std::sort(aVectorMeasureProcess.begin(), aVectorMeasureProcess.end(), [](const Process& f, const Process& s) {return f.arrivalTime < s.arrivalTime; });
	bool isSwap = false;
	for (int i = 0; i < aVectorMeasureProcess.size() - 1; i++)
	{
		isSwap = false;
		for (int j = 0; j < aVectorMeasureProcess.size() - i - 1; j++)
		{
			if (aVectorMeasureProcess[j].arrivalTime < aVectorMeasureProcess[j + 1].arrivalTime)
			{
				std::swap(aVectorMeasureProcess[j], aVectorMeasureProcess[j + 1]);
				isSwap = true;
			}
		}
		if (!isSwap)
		{
			break;
		}
	}
	for (int i = 0; i < aVectorMeasureProcess.size() - 1; i++)
	{
		for (int j = 0; j < aVectorMeasureProcess.size() - i - 1; j++)
		{
			if (aVectorMeasureProcess[j].arrivalTime == aVectorMeasureProcess[j + 1].arrivalTime && aVectorMeasureProcess[j].processName < aVectorMeasureProcess[j + 1].processName)
			{
				std::swap(aVectorMeasureProcess[j], aVectorMeasureProcess[j + 1]);
			}
		}
	}
}
void cAlgorithm_FCFS_LCFS_SJF::SJFvectorSort(std::vector<Process>& aVectorMeasureProcess, std::string parametr)
{
	bool isSwap = false;
	for (int i = 0; i < aVectorMeasureProcess.size() - 1; i++)
	{
		isSwap = false;
		for (int j = 0; j < aVectorMeasureProcess.size() - i - 1; j++)
		{
			if (aVectorMeasureProcess[j].arrivalTime > aVectorMeasureProcess[j + 1].arrivalTime && parametr == "arrival")
			{
				std::swap(aVectorMeasureProcess[j], aVectorMeasureProcess[j + 1]);
				isSwap = true;
			}
			if (aVectorMeasureProcess[j].serviceTime > aVectorMeasureProcess.at(j+1).serviceTime && parametr == "service")
			{
				std::swap(aVectorMeasureProcess[j], aVectorMeasureProcess[j + 1]);
				isSwap = true;
			}
		}
		if (!isSwap)
		{
			break;
		}
	}
}
void cAlgorithm_FCFS_LCFS_SJF::AVGturnaroundTimeAndWaithingTime(std::vector<Process>& aVectorMeasureProcess)
{
	float averageTurnaroundTime = 0;
	float averageWaitingTime = 0;
	std::vector<float> result;
	for (int i = 0; i < aVectorMeasureProcess.size(); i++)
	{
		averageTurnaroundTime += aVectorMeasureProcess[i].turnArroudTime;
		averageWaitingTime += aVectorMeasureProcess[i].waitingTime;
	}
	averageTurnaroundTime = averageTurnaroundTime / aVectorMeasureProcess.size();
	averageWaitingTime = averageWaitingTime / aVectorMeasureProcess.size();
	result.push_back(averageWaitingTime);
	result.push_back(averageTurnaroundTime);
	mResult.push_back(result);
}
void cAlgorithm_FCFS_LCFS_SJF::AlgorithmFCFS(std::vector<Process>& aVectorMeasureProcess)
{
	//najpierw sortujemy dane wedlug wymaganych warunkow
	FCFSvectorSort(aVectorMeasureProcess);
	float currentTime = 0;
	for (int i = 0; i < aVectorMeasureProcess.size(); i++) // iteracja po wszystkim processam
	{
		if (currentTime < aVectorMeasureProcess[i].arrivalTime) // jezeli zaden process nie czeka na wywalanie, znaczy ze process
			//zaczyna sie w czasie przybycia
		{
			aVectorMeasureProcess[i].startedTime = aVectorMeasureProcess[i].arrivalTime;
			currentTime = aVectorMeasureProcess[i].serviceTime + aVectorMeasureProcess[i].startedTime;
		}
		else // jezeli process juz czeka na wywalanie, znaczy musi sie zaczac w momencie, gdy konczy sie ostatni
		{
			aVectorMeasureProcess[i].startedTime = currentTime;
			currentTime += aVectorMeasureProcess[i].serviceTime; // obliczanie czasu, w ktorym process sie skonczyl
		}
		aVectorMeasureProcess[i].competedTime = currentTime;
		aVectorMeasureProcess[i].turnArroudTime = aVectorMeasureProcess.at(i).competedTime - aVectorMeasureProcess.at(i).arrivalTime;
		aVectorMeasureProcess[i].waitingTime = aVectorMeasureProcess.at(i).turnArroudTime - aVectorMeasureProcess.at(i).serviceTime;
	}
	AVGturnaroundTimeAndWaithingTime(aVectorMeasureProcess);
}
void cAlgorithm_FCFS_LCFS_SJF::AlgorithmLCFS(std::vector<Process>& aVectorMeasureProcess)
{
	//najpierw sortujemy dane wedlug wymaganych warunkow
	LCFSvectorSort(aVectorMeasureProcess);
	float currentTime = 0;
	for (int i = 0; i < aVectorMeasureProcess.size(); i++) //iteracja po wszystkim processam
	{
		if (currentTime < aVectorMeasureProcess[i].arrivalTime) // jezeli zaden process nie czeka na wywalanie, znaczy ze process
			//zaczyna sie w czasie przybycia
		{
			aVectorMeasureProcess[i].startedTime = aVectorMeasureProcess[i].arrivalTime;
			currentTime = aVectorMeasureProcess[i].serviceTime + aVectorMeasureProcess[i].startedTime;
		}
		else
		{
			aVectorMeasureProcess[i].startedTime = currentTime; 
			currentTime += aVectorMeasureProcess[i].serviceTime; // obliczanie czasu, w ktorym process sie skonczyl
		}
		aVectorMeasureProcess[i].competedTime = currentTime;
		aVectorMeasureProcess[i].turnArroudTime = aVectorMeasureProcess.at(i).competedTime - aVectorMeasureProcess.at(i).arrivalTime;
		aVectorMeasureProcess[i].waitingTime = aVectorMeasureProcess.at(i).turnArroudTime - aVectorMeasureProcess.at(i).serviceTime;
	}
	AVGturnaroundTimeAndWaithingTime(aVectorMeasureProcess);
}
void cAlgorithm_FCFS_LCFS_SJF::AlgorithmSJF(std::vector<Process>& aVectorMeasureProcess)
{
	std::vector<Process> correctSequence; // prawidlowa kolejniosc processow
	std::vector<Process> tempQueue; //czasowa kolejka processow 
	SJFvectorSort(aVectorMeasureProcess); // sortujemy processy malejaco wedlug czasu przebycia (parametr domyslny)
	float currentTime = 0;
	int size = aVectorMeasureProcess.size();
	bool firstIteration = true;
	for (int i = 0; i < size; i++)
	{
		//wpisujemy do kolejki elementy, ktore czkaja na wywalanie
		for (int j = 0; j < aVectorMeasureProcess.size(); j++) // iteracja po wszystkim procesam
		{
			if (currentTime >= aVectorMeasureProcess[j].arrivalTime || firstIteration)
				//jezeli czas >= czasu przebycia, znaczy ze proces czeka na wywalanie
			{
				tempQueue.push_back(aVectorMeasureProcess[j]);
				aVectorMeasureProcess.erase(aVectorMeasureProcess.begin() + j); // zmnejaszmy wektor
				j = -1; // zmnejaszmy, bo zmnejszylismy wektor
				firstIteration = false;
			}
		}
		if (!tempQueue.empty())
		{
			SJFvectorSort(tempQueue, "service"); // sortujemy wektor wedlug czasu obslugi
			correctSequence.push_back(tempQueue[0]);
			tempQueue.erase(tempQueue.begin());
		}
		else // zaden proces nie czeka na wywalanie
		{
			--i;
			currentTime = aVectorMeasureProcess[0].arrivalTime; //zwiekszamy czas
			continue;
		}
		if (currentTime < correctSequence[i].arrivalTime)
		{
			correctSequence[i].startedTime = correctSequence[i].arrivalTime;
			currentTime = correctSequence[i].serviceTime + correctSequence[i].startedTime;
		}
		else
		{
			correctSequence[i].startedTime = currentTime;
			currentTime += correctSequence[i].serviceTime;
		}
		correctSequence[i].competedTime = currentTime;
		correctSequence[i].turnArroudTime = correctSequence.at(i).competedTime - correctSequence.at(i).arrivalTime;
		correctSequence[i].waitingTime = correctSequence.at(i).turnArroudTime - correctSequence.at(i).serviceTime;
	}
	AVGturnaroundTimeAndWaithingTime(correctSequence);
}
void cAlgorithm_FCFS_LCFS_SJF::AlgorithmFCFStwoMeasures(std::vector<std::vector<Process>>& aVectorMeasureProcess)
{
	for (int i = 0; i < aVectorMeasureProcess.size(); i++)
	{
		AlgorithmFCFS(aVectorMeasureProcess[i]);
	}
}
void cAlgorithm_FCFS_LCFS_SJF::AlgorithmLCFStwoMeasures(std::vector<std::vector<Process>>& aVectorMeasureProcess)
{
	for (int i = 0; i < aVectorMeasureProcess.size(); i++)
	{
		AlgorithmLCFS(aVectorMeasureProcess[i]);
	}
}
void cAlgorithm_FCFS_LCFS_SJF::AlgorithmSJFtwoMeasures(std::vector<std::vector<Process>>& aVectorMeasureProcess)
{
	for (int i = 0; i < aVectorMeasureProcess.size(); i++)
	{
		AlgorithmSJF(aVectorMeasureProcess[i]);
	}
}
std::vector<std::vector<float>>cAlgorithm_FCFS_LCFS_SJF::getResult()
{
	return mResult;
}

