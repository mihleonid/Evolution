GO_STD_CD(Fighter)
void Fighter::Init(int ax, int ay) {
	GameObject::Init(ax, ay);
	energy = 30;
	strength = 128;
	speed = 8;
}
void Fighter::Do(MainWindow* mw) {
	if ((urand() % 16) == 0) {
		energy--;
	}
	if ((urand() % 5) == 0) {
		mw->FieldMov(x, y, x + (urand() % 3 - 1), y + (urand() % 3 - 1));
	}
	chk(x + 1, y, mw);
	chk(x + 1, y + 1, mw);
	chk(x + 1, y - 1, mw);
	chk(x - 1, y, mw);
	chk(x - 1, y + 1, mw);
	chk(x - 1, y - 1, mw);
	chk(x, y - 1, mw);
	chk(x, y + 1, mw);

}
void Fighter::chk(int ax, int ay, MainWindow* mw) {
	GameObject* go = mw->Get(ax, ay);
	if ((go != nullptr) && (go->Type != TWall) && (go->Type != TFighter)) {
		if ((urand() % 2) == 1) {
			if (go->strength > 10) {
				go->strength -= 6;
			}
			else {
				go->energy -= 8;
			}
			energy += 4;
			if (go->Type == TFood) {
				energy += go->energy;
				go->energy = 0;
			}
			if (go->Type == TGood) {
				energy += go->energy/2;
				go->energy /= 2;
				if (speed>4) {
					speed--;
				}
			}
			if (go->energy > 300) {
				GameObject* nue = mw->p.GFighter(ax, ay);
				nue->energy = 120;
				mw->Set(nue);
				go->energy = 120;
			}
		}
	}
}
Uint32 Fighter::Color() {
	int op = 100 + energy / 2;
	return rgb(op, op * 2-100, 100+op);
}