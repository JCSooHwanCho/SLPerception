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
	};//Neuron �ʱ�ȭ�� ����Ҽ� �ִ� ����ü

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
	void Learn();//1���� Learning�� �����Ѵ�.
	T GetOutputFromInput(std::vector<T>& Input);//Input�� �������·� �޾� ������� ��ȯ�Ѵ�.
	bool isLearningOver();//Learning�� �������� ���θ� ��ȯ�Ѵ�.
	static void IntializeVectorWithRangedRandomValue(std::vector<T>& a, int size, int Range);//Weight Vector�� ������ ������ �ʱ�ȭ�Ѵ�.
private:

	int nofInput;//bias�� ������ Input��
	std::vector<T> weight;
	T threshold;
	int learningCount;//Learing�� �õ��� Ƚ��
	std::vector<T> ExpectedOutput;//���ϴ� ������
	T bias;//������ Input��
	T constant;//delta rule������ constant
	int limits;//Learning �� �õ��� �� �ִ� �ִ�ġ

	void PrintWeight();//��ü�� ���� Weight���� ������� ����Ѵ�.
	void GetOutputsFromAllInputs(std::vector<T>& output);//output�� �����ϰ��� �ϴ� vector�� �Է¹޾� ��� Input�� ���� Output���� �����Ѵ�.
	void GetNetsFromAllInputs(std::vector<T>& net);//GetOutFromInput�� ���ο��� ���Ǵ� �Լ��� Input���� ���� Net���� ��´�
	void GetOutputsFromNets(const std::vector<T>& net, std::vector<T>& output);//GetOutFromInput�� ���ο��� ���Ǵ� �Լ��� Net������ ���� Output���� ��´�.
	T Activate(T net);//net���� �Է¹޾� Ȱ��ȭ ���θ� ��ȯ�Ѵ�.
	void UpdateWeight(const std::vector<T>& output);//weight�� �����Ѵ�.
	void MakeExpectedOutput();//�����ڿ��� ȣ��Ǿ� ����ϴ� ����� �Է¹޴´�.
	void PrintOutputsandExpectedOutputs(const std::vector<T>& output);
};

