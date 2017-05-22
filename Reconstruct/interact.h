#ifndef _INTERACT_
#define _INTERACT_

#include "operation.h"
#include <string>
#define MAX_NUM_OF_PROBLEM 1000

class Interact {
private:
	std::string location;
	int NumProblem;
	int CorrNum = 0, WrongNum = 0;
	int WrongQueNum[MAX_NUM_OF_PROBLEM];//�ش�������Ŀ�ı��
	int intAns[MAX_NUM_OF_PROBLEM];//�û��𰸣���ֵ��
	Operation *Problem[MAX_NUM_OF_PROBLEM];//ָ����Ŀ��ָ��

public:
	Interact():location(""),NumProblem(0),CorrNum(0),WrongNum(0)
	{
		int i;
		for (i = 0; i < MAX_NUM_OF_PROBLEM; i++)
		{
			WrongQueNum[i] = 0;
			intAns[i] = 0;
			Problem[i] = nullptr;
		}
	}
	~Interact()
	{
		int i;
		for (i = 0; i < MAX_NUM_OF_PROBLEM; i++)
		{
			delete Problem[i];
		}
	}
		
	Operation& generateExpression(int code);
	int ReadFile(char *);
	int BaseSetting(std::string &loca,int nProblem);
	int BaseSetting(std::string &loca);
	std::string ShowTips();
	
	std::string GetLoca();
	int GetUserAns(char ans[],int len,int &flag,int code);
	int GetUserAns(int code);
	int Interact::GetCorr();
	int Interact::GetWrong();
	int Interact::GetWrongCode(int code);
	Operation* Interact::getExpression(int code);
	int Interact::GetNumProblem();

	int Judge(int code);
};

#endif