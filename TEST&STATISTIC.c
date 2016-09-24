#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define N 500000 //总测试轮数
//#define N 2 //总测试轮数

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
    //FILE *p ;
    int times=0, i=0, number, number2, testFeedBack=-1, feedback;
    int num[4],res[4],arrayAsk[4];//用于保存四位数的拆开形式，0123号每个元素分别代表四位数的 千百十个 位
    int result;

    int r[11]={0};//统计第下标次猜对的轮数.r[11]表示十次都没猜对的情况数
    int round;
    int ask;
    int ok;//表示当轮是否已猜对，是为1，否为0
    int pre=0;

    srand(time(NULL)*time(NULL)); //用时间做种，每次产生随机数不一样

    for(round=0; round<N; round++)
    {
        if(pre!=round/10000)
        {
            printf("Now %d rounds.\n",round);
            pre=round/10000;
        }
        //一些变量的重新初始化
        index=123;
        testFeedBack=-1;
        feedback=-1;
        times=0;
        memset(all,0,sizeof(all));
        ok=0;
        //每一轮先生成题目，无重复数字的四位数
        do
        {
            ask=rand()%10000;
            //printf("%d\n",ask);
            number=ask;
            num[0]=number/1000; number-=num[0]*1000;
            num[1]=number/100;  number-=num[1]*100;
            num[2]=number/10;   number-=num[2]*10;
            num[3]=number;
        }while(num[0]==num[1] || num[0]==num[2] || num[0]==num[3] || num[1]==num[2] || num[1]==num[3] || num[2]==num[3]);
        //得到合法题目后，把这个数拆成数组，放入arrayAsk
        number=ask;
        arrayAsk[0]=number/1000; number-=arrayAsk[0]*1000;
        arrayAsk[1]=number/100;  number-=arrayAsk[1]*100;
        arrayAsk[2]=number/10;   number-=arrayAsk[2]*10;
        arrayAsk[3]=number;


        //第一次随机猜一个无重复数字的四位数
        do
        {

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
        //printf("第1次：%04d\n",result);
        times++;

        while(!ok && times<10)
        {
            times++;
            //把result拆成数组形式
            number2=result;
            res[0]=number2/1000; number2-=res[0]*1000;
            res[1]=number2/100;  number2-=res[1]*100;
            res[2]=number2/10;   number2-=res[2]*10;
            res[3]=number2;

            /*printf("请连续输入该猜测得到的反馈，如4、0，请输入40：\n");
            scanf("%d",&feedback);*/
            //把手动输入的反馈，改成机器自动判断的反馈
            feedback = tell(res,arrayAsk);
            if(feedback==40)
            {
                ok=1;
                r[times-2]++;
                break;
            }

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
                    continue;//其实有这一句，开始对all数组的初始化就没必要了。//不对，经过测试，还是有必要的
                }
                testFeedBack=tell(res,num);
                if(testFeedBack!=feedback)
                {
                    all[i]=1;
                }
            }
            result=guess();
            //printf("第%d次：%04d\n",times,result);
        }
        if(!ok)
        {
            r[11]++;
        }

    }
    for(i=0; i<11; i++)
    {
        printf("第%d次猜对的轮数：%d，占比%f%%。\n",i+1,r[i],(float)r[i]*100/N);
    }
    return 0;
}
