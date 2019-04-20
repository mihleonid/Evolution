class Svdg
{
public:
	bool ok;
	std::string text;
	explicit Svdg() {
		text="";
		ok=false;
		loop();
	}
	SDL_Window* win;
	TTF_Font* font;
	SDL_Renderer* ren;
	SDL_Color hi={60, 80, 150};
	SDL_Color back={6, 8, 100};
	SDL_Color fonc={170, 160, 150};
	SDL_Color fg, bg;
	void loop() {
		win = SDL_CreateWindow("LEvolution:Save", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WWIDTH, WHEIGHT, 0);//SDL_WINDOW_FULLSCREEN//SDL_WINDOW_OPENGL
		if (win == nullptr) {
			std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
			throw 1;
		}
		ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (ren == nullptr) {
			std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
			throw 1;
		}

		TTF_Font* fonta = TTF_OpenFont("assets/osreg.ttf", 21);
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
		while(SDL_PollEvent(&e)){}
		bool ex=true;
		bool h1, h2;
		h1=h2=false;
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
			Point p2=drawTextCenter(WWIDTH/2, p.second, "Введите путь для сохранения");
			p2.second+=20;

			font=fonta;

			Point h1p=Point(WWIDTH/2, p2.second+8+p.second);
			if(h1){
				bg=hi;
			}
			Point h1s=drawTextCenter(h1p.first, h1p.second, "OK");
			bg=back;

			Point h2p=Point(WWIDTH/2, h1s.second+6+p2.second+p.second+9);
			if(h2){
				bg=hi;
			}
			Point h2s=drawTextCenter(h2p.first, h2p.second, "Отмена");
			bg=back;

			Point you=drawText(30, h2p.second+h2s.second, text.c_str());
			Point youext=drawTextRight(WWIDTH-30, h2p.second+h2s.second, ".levolution");

			SDL_StartTextInput();
			while (SDL_PollEvent(&e)) {
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
					if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
						ex=false;
						goto evt;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
						ex=false;
						ok=true;
						goto evt;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
						text.pop_back();
						goto evt;
					}
					goto evt;
				}
				if (e.type == SDL_TEXTINPUT){
					text+=e.text.text;
				}
				if (e.type == SDL_MOUSEMOTION) {
					int x = e.button.x;
					int y = e.button.y;
					h1=false;
					h2=false;
					if((x>(h1p.first-(h1s.first/2)))&&(x<(h1p.first+(h1s.first/2)))){
						if((y>h1p.second)&&(y<h1p.second+h1s.second)){
							h1=true;
						}
					}
					if((x>(h2p.first-(h2s.first/2)))&&(x<(h2p.first+(h2s.first/2)))){
						if((y>h2p.second)&&(y<h2p.second+h1s.second)){
							h2=true;
						}
					}
					goto evt;
				}
				if (e.type == SDL_MOUSEBUTTONDOWN) {
					if(h1){
						h1=h2=false;
						ok=true;
						ex=false;
					}
					if(h2){
						h1=h2=false;
						ex=false;
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
		SDL_Delay(200);
		while(SDL_PollEvent(&e)){}
		SDL_DestroyWindow(win);
		TTF_CloseFont(fonta);
		TTF_CloseFont(fontb);
		TTF_CloseFont(fontc);
	}

	std::pair<int, int> draw(int x, int y, SDL_Texture* tex) {
		SDL_Rect pos;
		pos.x = x;
		pos.y = y;
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
		pos.y = y;
		SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
		pos.x-=pos.w;
		SDL_RenderCopy(ren, tex, NULL, &pos);
		return std::pair<int, int>(pos.w, pos.h);
	}
	std::pair<int, int> drawCenter(int x, int y, SDL_Texture* tex) {
		SDL_Rect pos;
		pos.x = x;
		pos.y = y;
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

