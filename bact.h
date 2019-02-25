GO_STD_CD(Bact)
void Bact::Init(int ax, int ay) {
	GameObject::Init(ax, ay);
	energy = 300;
	strength = 168;
	speed = 3;
	spor = false;
}
void Bact::Do(MainWindow* mw) {
	if (spor) {
		if ((urand()%6)==0) {
			energy--;
		}
		if ((urand()%3)==0) {
			mw->FieldMov(x, y, x + (urand() % 3 - 1), y + (urand() % 3 - 1));
		}
	}
	else {
		energy--;
		if ((urand()%3)==1) {
			mw->FieldMov(x, y, x + (urand() % 5 - 2), y + (urand() % 5 - 2));
		}
		if ((urand() % 10) == 1) {
			mw->FieldMov(x, y, x + (urand() % 3 - 1), y + (urand() % 3 - 1));
		}
	}
	if (energy<60) {
		spor = true;
	}
	if (energy>80) {
		spor = false;
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
void Bact::chk(int ax, int ay, MainWindow* mw) {
	GameObject* go = mw->Get(ax, ay);
	if ((go!=nullptr)&&(go->Type!=TWall)) {
		if (go->strength<strength) {
			if ((urand()%2)==1) {
				if (go->strength > 10) {
					go->strength -= 6;
				}
				else {
					go->energy -= 8;
				}
				energy += 4;
				if (go->Type==TFood) {
					energy += go->energy;
					go->energy = 0;
				}
				if (go->energy>300) {
					GameObject* nue = mw->p.GBact(ax, ay);
					nue->energy = 120;
					mw->Set(nue);
					go->energy = 120;
				}
			}
		}
	}
}
Uint32 Bact::Color() {
	int op = 100 + energy / 2;
	if (spor) {
		return rgb(op, op, 0);
	}
	else {
		return rgb(op*2, op, 0);
	}
}