GO_STD_CD(Clean);

void Clean::Init(int ax, int ay) {
	GameObject::Init(ax, ay);
	energy = 60;
	strength = 255;
	speed = 0;
	del = false;
}
void Clean::Do(MainWindow* mw) {
	energy--;
	if (energy<59) {
		del = true;
	}
	chk(x + 1, y + 1, mw);
	chk(x + 1, y, mw);
	chk(x + 1, y - 1, mw);
	chk(x, y + 1, mw);
	chk(x, y - 1, mw);
	chk(x - 1, y + 1, mw);
	chk(x - 1, y, mw);
	chk(x - 1, y - 1, mw);
}
void Clean::chk(int ax, int ay, MainWindow* mw) {
	GameObject* go = mw->Get(ax, ay);
	if (del) {
	} else {
		if ((go != nullptr) && (go->Type != TWall) && (go->Type != TClean)) {
			mw->Set(mw->p.GClean(ax, ay));
		}
		if (go == nullptr) {
			mw->Set(mw->p.GClean(ax, ay));
		}
	}
}
Uint32 Clean::Color() {
	if(del){
		return rgb(235, 235, 248);
	}
	return rgb(255, 255, 255);
}