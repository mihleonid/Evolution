GO_STD_CD(YYY);
#define TMPClamp(CM) Clamp(net[0+CM], 20, 254);Clamp(net[1+CM], 20, 254);Clamp(net[2+CM], 1, 20);Clamp(net[3+CM], 30, 80);Clamp(net[4+CM], 10, 80);Clamp(net[5+CM], 0, net[0+CM]);Clamp(net[6+CM], 1, 10)
#define RNDOF ((urand()%(NetSize))*NetSize)
void YYY::Init(int ax, int ay) {
	GameObject::Init(ax, ay);
	for(int i=0;i<NetSize;i++){
		net[0+i*NetSize] = 122;
		net[1+i*NetSize] = 122;
		net[2+i*NetSize] = 2;
		net[3+i*NetSize] = 40;
		net[4+i*NetSize] = 20;
		net[5+i*NetSize] = 60;
		net[6+i*NetSize] = 5;
	}
	energy = net[0]/2;
	strength = net[1];
	speed = net[2];
}
void YYY::Mutable(int lastnet[]) {
	for (int i = 0; i < NetSize*NetSize; i++) {
		if ((urand()%lastnet[3])==1) {
			net[i] = lastnet[i] + (urand()%3)-1;
		}
	}
	for(int i=0;i<NetSize;i++){
		TMPClamp(i*NetSize);
	}
}
void YYY::Do(MainWindow* mw) {
	energy--;
	chk(x + 1, y + 1, mw);
	chk(x + 1, y, mw);
	chk(x + 1, y - 1, mw);
	chk(x, y + 1, mw);
	chk(x, y - 1, mw);
	chk(x - 1, y + 1, mw);
	chk(x - 1, y, mw);
	chk(x - 1, y - 1, mw);
	if ((urand()%net[4+RNDOF])==1) {
		for (int i = 0; i < NetSize; i++) {
			if ((urand() % net[3+RNDOF]) == 1) {
				net[i+RNDOF] += (urand() % 9) - 4;
			}
		}
		for(int i=0;i<NetSize;i++){
			TMPClamp(i*NetSize);
		}
	}
	if (energy>net[0+RNDOF]) {
		energy = net[0+RNDOF];
	}
}
void YYY::chk(int ax, int ay, MainWindow* mw) {
	GameObject* go = mw->Get(ax, ay);
	if ((go != nullptr) && (go->Type != TWall)) {
		int delta = urand() % net[6+RNDOF];
		go->energy -= delta;
		energy += delta;
		if (energy > go->energy) {
			SetNew(ax, ay, mw);
		}
	}
	if (go == nullptr) {
		SetNew(ax, ay, mw);
	}
}
void YYY::SetNew(int ax, int ay, MainWindow* mw) {
	if (energy!=0) {
		if ((urand() % energy) > net[5+RNDOF]) {
			YYY* go = mw->p.GYYY(ax, ay);
			go->Mutable(net);
			go->energy = go->net[0+RNDOF] / 2;
			go->strength = go->net[1+RNDOF];
			go->speed = go->net[2+RNDOF];
			mw->Set(go);
			energy -= go->net[0+RNDOF] / 2;
		}
	}
}
Uint32 YYY::Color() {
	b=net[2+RNDOF];
	a=net[1+RNDOF];
	c=net[0+RNDOF];
	if(a==0){
		a=1;
	}
	if(b==0){
		b=1;
	}
	if(c==0){
		c=1;
	}
	return rgb(255*speed/a, 255*strength/b, 255*energy/c);
}
#undef TMPClamp
#undef RNDOF

