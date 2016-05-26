// Shema Laksa 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
using namespace std;

double func(double x, double t){ //nach usl
	return x;
}
int n = 100; // kol-vo razbienii po x
double h = 1/(double)n;
int k = 100; //kol-vo razbienii po t
double tau = 1/(double)k;
double a = 0.01;
double sigma = a*tau/h;

int check(int s){
	if (s>1)
		return 0;
	else 
		return 1;
}

double e = 0.01; //tochnost'

int p = 100*n;

double laks(double right, double left){
        double result = (h-a*tau)/(2*h-a*tau)*right + (h+a*tau)/(2*h-a*tau)*left;
        return result;
}
void solver(){ //Method Yakobi
        vector <vector <double> > u0(n, vector <double>(k));
        vector <vector <double> > u1(n, vector <double>(k));
        for (int i=0; i<n-1; i++){//nach pribl
		for (int j=0; j<k-1; j++){
			u0[i][j]=1.0;
			u1[i][j]=1.0;
		}
	}
	for (int i=0; i<n-1; i++){ //nach usl
                        u0[i][0]=func(i*h, 0);
                        u1[i][0]=func(i*h, 0);
        }
	for (int j=0;j<k-1;j++){ //gr usl
		u0[0][j]=0;
		u1[0][j]=0;
		u0[n-1][j]=0;
		u1[n-1][j]=0;
	}
        for (int q=1; q<p; q++){
                for (int i=1; i<n-1; i++){
                        for (int j=1; j<k-1; j++){
                                u1[i][j+1] = laks(u0[i+1][j], u0[i-1][j]);
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
	int check_ = check(sigma);
	if (check_==1){	
		printf("%d\n", p);
		solver();
	}
	else{
		printf("Invalid values of tau, h or a\n");
	}
	return 0;
}
