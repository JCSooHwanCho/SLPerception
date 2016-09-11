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
		GetOutputsFromAllInputs(output);
		UpdateWeight(expectedOutput,output);
	} while ((!isLearningOver(expectedOutput,output))&&(learningCount++<limits));

	if (!isLearningOver(expectedOutput, output))//Learning Count가 limit까지 이르렀는데도 원하는 결과가 안나오면 실패. 
		std::cout << "Learning Failed!" << std::endl;


	return;
}

void SLNeuron::GetOutputsFromAllInputs(std::vector<int>& output)
{
	std::vector<int> net;
	int n = output.size();
	for(int i=0;i<n;i++)
	{
		net.push_back(0);
	}

	GetNetsFromAllInputs(net);
	GetOutputsFromNets(net, output);

	return;
}

void SLNeuron::GetNetsFromAllInputs(std::vector<int>& net)
{
	int sum = bias*weight.at(0);//bias*weight(0)의 값은 미리 구해놓는다.
	int pow = 1;
	int n = net.size();

	for (int i = 0; i < n; i++)//i는 input의 배열이 되고 j는 배열참조의 Index역할을 하게 된다.
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
void SLNeuron::GetOutputsFromNets(const std::vector<int>& net, std::vector<int>& output)
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
	int error;
	for (int i = 0; i < n; i++)
	{
		error = expectedOutput.at(i) - output.at(i);
		weight.at(0) += bias*error*constant;//Loop안에 넣기 곤란한 bias와의 계산은 따로 한다.
		for (int j = 0; j < nofInput; j++)
		{
			weight.at(j+1) += ((i&pow)>>j)*error*constant;
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
		if (expectedOutput.at(i) != output.at(i))//기대 출력값과 하나라도 다른게 있으면 false
			return false;
	}
	return true;
}
int SLNeuron::GetOutputFromInput(std::vector<int> Input)//Input의 유효성 검사와 동시에 Output 값을 반환한다.
{
	if (nofInput != Input.size())
	{
		std::cout << "Invalid Input!" << std::endl;
		return -1;
	}
	
	int sum=bias*weight.at(0);

	for (int i = 0; i < nofInput; i++)
	{
		if (Input.at[i] < 0 && Input.at[i]>1)
		{
			std::cout << "Invalid Input!" << std::endl;
			return -1;
		}
		sum += Input.at(i)*weight.at(i + 1);
	}

	return Activate(sum);
}