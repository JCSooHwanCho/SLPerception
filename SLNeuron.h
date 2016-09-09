#pragma once
#include <iostream>
#include <vector>
#include <cmath>
class SLNeuron {
private:
	const int nofInput;//bias�� ������ Input��
	std::vector<int> weight;
	int threshold;
	int learningCount;//Learing�� �õ��� Ƚ��
	const int bias;
	const int constant;//delta rule������ constant
	const int limits;//Learning �� �õ��� �� �ִ� �ִ�ġ
public:
	SLNeuron(int n, std::vector<int>& w, int th, int con,int b) :nofInput(n), threshold(th), constant(con), learningCount(0),limits(100),bias(b)
	{
		weight.assign(w.begin(), w.end());
	}
	void Learn(std::vector<int>& expectedOutput);//Output���� expectedOutput���� ������������ Learning�� �����ϴ� �Լ�
private:
	void PrintWeight();//��ü�� ���� Weight���� ������� ����Ѵ�.
	void GetOutputFromInput(std::vector<int>& output);//output�� �����ϰ��� �ϴ� vector�� �Է¹޾� ��� Input�� ���� Output���� �����Ѵ�.
	void GetNetFromInput(std::vector<int>& net);//GetOutFromInput�� ���ο��� ���Ǵ� �Լ��� Input���� ���� Net���� ��´�
	void GetOutputFromNets(const std::vector<int>& net, std::vector<int>& output);//GetOutFromInput�� ���ο��� ���Ǵ� �Լ��� Net������ ���� Output���� ��´�.
	int Activate(int net);//net���� �Է¹޾� Ȱ��ȭ ���θ� ��ȯ�Ѵ�.
	void UpdateWeight(const std::vector<int>& expectedOutput, const std::vector<int>& output);//weight�� �����Ѵ�.
	bool isLearningOver(const std::vector<int>& expectedOutput, const std::vector<int>& output);//Learning�� �������� ���θ� ��ȯ�Ѵ�.

};
