#include<iostream>
#include<stdio.h>
#include <conio.h>
#include<string.h>
using namespace std;
FILE *out1,*out2,*out3; 
struct elevator
{
    int t;//此时的时间
    int fl;//电梯这时的楼层
    int ok;//电梯方向
    int num;//电梯内人数
}A,B,C;
struct passager
{
    int t;//乘客发出请求的时刻
    int begin;//乘客出发楼层
    int end;//乘客去往楼层
    int ok1;//乘客等待状态
    int ok2;//乘客是否完成
    int ok3;//乘客去往方向1为下楼2为上楼
    int kind;//乘客可坐电梯类型
    int elev;//乘坐的电梯
}a[100];
int n,ok2=1,ok1[3];
void passager_kind(struct passager &x)
{
	
    if(x.begin%2==1&& x.end%2==1)
        x.kind=1;
    else if((x.begin==1||x.begin%2==0)&&(x.end==1||x.end%2==0))
        x.kind=3;
    else
        x.kind=2;
}
void initialise(struct elevator &ele)
{
    ele.t=0;
    ele.fl=0;
    ele.ok=0;
    ele.num=0;
}

void elev_A(int i)//当A电梯无人时前往指定楼层载人
{
    int j;
    //printf("%d %d %d %d\n",ele.num,a[i].t,ele.t,a[i].ok2);
    
    if(A.num==0&&a[i].t<=A.t&&a[i].ok2==1&&a[i].kind==1&&a[i].elev==0)//是否收到乘客请求
    {
        if(a[i].begin>A.fl)
        {
            for(j=0;j<a[i].begin-A.fl;j++)//向上
            {
                A.fl++;
                A.t++;
            }
            A.ok=a[i].ok3;
        }
        else
        {
            for(j=0;j<A.fl-a[i].begin;j++)//向下
            {
                A.fl--;
                A.t++;
            }
            A.ok=a[i].ok3;
        }
        a[i].elev=1;
        //printf("%d %d\n",ele.fl,ele.ok);
    }
    
}
void elev_B(int i)
{
    int j;
    //printf("%d %d %d %d\n",ele.num,a[i].t,ele.t,a[i].ok2);
    
    if(B.num==0&&a[i].t<=B.t&&a[i].ok2==1&&a[i].elev==0)//是否收到乘客请求
    {
        if(a[i].begin>B.fl)
        {
            for(j=0;j<a[i].begin-B.fl;j++)//向上
            {
                B.fl++;
                B.t++;
            }
            B.ok=a[i].ok3;
        }
        else
        {
            for(j=0;j<A.fl-a[i].begin;j++)//向下
            {
                B.fl--;
                B.t++;
            }
            B.ok=a[i].ok3;
        }
        //printf("%d %d\n",ele.fl,ele.ok);
        a[i].elev=2;
    }
}
void elev_C(int i)
{
    int j;
    //printf("%d %d %d %d\n",ele.num,a[i].t,ele.t,a[i].ok2);
    
    if(C.num==0&&a[i].t<=C.t&&a[i].ok2==1&&a[i].kind==3&a[i].elev==0)//是否收到乘客请求
    {
        if(a[i].begin>C.fl)
        {
            for(j=0;j<a[i].begin-C.fl;j++)//向上
            {
                C.fl++;
                C.t++;
            }
            C.ok=a[i].ok3;
        }
        else
        {
            for(j=0;j<A.fl-a[i].begin;j++)//向下
            {
                C.fl--;
                C.t++;
            }
            C.ok=a[i].ok3;
        }
        a[i].elev=3;
        //printf("%d %d\n",ele.fl,ele.ok);
    }
}
void ele_print()
{
	

   

    if(ok1[0]==1)//输出时刻和楼层
    {
        fprintf(out1,"%d %d\n",A.t,A.fl);
        A.t++;
    }
    if(ok1[1])
    {
        fprintf(out2,"%d %d\n",B.t,B.fl);
        B.t++;
    }
    if(ok1[2])
    {
    	
        fprintf(out3,"%d %d\n",C.t,C.fl);
        C.t++;
    }
    A.t++;
    B.t++;
    C.t++;
    if(A.ok==1)
        A.fl--;
    else
        A.fl++;
    if(B.ok==1)
        B.fl--;
    else
        B.fl++;
    if(C.ok==1)
        C.fl--;
    else
        C.fl++;
    ok2=0;
    ok1[0]=0;
    ok1[1]=0;
    ok1[2]=0;
}
void elev (int i,struct elevator &ele,int x)
{
    if(a[i].ok1==0&&a[i].t<=ele.t&&a[i].ok2==1&&a[i].begin==ele.fl&&ele.ok==a[i].ok3)//乘客上电梯
    {
        ele.num++;
        a[i].ok1=1;
        ok1[x-1]=1;
        a[i].elev=x;
    }
    //printf("**%d %d %d %d\n",a[i].ok1,a[i].end,ele.fl,a[i].ok2);
    if(a[i].ok1&&a[i].end==ele.fl&&a[i].ok2==1)//乘客下电梯
    {
        ele.num--;
        a[i].ok2=0;
        ok1[x-1]=1;
    }
}
int main(int argc,char*argv[])
{
	if(argc>1&&fopen(argv[1],"rt")!=NULL)
	{
	initialise(A);
    initialise(B);
    initialise(C);
    FILE *in;
	in=fopen("input.txt","rt");//打开文件 
    int i;
    fscanf(in,"%d",&n);//输入乘客数
    for(i=0;i<n;i++)
    {
        fscanf(in,"%d%d%d",&a[i].t,&a[i].begin,&a[i].end);//输入乘客信息
        passager_kind(a[i]);
        a[i].ok1=0;
        a[i].ok2=1;
        a[i].elev=0;
        if(a[i].begin>a[i].end)//判断乘客去往方向
            a[i].ok3=1;
        else
            a[i].ok3=2;
    }
    fclose(in);
    extern clrscr();
    out1=fopen("output1.txt","wt");
    out2=fopen("output2.txt","wt");
    out3=fopen("output3.txt","wt");
    while(ok2)
    {
        //printf("%d",ok2);
        ok1[0]=0;ok1[1]=0;ok1[2]=0;//判断是否有人上电梯
        for(i=0;i<n;i++)
        {
            elev_A(i);
            elev_B(i);
            elev_C(i);
            if(a[i].kind==1&&(a[i].elev==0||a[i].elev==1))
            {
                elev(i, A, 1);
            }
            if(a[i].elev==0||a[i].elev==2)
            {
                elev(i, B, 2);
            }
            if(a[i].kind==3&&(a[i].elev==0||a[i].elev==3))
            {
                elev(i,C,3);
            }
    
        }
        ele_print();
        for(i=0;i<n;i++)//判断是否停止循环
        {
            ok2+=a[i].ok2;
        }
        //printf("%d\n",ok2);
    }
    fclose(out1);fclose(out2);fclose(out3);
  
    cout<<"运行成功"<<endl; 
  }
  else if(argc==1)
  {
  	cout<<"请输入input.txt"<<endl;
  }
  else
  cout<<"找不到input.txt"<<endl; 
    return 0;
}

