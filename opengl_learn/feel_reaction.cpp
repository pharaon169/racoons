#include "feel_reaction.h"

void feel_mouse_pressed(int button, int state)
{
    if (something_taken && state==GLUT_UP && button==GLUT_LEFT_BUTTON)
    {
        for (int i=1;i<feel_size;i++)
            for (int j=1;j<feel_size;j++)
            if (object[i][j].f.tex==empty_ && object[i][j].f.alpha==1.0)
            {
                object[i][j].f.tex=taken;
                object[i][j].f.x1=i*feel_seg_size-feel_seg_size/2.0;
                object[i][j].f.x2=i*feel_seg_size+feel_seg_size/2.0;
                object[i][j].f.y1=j*feel_seg_size-feel_seg_size/2.0;
                object[i][j].f.y2=j*feel_seg_size+feel_seg_size/2.0;
                object[i][j].f.alpha=1.0;
            }

        something_taken=0;
    }
}

void left_menu_mouse_pressed(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        for (int i=0;i<7;i++)
            if (left_menu_horizontal[i].in())
            {
                something_taken=1;
                taken=left_menu_horizontal[i].tex;
            }
        for (int i=0;i<7;i++)
            if (left_menu_vertical[i].in())
            {
                something_taken=1;
                taken=left_menu_vertical[i].tex;
            }
    } else
    if (state==GLUT_UP)
    {
        something_taken=0;
    }
}
