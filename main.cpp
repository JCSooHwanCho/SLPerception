#include"SLNeuron.h"
#include<cstdlib>
#include<ctime>
#include"SLNeuron.cpp"

template <typename T>
void IntializeVectorWithRangedRandomValue(std::vector<T>& a, int size, int Range);//size만큼의 weight 값을 -Half~(Half-1)사이의 임의의 수로 초기화한다. 

int main()
{
	int NofInput;
	double Threshold;
	double Constant;
	double Bias;
	int Limit;

	std::cout << "Insert # of Input(without bias) :";
	std::cin >> NofInput;

	std::cout << "Insert Value of Threshold : ";
	std::cin >> Threshold;

	std::cout << "Insert Value of Constant(except 0) : ";
	std::cin >> Constant;

	std::cout << "Insert Value of Bias(except 0) : ";
	std::cin >> Bias;

	if (Constant*Bias == 0)
	{
		std::cout << "Both Constant and Bias mustn't be 0" << std::endl;
		exit(1);
	}
	std::cout << "Insert Value of limit of Learning : ";
	std::cin >> Limit;

	srand(static_cast<unsigned int>(time(NULL)));

	const int Range_of_Initial_Weight = 10;//weight의 초기화 범위
	std::vector<double> Initial_Weight;

	IntializeVectorWithRangedRandomValue(Initial_Weight,NofInput+1,Range_of_Initial_Weight);

	SLNeuron<double> *Neuron = new SLNeuron<double>(NofInput,Initial_Weight, Threshold, Constant,Bias,Limit);

	while (!(Neuron->isLearningOver()))
	{
		Neuron->Learn();
	}

	delete Neuron;
	return 0;
}

template <typename T>
void IntializeVectorWithRangedRandomValue(std::vector<T>& a, int size, int Range)
{
	int Half = Range / 2;
	for (int i = 0; i < size; i++)
	{
		a.push_back(static_cast<T>(rand() % Range - Half));
	}
}