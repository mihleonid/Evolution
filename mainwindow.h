#define MACRO_KEYHANDEL_GO(GO, KEY)if (e.key.keysym.scancode == SDL_SCANCODE_####KEY){current = GO; goto evt; }
#define MACRO_MOUSEMOVE_GO(GO)if (current==T##GO){Set(p.G##GO(i, j));}

class MainWindow
{
public:
#pragma region Init
	explicit MainWindow() {
		ex = true;
		/*if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
		}*/
		Init();
		for (int x = 300; x < 400; x++) {
			for (int y = 300; y < 400; y++) {
				Set(p.GFood(x, y));
			}
		}
		for (int x = 299; x <= 400; x+=101) {
			for (int y = 299; y <= 400; y++) {
				Set(p.GWall(x, y));
			}
		}
		for (int y = 299; y <= 400; y++) {
			Set(p.GWall(y, 299));
			Set(p.GWall(y, 400));
		}

		for (int y = 9; y <= 230; y++) {
			Set(p.GWall(230, y));
		}
		for (int y = 9; y <= 230; y++) {
			Set(p.GWall(9, y));
		}
		for (int y = 9; y <= 230; y++) {
			Set(p.GWall(y, 9));
			Set(p.GWall(y, 230));
		}

		for (int y = 9; y <= 110; y++) {
			Set(p.GWall(110+240, y));
		}
		for (int y = 9; y <= 110; y++) {
			Set(p.GWall(9+240, y));
		}
		for (int y = 9; y <= 110; y++) {
			Set(p.GWall(y+240, 9));
			Set(p.GWall(y+240, 110));
		}

		auto func = [](MainWindow* mw)
		{
			mw->gameLoop();
		};
		std::thread t(func, this);
		t.detach();
		auto funcs = [](MainWindow* mw)
		{
			mw->renderLoop();
        };
        std::thread ts(funcs, this);
        ts.detach();
	}
	~MainWindow() {
		ex = false;
		//SDL_Quit();
	}
#pragma endregion
#pragma region Prop
	GameObject** all = new GameObject*[LIMIT];
	GameObject** field = new GameObject*[WIDTH*HEIGHT];
	GameObject** buffer = new GameObject*[1];
	int buffersize = 1;
	int nxt = 0;
	bool ex;
	SDL_Surface* surface;
	SDL_Window* win;
	Pools p;
#pragma endregion
#pragma region Field
	void Set(GameObject* go);
	GameObject* Get(int x, int y);
	GameObject* Delete(int x, int y);
	bool Exists(int x, int y);
	void Coordinate(int & x, int & y);
	void Init();
	void AllMov(int from, int to);
	void FieldMov(int x1, int y1, int x2, int y2);
#pragma endregion
	void renderLoop() {
        	win = SDL_CreateWindow("LEvolution:Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WWIDTH, WHEIGHT, 0);//SDL_WINDOW_FULLSCREEN//SDL_WINDOW_OPENGL
        	//win = SDL_CreateWindow("LEvolution", GLOBX, GLOBY, WWIDTH, WHEIGHT, 0);//SDL_WINDOW_FULLSCREEN//SDL_WINDOW_OPENGL
		surface = SDL_GetWindowSurface(win);
		SDL_Event e;
		buffer[0] = nullptr;
		while (ex) {
			if (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					ex = false;
					goto evt;
				}
				if (e.type == SDL_WINDOWEVENT) {
					if(e.window.event==SDL_WINDOWEVENT_CLOSE){
						ex = false;
						goto evt;
					}
				}
				if (e.type == SDL_KEYDOWN) {
					MACRO_KEYHANDEL_GO(TWall, W);
					MACRO_KEYHANDEL_GO(TDel, D);
					MACRO_KEYHANDEL_GO(TFood, F);
					MACRO_KEYHANDEL_GO(TEater, E);
					MACRO_KEYHANDEL_GO(TEnergy, N);
					MACRO_KEYHANDEL_GO(TBact, A);
					MACRO_KEYHANDEL_GO(TGood, G);
					MACRO_KEYHANDEL_GO(TFighter, I);
					MACRO_KEYHANDEL_GO(TUniversal, U);
					MACRO_KEYHANDEL_GO(TZed, Z);
					MACRO_KEYHANDEL_GO(TClean, C);
					MACRO_KEYHANDEL_GO(TNeuro, O);
					MACRO_KEYHANDEL_GO(TMove, M);
					MACRO_KEYHANDEL_GO(TPaste, P);
					MACRO_KEYHANDEL_GO(TCopy, K);
					if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
						ex = false;
						goto evt;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
						size += 2;
						goto evt;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
						size -= 2;
						goto evt;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_1) {
						fielddraw = !fielddraw;
						goto evt;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_Q) {
						ex = false;
						goto evt;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
						ex = false;
						goto evt;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
						size += 2;
						goto evt;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
						size -= 2;
						goto evt;
					}
				}
				if (e.type == SDL_MOUSEMOTION) {
					if (ris) {
						if ((current == TMove) || (current == TCopy)) {
							for (int i = 0; i < buffersize*buffersize;i++) {
								delete buffer[i];
							}
							delete buffer;
							buffersize = size + 1;
							buffer = new GameObject*[buffersize*buffersize];
						}
						int x = 0;
						int y = 0;
						for (int i = e.button.x - size; i <= e.button.x + size; i++) {
							for (int j = e.button.y - size; j <= e.button.y + size; j++) {
								if (current == TDel) {
									Delete(i, j);
								}
								if (current == TMove) {
									Coordinate(i, j);
									if (Exists(i, j)) {
										GameObject* goe = field[i*HEIGHT + j];
										field[i*HEIGHT + j] = nullptr;
										if (goe->Type != TWall) {
											AllMov(nxt - 1, goe->pos);
											nxt--;
										}
										buffer[x + buffersize * y]=goe;
									}
								}
								if (current == TCopy) {
									Coordinate(i, j);
									if (Exists(i, j)) {
										GameObject* goe = field[i*HEIGHT + j];
										GameObject* ngoe = (GameObject*)malloc(sizeof(*goe));
										memcpy(ngoe, goe, sizeof(*goe));
										buffer[x + buffersize * y] = ngoe;
									}
								}
								if (current == TPaste){
									GameObject* go = buffer[x + buffersize * y];
									go->x = i;
									go->y = j;
									Set(go);
								}
								MACRO_MOUSEMOVE_GO(Food);
								MACRO_MOUSEMOVE_GO(Eater);
								MACRO_MOUSEMOVE_GO(Wall);
								MACRO_MOUSEMOVE_GO(Energy);
								MACRO_MOUSEMOVE_GO(Bact);
								MACRO_MOUSEMOVE_GO(Good);
								MACRO_MOUSEMOVE_GO(Fighter);
								MACRO_MOUSEMOVE_GO(Universal);
								MACRO_MOUSEMOVE_GO(Zed);
								MACRO_MOUSEMOVE_GO(Clean);
								MACRO_MOUSEMOVE_GO(Neuro);
								y++;
							}
							x++;
						}
					}
					goto evt;
				}
				if (e.type == SDL_MOUSEBUTTONDOWN) {
					ris = true;
					goto evt;
				}
				if (e.type == SDL_MOUSEBUTTONUP) {
					ris = false;
					goto evt;
				}
			evt:;
			}
			for (int x = 0; x < WWIDTH; x++) {
				for (int y = 0; y < WHEIGHT; y++) {
					if ((x + y) < size) {
						pixel(x, y, 0xFFFF0000);
					} else {
						GameObject* go = field[x*HEIGHT + y];
						if (go == nullptr) {
							pixel(x, y, 0xFFE0E0E0);
						}
						else {
							pixel(x, y, go->Color());
						}
					}
				}
			}
			SDL_UpdateWindowSurface(win);
            //std::this_thread::sleep_for(std::chrono::milliseconds(41));
		}
		SDL_DestroyWindow(win);
	}
	void gameLoop() {
		while (ex) {
			int lim = nxt;
			for (int i = 0; i < lim; i++) {
				GameObject* ptr = all[i];
				if (ptr != nullptr) {
					if ((ptr->energy) <= 0) {
						ptr->DeleteSelf(this);
					}
					else {
						if (ptr->energy > MAXPARAM) {
							ptr->energy = MAXPARAM;
						}
						if (ptr->tospeed >= ptr->speed) {
							ptr->Do(this);
							ptr->tospeed = 0;
						}
						else {
							ptr->tospeed++;
						}
					}
				}
			}
			while (ris) {
				std::this_thread::sleep_for(std::chrono::milliseconds(3));
			}
		}
	}
	void pixel(int x, int y, Uint32 color) {
		if (x < 0) {
			x = 0;
		}
		if (x >= WWIDTH) {
			x = WWIDTH - 1;
		}
		if (y < 0) {
			y = 0;
		}
		if (y >= WHEIGHT) {
			y = WHEIGHT - 1;
		}
		Uint8 * pixel = (Uint8*)surface->pixels;
		pixel += (y * surface->pitch) + (x * sizeof(Uint32));
		*((Uint32*)pixel) = color;
	}
};
