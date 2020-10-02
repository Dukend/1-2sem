#include <stdio.h>
long long ams(long long a){
	if (a >= 0) return a;
	return -a;
}
int main(void) {
	long long aa;
	while (scanf("%lld", &aa) != EOF) {
		
		long long c,a=0,b=0,zz,k=0,ans=0;
		zz=aa;
		while(zz!=0) {
			k++;
			zz/=10;
		}
		for (int i = 0; i < k; i++)
		{
			c=aa%10;
			if (ams(a-b)==ams(c)) ans=ans*10+ams(c);
			aa/=10;
			a=b;
			b=c;
		}
		zz=ans;
		k=0;
		while(zz!=0) {
			k++;
			zz/=10;
		}
		a=ans;
		for (int i = 0; i < k; i++){
			printf("%lld\n",a%10);
			a/=10;
		}
		
	}
	return 0;
}
