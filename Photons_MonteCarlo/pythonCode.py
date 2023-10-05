import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import linregress

def reg(a, b, x):
    line = []
    for i in range(len(x)): line.append(a*x[i] + b)
    return line

# Exercício 3.1
def p1():
    x = []
    i_i0 = []
    mu_T = 3196.1283

    data = open('data1.txt')
    next(data)
    for line in data:
        values = line.split()
        x.append(float(values[0]))
        i_i0.append(float(values[1]))
    data.close()
    
    func = np.exp( -mu_T * np.asarray(x) )

    plt.title('Fração de fótons sobreviventes em função da distância percorrida')
    plt.xlabel('x (cm)')
    plt.ylabel('I/Io')
    plt.axvline(x=0.000216493, color='red')
    plt.xlim(0,0.001)
    plt.yticks(np.arange(0,1.1,0.1))
    plt.plot(x, func, label = r'$ I/I_0 = e^{-\mu_T x}$', color = 'navy', linestyle = '--',linewidth=3)
    x.append(2.45)
    plt.stairs(i_i0, x, edgecolor = 'black', linewidth = 1.2, facecolor = 'cyan', fill = True, label = 'Monte Carlo')
    plt.legend()
    plt.show()

# Exercício 3.2
def p2():
    x = []
    i_i0 = []
    
    data = open('data2.txt')
    next(data)
    for line in data:
        values = line.split()
        x.append(float(values[0]))
        i_i0.append(float(values[1]))
    data.close()

    plt.title('Fração de fótons sobreviventes em função da distância percorrida')
    plt.xlabel('x (cm)')
    plt.ylabel('I/Io')
    plt.xlim(0,8)
    plt.axvline(x=0.565586, color='red')
    plt.yticks(np.arange(0, 1.01, 0.1))
    x.append(7.999)
    plt.stairs(i_i0, x, edgecolor = 'black', linewidth = 1.2, facecolor = 'darkgoldenrod', fill = True, label = 'Monte Carlo')
    plt.legend()
    plt.show()

    plt.title('Fração de fótons sobreviventes linearizada, em função da distância percorrida')
    plt.xlabel('x (cm)')
    plt.ylabel('ln(I/Io)')
    
    ln = np.log(i_i0)
    x.pop(-1)
    (a, b) = np.polyfit(x, ln, 1)
    print("y = ax + b")
    print("Slope a: ", a)
    print("Intercept b: ", b)
    print("Length: ", 1/(-a) )
    yp = np.polyval( [a, b] , x)
    plt.plot(x, yp, label = "Regressão Linear")
    plt.grid(True)
    plt.scatter(x, ln, label = 'Dados do feixe', marker = "+", color = "red")
    
    #plt.plot(x, ln, label = 'Monte Carlo', color = 'darkgoldenrod', linestyle = '-')
    plt.legend()
    plt.show()
    
p1()
p2()
