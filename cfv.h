#define WIDTH 800
#define HEIGHT 600
#define WWIDTH 800
#define WHEIGHT 600
#define MAXPARAM 40000
#define LIMIT 1800000
#define RND 20000000
#define max(A, B) ((A>B)?(A):(B))
#define min(A, B) ((A<B)?(A):(B))
#define Clamp(X, Y, Z) (X = min(max((X), (Y)), (Z)))

int* rando = new int[RND];
int randtop = 0;
int cycles = 0;
Type current = TDel;
bool ris = false;
int size = 5;
bool fielddraw = false;

Uint32 rgb(int r, int g, int b) {
	return(min(max(b, 0), 255) | (0x100 * min(max(g, 0), 255)) | (0x10000 * min(max(r, 0), 255)) | 0xFF000000);
}
Uint32 alpha(Uint32 color, byte a) {
	return((color | 0xFF000000)&(0x1000000 * a));
}
int urand() {
	if (++randtop == RND) {
		randtop = 0;
		cycles++;
		if (cycles == 20000) {
			for (int i = 0; i < RND; i++) {
				rando[i] = rand();
			}
			cycles = 0;
		}
	}
	return rando[randtop];
}
int urand(int max) {
	return(urand() % max);
}
int urand(int from, int to) {
	return(urand(to - from) + from);
}
