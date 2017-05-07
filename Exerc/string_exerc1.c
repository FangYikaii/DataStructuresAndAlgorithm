#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  

/*
重新标准化一个字符串S表示一个电话号码，字符串由N个字符组成：数字，空格，短折线（-），并且至少包含两位数字
重新标准化：（1）可以忽略字符串S中的空格和短折线，（2）将数字以长度为3的块进行分组，用单个短折线分隔（3）其中最后一个块或者最后两个块字符长度可以是2

N为2-100内的整数；
字符串s仅有0-9，空格和短折线组成
s至少包含两位数字
*/

#define N 100           //字符串最大长度

char* solution(char* s)          
{
	int i,j=0;
	int len = strlen(s);        //长度
	char* str_cut = NULL;       //定义：删除多余字符后的字符串
	char* str_out = NULL;       //定义：最终输出的字符串
	str_cut=(char*)malloc(N * sizeof(char));        //malloc分配N长度的char内存
	str_out= (char*)malloc(N * sizeof(char));       //malloc分配N长度的char内存

	//检查字符串是否符合0-9，空格，短折线
	for (i = 0; i < len; i++)
	{
		if (s[i] <= '9'&&s[i] >= '0' || s[i] == '-'||s[i]==' ')
		{

		}
		else
		{
			exit(1);
		}
	}

	//字符串精简
	for (i = 0; i < len; i++)
	{
		if (s[i] <= '9'&&s[i] >= '0')
		{
			str_cut[j] = s[i];
			j++;
		}
	}
	str_cut[j] = '\0';            //精简后的字符串
	len = strlen(str_cut);        //精简后的长度
	if (len < 2)
	{
		exit(1);
	}
	if (len % 3 == 0)
	{
		j = len / 3;
		for (i = 0; i < j-1; i++)  //比如有6个数，j=2，但是只能循环一次，就是i=0，i要＜j-1
		{
			str_out[i * 4] = str_cut[i * 3];
			str_out[i * 4 + 1] = str_cut[i * 3 + 1];
			str_out[i * 4 + 2] = str_cut[i * 3 + 2];
			str_out[i * 4 + 3] = '-';
		}
		//最后一组
		str_out[i * 4] = str_cut[i * 3];
		str_out[i * 4 + 1] = str_cut[i * 3 + 1];
		str_out[i * 4 + 2] = str_cut[i * 3 + 2];
		str_out[i * 4 + 3] = '\0';
	}
	else if (len % 3 == 1)
	{
		j = len / 3;
		for (i = 0; i < j-1; i++)     //比如有7个数，j=2，但是只能循环一次，就是i=0，i要＜j-1，省下4个
		{
			str_out[i * 4] = str_cut[i * 3];
			str_out[i * 4 + 1] = str_cut[i * 3 + 1];
			str_out[i * 4 + 2] = str_cut[i * 3 + 2];
			str_out[i * 4 + 3] = '-';
		}
		//最后一组
		str_out[i * 4] = str_cut[i * 3];
		str_out[i * 4 + 1] = str_cut[i * 3 + 1];
		str_out[i * 4 + 2] = '-';
		str_out[i * 4 + 3] = str_cut[i * 3 + 2];
		str_out[i * 4 + 4] = str_cut[i * 3 + 3];
		str_out[i * 4 + 5] = '\0';
	}
	else
	{
		j = len / 3;
		for (i = 0; i < j; i++)   //比如有7个数，j=2，但是只能循环一次，就是i=0，i要＜j-1，剩下5个
		{
			str_out[i * 4] = str_cut[i * 3];
			str_out[i * 4 + 1] = str_cut[i * 3 + 1];
			str_out[i * 4 + 2] = str_cut[i * 3 + 2];
			str_out[i * 4 + 3] = '-';
		}
		//最后一组
		str_out[i * 4] = str_cut[i * 3];
		str_out[i * 4 + 1] = str_cut[i * 3 + 1];
		str_out[i * 4 + 2] = str_cut[i * 3 + 2];
		str_out[i * 4 + 3] = '-';
		str_out[i * 4 + 4] = str_cut[i * 3 + 3];
		str_out[i * 4 + 5] = str_cut[i * 3 + 4];
		str_out[i * 4 + 6] = '\0';
	}
	free(str_cut);   //释放精简数组的内存
	return str_out;
}

//主函数  
void main()
{
	char str[N];   //定义一个str
	char* str_new = NULL;
	str_new = (char*)malloc(N * sizeof(char));       //malloc分配N长度的char内存
	gets(str);     //gets和fgets接收空格
	printf("原始字符串：%s\n", str);
	str_new=solution(str);
	printf("返回字符串：%s\n",str_new);
	while (1);
}