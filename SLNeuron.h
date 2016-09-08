#pragma once
#include <iostream>
#include <vector>
#include <cmath>
class SLNeuron {
private:
	const int nofInput;
	std::vector<int> weight;
	int threshold;
	int learningCount;//Learing�� �õ��� Ƚ��
	const int bias;
	const int constant;//delta rule������ constant
	const int limits;//Learning �� �õ��� �� �ִ� �ִ�ġ
public:
	SLNeuron(std::vector<int>& w, int th, int con,int b) :nofInput(w.size()-1), threshold(th), constant(con), learningCount(0),limits(100),bias(b)
	{
		weight.assign(w.begin(), w.end());
	}
	void Learn(std::vector<int>& expectedOutput);
private:
	void PrintWeight();
	void GetOutputFromInput(std::vector<int>& output);
	void GetNetFromInput(std::vector<int>& net);
	void GetOutputFromNets(const std::vector<int>& net, std::vector<int>& output);
	int Activate(int net);
	void UpdateWeight(const std::vector<int>& expectedOutput, const std::vector<int>& output);
	bool isLearningOver(const std::vector<int>& expectedOutput, const std::vector<int>& output);

};
