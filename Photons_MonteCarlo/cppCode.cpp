#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>

using namespace std;

double randomDouble(double a, double b)
{
    double diff = b - a;
    double r = drand48() * diff;
    return a + r;
}

double x(long double mu_T)
{
    long double x = -(1/mu_T)*log( 1 - drand48() );
    return x;
}

double P(long double x, long double mu_T)
{
    long double p = exp(-mu_T * x);
    return p;
}

double monteCarloInt(vector<double> list)
{
    long double sum = 0;
    long double integral;
    int max = list[list.size()-1];
    int min = list[0];
    
    for (int i = 0; i < list.size(); i++) sum += randomDouble(min, max);

    integral = (max - min)*sum/list.size();
    
    return integral;
}

int attribute(vector<double> list, double p) // atribui um indice 
{
    int N = list.size() + 1;
    int interval = 3;
    for (int i = 0; i <= N; i++) // iterar sobre todos os índices
    {
        if (p >= list[i] && p < list[i+1]) // se estiver no índice certo
        {
            interval = i+1;
            //cout << "p: " << p << " | i+1: " << interval << endl;
            return interval; // devolver intervalo correspondente
        }
    }
    return interval;
}

int index(vector<double> v, double K)
{
    int index = 3;
    for (int i = 0; i < v.size(); i++)
    {
        //cout << K << " " << v[i] << endl;
        if (K == v[i]) index = i;
    }
    return index;
}

void exercicio1()
{
    // Variáveis
    long double mu_f = 3.19 * pow(10, 3);
    long double mu_R = 6.09 * pow(1 ,  1);
    long double mu_C = 3.83 * pow(10, -2);
    long double mu_T = mu_f + mu_R + mu_C;

    int n = 100000; // numero de fotons
    int nBins = 100;
    long double delta = 1 * pow(10, -5); // intervalo de cada bin, isto é, intervalo de espessura dx
    vector<double> x_list;
    vector<double> P_list;
    vector<int> histogram(nBins);
    vector<int> survivors(nBins); // fotões sobreviventes num dado bin

    ofstream data1("data1.txt");

    // Gerar fotões
    for (int i = 0; i < n; i++)
    {
        long double x_i = x(mu_T);
        if (x_i < 0) break;
        long double P_i = P(x_i, mu_T);
        x_list.push_back(x_i);
        P_list.push_back(P_i);
    }
    
    // Espessura
    sort(x_list.begin(), x_list.end());
    cout << "Espessura 3.1:" <<  x_list[(n/2)-1] << endl;
    
    // Histograma (da fração de fotões sobreviventes)
    for (int i = 0; i < n; i++) // iterar sobre os fotões
    {
        for (int j = 0; j < nBins; j++) // iterar sobre os bins
        {
            if (x_list[i] >= j*delta && x_list[i] < (j+1)*delta) histogram[j]+=1; // se fotão morreu no intervalo correto do bin, adicionar mais 1 fotão no bin
        }
    }
    
    survivors[0] += n - histogram[0];
    data1 << "x (m)" << "\t\t" << "I/Io" << endl;
    data1 << 0 << "\t\t" << double(survivors[0])/double(n) << endl;
    for (int i = 1; i < nBins; i++)
    {
        survivors[i] += survivors[i-1] - histogram[i]; // atualizar sobreviventes
        data1 << i*delta << "\t\t" << double(survivors[i])/double(n) << endl;
    }
    
    data1.close();
}

void exercicio2()
{
    // Data Input
    ifstream File1("data_fcul.txt");
    ifstream File2("data_nist.txt");
    vector<double> eData; // energias
    vector<double> nData; // frequencias
    vector<double> mData; // mu
    double rho = 2.69890; // densidade do Al
    
    // > ler texto das files:
    string text;
    char delimiter = '\t';
    
    // >> file FCUL
    int num = 0;
    for (int i = 0 ; i < 18 ; i++) File1.ignore(100, '\n'); //getline(File1, text); // ignorar 3 primeiras linhas.
    
    for (int i = 10; i < 100; i++) // enquanto nao chegamos em End Of File
    {
        getline(File1, text); // pegar linha
        string s1 = text.substr(0, 3); // pegar 1o valor (energia)
        string s2 = text.substr(4, 15); // 2o valor (n)
        eData.push_back(stod(s1));
        nData.push_back(stod(s2));
    }
    for (int i = 100; i < 110; i++) // enquanto nao chegamos em End Of File
    {
        getline(File1, text); // pegar linha
        string s1 = text.substr(0, 4); // pegar 1o valor (energia)
        string s2 = text.substr(5, 15); // 2o valor (n)
        eData.push_back(stod(s1));
        nData.push_back(stod(s2));
    }
    
    // >> file NIST
    for (int i = 0 ; i < 3 ; i++) getline(File2, text); // ignorar 3 primeiras linhas.
    while(!File2.eof()) // enquanto nao chegamos em End Of File
    {
        getline(File2, text); // pegar linha
        string s = text.substr(10, 20); // pegar segundo valor
        double mu_T = stod(s)* rho; // ja multiplica pela densidade pois stod(s) = mu/rho
        mData.push_back(mu_T);
    }
    // stod: convert string to double.
    
    File1.close();
    File2.close();
    
    // Probabilidades
    // normalizar frequencias:
    vector<double> pData;
    double normSum = 0;
    for (int i = 0; i < nData.size(); i++) normSum += nData[i];
    // estabelecer probabilidades
    for (int i = 0; i < nData.size(); i++) pData.push_back( nData[i] / normSum );
    
    // > Sorted
    vector<double> pSorted = pData;
    sort(pSorted.begin(), pSorted.end());
    
    // > Somadas
    vector<double> pSum (pSorted.size()+1, 0);
    for (int i = 1; i < pSum.size(); i++)
    {
        for (int j = 0; j < i; j++) pSum[i-1] += pSorted[j];
    }
    
    //for (int i = 0; i < mData.size(); i++) cout << i+11 << "): eData: " << eData[i] << " | mData: " <<  mData[i] << " | pSorted: " << pSorted[i] << " | pSum: " << pSum[i] << endl;
    
    // Simulação de fotões
    int n = 100000;
    
    vector<double> eList;
    vector<double> pList;
    vector<double> xList;
    
    for (int i = 0; i < n; i++)
    {
        double pInterval = pSorted[attribute(pSum, drand48())]; // atribuir intervalo de probabilidade ao numero aleatorio drand48
        double pIndex = index(pData, pInterval);
        double mu = mData[pIndex];
        double x_i = x(mu);
        
        eList.push_back(eData[pIndex]);
        xList.push_back(x_i);
        pList.push_back(P(x_i, mu));
        //cout << "pInterval: " << pInterval << " | pIndex: " << pIndex << " | mu: " << mu << " | x: " << x_i << endl;
    }
    
    // Data Output
    // > Espessura
    vector<double> xSort = xList;
    sort(xSort.begin(), xSort.end());
    cout << "Espessura 3.2:" << xSort[(n/2)-1] << endl;
    
    // > Histograma
    ofstream data2("data2.txt");
    int nBins = 4000;
    double delta = 2 * pow(10, -3);
    
    vector<int> histogram(nBins, 0);
    vector<int> survivors(nBins);
    
    for (int i = 0; i < n; i++) // iterar sobre os fotões
    {
        for (int j = 0; j < nBins; j++) // iterar sobre os bins
        {
            if (xList[i] >= j*delta && xList[i] < (j+1)*delta) histogram[j]+=1; // se fotão morreu no intervalo correto do bin, adicionar mais 1 fotão no bin
        }
    }
    
    survivors[0] = n - histogram[0];
    data2 << "x (m)" << "\t\t" << "I/Io" << "\t\t" << "mu_T" << endl;
    for (int i = 1; i < nBins; i++)
    {
        survivors[i] = survivors[i-1] - histogram[i]; // atualizar sobreviventes
    }
    for (int i = 0; i < nBins; i++)
    {
        data2 << i*delta << "\t\t" << double(survivors[i])/double(n) << endl;
    }
    
    cout << "Fim." << endl;
    data2.close();
}

int main()
{
    srand(123211);
    exercicio1();
    exercicio2();
    return 0;
}