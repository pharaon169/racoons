#include "basik_classes.h"

float WinWid=0.0;
float WinHei=0.0;

float speed_scrol=1.05;
float speed_move=20.0;
float startx=0,starty=0;
float feel_seg_size=100;
int feel_size=30;
float scrol=1.0;
float mousex=0.0, mousey=0.0;
bool in_feel=1;
float left_menu_size=350;

GLuint feel_background_texture[2];
GLuint empty_;
vector<Figure> feel_background;
Figure left_menu_background;
Circle_element object[30][30];

Figure left_menu_vertical[9];
Figure left_menu_horizontal[9];

float sqr(float a)
{
    return(a*a);
}

float dist_(float x1, float y1, float x2, float y2)
{
    return(sqrt(sqr(x1-x2)+sqr(y1-y2)));
}

Figure :: Figure()
{

}

Figure :: Figure(float x1_, float x2_, float y1_, float y2_, GLuint tex_, float alpha_)
{
    x1=x1_;
    x2=x2_;
    y1=y1_;
    y2=y2_;
    tex=tex_;
    alpha=alpha_;
}

void Figure :: draw()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
        glPushMatrix();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1, 1, 1, alpha);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f((x1-startx)*scrol, (y1-starty)*scrol);
            glTexCoord2f(1, 0); glVertex2f((x2-startx)*scrol, (y1-starty)*scrol);
            glTexCoord2f(1, 1); glVertex2f((x2-startx)*scrol, (y2-starty)*scrol);
            glTexCoord2f(0, 1); glVertex2f((x1-startx)*scrol, (y2-starty)*scrol);
        glEnd();

        glDisable(GL_BLEND);

        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void Figure :: draw_state()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
        glPushMatrix();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1, 1, 1, alpha);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(x1, y1);
            glTexCoord2f(1, 0); glVertex2f(x2, y1);
            glTexCoord2f(1, 1); glVertex2f(x2, y2);
            glTexCoord2f(0, 1); glVertex2f(x1, y2);
        glEnd();

        glDisable(GL_BLEND);

        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

float Figure :: dist()
{
    float x1_=(x1-startx)*scrol;
    float x2_=(x2-startx)*scrol;
    float y1_=(y1-starty)*scrol;
    float y2_=(y2-starty)*scrol;

    float res=100000;

    res=min(res,dist_(x1_,y1_,mousex,mousey));
    res=min(res,dist_(x1_,y2_,mousex,mousey));
    res=min(res,dist_(x2_,y1_,mousex,mousey));
    res=min(res,dist_(x2_,y2_,mousex,mousey));
    return(res);
}

Circle_element :: Circle_element()
{

}

Circle_element :: Circle_element(float x, float y)
{
    f=Figure(x-20.0,x+20.0,y-20.0, y+20.0, empty_, 0.3);
    R=0.0;
    U=0.0;
}

Circle_element :: Circle_element(Figure f_, float R_, float U_)
{
    f=f_;
    R=R_;
    U=U_;
}
