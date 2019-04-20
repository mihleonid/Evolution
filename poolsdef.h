#define POOL_STD_P(GO) void Pools::P##GO(GO* f){if(GO##Top == MAXPOOL){delete f;}else{GO##Stack[GO##Top++]=f;}}
#define POOL_STD_G(GO) GO* Pools::G##GO (int x, int y){GO* f;if (GO##Top == 0) {f = new GO();}else {f = GO##Stack[--GO##Top];}f->Init(x, y);return f;}
#define POOL_STD_GP(GO) POOL_STD_P(GO) POOL_STD_G(GO)

POOL_STD_GP(Food)
POOL_STD_GP(Eater)
POOL_STD_GP(Wall)
POOL_STD_GP(Energy)
POOL_STD_GP(Bact)
POOL_STD_GP(Good)
POOL_STD_GP(Fighter)
POOL_STD_GP(Universal)
POOL_STD_GP(Zed)
POOL_STD_GP(Clean)
POOL_STD_GP(Neuro)
POOL_STD_GP(XXX)
POOL_STD_GP(YYY)
Eater* Pools::GEater(int x, int y, int e, int m)
{
	Eater* f;
	if (EaterTop == 0) {
		f = new Eater();
	}
	else {
		f = EaterStack[--EaterTop];
	}
	f->Init(x, y, e, m);
	return f;
}
