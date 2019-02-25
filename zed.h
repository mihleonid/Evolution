GO_STD_CD(Zed);

void Zed::Init(int ax, int ay) {
	GameObject::Init(ax, ay);
	energy = 300;
	strength = 160;
	speed = 13;
}
void Zed::Do(MainWindow* mw) {
	if ((urand() % 43) == 1) {
		energy--;
	}
	chk(x + 1, y + 1, mw);
	chk(x + 1, y, mw);
	chk(x + 1, y - 1, mw);
	chk(x, y + 1, mw);
	chk(x, y - 1, mw);
	chk(x - 1, y + 1, mw);
	chk(x - 1, y, mw);
	chk(x - 1, y - 1, mw);
	if (((urand() % 30) == 1)&&(energy < 200)) {
		mw->FieldMov(x, y, x + urand(3) - 1, y + urand(3) - 1);
	}
}
void Zed::chk(int ax, int ay, MainWindow* mw) {
	GameObject* go = mw->Get(ax, ay);
	if ((go != nullptr) && (go->Type != TWall)) {
		go->energy -= 3;
		energy += 3;
		if (((go->energy)*4)<=(energy)) {
			energy += go->energy;
			mw->Delete(ax, ay);
			if ((urand()%4)==0) {
				if ((urand() % (43 - min(energy/50, 3))) == 0) {
					mw->Set(mw->p.GZed(ax, ay));
				}
				else {
					mw->FieldMov(x, y, ax, ay);
				}
			}
		}
		else {
			if (go->Type == TBact) {
				mw->Delete(ax, ay);
			}
		}
	}
}
Uint32 Zed::Color() {
	return rgb(0, energy, 255 - energy);
}