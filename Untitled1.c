#include <stdio.h>
#include <stdlib.h>

int all[10000]={0};//用该数组的下标来表示所有的四位数们，数组值0表示可用，1表示已被排除
int index = 123;//数组all的下标，每次猜数都返回可取的（即可以使all[index]==0的）最小的数

/**
    n为“用户”输入进行尝试的四位数，target为目标数，即题目出的那个四位数
*/
int tell(int n[], int target[])
{
    int i,j, a=0, b=0;
    int hasBeenRight[4]={0};
    for(i=0; i<4; i++)
    {
        if(n[i]==target[i])
        {
            a++;
            hasBeenRight[i]=1;
        }
    }
    for(i=0; i<4; i++)
    {
        if(hasBeenRight[i])
        {
            continue;
        }
        for(j=0; j<4; j++)
        {
            if(i!=j && n[i]==target[j])
            {
                b++;
            }
        }
    }

/*if(target[0]<2 && target[1]<2 && target[2]<2)
    printf("Test %d%d%d%d, Target %d%d%d%d, %dA%dB\n",n[0],n[1],n[2],n[3],target[0],target[1],target[2],target[3],a,b);
*/
    return a*10+b;
}

int guess()
{
    while(all[index])
    {
        index++;
    }
    return index;
}


int main()
{
    FILE *p ;
    int times=9, i=0, number, number2, testFeedBack=-1, feedback;
    int num[4],res[4];//用于保存四位数的拆开形式，0123号每个元素分别代表四位数的 千百十个 位
    int result;

    do
    {
        srand(time(NULL)*time(NULL)); //用时间做种，每次产生随机数不一样
        result=rand()%10000;
        //printf("%d\n",result);
        number=result;
        num[0]=number/1000; number-=num[0]*1000;
        num[1]=number/100;  number-=num[1]*100;
        num[2]=number/10;   number-=num[2]*10;
        num[3]=number;
    }while(num[0]==num[1] || num[0]==num[2] || num[0]==num[3] || num[1]==num[2] || num[1]==num[3] || num[2]==num[3]);


    //初始化all数组，把有重复数字的都标记为1
    for(i=0; i<9999; i++)
    {
        number=i;
        num[0]=number/1000; number-=num[0]*1000;
        num[1]=number/100;  number-=num[1]*100;
        num[2]=number/10;   number-=num[2]*10;
        num[3]=number;
        if(num[0]==num[1] || num[0]==num[2] || num[0]==num[3] || num[1]==num[2] || num[1]==num[3] || num[2]==num[3])
        {
            all[i]=1;
        }
    }

 /*   printf("%d\n\n",all[9591]);

    p= fopen("1.txt","w");
    for(i=9500; i<9999; i++)
    {
        fprintf(p,"%d\t%d\n",i,all[i]);
    }*/

    printf("第1次：%04d\n",result);
    times--;

    while(times--)
    {
        printf("请连续输入该猜测得到的反馈，如4、0，请输入40：\n");
        scanf("%d",&feedback);
        //把result拆成数组形式
        number2=result;
        res[0]=number2/1000; number2-=res[0]*1000;
        //printf("%d",number2);
        res[1]=number2/100;  number2-=res[1]*100;
        //printf("%d",number2);
        res[2]=number2/10;   number2-=res[2]*10;
        //printf("%d",number2);
        res[3]=number2;
        //遍历所有可能的四位数，对不可能是答案的进行排除，即把all数组对应位置标为1
        for(i=index; i<9990; i++)
        {
            number=i;
            num[0]=number/1000; number-=num[0]*1000;
            num[1]=number/100;  number-=num[1]*100;
            num[2]=number/10;   number-=num[2]*10;
            num[3]=number;
            if(num[0]==num[1] || num[0]==num[2] || num[0]==num[3] || num[1]==num[2] || num[1]==num[3] || num[2]==num[3])
            {
                continue;//其实有这一句，开始对all数组的初始化就没必要了
            }
            //printf("res数组：%d%d%d%d\n",res[0],res[1],res[2],res[3]);
            testFeedBack=tell(res,num);
            if(testFeedBack!=feedback)
            {
                all[i]=1;
            }
        }
        result=guess();
        printf("第%d次：%04d\n",9-times,result);
    }
    printf("GG.\n");
    return 0;
}
