#include"SLNeuron.h"

void SLNeuron::PrintWeight()
{
	int s = weight.size();
	for (int i = 0; i < s; i++)
	{
		std::cout << "w" << i << " : " << weight.at(i) << " ";
	}
	std::cout << std::endl;
}

void SLNeuron::Learn(std::vector<int>& expectedOutput)
{
	std::vector<int> output;
	int size = expectedOutput.size();

	std::cout << "Initlal Weight:" << std::endl;
	for (int i = 0; i < size; i++)
	{
		output.push_back(0);
	}

	do {
		GetOutputFromInput(output);
		UpdateWeight(expectedOutput,output);
	} while ((!isLearningOver(expectedOutput,output))&&(learningCount++<limits));

	if (!isLearningOver(expectedOutput, output))//Learning Count가 limit까지 이르렀는데도 원하는 결과가 안나오면 실패. 
		std::cout << "Learning Failed!" << std::endl;


	return;
}

void SLNeuron::GetOutputFromInput(std::vector<int>& output)
{
	std::vector<int> net;
	int n = output.size();
	for(int i=0;i<n;i++)
	{
		net.push_back(0);
	}

	GetNetFromInput(net);
	GetOutputFromNets(net, output);

	return;
}

void SLNeuron::GetNetFromInput(std::vector<int>& net)
{
	int sum = bias*weight.at(0);
	int pow = 1;
	int n = net.size();

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < nofInput; j++)
		{
			sum += ((i&pow)>>j)*weight.at(j+1);
			pow <<= 1;
		}
		net.at(i) = sum;
		sum = bias*weight.at(0);
		pow = 1;
	}

	return;
}
void SLNeuron::GetOutputFromNets(const std::vector<int>& net, std::vector<int>& output)
{
	int size = net.size();

	for (int i = 0; i < size; i++)
	{
		output.at(i) = Activate(net.at(i));
	}

	return;
}

int SLNeuron::Activate(int net)
{
	if (net >= threshold)
		return 1;
	else
		return 0;
}
void SLNeuron::UpdateWeight(const std::vector<int>& expectedOutput,const std::vector<int>& output)
{
	int n = output.size();
	int pow = 1;
	for (int i = 0; i < n; i++)
	{
		weight.at(0) += bias*(expectedOutput.at(i) - output.at(i))*constant;
		for (int j = 0; j < nofInput; j++)
		{
			weight.at(j+1) += ((i&pow)>>j)*(expectedOutput.at(i) - output.at(i))*constant;
			pow <<= 1;
		}
		pow = 1;

	}
	
	PrintWeight();
	return;
}
bool SLNeuron::isLearningOver(const std::vector<int>& expectedOutput, const std::vector<int>& output)
{
	int n = output.size();
	for (int i = 0; i < n; i++)
	{
		if (expectedOutput.at(i) != output.at(i))
			return false;
	}
	return true;
}
