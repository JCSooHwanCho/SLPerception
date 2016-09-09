#include"SLNeuron.h"
#include<cstdlib>
#include<ctime>


int main()
{
	int NofInput;
	int Threshold;
	int Constant;
	int Bias;

	std::cout << "Insert # of Input(without bias) :";
	std::cin >> NofInput;

	std::cout << "Insert Value of Threshold : ";
	std::cin >> Threshold;

	std::cout << "Insert Value of Constant(except 0) : ";
	std::cin >> Constant;

	std::cout << "Insert Value of Bias(except 0): ";
	std::cin >> Bias;

	if (Constant*Bias == 0)
	{
		std::cout << "Both Constant and Bias mustn't be 0" << std::endl;
		exit(0);
	}

	srand(static_cast<unsigned int>(time(NULL)));

	const int Range_of_Initial_Weight = 10;//weight�� �ʱ�ȭ ����
	const int Half_of_Range = Range_of_Initial_Weight / 2;
	std::vector<int> Initial_Weight;

	for (int i = 0; i <=NofInput; i++)//input�� ����+1(bias)��ŭ�� weight ���� -5~4������ ������ ���� �ʱ�ȭ�Ѵ�. 
	{
		Initial_Weight.push_back(rand() % Range_of_Initial_Weight - Half_of_Range);
	}

	SLNeuron* Neuron = new SLNeuron(NofInput,Initial_Weight, Threshold, Constant,Bias);

	std::vector<int> ExpectedOutput;//����ϰ��� �ϴ� �����
	int NofOutput = static_cast<int>(pow(2, NofInput));
	int a;
	for (int i = 0; i < NofOutput; i++)
	{
		if ((i % 10 == 0) && (i / 10 < 2))
			std::cout << "insert " << i+1 << "st Value of expected output : ";
		else if ((i % 10 == 1) && (i / 10 < 2))
			std::cout << "insert " << i+1 << "nd Value of expected output : ";
		else if ((i % 10 == 2) && (i / 10 < 2))
			std::cout << "insert " << i+1 << "rd Value of expected output : ";
		else
			std::cout << "insert " << i+1 << "th Value of expected output : ";

		std::cin >> a;
		ExpectedOutput.push_back(a);
	}

	Neuron->Learn(ExpectedOutput);

	return 0;
}