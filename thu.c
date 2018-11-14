#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float a,b,c,d,e;
float v,y,z,t,k;
float x;

float ratcao(float x,float a, float b,float c,float d,float e){
	if(0<x && x<=a){
		return 1.0;
		} else if(a<x && x<b){
			return (b-x)/(b-a);
			} else {
				return 0.0;
				}
    }
float cao(float x,float a, float b,float c,float d,float e){
	if(x<=a){
		return 0.0;
		} else if(a<x && x<=b){
			return (x-a)/(b-a);
			}else if(b<x && x<c){
				return (c-x)/(c-b);
				}else {
					return 0.0;
				}
}
float trungbinh(float x,float a, float b,float c,float d,float e){
	if(x<=b){
		return 0.0;
		}else if(b<x && x<=c){
			return (x-b)/(c-b);
			}else if(c<x && x<d){
				return (d-x)/(d-c);
				}else {
					return 0.0;
					}
}
float thap(float x,float a, float b,float c,float d,float e){
	if(x<=c){
		return 0.0;
		}else if(c<x && x<=d){
			return (x-c)/(d-c);
			}else if(d<x && x<e){
				return (e-x)/(e-d);
				}else {
					return 0.0;
					}
}
float ratthap(float x,float a, float b,float c,float d,float e){
	if(x<=d){
		return 0.0;
		} else if(d<x && x<e){
			return (x-d)/(e-d);
			} else {
				return 1.0;
				}
}

void main(){
	printf("Nhap a= ");
	scanf("%f",&a);
	printf("Nhap b= ");
	scanf("%f",&b);
	printf("Nhap c= ");
	scanf("%f",&c);
	printf("Nhap d= ");
	scanf("%f",&d);
	printf("Nhap e= ");
	scanf("%f",&e);
	/*printf("Nhap v= ");
	scanf("%f",&v);
	printf("Nhap y= ");
	scanf("%f",&y);
	printf("Nhap z= ");
	scanf("%f",&z);
	printf("Nhap t= ");
	scanf("%f",&t);
	printf("Nhap k= ");
	scanf("%f",&k);*/
	printf("Nhap do am x= ");
	scanf("%f",&x);
	printf("Rat cao= %f\n",ratcao(x,a,b,c,d,e));
	printf("Cao= %f\n",cao(x,a,b,c,d,e));
	printf("Trung binh= %f\n",trungbinh(x,a,b,c,d,e));
	printf("Thap= %f\n",thap(x,a,b,c,d,e));
	printf("Rat thap= %f\n",ratthap(x,a,b,c,d,e));
	
	
}
