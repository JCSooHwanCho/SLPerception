#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include<random>
#include<chrono>

template<typename T>
class SLNeuron {
public:
	struct NeuronInfo {
		int nofInput;
		T threshold;
		T bias;
		T constant;
		int limits;
	};//Neuron 초기화에 사용할수 있는 구조체

	SLNeuron(int n, std::vector<T>& w, T th, T con, T b, int l) :nofInput(n), threshold(th), constant(con), learningCount(0), limits(l), bias(b)
	{
		weight.assign(w.begin(), w.end());
		MakeExpectedOutput();
	}
	SLNeuron(NeuronInfo& info, std::vector<T>& w) :nofInput(info.nofInput), threshold(info.threshold), constant(info.constant), learningCount(0), limits(info.limits), bias(info.bias)
	{
		weight.assign(w.begin(), w.end());
		MakeExpectedOutput();
	}
	SLNeuron(int n, std::vector<T>& w, T th, T con, T b, int l, std::vector<T>& e) :nofInput(n), threshold(th), constant(con), learningCount(0), limits(l), bias(b)
	{
		weight.assign(w.begin(), w.end());
		if (e.size() != static_cast<int>(pow(2, nofInput)))
		{
			std::cout << "Invalid Output! make new expected output now! " << std::endl;
			MakeExpectedOutput();
		}
		else
		{
			ExpectedOutput.assign(e.begin(), e.end());
		}
	}
	SLNeuron(NeuronInfo& info, std::vector<T>&w, std::vector<T>& e) :nofInput(info.nofInput), threshold(info.threshold), constant(info.constant), learningCount(0), limits(info.limits), bias(info.bias)
	{
		weight.assign(w.begin(), w.end());
		if (e.size() != static_cast<int>(pow(2, nofInput)))
		{
			std::cout << "Invalid Output! make new expected output now! " << std::endl;
			MakeExpectedOutput();
		}
		else
		{
			ExpectedOutput.assign(e.begin(), e.end());
		}

	}

	SLNeuron(SLNeuron<T>& N) : nofInput(N.nofInput), threshold(N.threshold), constant(N.constant), learningCount(N.learningCount), limits(N.limits), bias(N.bias)
	{
		weight.assign(N.weight.begin(), N.weight.end());
		ExpectedOutput.assign(N.ExpectedOutput.begin(), N.ExpectedOutput.end());
	}
	SLNeuron<T>& operator=(SLNeuron<T>& n);
	void Learn();//1번의 Learning을 수행한다.
	T GetOutputFromInput(std::vector<T>& Input);//Input을 벡터형태로 받아 결과값을 반환한다.
	bool isLearningOver();//Learning이 끝났는지 여부를 반환한다.
	static void IntializeVectorWithRangedRandomValue(std::vector<T>& a, int size, int Range);//Weight Vector를 랜덤한 값으로 초기화한다.
private:

	int nofInput;//bias를 제외한 Input값
	std::vector<T> weight;
	T threshold;
	int learningCount;//Learing을 시도한 횟수
	std::vector<T> ExpectedOutput;//원하는 결과출력
	T bias;//고정된 Input값
	T constant;//delta rule에서의 constant
	int limits;//Learning 을 시도할 수 있는 최대치

	void PrintWeight();//객체의 현재 Weight값을 순서대로 출력한다.
	void GetOutputsFromAllInputs(std::vector<T>& output);//output을 저장하고자 하는 vector를 입력받아 모든 Input에 대한 Output값을 저장한다.
	void GetNetsFromAllInputs(std::vector<T>& net);//GetOutFromInput의 내부에서 사용되는 함수로 Input으로 부터 Net값을 얻는다
	void GetOutputsFromNets(const std::vector<T>& net, std::vector<T>& output);//GetOutFromInput의 내부에서 사용되는 함수로 Net값으로 부터 Output값을 얻는다.
	T Activate(T net);//net값을 입력받아 활성화 여부를 반환한다.
	void UpdateWeight(const std::vector<T>& output);//weight를 갱신한다.
	void MakeExpectedOutput();//생성자에서 호출되어 희망하는 출력을 입력받는다.
	void PrintOutputsandExpectedOutputs(const std::vector<T>& output);
};

