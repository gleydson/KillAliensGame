#include "global.h"


Boolean rect_is_inside(float x, float y, Rect r){
    if((x >= r.pos.x) && (x <= r.pos.x + r.tam.x))
        if((y >= r.pos.y) && (y <= r.pos.y + r.tam.y))
            return True;
    return False;
}


Boolean rect_intersect(Rect a, Rect b){
    if(rect_is_inside(a.pos.x               , a.pos.y           , b) ||
            rect_is_inside(a.pos.x + a.tam.x, a.pos.y           , b) ||
            rect_is_inside(a.pos.x          , a.pos.y + a.tam.y , b) ||
            rect_is_inside(a.pos.x + a.tam.x, a.pos.y + a.tam.y , b))
        return True;
    return False;
}


Boolean rect_keep_inside_wall(Rect *rect, Par wall_tam){
    Boolean bateu = False;
    if(rect->pos.y < 0){
        rect->pos.y = 0;
        bateu = True;
    }
    if( rect->pos.y > wall_tam.y - rect->tam.y){
        rect->pos.y = wall_tam.y - rect->tam.y;
        bateu = True;
    }
    if(rect->pos.x  < 0){
        rect->pos.x = 0;
        bateu = True;
    }
    if( rect->pos.x > wall_tam.x - rect->tam.x){
        rect->pos.x = wall_tam.x - rect->tam.x;
        bateu = True;
    }
    return bateu;
}
