#include "mbed.h"
#include "NHD_0216HZ.h"
#include <cstdlib>


InterruptIn right(D2);
InterruptIn left(D3);
InterruptIn up(D4);
InterruptIn down(D5);


bool right_pressed = false;
bool left_pressed = false;
bool up_pressed = false;
bool down_pressed = false;

    const char *first_string = "Hello";
    const char *second_string = "World";
    const char *third_string = "O";
    const char *fourth_string = "W";
    const char *game_over = "   Game Over  ";
    const char *start_again = "Up to Reset";
    const char *erase = " ";
    const int left_bound = 1;
    const int right_bound = 16;
    const int up_bound = 0;
    const int low_bound = 1;

    int obj_x = right_bound;
    int obj_y = 1;
    int user_x = 0;
    int user_y = 0;
    bool end_game = false;






void right_ISR()
{
    right_pressed = true;
}


void left_ISR()
{
    left_pressed = true;
}


void up_ISR()
{
    up_pressed = true;
}


void down_ISR()
{
    down_pressed = true;
}

void clear_screen(){
    const char *blank_line = "                ";
    set_cursor(0, 0);
    print_lcd(blank_line);
    set_cursor(0,1);
    print_lcd(blank_line);
}

//Reset Game
void reset_loop(){
    clear_screen();
    set_cursor(0, 0);
    print_lcd(game_over);
    set_cursor(0, 1);
    print_lcd(start_again);
    obj_x = right_bound;
    obj_y = 1;
    user_x = 0;
    user_y = 0;
}

void reset(){
    clear_screen();
    obj_x = right_bound;
    obj_y = 1;
    user_x = 0;
    user_y = 0;
    set_cursor(0, 0);
    print_lcd(third_string);
}





/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
int main() {
    srand(time(NULL));

    int random_num = rand() % 2;




    init_spi();
    init_lcd();
    init_lcd();
    set_cursor(0, 0);
    print_lcd(third_string);
    right.rise(&right_ISR);
    left.rise(&left_ISR);
    up.rise(&up_ISR);
    down.rise(&down_ISR);

    while(1){
        random_num = rand() % 2;

        if(user_x == obj_x && user_y == obj_y){
            end_game = true;
        }

        if(end_game == true){
            up_pressed = false;
            reset_loop();
            if(up_pressed == true){
    
                end_game = false;
                reset();
            }
        }else{
        
        if(right_pressed == true && user_x < right_bound){
            set_cursor((user_x - 1), user_y);
            print_lcd(erase);
            print_lcd(third_string);
            right_pressed = false;
            user_x++;
            set_cursor(obj_x, obj_y);

        }else{
            right_pressed = false;
        }
        if(left_pressed == true && user_x > left_bound){
            set_cursor((user_x - 1), user_y);
            print_lcd(erase);
            set_cursor((user_x - 2), user_y);
            print_lcd(third_string);
            left_pressed = false;
            user_x--;
            set_cursor(obj_x, obj_y);
        }else{
            left_pressed = false;
        }
        if(up_pressed == true && user_y > 0){
            set_cursor((user_x - 1), user_y);
            print_lcd(erase);
            set_cursor(user_x - 1, (user_y - 1));
            print_lcd(third_string);
            up_pressed = false;
            user_y--;
            set_cursor(obj_x, obj_y);
        }else{
            up_pressed = false;
        }
        if(down_pressed == true && user_y < 1){
            set_cursor((user_x - 1), user_y);
            print_lcd(erase);
            set_cursor(user_x - 1, (user_y + 1));
            print_lcd(third_string);
            
            down_pressed = false;
            user_y++;

            set_cursor(obj_x, obj_y);
        }else{
            down_pressed = false;
        }


        if(obj_x != left_bound && !left_pressed && !right_pressed && !up_pressed && !down_pressed){
            set_cursor((obj_x - 1),obj_y);
            print_lcd(erase);
            set_cursor((obj_x - 2), obj_y);
            print_lcd(fourth_string);
            obj_x--;

            set_cursor(obj_x, obj_y);

        }
        else if(!left_pressed && !right_pressed && !up_pressed && !down_pressed){
            set_cursor((obj_x - 1), obj_y);
            print_lcd(erase);
            obj_y = random_num;
            set_cursor(right_bound,obj_y);
            print_lcd(fourth_string);
            obj_x = right_bound;
            set_cursor(obj_x, obj_y);

        }

        ThisThread::sleep_for(100ms);

        }
                ThisThread::sleep_for(100ms);

    }
}