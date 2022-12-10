#include"cController.h"
#include "time.h"
int main()
{
	srand(time(NULL));
	cAlgorithm_FCFS_LCFS_SJF algFLS;
	cOperationFile_FCFS_LCFS_SJF fileFLS;
	cOperationFile_LRU_LFU_MFU fileLLM;
	cAlgorithm_LRU_LFU_MFU algLLM(fileLLM.getDataStorageOneMesures(), fileLLM.gerDataStorageTwoMesures());
	cController controller(algFLS, fileFLS, algLLM, fileLLM);
	while (controller.getAlgorithmState() != 0)
	{
		if (controller.getAlgorithmStateLLM() == 0)
		{
			break;
		}
		controller.draw();
	}
	return 0;
}