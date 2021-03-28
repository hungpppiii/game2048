#include "draw.h"
#include "game.h"

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event* event = NULL;

const int cell_num = 4;
const int le = 90;
const int dienTich = (SCREEN_HEIGHT - 2 * le) / cell_num;

//tạo backgroung
void background()
{
    SDL_SetRenderDrawColor(renderer, 153, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 102, 255);
    SDL_Rect filled_rect;
    filled_rect.x = le;
    filled_rect.y = le;
    filled_rect.h = dienTich * cell_num;
    filled_rect.w = dienTich * cell_num;
    SDL_RenderFillRect(renderer, &filled_rect);

    for(int r = 0; r < cell_num; r++){
        for(int c = 0; c < cell_num; c++){
            SDL_Rect filled_rect;
            filled_rect.x = le + dienTich * r;
            filled_rect.y = le + dienTich * c;
            filled_rect.h = dienTich;
            filled_rect.w = dienTich;
            SDL_SetRenderDrawColor(renderer, 0, 0, 204, 255);
            SDL_RenderDrawRect(renderer, &filled_rect);
        }
    }
    //cập nhật thay đổi lên màn hình
    SDL_RenderPresent(renderer);
}


// vẽ ô trong bảng chơi
void drawSquare(const int &so, const int &x, const int &y)
{
    SDL_Texture* image = NULL;
    switch(so)
    {
    case 0:
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 102, 255);
            SDL_Rect filled_rect;
            filled_rect.x = le + dienTich * x + 1;
            filled_rect.y = le + dienTich * y + 1;
            filled_rect.h = dienTich - 2;
            filled_rect.w = dienTich - 2;
            SDL_RenderFillRect(renderer, &filled_rect);
            return;
        }
    case 2:
        {
            image = loadTexture("picture//2.bmp");
            break;
        }
    case 4:
        {
            image = loadTexture("picture//4.bmp");
            break;
        }
    case 8:
        {
            image = loadTexture("picture//8.bmp");
            break;
        }
    case 16:
        {
            image = loadTexture("picture//16.bmp");
            break;
        }
    case 32:
        {
            image = loadTexture("picture//32.bmp");
            break;
        }
    case 64:
        {
            image = loadTexture("picture//64.bmp");
            break;
        }
    case 128:
        {
            image = loadTexture("picture//128.bmp");
            break;
        }
    case 256:
        {
            image = loadTexture("picture//256.bmp");
            break;
        }
    case 512:
        {
            image = loadTexture("picture//512.bmp");
            break;
        }
    case 1024:
        {
            image = loadTexture("picture//1024.bmp");
            break;
        }
    case 2048:
        {
            image = loadTexture("picture//2048.bmp");
            break;
        }
    }
    renderTexture(image, le + dienTich * x + 1, le + dienTich * y + 1, dienTich - 2, dienTich - 2);
    //cập nhật thay đổi lên màn hình
    SDL_DestroyTexture(image);
    SDL_RenderPresent(renderer);
}

// Các hàm chung về khởi tạo và huỷ SDL
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}


//Hàm khởi tạo bút vẽ
void initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

//Hàm giải phóng bút vẽ
void quitSDL()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


//nhận ảnh
SDL_Texture* loadTexture(const std::string &file)
{
	//Khởi tạo là nullptr để tránh lỗi 'dangling pointer'
	SDL_Texture *texture = nullptr;
	//Nạp ảnh từ tên file (với đường dẫn)
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//Nếu không có lỗi, chuyển đổi về dạng texture and và trả về
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Đảm bảo việc chuyển đổi không có lỗi
		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}

// vẽ ảnh vào màn hình
void renderTexture(SDL_Texture *tex, int x, int y, int w, int h)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect filled_rect;
    filled_rect.x = x;
	filled_rect.y = y;
	filled_rect.h = h;
	filled_rect.w = w;
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
    //(ảnh sẽ co dãn cho khớp với kích cỡ mới)
	SDL_RenderCopy(renderer, tex, NULL, &filled_rect);
}
