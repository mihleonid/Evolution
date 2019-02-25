GO_STD_CD(Eater);
void Eater::Init(int ax, int ay) {
	Init(ax, ay, 100, 255);
}
void Eater::Init(int ax, int ay, int e, int max) {
	GameObject::Init(ax, ay);
	energy = e;
	MaxSpeed = urand(50, 60);
	MaxTD = urand(300, 600);
	energy += urand(-10, 11);
	if (max >= 255)
	{
		speed = urand(5, 10);
	}
	else
	{
		speed = max;
	}
	int tmp = speed + urand(-2, 3);
	if (tmp < 0)
	{
		speed = 0;
	}
	else
	{
		if (tmp > 100)
		{
			speed = 100;
		}
		else
		{
			speed = tmp;
		}
	}
	strength = 120;
}
void Eater::Do(MainWindow* mw) {
	energy--;
	speed;
	if (energy > MaxTD)
	{
		DeleteSelf(mw);
	}
	else
	{
		energy--;
		if (energy < 120)
		{
			Mnoz(x + 1, y, mw);
			Mnoz(x + 1, y + 1, mw);
			Mnoz(x + 1, y - 1, mw);
			Mnoz(x - 1, y, mw);
			Mnoz(x - 1, y + 1, mw);
			Mnoz(x - 1, y - 1, mw);
			Mnoz(x, y - 1, mw);
			Mnoz(x, y + 1, mw);
			energy--;
		}
		else
		{
			energy--;
			Mnoz(x - 1, y + 1, mw);
			Mnoz(x - 1, y - 1, mw);
			Mnoz(x + 1, y + 1, mw);
			Mnoz(x + 1, y - 1, mw);
		}
	}
}
void Eater::Mnoz(int ax, int ay, MainWindow* mw)
{
	GameObject* go = mw->Get(ax, ay);
	if (go != nullptr)
	{
		if (go->Type == TFood)
		{
			energy += (go->energy / 2);
			int tmp = speed + urand(-2, 16);
			if (tmp < 0)
			{
				tmp = 0;
			}
			if (tmp > MaxSpeed)
			{
				tmp = MaxSpeed;
			}
			speed = tmp;
			mw->Set(mw->p.GEater(ax, ay, energy, speed));
		}
	}
}
Uint32 Eater::Color() {
	return rgb(195, 195, 195);
}