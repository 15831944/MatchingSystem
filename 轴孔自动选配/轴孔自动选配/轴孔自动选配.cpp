#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<iomanip>
#include<fstream> 

#define M 100
#define N 10
#define X 159600
#define Y 159850
#define W 160150
#define Z 160400

using namespace std; 

int main()
{

//	double zhou[M], kong[M];
//	srand(time(NULL));	
//	//生成尺寸随机数 
//	for(int i = 0; i < M; i++)
//	{
//		int k=rand()%(Y-X+1)+X;
//		zhou[i]=k/10000.0;
//	}
//	for(int i = 0; i < M; i++)
//	{
//		int k=rand()%(Z-W+1)+W;
//		kong[i]=k/10000.0;
//	}
//	
//	freopen("轴尺寸.txt", "w", stdout);
//	//cout <<  "孔编号" << "     " << "孔尺寸" << endl;
//    for(int i = 0; i < M; i++)
//	cout << setw(4) << setfill('0') << i + 1 << "     " << setprecision(4) << setiosflags(ios::fixed) << zhou[i] << endl;
//    fclose(stdout);
//    
//    freopen("孔尺寸.txt", "w", stdout);
//	//cout << "轴编号" << "     " << "轴尺寸" << endl;
//    for(int i = 0; i < M; i++)
//	cout << setw(4) << setfill('0') << i + 1 << "     " << setprecision(4) << setiosflags(ios::fixed) << kong[i] <<endl;
//    fclose(stdout);
	
	clock_t startTime, endTime;
	startTime = clock();
	double a[N], b[N]; int c[N][N];
	ifstream fin1;
	fin1.open("C:\\Users\\明友\\Desktop\\新建MFC\\轴孔自动选配\\轴孔自动选配\\轴尺寸.txt");
	double BH1, zhou[M];
	for(int i = 0; i < M; i++)
	{
		fin1 >> BH1;
		fin1 >> zhou[i];
	}
	fin1.close();	
	ifstream fin2;
	fin2.open("C:\\Users\\明友\\Desktop\\新建MFC\\轴孔自动选配\\轴孔自动选配\\孔尺寸.txt");
	double BH2, kong[M];
	for(int i = 0; i < M; i++)
	{
		fin2 >> BH2;
		fin2 >> kong[i];
	}
	fin2.close();
	
	freopen("轴孔选配.txt", "w", stdout);
	//cout << "轴编号" << "     " << "轴尺寸" << "     " << "孔编号" << "     " << "孔尺寸" << "     " << "配合间隙" << endl;
	
	int nn1 = N, nn2 = N, max = 0, idx = 1, sum = 0, bh1[N], bh2[N];
	while (sum <= M - N)
	{

		if (max == 0)
		{
			for (int i = 0; i < N; i++)
			{
				a[i] = zhou[i];
				b[i] = kong[i];
				bh1[i] = i + 1;
				bh2[i] = i + 1;
			}
		}
		else
		{
			for (int i = N - max; i < N; i++)
			{
				a[i] = zhou[nn1++];
				b[i] = kong[nn2++];
				bh1[i] = sum + i + 1;
				bh2[i] = bh1[i];
			}
		}

		max = 0;

		//标记 
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (b[i] - a[j] >= 0.05 && b[i] - a[j] <= 0.075)
				{
					c[i][j] = 1;
				}
				else
				{
					c[i][j] = 0;
				}
			}
		}


		int m[N], n[N], p[N], q[N], temp3[N], temp4[N];
		double temp1[N], temp2[N];

	
	for(int j0 = 0; j0 < N; j0++)
	{
		m[0] = c[0][j0];
		p[j0] = 1;
		for(int j1 = 0; j1 < N; j1++)
		{
			if(p[j1] == 1)
			continue;
			m[1] = c[1][j1];
		    p[j1] = 1;
		    for(int j2 = 0; j2 < N; j2++)
			{
				if(p[j2] == 1)
				continue;
				m[2] = c[2][j2];
		    	p[j2] = 1;
		    	for(int j3 = 0; j3 < N; j3++)
				{
					if(p[j3] == 1)
					continue;
					m[3] = c[3][j3];
		    		p[j3] = 1;
		    		for(int j4 = 0; j4 < N; j4++)
					{
						if(p[j4] == 1)
						continue;
						m[4] = c[4][j4];
		    			p[j4] = 1;
		    			for(int j5 = 0; j5 < N; j5++)
						{
							if(p[j5] == 1)
							continue;
							m[5] = c[5][j5];
		    				p[j5] = 1;
		    				for(int j6 = 0; j6 < N; j6++)
							{
								if(p[j6] == 1)
								continue;
								m[6] = c[6][j6];
		    					p[j6] = 1;
		    					for(int j7 = 0; j7 < N; j7++)
								{
									if(p[j7] == 1)
									continue;
									m[7] = c[7][j7];
		    						p[j7] = 1;
		    						for(int j8 = 0; j8 < N; j8++)
									{
										if(p[j8] == 1)
										continue;
										m[8] = c[8][j8];
		    							p[j8] = 1;
		    							for(int j9 = 0; j9 < N; j9++)
										{
											if(p[j9] == 1)
											continue;
											m[9] = c[9][j9];
											p[j9] = 1;   								
		    								int t = m[0] + m[1] + m[2] + m[3] + m[4] + m[5] + m[6] + m[7] + m[8] + m[9];
											if(t == N)
											{
												max = N;
												n[0] = j0; n[1] = j1; n[2] = j2; n[3] = j3; n[4] = j4; n[5] = j5; n[6] = j6; n[7] = j7; n[8] = j8; n[9] = j9; 
												q[0] = m[0]; q[1] = m[1]; q[2] = m[2]; q[3] = m[3]; q[4] = m[4]; q[5] = m[5]; q[6] = m[6]; q[7] = m[7]; q[8] = m[8]; q[9] = m[9];
												goto here; 
											}
											if(t > max)
											{
												max = t;
												n[0] = j0; n[1] = j1; n[2] = j2; n[3] = j3; n[4] = j4; n[5] = j5; n[6] = j6; n[7] = j7; n[8] = j8; n[9] = j9;
												q[0] = m[0]; q[1] = m[1]; q[2] = m[2]; q[3] = m[3]; q[4] = m[4]; q[5] = m[5]; q[6] = m[6]; q[7] = m[7]; q[8] = m[8]; q[9] = m[9];
											}
											p[j9] = 0;
										}
										p[j8] = 0;
									}
									p[j7] = 0;
								}
								p[j6] = 0;
							}
							p[j5] = 0;
						}
						p[j4] = 0;
					}
					p[j3] = 0;
				}
				p[j2] = 0;
			}
			p[j1] = 0;
		}
		p[j0] = 0;
	}
	here:
	if (max == 0)
	{
		//cout << "第" << idx << "组零件选配不成功" << endl;
		fclose(stdout);
		return -1;
	}
	
	idx++;
	sum += max;
		for(int i = 0, j = 0; i < N; i++)
		{
			if(q[i] == 1)
			{
				cout << setw(4) << setfill('0') << bh1[n[i]] << "     " << setprecision(4) << setiosflags(ios::fixed) << a[n[i]] 
				<< "     " << setw(4) << setfill('0') << bh2[i] << "     " << setprecision(4) << setiosflags(ios::fixed) << b[i] 
				<< "     " << setprecision(4) << setiosflags(ios::fixed) << b[i] - a[n[i]] << endl;
			}
			else
			{
				temp3[j] = bh1[n[i]];
				temp4[j] = bh2[i];
				temp2[j] = b[i];
				temp1[j] = a[n[i]];
				j++;
			}
		}
		for (int i = 0; i < N - max; i++)
		{
			bh1[i] = temp3[i];
			bh2[i] = temp4[i];
			a[i] = temp1[i];
			b[i] = temp2[i];
		}
		cout << endl;
	}
	//cout << "已选配" << sum << "对零件" << endl;
	fclose(stdout);
	endTime = clock();
	cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	return 0;
}
