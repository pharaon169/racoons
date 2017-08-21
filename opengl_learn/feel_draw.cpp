#include "feel_draw.h"
#include "basik_classes.h"
void draw_feel()
{
    for (int i=0;i<int(feel_background.size());i++)
        feel_background[i].draw();

    float mn=100000;
    int imn=0;
    int jmn=0;

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        {
            if (object[i][j].f.tex==empty_)
                object[i][j].f.alpha=0.3;
            if (object[i][j].f.dist()<mn)
            {
                imn=i;
                jmn=j;
                mn=object[i][j].f.dist();
            }
        }
    if (object[imn][jmn].f.tex==empty_ && mousex>left_menu_size)
        object[imn][jmn].f.alpha=1.0;

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
            object[i][j].f.draw();

}

void draw_left_menu()
{
    //cout<<left_menu_background.y1<<' '<<left_menu_background.y2<<'\n';
    left_menu_background.draw_state();
    for (int i=0;i<7;i++)
    {
        left_menu_horizontal[i].draw_state();
        left_menu_vertical[i].draw_state();
    }
}
