void MainWindow::Coordinate(int &x, int &y) {
	x %= WIDTH;
	y %= HEIGHT;
	if (x < 0) {
		x += WIDTH;
	}
	if (y < 0) {
		y += HEIGHT;
	}
}
void MainWindow::Init() {
	for (int i = 0; i < WIDTH*HEIGHT; i++) {
		field[i] = nullptr;
	}
	for (int i = 0; i < LIMIT; i++) {
		all[i] = nullptr;
	}
}
void MainWindow::Set(GameObject* go) {
	Coordinate(go->x, go->y);
	if (Exists(go->x, go->y)) {
		Delete(go->x, go->y);
		if (go->Type != TWall) {
			all[nxt] = go;
			go->pos = nxt;
			nxt++;
		}
		field[(go->x)*HEIGHT + (go->y)] = go;
	}
	else {
		if (go->Type != TWall) {
			all[nxt] = go;
			go->pos = nxt;
			nxt++;
		}
		field[(go->x)*HEIGHT + (go->y)] = go;
	}
}
GameObject* MainWindow::Get(int x, int y) {
	Coordinate(x, y);
	return field[x*HEIGHT + y];
}
bool MainWindow::Exists(int x, int y) {
	Coordinate(x, y);
	return ((field[x*HEIGHT + y]) != nullptr);
}
GameObject* MainWindow::Delete(int x, int y) {
	Coordinate(x, y);
	if (Exists(x, y)) {
		GameObject* go = field[x*HEIGHT + y];
		field[x*HEIGHT + y] = nullptr;
		if (go->Type != TWall) {
			AllMov(nxt - 1, go->pos);
			nxt--;
		}
		go->Delete(this);
		return go;
	}
	return nullptr;
}
void MainWindow::AllMov(int from, int to) {
	all[from]->pos = to;
	all[to] = all[from];
	all[from] = nullptr;
}
void MainWindow::FieldMov(int x1, int y1, int x2, int y2) {
	Coordinate(x1, y1);
	Coordinate(x2, y2);
	GameObject* go = field[x1*HEIGHT + y1];
	if ((go!=nullptr)&&(field[x2*HEIGHT + y2]==nullptr)) {
		field[x2*HEIGHT + y2] = go;
		field[x1*HEIGHT + y1] = nullptr;
		go->x = x2;
		go->y = y2;
	}
}