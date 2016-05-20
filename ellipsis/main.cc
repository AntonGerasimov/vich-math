#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
using namespace std;
double sqr(double x){return x*x;}
double func(double x, double y) {
        if ((x>=0.25)and(x<=0.75)and(y>=0.25)and(y<=0.75))
                return -1;
        else  return 0;

//  return sin(x*M_PI) * sin(y/2*M_PI);
}
int n = 100; // kol-vo razbienii 
double h = 1/(double)n;
double e = 0.01; //tochnost'
int p = (int) 2*n*n/(3.14*3.14)*log(1/e); //number of iterations

double yakobi(double up, double down, double right, double left, double f, double h){
	double result = 0.25* (up+down+right+left)+h*h*f/4; 
	return result;
}
void solver(){ //Method Yakobi
	vector <vector <double> > u0(n, vector <double>(n));
	vector <vector <double> > u1(n, vector <double>(n));
	for (int i=0; i<n-1; i++){
		for (int j=0; j<n-1; j++){
			u0[i][j]=0.0;
			u1[i][j]=0.0;
		}
	} 
	for (int q=1; q<p; q++){
		for (int i=1; i<n-1; i++){
			for (int j=1; j<n-1; j++){
				double f = func(i*h, j*h);
				u1[i][j] = yakobi(u0[i][j+1], u0[i][j-1], u0[i+1][j], u0[i-1][j], f, h);
			}
		}

		for (int i=1; i<n-1; i++){
			for (int j=1; j<n-1; j++){
				u0[i][j] = u1[i][j];
			}
		}
		if (q%1000==0)
			printf("%d\n",q);
	}
	FILE* file = fopen("out.txt", "w+");
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			fprintf(file, "%lf %lf %lf\n", i*h, j*h, u1[i][j]);
		}
	}
	
}
int main(){
//	solver();
	printf("%d %f\n", p, e);
	solver();
	return 0;
}
