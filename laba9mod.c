#include <stdio.h>

int mod(int a, int z){
	if (a >= 0 && z > 0)	return a % z;
	if (a < 0 && z > 0)		return (z + a % z) % z;
	if (a >= 0 && z < 0)	return a % z;
	if (a < 0 && z < 0)		return -(z - a % z) % z;


	return 0;
}

int main(){
	int x, y;
	while (scanf("%d %d", &x, &y)) {
		printf("%d \n", mod(x, y));
	}
}