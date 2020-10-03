#include <stdio.h>

int mod(int a,int b){
    if (a>0 && b>0){
        return a%b;
    }else if(a<0 && b>0){
        return (b+a%b)%b;
    }else if(a>=0 && b<0){
        return (b+a%b)%b;
    }else {
        return -(b-a%b)%b;
    }
 	
}
int min (int a,int b){
    if (a>=b){
        return b;
    }else{
        return a;
    }
}
int max (int a,int b){
    if (a>=b){
        return a;
    }else{
        return b;
    }
}
int abs(int a){
    if (a<0){
        return -a;
    }else{
        return a;    
    }
    

}
int sign(int a){
    if(a<0){
       			 return -1;
    }else if (a==0){
       			 return 0;
    }else{
      			  return 1;
    }
}
int in(int i, int j){
    return (i+j+10<=0 && i+j+20>=0);
}
int main(){
    int i=13,j=19,l=14;
    for (int k=0;k<51;k++)
    {
        if (in(i,j))
        {
            printf("success %d \n",k);
                break;
        }
        int ii=i,jj=j,ll=l;
        i=sign(ii+1)*abs(abs(k-jj)-abs(ii-ll));
        j=mod(jj,20)+max(mod(ii,20), min(jj-k,ll-k))-10;
        l=mod(k*(ii+1)*(jj+2)*(ll+3),20);
        if (k==50) printf("fail \n");
    }

}