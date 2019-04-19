class Help
{
public:
	explicit Help(SDL_Window* www) {
		loop(www);
	}
	SDL_Window* win;
	TTF_Font* font;
	SDL_Renderer* ren;
	SDL_Color hi={60, 80, 150};
	SDL_Color back={6, 8, 100};
	SDL_Color fonc={170, 160, 150};
	SDL_Color fg, bg;
	int scroll=0;
	void loop(SDL_Window* www) {
		win = SDL_CreateWindow("LEvolution:Help", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WWIDTH, WHEIGHT, 0);//SDL_WINDOW_FULLSCREEN//SDL_WINDOW_OPENGL
		if (win == nullptr) {
			std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
			throw 1;
		}
		ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (ren == nullptr) {
			std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
			throw 1;
		}
		TTF_Font* fonta = TTF_OpenFont("assets/ubuntumono.ttf", 18);
		TTF_Font* fontb = TTF_OpenFont("assets/robbo.ttf", 30);
		TTF_Font* fontc = TTF_OpenFont("assets/roboreg.ttf", 25);
		if(!fonta) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
		}
		if(!fontb) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
		}
		if(!fontc) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
		}
		SDL_Event e;
		bool ex=true;
		std::ifstream filehelp("assets/help.txt");
		std::ifstream filehot("assets/hot.txt");
		std::ifstream* file;
		file=&filehelp;
		bool h1, h2, h35;
		h2=false;
		h1=false;
		h35=false;
		SDL_HideWindow(www);
		while (ex) {
			bg=back;
			fg=fonc;

			SDL_SetRenderDrawColor(ren, bg.r, bg.g, bg.b, 255);
			SDL_RenderClear(ren);
			//SDL_GetWindowPosition(win, &GLOBX, &GLOBY);

			font=fontb;
			Point p=drawTextCenter(WWIDTH/2, 7, "LEvolution");
			p.second+=29;
			font=fontc;
			Point p2=drawTextCenter(WWIDTH/2, p.second, "Помощь");
			p2.second+=20;

			if(h1){
				bg=hi;
			}
			Point p3=drawText(30, p2.second+p.second, "Описание");
			bg=back;
			if(h35){
				bg=hi;
			}
			Point p35=drawTextCenter(WWIDTH/2, p2.second+p.second, "Назад");
			bg=back;
			if(h2){
				bg=hi;
			}
			Point p4=drawTextRight(WWIDTH-30, p2.second+p.second, "Горячие клавиши");
			bg=back;

			int h1l=30;
			int h1r=p3.first+h1l;
			int h2r=WWIDTH-30;
			int h2l=h2r-p4.first;
			int h35r=WWIDTH/2 + p35.first/2;
			int h35l=WWIDTH/2 - p35.first/2;

			int top=p2.second+p.second;

			int maxo=p3.second+20;
			int maxoo=p4.second+20;
			int maxooo=p35.second+20;
			if(maxo<maxooo){
				maxo=maxooo;
			}
			if(maxo<maxoo){
				maxo=maxoo;
			}
			int bot=maxo-20+top;
			maxo+=p2.second+p.second;

			font=fonta;

			std::string str;
			int ny=maxo+8;
			while(getline(*file,str)){
				Point ptmp=drawText(20, ny, str.c_str());
				ny+=ptmp.second;
			}
			(*file).clear();
			(*file).seekg(0, std::ios::beg);

			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_WINDOWEVENT) {
					if(e.window.event==SDL_WINDOWEVENT_CLOSE){
						ex = false;
						goto evt;
					}
				}
				if (e.type == SDL_QUIT) {
					ex = false;
					goto evt;
				}
				if (e.type == SDL_KEYDOWN) {
					if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
						scroll+=2;
						if(scroll>200){
							scroll=200;
						}
						goto evt;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
						scroll-=2;
						if(scroll<0){
							scroll=0;
						}
						goto evt;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_Q) {
						ex=false;
						goto evt;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
						ex=false;
						goto evt;
					}
					goto evt;
				}
				if (e.type == SDL_MOUSEMOTION) {
					int x = e.button.x;
					int y = e.button.y;
					h1=false;
					h2=false;
					h35=false;
					if((x>h1l)&&(x<h1r)&&(y>top)&&(y<bot)){
						h1=true;
					}
					if((x>h35l)&&(x<h35r)&&(y>top)&&(y<bot)){
						h35=true;
					}
					if((x>h2l)&&(x<h2r)&&(y>top)&&(y<bot)){
						h2=true;
					}
					goto evt;
				}
				if (e.type == SDL_MOUSEBUTTONDOWN) {
					if(h1){
						file=&filehelp;
					}
					if(h2){
						file=&filehot;
					}
					if(h35){
						ex=false;
						goto evt;
					}
					goto evt;
				}
				if (e.type == SDL_MOUSEBUTTONUP) {
					goto evt;
				}
			evt:;
			}
			//SDL_UpdateWindowSurface(win);
			SDL_RenderPresent(ren);
		}
		SDL_ShowWindow(www);
		SDL_DestroyWindow(win);
	}

	std::pair<int, int> draw(int x, int y, SDL_Texture* tex) {
		SDL_Rect pos;
		pos.x = x;
		pos.y = y-scroll;
		SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
		SDL_RenderCopy(ren, tex, NULL, &pos);
		return std::pair<int, int>(pos.w, pos.h);
	}
	std::pair<int, int> drawText(int x, int y, const char* text){
		SDL_Texture* txt=makeText(ren, text);
		std::pair<int, int> res=draw(x, y, txt);
		SDL_DestroyTexture(txt);
		return res;
	}
	std::pair<int, int> drawText(int x, int y, int text){
		SDL_Texture* txt=makeText(ren, std::to_string(text).c_str());
		std::pair<int, int> res=draw(x, y, txt);
		SDL_DestroyTexture(txt);
		return res;
	}

	std::pair<int, int> drawRight(int x, int y, SDL_Texture* tex) {
		SDL_Rect pos;
		pos.x = x;
		pos.y = y-scroll;
		SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
		pos.x-=pos.w;
		SDL_RenderCopy(ren, tex, NULL, &pos);
		return std::pair<int, int>(pos.w, pos.h);
	}
	std::pair<int, int> drawCenter(int x, int y, SDL_Texture* tex) {
		SDL_Rect pos;
		pos.x = x;
		pos.y = y-scroll;
		SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
		pos.x-=pos.w/2;
		SDL_RenderCopy(ren, tex, NULL, &pos);
		return std::pair<int, int>(pos.w, pos.h);
	}
	std::pair<int, int> drawTextCenter(int x, int y, const char* text){
		SDL_Texture* txt=makeText(ren, text);
		std::pair<int, int> res=drawCenter(x, y, txt);
		SDL_DestroyTexture(txt);
		return res;
	}
	std::pair<int, int> drawTextRight(int x, int y, const char* text){
		SDL_Texture* txt=makeText(ren, text);
		std::pair<int, int> res=drawRight(x, y, txt);
		SDL_DestroyTexture(txt);
		return res;
	}
	std::pair<int, int> drawTextRight(int x, int y, int text){
		SDL_Texture* txt=makeText(ren, std::to_string(text).c_str());
		std::pair<int, int> res=drawRight(x, y, txt);
		SDL_DestroyTexture(txt);
		return res;
	}

	SDL_Texture* makeText(SDL_Renderer* ren, const char* c){
		SDL_Surface* surfaceMessage=TTF_RenderUTF8_Shaded(font, c, fg, bg);
		SDL_Texture* message=SDL_CreateTextureFromSurface(ren, surfaceMessage);
		SDL_FreeSurface(surfaceMessage);
		return message;
	}

};


