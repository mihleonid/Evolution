#define MAXPOOL 200000
#define HE_POOLDEFINE(PARAM)PARAM** PARAM####Stack = new PARAM*[MAXPOOL]; int PARAM####Top = 0;
#define HC_POOLDEFINE(PARAM)void P####PARAM(PARAM* f); PARAM* G##PARAM(int x, int y);

class Pools {
	private:
		HE_POOLDEFINE(Food)
		HE_POOLDEFINE(Eater)
		HE_POOLDEFINE(Wall)
		HE_POOLDEFINE(Energy)
		HE_POOLDEFINE(Bact)
		HE_POOLDEFINE(Good)
		HE_POOLDEFINE(Fighter)
		HE_POOLDEFINE(Universal)
		HE_POOLDEFINE(Zed)
		HE_POOLDEFINE(Clean)
		HE_POOLDEFINE(Neuro)
	public:
		HC_POOLDEFINE(Food)
		HC_POOLDEFINE(Eater)
		Eater* GEater(int x, int y, int e, int m);
		HC_POOLDEFINE(Wall)
		HC_POOLDEFINE(Energy)
		HC_POOLDEFINE(Bact)
		HC_POOLDEFINE(Good)
		HC_POOLDEFINE(Fighter)
		HC_POOLDEFINE(Universal)
		HC_POOLDEFINE(Zed)
		HC_POOLDEFINE(Clean)
		HC_POOLDEFINE(Neuro)
};
