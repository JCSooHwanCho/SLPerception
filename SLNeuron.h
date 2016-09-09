#pragma once
#include <iostream>
#include <vector>
#include <cmath>
class SLNeuron {
private:
	const int nofInput;//bias를 제외한 Input값
	std::vector<int> weight;
	int threshold;
	int learningCount;//Learing을 시도한 횟수
	const int bias;
	const int constant;//delta rule에서의 constant
	const int limits;//Learning 을 시도할 수 있는 최대치
public:
	SLNeuron(int n, std::vector<int>& w, int th, int con,int b) :nofInput(n), threshold(th), constant(con), learningCount(0),limits(100),bias(b)
	{
		weight.assign(w.begin(), w.end());
	}
	void Learn(std::vector<int>& expectedOutput);//Output값이 expectedOutput값과 같아질때까지 Learning을 수행하는 함수
private:
	void PrintWeight();//객체의 현재 Weight값을 순서대로 출력한다.
	void GetOutputFromInput(std::vector<int>& output);//output을 저장하고자 하는 vector를 입력받아 모든 Input에 대한 Output값을 저장한다.
	void GetNetFromInput(std::vector<int>& net);//GetOutFromInput의 내부에서 사용되는 함수로 Input으로 부터 Net값을 얻는다
	void GetOutputFromNets(const std::vector<int>& net, std::vector<int>& output);//GetOutFromInput의 내부에서 사용되는 함수로 Net값으로 부터 Output값을 얻는다.
	int Activate(int net);//net값을 입력받아 활성화 여부를 반환한다.
	void UpdateWeight(const std::vector<int>& expectedOutput, const std::vector<int>& output);//weight를 갱신한다.
	bool isLearningOver(const std::vector<int>& expectedOutput, const std::vector<int>& output);//Learning이 끝났는지 여부를 반환한다.

};
