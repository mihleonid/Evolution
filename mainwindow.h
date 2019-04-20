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
					if (e.key.keysym.scancode == SDL_SCANCODE_S) {
						ris=true;
						Svdg dg;
						while(SDL_PollEvent(&e)){}
						if(dg.ok){
							save(dg.text+".levolution");
						}
						ris=false;
						goto evt;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_R) {
						ris=true;
						Svdg dg;
						while(SDL_PollEvent(&e)){}
						if(dg.ok){
							restore(dg.text+".levolution");
						}
						ris=false;
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
	void restore(std::string f){
		try{
			FILE *fp = fopen(f.c_str(), "r");
			if (fp == NULL) {
				if (errno == EACCES){
					std::cerr<<"Permission denied"<<std::endl;
				}else{
					std::cerr<<"Something went wrong: "<<strerror(errno)<<std::endl;
				}
				throw 1;
			}
			fclose(fp);
			std::ifstream file(f.c_str());
			std::string type;
			GameObject* go;
			for(int x=0;x<WIDTH;x++){
				for(int y=0;y<HEIGHT;y++){
					file>>type;
					if(file.eof()){throw 1;}
					if(type[0]=='D'){
						Delete(x, y);
						continue;
					}
					if(type[0]=='W'){
						Set(p.GWall(x, y));
						continue;
					}
					if(type[0]=='A'){
						Bact* g=p.GBact(x, y);
						int sp;
						file>>sp;
						if(file.eof()){throw 1;}
						g->spor=(bool)sp;
						go=g;
					}
					if(type[0]=='G'){
						Good* g=p.GGood(x, y);
						int sp;
						file>>sp;
						if(file.eof()){throw 1;}
						g->spor=(bool)sp;
						go=g;
					}
					if(type[0]=='N'){
						Energy* g=p.GEnergy(x, y);
						int sp;
						file>>sp;
						if(file.eof()){throw 1;}
						g->charge=(bool)sp;
						go=g;
					}
					if(type[0]=='C'){
						Clean* g=p.GClean(x, y);
						int sp;
						file>>sp;
						if(file.eof()){throw 1;}
						g->del=(bool)sp;
						go=g;
					}
					if(type[0]=='E'){
						Eater* g=p.GEater(x, y);
						int sp;
						int ss;
						file>>sp;
						if(file.eof()){throw 1;}
						file>>ss;
						if(file.eof()){throw 1;}
						g->MaxSpeed=sp;
						g->MaxTD=ss;
						go=g;
					}
					if(type[0]=='F'){
						Food* g=p.GFood(x, y);
						int sp;
						int ss;
						file>>sp;
						if(file.eof()){throw 1;}
						file>>ss;
						if(file.eof()){throw 1;}
						g->Delenie=sp;
						g->DelenieMax=ss;
						go=g;
					}
					if(type[0]=='Z'){
						go=p.GZed(x, y);
					}
					if(type[0]=='U'){
						go=p.GUniversal(x, y);
					}
					if(type[0]=='I'){
						go=p.GFighter(x, y);
					}
					if(type[0]=='O'){
						Neuro* g=p.GNeuro(x, y);
						for(int i=0;i<NetSize;i++){
							file>>(g->net)[i];
						}
						go=g;
					}
					int a, b, c, d;
					file>>a;
					if(file.eof()){throw 1;}
					file>>b;
					if(file.eof()){throw 1;}
					file>>c;
					if(file.eof()){throw 1;}
					file>>d;
					if(file.eof()){throw 1;}
					go->strength=(byte) a;
					go->speed=(byte) b;
					go->energy=c;
					go->tospeed=(byte)d;
					Set(go);
				}
			}
		}catch(std::exception& e){
			std::cerr<<"Save is not valid"<<std::endl;
		}catch(int e){
			std::cerr<<"Save is not valid"<<std::endl;
		}
	}
	void save(std::string f){
		try{
			FILE *fp = fopen(f.c_str(), "w");
			if (fp == NULL) {
				if (errno == EACCES){
					std::cerr<<"Permission denied"<<std::endl;
				}else{
					std::cerr<<"Something went wrong: "<<strerror(errno)<<std::endl;
				}
				throw 1;
			}
			fclose(fp);
			std::ofstream file(f.c_str());
			for(int x=0;x<WIDTH;x++){
				for(int y=0;y<HEIGHT;y++){
					GameObject* g=Get(x, y);
					if(g==nullptr){
						file<<"D ";
						continue;
					}
					if(g->Type==TWall){
						file<<"W ";
						continue;
					}
					if(g->Type==TZed){
						file<<"Z ";
					}
					if(g->Type==TFighter){
						file<<"I ";
					}
					if(g->Type==TUniversal){
						file<<"U ";
					}
					if(g->Type==TBact){
						file<<"A ";
						file<<(int)(((Bact*)g)->spor)<<" ";
					}
					if(g->Type==TGood){
						file<<"G ";
						file<<(int)(((Good*)g)->spor)<<" ";
					}
					if(g->Type==TEnergy){
						file<<"N ";
						file<<(int)(((Energy*)g)->charge)<<" ";
					}
					if(g->Type==TClean){
						file<<"C ";
						file<<(int)(((Clean*)g)->del)<<" ";
					}
					if(g->Type==TEater){
						file<<"E ";
						file<<((Eater*)g)->MaxSpeed<<" ";
						file<<((Eater*)g)->MaxTD<<" ";
					}
					if(g->Type==TFood){
						file<<"F ";
						file<<((Food*)g)->Delenie<<" ";
						file<<((Food*)g)->DelenieMax<<" ";
					}
					if(g->Type==TNeuro){
						file<<"O ";
						for(int i=0;i<NetSize;i++){
							file<<(((Neuro*)g)->net)[i]<<" ";
						}
					}
					file<<(int)(g->strength)<<" ";
					file<<(int)(g->speed)<<" ";
					file<<(int)(g->energy)<<" ";
					file<<(int)(g->tospeed)<<" ";
				}
			}
			file<<"EOF";
			file<<std::endl;
		}catch(std::exception& e){
			std::cerr<<"Cannot write file"<<std::endl;
		}catch(int e){
			std::cerr<<"Cannot write file"<<std::endl;
		}
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
