GO_STD_CD(Food)
void Food::Init(int ax, int ay) {
	GameObject::Init(ax, ay);
	strength = 128;
	speed = urand() % 2;
	energy = urand() % 20 + 1;
	Delenie = 0;
	DelenieMax = urand() % 30 + 10;
}
void Food::Do(MainWindow* mw) {
	Delenie++;
	if (Delenie > DelenieMax)
	{
		Delenie = 0;
		DelenieMax = urand() % 20 + 10;
		switch (urand() % 8) {
		case 0:
		{
			if (!(mw->Exists(x + 1, y)))
			{
				mw->Set(mw->p.GFood(x + 1, y));
			}
		}
		case 1:
		{
			if (!(mw->Exists(x - 1, y)))
			{
				mw->Set(mw->p.GFood(x - 1, y));
			}
		}
		case 2:
		{
			if (!(mw->Exists(x, y + 1)))
			{
				mw->Set(mw->p.GFood(x, y + 1));
			}
		}
		case 3:
		{
			if (!(mw->Exists(x, y - 1)))
			{
				mw->Set(mw->p.GFood(x, y - 1));
			}
		}
		case 4:
		{
			if (!(mw->Exists(x + 1, y + 1)))
			{
				mw->Set(mw->p.GFood(x + 1, y + 1));
			}
		}
		case 5:
		{
			if (!(mw->Exists(x + 1, y - 1)))
			{
				mw->Set(mw->p.GFood(x + 1, y - 1));
			}
		}
		case 6:
		{
			if (!(mw->Exists(x - 1, y + 1)))
			{
				mw->Set(mw->p.GFood(x - 1, y + 1));
			}
		}
		case 7:
		{
			if (!(mw->Exists(x - 1, y - 1)))
			{
				mw->Set(mw->p.GFood(x - 1, y - 1));
			}
		}
		}
		energy -= 2;
	}
	if ((urand() % 23) < 11)
	{
		if (energy < 30)
		{
			energy++;
		}
	}
	else
	{
		energy--;
	}
	/*int mod = rand() % 5;
	int md = rand() % 5;
	mod *= (rand() % 8) + 1;
	md *= (rand() % 8) + 1;
	if (!(mw->Exists(x + md, y + mod))) {
	mw->Set(mw->p.GFood(x + md, y + mod));
	}
	if (((rand() % 2) == 0) || ((rand() % 2) == 0) || ((rand() % 2) == 0) || ((rand() % 5) == 0) || ((rand() % 4) == 0) || ((rand() % 5) == 0)) {
	//mw->Delete(x, y);
	DeleteSelf(mw);
	}*/
}
Uint32 Food::Color() {
	return rgb(0, 195 + energy * 2, 0);
}