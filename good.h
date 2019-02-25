GO_STD_CD(Good)
void Good::Init(int ax, int ay) {
	GameObject::Init(ax, ay);
	energy = 300;
	strength = 160;
	speed = 3;
	spor = false;
}
void Good::Do(MainWindow* mw) {

	if (spor) {
		if ((urand() % 6) == 0) {
			energy--;
		}
		int movx = (urand() % 3 - 1);
		int movy = (urand() % 3 - 1);
		if (mov(x+movx, y+movy, mw)) {
			goto end;
		}
		if (mov(x - movx, y + movy, mw)) {
			goto end;
		}
		if (mov(x + movx, y - movy, mw)) {
			goto end;
		}
		if (mov(x - movx, y - movy, mw)) {
			goto end;
		}
		if ((urand()%14)==1) {
			mw->FieldMov(x, y, x+movx, y+movy);
		}
		else {
			if ((urand()%3)==1) {
				energy++;
			}
		}
	}
	else {
		energy--;
		int movx = (urand() % 5 - 2);
		int movy = (urand() % 5 - 2);
		if (mov(x + movx, y + movy, mw)) {
			goto end;
		}
		if (mov(x - movx, y + movy, mw)) {
			goto end;
		}
		if (mov(x + movx, y - movy, mw)) {
			goto end;
		}
		if (mov(x - movx, y - movy, mw)) {
			goto end;
		}
		if ((urand() % 10) == 2) {
			mw->FieldMov(x, y, x + movx, y + movy);
		}
		else {
			if ((urand()%6)==1) {
				energy++;
			}
		}
	}
	end:;
	if (energy < 60) {
		spor = true;
	}
	if (energy > 80) {
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
bool Good::mov(int ax, int ay, MainWindow* mw) {
	if (!(mw->Exists(ax, ay))) {
		if ((mw->Exists(ax+1, ay))&& (mw->Get(ax+1, ay)->Type==TGood)) {
			mw->FieldMov(x, y, ax+1, ay);
			return true;
		}
		if ((mw->Exists(ax - 1, ay)) && (mw->Get(ax - 1, ay)->Type == TGood)) {
			mw->FieldMov(x, y, ax - 1, ay);
			return true;
		}
		if ((mw->Exists(ax, ay+1)) && (mw->Get(ax, ay+1)->Type == TGood)) {
			mw->FieldMov(x, y, ax, ay+1);
			return true;
		}
		if ((mw->Exists(ax, ay-1)) && (mw->Get(ax, ay-1)->Type == TGood)) {
			mw->FieldMov(x, y, ax, ay-1);
			return true;
		}
	}
	return false;
}
void Good::chk(int ax, int ay, MainWindow* mw) {
	GameObject* go = mw->Get(ax, ay);
	if ((go != nullptr) && (go->Type != TWall) && (go->Type != TGood)) {
		if (go->strength < strength) {
			if ((urand() % 2) == 1) {
				if (go->strength > 10) {
					go->strength -= 6;
				}
				else {
					go->energy -= 8;
				}
				energy += 4;
				if (go->Type == TFood) {
					energy += go->energy + (go->strength)/10;
					go->energy = 0;
				}
				if (go->energy > 300) {
					GameObject* nue = mw->p.GGood(ax, ay);
					nue->energy = 120;
					mw->Set(nue);
					go->energy = 120;
				}
			}
		}
	}
	if ((go!=nullptr)&&(go->Type==TGood)) {
		int sum = go->energy + energy;
		go->energy = sum / 2;
		energy = (sum / 2)+1;
	}
}
Uint32 Good::Color() {
	int op = 100 + energy / 2;
	if (spor) {
		return rgb(op, 0, op);
	}
	else {
		return rgb(op * 2, 0, op);
	}
}