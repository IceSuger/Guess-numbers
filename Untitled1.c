#include <stdio.h>
#include <stdlib.h>

int all[10000]={0};//�ø�������±�����ʾ���е���λ���ǣ�����ֵ0��ʾ���ã�1��ʾ�ѱ��ų�
int index = 123;//����all���±꣬ÿ�β��������ؿ�ȡ�ģ�������ʹall[index]==0�ģ���С����

/**
    nΪ���û���������г��Ե���λ����targetΪĿ����������Ŀ�����Ǹ���λ��
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
    int num[4],res[4];//���ڱ�����λ���Ĳ���ʽ��0123��ÿ��Ԫ�طֱ������λ���� ǧ��ʮ�� λ
    int result;

    do
    {
        srand(time(NULL)*time(NULL)); //��ʱ�����֣�ÿ�β����������һ��
        result=rand()%10000;
        //printf("%d\n",result);
        number=result;
        num[0]=number/1000; number-=num[0]*1000;
        num[1]=number/100;  number-=num[1]*100;
        num[2]=number/10;   number-=num[2]*10;
        num[3]=number;
    }while(num[0]==num[1] || num[0]==num[2] || num[0]==num[3] || num[1]==num[2] || num[1]==num[3] || num[2]==num[3]);


    //��ʼ��all���飬�����ظ����ֵĶ����Ϊ1
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

    printf("��1�Σ�%04d\n",result);
    times--;

    while(times--)
    {
        printf("����������ò²�õ��ķ�������4��0��������40��\n");
        scanf("%d",&feedback);
        //��result���������ʽ
        number2=result;
        res[0]=number2/1000; number2-=res[0]*1000;
        //printf("%d",number2);
        res[1]=number2/100;  number2-=res[1]*100;
        //printf("%d",number2);
        res[2]=number2/10;   number2-=res[2]*10;
        //printf("%d",number2);
        res[3]=number2;
        //�������п��ܵ���λ�����Բ������Ǵ𰸵Ľ����ų�������all�����Ӧλ�ñ�Ϊ1
        for(i=index; i<9990; i++)
        {
            number=i;
            num[0]=number/1000; number-=num[0]*1000;
            num[1]=number/100;  number-=num[1]*100;
            num[2]=number/10;   number-=num[2]*10;
            num[3]=number;
            if(num[0]==num[1] || num[0]==num[2] || num[0]==num[3] || num[1]==num[2] || num[1]==num[3] || num[2]==num[3])
            {
                continue;//��ʵ����һ�䣬��ʼ��all����ĳ�ʼ����û��Ҫ��
            }
            //printf("res���飺%d%d%d%d\n",res[0],res[1],res[2],res[3]);
            testFeedBack=tell(res,num);
            if(testFeedBack!=feedback)
            {
                all[i]=1;
            }
        }
        result=guess();
        printf("��%d�Σ�%04d\n",9-times,result);
    }
    printf("GG.\n");
    return 0;
}
