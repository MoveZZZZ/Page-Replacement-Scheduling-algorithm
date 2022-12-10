#ifndef C_ALGORITHM_FCFS_LCFS_SJF_H
#define C_ALGORITHM_FCFS_LCFS_SJF_H
#include "cOperationFile_FCFS_LCFS_SJF.h"
class cAlgorithm_FCFS_LCFS_SJF
{
	std::vector<std::vector<float>> mResult;
	//przechowunje wyniki algorytmow typu float 
public:
	cAlgorithm_FCFS_LCFS_SJF();
	void AlgorithmFCFS(std::vector<Process>& aVectorMeasureProcess);
	void AlgorithmFCFStwoMeasures(std::vector<std::vector<Process>>& aVectorMeasureProcess);
	//polega na wywalaniu AlgorithmFCFS dla kazdego z procesow
	void AlgorithmLCFS(std::vector<Process>& aVectorMeasureProcess);
	void AlgorithmLCFStwoMeasures(std::vector<std::vector<Process>>& aVectorMeasureProcess);
	//polega na wywalaniu AlgorithmLCFS dla kazdego z procesow
	void AlgorithmSJF(std::vector<Process>& aVectorMeasureProcess);
	//polega na wywalaniu AlgorithmSJF dla kazdego z procesow
	void AlgorithmSJFtwoMeasures(std::vector<std::vector<Process>>& aVectorMeasureProcess);
	void FCFSvectorSort(std::vector<Process>& aVectorMeasureProcess);
	//buble sort dla FLCFS, przyjmuje wektor ze wszystkimi processami. Sortuje wedlug czasu przybycia ( jezeli 100 porces dotarl jednoczasowo
	// z np 50, to najpierw zostanie obsluzony 50 proces, bo jest wczesnejszym (dzialanie algorytmu))
	void LCFSvectorSort(std::vector<Process>& aVectorMeasureProcess);
	//tak samo, jak w FCFS, ale w innej kolejnosci
	void SJFvectorSort(std::vector<Process>& aVectorMeasureProcess, std::string parametr = "arrival");
	//sortowanie wektora z wartosciami wedlug parametru "arrival" lub "service" (sorotowanie wedlug czasy przebycia
	// \czasu wykonania)
	void AVGturnaroundTimeAndWaithingTime(std::vector<Process>& aVectorMeasureProcess);
	//liczenie sredniego ze srednich wartosci dla turnarondTime i WaithingTime
	std::vector<std::vector<float>>getResult();
	//zwraca wektor z wynikami, zeby zapisac do plikow 
};
#endif // !C_ALGORITHM_FCFS_LCFS_SJF_H

