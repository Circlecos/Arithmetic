#include<prompt.h>
#include<iostream>
int setpro(int prompt)
{
	m_iprompt=prompt;
}
void getpro()
{
	return m_iprompt;
}
void selectpro()
{
	cout<<"请选择提示语言，输入1为中文，输入2为英文。"<<endl;
	cout<<"Please select the prompt language，click “1”means you need Chinese prompt language,whlie “2”means english."<<endl;
	if(m_iprompt==1)
	 {
	 	cout<<"输入题目数量:"<<endl;
		cout<<"你可以随时按e终止答题，当前题目不计入成绩"<<endl; 
	 }
	 else if(m_iprompt==2)
	 {
		cout<<"Enter the number of topics:"<<endl; 
		cout<<"You can press e to stop answering at any time,while the question you are answering will no judged."<<endl;
	 }
}
