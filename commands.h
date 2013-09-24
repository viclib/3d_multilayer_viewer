#ifndef COMMANDS_H
#define COMMANDS_H
void commands(unsigned char key, int x, int y){
    switch(key){
        case 'a': show_axis = !show_axis; break;
        case 'g': show_grid = !show_grid; break;
        case 'w': show_wave = !show_wave; break;
        case 'u': cam_radius += 0.2; break;
        case 'o': cam_radius -= 0.2; break;
        case 'l': rotate_y += 5; break;
        case 'j': rotate_y -= 5; break;
        case 'k': rotate_x += 5; break;
        case 'i': rotate_x -= 5; break;
    }
}

#endif // COMMANDS_H
