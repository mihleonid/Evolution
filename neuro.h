GO_STD_CD(Neuro);
#define TMPClamp Clamp(net[0], 20, 254);Clamp(net[1], 20, 254);Clamp(net[2], 1, 20);Clamp(net[3], 30, 80);Clamp(net[4], 10, 80);Clamp(net[5], 0, net[0]);Clamp(net[6], 1, 10)
void Neuro::Init(int ax, int ay) {
	GameObject::Init(ax, ay);
	net[0] = 122;
	net[1] = 122;
	net[2] = 2;
	net[3] = 40;
	net[4] = 20;
	net[5] = 60;
	net[6] = 5;
	energy = net[0]/2;
	strength = net[1];
	speed = net[2];
}
void Neuro::Mutable(int lastnet[]) {
	for (int i = 0; i < NetSize; i++) {
		if ((urand()%lastnet[3])==1) {
			net[i] = lastnet[i] + (urand()%3)-1;
		}
	}
	TMPClamp;
}
void Neuro::Do(MainWindow* mw) {
	energy--;
	chk(x + 1, y + 1, mw);
	chk(x + 1, y, mw);
	chk(x + 1, y - 1, mw);
	chk(x, y + 1, mw);
	chk(x, y - 1, mw);
	chk(x - 1, y + 1, mw);
	chk(x - 1, y, mw);
	chk(x - 1, y - 1, mw);
	if ((urand()%net[4])==1) {
		for (int i = 0; i < NetSize; i++) {
			if ((urand() % net[3]) == 1) {
				net[i] += (urand() % 3) - 1;
			}
		}
		TMPClamp;
	}
	if (energy>net[0]) {
		energy = net[0];
	}
}
void Neuro::chk(int ax, int ay, MainWindow* mw) {
	GameObject* go = mw->Get(ax, ay);
	if ((go != nullptr) && (go->Type != TWall)) {
		int delta = urand() % net[6];
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
void Neuro::SetNew(int ax, int ay, MainWindow* mw) {
	if (energy!=0) {
		if ((urand() % energy) > net[5]) {
			Neuro* go = mw->p.GNeuro(ax, ay);
			go->Mutable(net);
			go->energy = go->net[0] / 2;
			go->strength = go->net[1];
			go->speed = go->net[2];
			mw->Set(go);
			energy -= go->net[0] / 2;
		}
	}
}
Uint32 Neuro::Color() {
	return rgb(255*speed/net[2], 255*strength/net[1], 255*energy/net[0]);
}
#undef TMPClamp