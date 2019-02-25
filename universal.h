GO_STD_CD(Universal);

void Universal::Init(int ax, int ay) {
	GameObject::Init(ax, ay);
	energy = 30;
	strength = 200;
	speed = 3;
}
void Universal::Do(MainWindow* mw) {
	if ((urand()%430)==1) {
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
	if (energy<10) {
		energy += strength;
		strength = 0;
	}
	if ((urand()%30)==1) {
		mw->FieldMov(x, y, x + urand(3) - 1, y + urand(3) - 1);
	}
}
void Universal::chk(int ax, int ay, MainWindow* mw) {
	GameObject* go = mw->Get(ax, ay);
	if ((go!=nullptr)&&(go->Type!=TWall)) {
		if ((urand()%((go->Type==TUniversal)?(800):(30)))==1) {
			energy += (go->energy)*(urand()%3);
			go->energy = 0;
		}
		if (go->Type==TUniversal) {
			if ((go->energy < 10) && (energy > 50)) {
				energy -= (10 - go->energy);
				go->energy = 10;
			}
			else {
				if (go->energy>20) {
					go->energy--;
					energy++;
				}
			}
		}
		else {
			int k = urand() % 10;
			go->energy -= k;
			energy += k;
		}
		if (energy>100) {
			energy = 50;
			GameObject* gg = mw->p.GUniversal(ax, ay);
			gg->energy = 50;
		}
	}
}
Uint32 Universal::Color() {
	return rgb(strength, energy, 255-energy);
}