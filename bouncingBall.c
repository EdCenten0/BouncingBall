#include "terminal_draw.h"
#include "stdbool.h"

typedef struct{
 int x;
 int y;
} Position;

typedef struct{
    Position position;
    char character;
    Color color;
} Ball;


void draw_hline(int x, int y, int length, char c, Color color) {
    for (int i = 0; i < length; i++){
        draw_char(x + i, y, c, color);
    }
}

void draw_vline(int x, int y, int length, char c, Color color){
    for (int i = 0; i < length; i++)
    {
        draw_char(x, y + i, c, color);
    }
}

void draw_ball(Ball *ball ){
    int x = ball->position.x;
    int y = ball->position.y;
    char c = ball->character;
    Color color = ball->color;

    draw_hline(x, y, 3, c, color);
    draw_hline(x - 1, y + 1, 5, c, color);
    draw_hline(x, y + 2, 3, c, color);
}

bool isCollidingX(Ball *ball, int width){
    if((ball->position.x) + 3 >= width || ball->position.x <= 0){
        return true;
    }
        return false;
}

bool isCollidingY(Ball *ball, int height){
    if((ball->position.y) + 3 >= height || ball->position.y <= 0){
        return true;
    }
        return false;
    
}

// it changes to the next character
void change_character(Ball *ball){
    if(ball->character == 'O'){
        ball->character = 'X';
    }else{
        ball->character = 'O';
    }
}

// it changes to the next color in the Color enum
void change_color(Ball *ball){
    if(ball->color >= 30 && ball -> color < 37){
        ball->color = ball -> color + 1;
    }else{
        ball->color = 30;
    }
}

int main(){

    int width, height;
    get_screen_size(&width, &height);

    Ball ball;
    ball.position.x = width/2;
    ball.position.y = height/2;
    ball.character = 'O';
    ball.color = BLUE;

    int dx = 1;
    int dy = 1;

    
    while(true){
        clear_screen();
        draw_hline(0,0,width,'-', BLUE);
        draw_hline(0,height - 1,width,'-', BLUE);

        draw_vline(0,0,height,'|', RED);
        draw_vline(width - 1,0,height,'|', RED);

        draw_ball(&ball);
        
        ball.position.x += dx;
        ball.position.y += dy;

        if(isCollidingX(&ball, width)){
            dx = -dx;
            change_character(&ball);
        }
        if(isCollidingY(&ball, height)){
            dy = -dy;
            change_color(&ball);
        }


        sleep_ms(10);
    }

    return 0;
}