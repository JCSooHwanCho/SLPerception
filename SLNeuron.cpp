#include "SLNeuron.h"


template <typename T>
void SLNeuron<T>::PrintWeight()
{
	int s = weight.size();
	for (int i = 0; i < s; i++)
	{
		std::cout << "w" << i << " : " << weight.at(i) << " ";
	}
	std::cout << std::endl;
}

template <typename T>
void SLNeuron<T>::Learn()
{
	std::vector<T> output;
	int size = static_cast<int>(pow(2, nofInput));

	if (learningCount == 0)
	{
		std::cout << "Initial Weight" << std::endl;
		PrintWeight();
		std::cout << std::endl;
	}

	for (int i = 0; i < size; i++)
	{
		output.push_back(0);
	}

	GetOutputsFromAllInputs(output);
	UpdateWeight(output);
	learningCount++;

	return;
}

template<typename T>
void SLNeuron<T>::GetOutputsFromAllInputs(std::vector<T>& output)
{
	std::vector<T> net;
	int n = static_cast<int>(pow(2, nofInput));
	for (int i = 0; i<n; i++)
	{
		net.push_back(0);
	}

	GetNetsFromAllInputs(net);
	GetOutputsFromNets(net, output);

	return;
}

template <typename T>
void SLNeuron<T>::GetNetsFromAllInputs(std::vector<T>& net)
{
	T sum = bias*weight.at(0);//bias*weight(0)의 값은 미리 구해놓는다.
	int pow = 1;
	int n = net.size();

	for (int i = 0; i < n; i++)//i는 input의 배열이 되고 j는 배열참조의 Index역할을 하게 된다.
	{
		for (int j = 0; j < nofInput; j++)
		{
			if ((i&pow) >> j == 1)
			{
				sum += weight.at(j + 1);
			}
			pow <<= 1;
		}
		net.at(i) = sum;
		sum = bias*weight.at(0);
		pow = 1;
	}

	return;
}

template <typename T>
void SLNeuron<T>::GetOutputsFromNets(const std::vector<T>& net, std::vector<T>& output)
{
	int size = net.size();

	for (int i = 0; i < size; i++)
	{
		output.at(i) = Activate(net.at(i));
	}

	return;
}

template <typename T>
T SLNeuron<T>::Activate(T net)
{
	if (net >= threshold)
		return static_cast<T>(1);
	else
		return static_cast<T>(0);
}


template <typename T>
void SLNeuron<T>::UpdateWeight(const std::vector<T>& output)
{
	int n = static_cast<int>(pow(2, nofInput));
	int p = 1;
	T error;

	for (int i = 0; i < n; i++)
	{
		error = ExpectedOutput.at(i) - output.at(i);
		weight.at(0) += bias*error*constant;//Loop안에 넣기 곤란한 bias와의 계산은 따로 한다.
		for (int j = 0; j < nofInput; j++)
		{
			if (((i&p) >> j) == 1)
			{
				weight.at(j + 1) += error*constant;
			}
			p <<= 1;
		}
		p = 1;

	}
	std::cout << "learning " << learningCount + 1<<std::endl;
	PrintWeight();
	return;
}

template <typename T>
bool SLNeuron<T>::isLearningOver()
{
	int n = ExpectedOutput.size();
	std::vector<T> output;
	if (learningCount >= limits)
	{
		std::cout << "learning limit exceeds!" << std::endl;
		return true;
	}
	for (int i = 0; i<n; i++)
	{
		output.push_back(0);
	}

	GetOutputsFromAllInputs(output);
	for (int i = 0; i < n; i++)
	{
		if (ExpectedOutput.at(i) != output.at(i))
			return false;
	}
	return true;
}

template <typename T>
T SLNeuron<T>::GetOutputFromInput(std::vector<T>& Input)//Input의 유효성 검사와 동시에 Output 값을 반환한다.
{
	if (nofInput != Input.size())
	{
		std::cout << "Invalid Input!" << std::endl;
		return static_cast<T>(-1);
	}

	int sum = bias*weight.at(0);

	for (int i = 0; i < nofInput; i++)
	{
		if (Input.at(i) < 0 && Input.at(i)>1)
		{
			std::cout << "Invalid Input!" << std::endl;
			return -1;
		}
		sum += Input.at(i)*weight.at(i + 1);
	}

	return Activate(sum);
}

template <typename T>
void SLNeuron<T>::MakeExpectedOutput()
{
	int NofOutput = static_cast<int>(pow(2, nofInput));
	T a;
	for (int i = 0; i < NofOutput; i++)
	{
		if ((i % 10 == 0) && (i / 10 < 2))
			std::cout << "insert " << i + 1 << "st Value of expected output : ";
		else if ((i % 10 == 1) && (i / 10 < 2))
			std::cout << "insert " << i + 1 << "nd Value of expected output : ";
		else if ((i % 10 == 2) && (i / 10 < 2))
			std::cout << "insert " << i + 1 << "rd Value of expected output : ";
		else
			std::cout << "insert " << i + 1 << "th Value of expected output : ";

		std::cin >> a;
		ExpectedOutput.push_back(a);
	}
}

template <typename T>
SLNeuron<T>& SLNeuron<T>::operator=(SLNeuron<T>& n)
{
	nofInput = n.nofInput;
	weight.assign(n.weight.begin(), n.weight.end());
	threshold = n.threshold;
	learningCount = n.learningCount;
	ExpectedOutput.assign(n.ExpectedOutput.begin(), n.ExpectedOutput.end());
	bias = n.bias;
	constant = n.constant;
	limits = n.limits;

	return *this;
}