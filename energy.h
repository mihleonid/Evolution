GO_STD_CD(Energy)

void Energy::Init(int ax, int ay) {
	GameObject::Init(ax, ay);
	energy = 100;
	strength = 100;
	speed = 5;
	charge = false;
}
void Energy::Do(MainWindow* mw) {
	int e = 500;
	int m = 4;
	int p = 6;
	GameObject* go;

	if (energy < 650) {
		m = 9;
		p = 13;
		if (urand(222) == 0) {
			charge = true;
		}
	}
	if (energy > 800) {
		m = 20;
		p = 32;
	}
	go = mw->Get(x + 1, y);
	chk(mw, go, e, m, p);
	go = mw->Get(x - 1, y);
	chk(mw, go, e, m, p);
	go = mw->Get(x + 1, y + 1);
	chk(mw, go, e, m, p);
	go = mw->Get(x + 1, y - 1);
	chk(mw, go, e, m, p);
	go = mw->Get(x, y + 1);
	chk(mw, go, e, m, p);
	go = mw->Get(x, y - 1);
	chk(mw, go, e, m, p);
	go = mw->Get(x - 1, y + 1);
	chk(mw, go, e, m, p);
	go = mw->Get(x - 1, y - 1);
	chk(mw, go, e, m, p);
	if ((urand() % 1136) == 0) {
		if (urand() % 9 <= 6) {
			energy--;
		}
		if (urand() % 6 <= 3) {
			energy--;
		}
		energy--;
	}
	if (energy < 500) {
		if (urand(3) == 0) {
			charge = true;
		}
	}
	if (energy > 1800) {
		energy -= 100;
		strength += 10;
		if (strength >= 255) {
			strength = 254;
		}
		charge = false;
	}
	if ((energy > 1300)) {
		if (urand(222)) {
			charge = false;
		}
	}
	else {
		if (urand(30000) == 0) {
			charge = !charge;
		}
	}
}
void Energy::chk(MainWindow* mw, GameObject* go, int e, int m, int p) {
	if ((go != nullptr) && (go->Type != TWall)) {
		if (charge) {
			int o = urand(6);
			go->energy -= o;
			energy += o;
		}
		else {
			if (energy < 100) {
				if (urand(2)) {
					go->energy--;
					energy++;
					charge = true;
				}
			}
			if (energy < 50) {
				if (urand(5) < 2) {
					go->energy -= 10;
					energy += 10;
				}
			}
			if (energy < 10) {
				if (urand(2)) {
					go->energy -= 4;
					energy += 4;
				}
			}
			if (go->Type == TEnergy) {
				if (energy < 700) {
					if (go->energy > 900) {
						go->energy--;
						energy++;
					}
				}
				else {
					go->energy++;
					energy--;
					if (energy > 800) {
						int dif = energy - go->energy;
						dif /= 10;
						energy -= dif;
						go->energy += dif;
					}
					if (energy > 1600) {
						int mod = ((1800 - (go->energy)) / 18);
						int o = urand() % max(1, mod);
						go->energy += o;
						energy -= o;
					}
					if (energy > 1400) {
						if (go->energy < 900) {
							go->energy += 3;
							energy -= 3;
						}
					}
					else {
						if (urand(2)) {
							go->energy--;
							energy++;
						}
						else {
							go->energy++;
							energy--;
						}
					}
				}
			}
			else {
				if ((urand() % energy) < e) {
					int h = urand(p - m);
					go->energy -= h + m;
					energy += h + p;
				}
				else {
					int k = urand(p - m);
					go->energy += k + (p / 2);
					energy -= k + m;
				}
			}
		}
	}
}
Uint32 Energy::Color() {
	if (charge) {
		return 0xFF005533 + min(255, (energy + 300) * 255 / 1760) * 0x10000;
	}
	return 0xFF335500 + min(255, energy * 255 / 1760);
}