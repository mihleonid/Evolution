#define GO_STD_CREATE(GO) GO::GO(){Type=T##GO;}
#define GO_STD_DELETE(GO) void GO::Delete(MainWindow* mw){mw->p.P##GO(this);}
#define GO_STD_CD(GO) GO_STD_CREATE(GO)GO_STD_DELETE(GO)
#define GO_STD_H(GO) explicit GO();void Do(MainWindow *mw);void Delete(MainWindow* mw);Uint32 Color();void Init(int ax, int ay);
#define NetSize 10
class GameObject {
public:
	explicit GameObject() {}
	int x;
	int y;
	int pos;
	int Type;
	int energy;
	byte strength;
	byte speed;
	byte tospeed;
	void Init(int ax, int ay) {
		x = ax;
		y = ay;
		tospeed = 0;
		energy = 1;
		speed = 255;
	}
	virtual void Do(MainWindow *mw) {}
	virtual Uint32 Color() { return 0; }
	virtual void Delete(MainWindow* mw) = 0;
	void DeleteSelf(MainWindow * mw);
};
class Food :public GameObject {
public:
	GO_STD_H(Food)
	int Delenie = 0;
	int DelenieMax;
};
class Eater :public GameObject {
public:
	GO_STD_H(Eater)
	int MaxSpeed;
	int MaxTD;
	void Init(int ax, int ay, int e, int max);
	void Mnoz(int ax, int ay, MainWindow* mw);
};
class Wall :public GameObject {
public:
	explicit Wall() {
		Type = TWall;
		strength = 255;
	}
	void Delete(MainWindow* mw);
};
class Energy :public GameObject {
public:
	GO_STD_H(Energy)
	bool charge;
	void chk(MainWindow* mw, GameObject* go, int e, int m, int p);
};
class Bact :public GameObject {
public:
	GO_STD_H(Bact)
	bool spor;
	void chk(int x, int y, MainWindow * mw);
};
class Good :public GameObject {
public:
	GO_STD_H(Good)
	bool spor;
	void chk(int x, int y, MainWindow * mw);
	bool mov(int x, int y, MainWindow * mw);
};
class Fighter :public GameObject {
public:
	GO_STD_H(Fighter)
	void chk(int x, int y, MainWindow * mw);
};
class Universal :public GameObject {
public:
	GO_STD_H(Universal)
	void chk(int x, int y, MainWindow * mw);
};
class Zed :public GameObject {
public:
	GO_STD_H(Zed)
	void chk(int x, int y, MainWindow * mw);
};
class Clean :public GameObject {
public:
	bool del = false;
	GO_STD_H(Clean)
	void chk(int x, int y, MainWindow * mw);
};
class Neuro :public GameObject {
public:
	int net[NetSize];
	GO_STD_H(Neuro)
	void chk(int x, int y, MainWindow * mw);
	void SetNew(int x, int y, MainWindow * mw);
	void Mutable(int lastnet[]);
};
