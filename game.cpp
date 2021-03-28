#include "game.h"
#include "draw.h"

using namespace std;

int mangInRa[4][4] = {0};
int diem = 0;

void startGame()
{
    while(true)
    {
        //khi bảng đầy thì kiểm tra xem đã end game chưa
        if(viTriTrong() == 0){
            if(endGame()){
                cout << "game over!!!";
                return;
            }
        }
        SDL_Event e;
        // kiểm tra xem có sự kiện bàn phím không
        while(SDL_PollEvent(&e) != 0)
        {

            if(e.type == SDL_QUIT){
                return;
            }
            else if(e.type == SDL_KEYDOWN){
                bool check = false;
                switch(e.key.keysym.sym)
                {
                case SDLK_UP:
                    {
                        left(check);
                        drawTable(1);
                        break;
                    }
                case SDLK_DOWN:
                    {
                        right(check);
                        drawTable(2);
                        break;
                    }
                case SDLK_RIGHT:
                    {
                        down(check);
                        drawTable(3);
                        break;
                    }
                    break;;
                case SDLK_LEFT:
                    {
                        up(check);
                        drawTable(4);
                        break;
                    }
                }
                // check xem bảng có thay đổi sau khi nhấn phím
                // thay đổi thì tạo thêm số
                if(check){
                    khoiTaoThemSo();
                }
            }
        }
    }
}


// kiểm tra game kết thúc chưa
bool endGame()
{
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if((mangInRa[i][j] == mangInRa[i][j+1]) || (mangInRa[i][j] == mangInRa[i+1][j])){
                return 0;
            }
        }
        if((mangInRa[i][3] == mangInRa[i+1][3]) || (mangInRa[3][i] == mangInRa[3][i+1])){
            return 0;
        }
    }
    return 1;
}


//++++++++++++++++++++++++++++++++++++++++
void left(bool &check)
{
    for(int i=0; i<4; i++){
        int j = 0;
        hamLeft_Right(i, j, 1, check);
    }
}

void right(bool &check)
{
    for(int i=0; i<4; i++){
        int j = 3;
        hamLeft_Right(i, j, -1, check);
    }
}

void up(bool &check)
{
    for(int j=0; j<4; j++){
        int i = 0;
        hamUp_Down(i, j, 1, check);
    }
}

void down(bool &check)
{
    for(int j=0; j<4; j++){
        int i = 3;
        hamUp_Down(i, j, -1, check);
    }
}

//**************************************************

// thuc hien lenh sang trai hoạc phải
void hamLeft_Right(const int row, const int col, const int x, bool &check)
{
    int n;
    if(x == 1) n = 3;
    else n = 0;
    for(int j=col+x; (j*x)<=n; j=j+x){
        //kiểm tra xem ô này có khác 0
        if(mangInRa[row][col]){
            //2 ô gần nhất có giá trị bằng nhau và khác 0 thì cộng lại
            if(mangInRa[row][col] == mangInRa[row][j]){
            mangInRa[row][col] = mangInRa[row][col] * 2;
            diem += mangInRa[row][col];
            check = true;
            mangInRa[row][j] = 0;
            hamLeft_Right(row, col+x, x, check);
            break;
            }//kiểm tra hết với các ô phía sau(ko thay đổi) thì kiểm tra ô tiếp theo
            else if(mangInRa[row][j] != 0){
                hamLeft_Right(row, col+x, x, check);
                break;
            }
        }//ô này = 0 thì đổi chỗ ô này với ô gần nhất khác 0
        else {
            if(mangInRa[row][j]){
                mangInRa[row][col] = mangInRa[row][j];
                mangInRa[row][j] = 0;
                check = true;
                hamLeft_Right(row, col, x, check);
                break;
            }
        }
    }
}

//thuc hien lenh len hoặc xuống
void hamUp_Down(const int row, const int col, const int x, bool &check)
{
    int n;
    if(x == 1) n = 3;
    else n = 0;
    for(int i=row+x; (i*x)<=n; i=i+x){
        if(mangInRa[row][col]){
            if(mangInRa[row][col] == mangInRa[i][col]){
            mangInRa[row][col] = mangInRa[row][col] * 2;
            diem += mangInRa[row][col];
            check = true;
            mangInRa[i][col] = 0;
            hamUp_Down(row+x, col, x, check);
            break;
            }
            else if(mangInRa[i][col] != 0){
                hamUp_Down(row+x, col, x, check);
                break;
            }
        }
        else {
            if(mangInRa[i][col]){
                mangInRa[row][col] = mangInRa[i][col];
                mangInRa[i][col] = 0;
                check = true;
                hamUp_Down(row, col, x, check);
                break;
            }
        }
    }
}

// vẽ lại bảng sau khi nhấn phím
void drawTable(int dk)
{
    dk = 1;
    if(dk == 1){
        for(int j = 0; j < 4; j++){
            for(int i = 0; i < 4; i++){
                drawSquare(mangInRa[i][j], i, j);
            }
        }
    }
    else if(dk == 2) {
        for(int j = 3; j >= 0; j--){
            for(int i = 0; i < 4; i++){
                drawSquare(mangInRa[i][j], i, j);
            }
        }
    }
    else if(dk == 3) {
        for(int i = 3; i >= 0; i--){
            for(int j = 0; j < 4; j++){
                drawSquare(mangInRa[i][j], i, j);
            }
        }
    }
    else {
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                drawSquare(mangInRa[i][j], i, j);
            }
        }
    }
}


//khởi tạo 2 giá trị ban đầu của mảng
void khoiTaoBanDau()
{

    khoiTaoThemSo();
    khoiTaoThemSo();

}

//tìm các vị trí trống trong mảng
bool viTriTrong()
{
    int dem = 0;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++){
            if(!mangInRa[i][j]){
                return true;
            }
        }
    }
    return false;
}
//khơi tạo thêm gia trị cho mang
void khoiTaoThemSo()
{
    //srand((int)time(NULL));
    if(viTriTrong()){
        int i, j;
        do{
            i = rand() % 4;
            j = rand() % 4;
        } while(mangInRa[i][j] != 0);
        mangInRa[i][j] = (rand() % 2 + 1) * 2;
        drawSquare(mangInRa[i][j], i, j);
    }
}
