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
	cout<<"��ѡ����ʾ���ԣ�����1Ϊ���ģ�����2ΪӢ�ġ�"<<endl;
	cout<<"Please select the prompt language��click ��1��means you need Chinese prompt language,whlie ��2��means english."<<endl;
	if(m_iprompt==1)
	 {
	 	cout<<"������Ŀ����:"<<endl;
		cout<<"�������ʱ��e��ֹ���⣬��ǰ��Ŀ������ɼ�"<<endl; 
	 }
	 else if(m_iprompt==2)
	 {
		cout<<"Enter the number of topics:"<<endl; 
		cout<<"You can press e to stop answering at any time,while the question you are answering will no judged."<<endl;
	 }
}
