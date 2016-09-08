#pragma once
#include <iostream>
#include <vector>
#include <cmath>
class SLNeuron {
private:
	const int nofInput;
	std::vector<int> weight;
	int threshold;
	int learningCount;//Learing을 시도한 횟수
	const int bias;
	const int constant;//delta rule에서의 constant
	const int limits;//Learning 을 시도할 수 있는 최대치
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
