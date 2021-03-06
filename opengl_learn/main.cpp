#include "includes.h"
#include "load_textures.h"
#include "basik_classes.h"
#include "feel_draw.h"
#include "feel_reaction.h"

void Draw()
{

    glClear(GL_COLOR_BUFFER_BIT);
    if (in_feel)
    {
        draw_feel();
        draw_left_menu();
    }

    glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y)
{
    switch (c)
    {
        case 'q':
            exit(0);
            break;
        case '+':
            scrol*=speed_scrol;
            scrol=min(scrol,float(2.0));
            break;
        case '-':
            if ((feel_size*feel_seg_size-startx)*scrol/speed_scrol>WinWid && (feel_size*feel_seg_size-starty)*scrol/speed_scrol>WinHei)
            {
                scrol/=speed_scrol;
            } else
            {
                if ((feel_size*feel_seg_size-startx)*scrol/speed_scrol<=WinWid)
                {
                    startx-=speed_move;
                    startx=max(float(-left_menu_size)/scrol,startx);
                }

                if ((feel_size*feel_seg_size-starty)*scrol/speed_scrol<=WinHei)
                {
                    starty-=speed_move;
                    starty=max(float(0.0),starty);
                }

                if ((feel_size*feel_seg_size-startx)*scrol/speed_scrol>WinWid && (feel_size*feel_seg_size-starty)*scrol/speed_scrol>WinHei)
                {
                    scrol/=speed_scrol;
                }
            }
            break;
        default:
            break;
    }
}

void skeyboard(int c, int x, int y)
{
    switch (c)
    {
        case GLUT_KEY_RIGHT:
            startx+=speed_move;
            startx=min(startx,feel_seg_size*feel_size-WinWid/scrol);
            break;
        case GLUT_KEY_LEFT:
            startx-=speed_move;
            startx=max(float(-left_menu_size)/scrol,startx);
            break;
        case GLUT_KEY_DOWN:
            starty+=speed_move;
            starty=min(starty,feel_seg_size*feel_size-WinHei/scrol);
            break;
        case GLUT_KEY_UP:
            starty-=speed_move;
            starty=max(float(0.0),starty);
            break;
        default:
            break;
    }
}

void creat_feel()
{
    cout<<WinHei<<'\n';
    for (int i=0;i<feel_size;i++)
        for (int j=0;j<feel_size;j++)
        if (rand()%3)
        feel_background.push_back(Figure(feel_seg_size*i, feel_seg_size*(i+1), feel_seg_size*j, feel_seg_size*(j+1), feel_background_texture[0],1)); else
        feel_background.push_back(Figure(feel_seg_size*i, feel_seg_size*(i+1), feel_seg_size*j, feel_seg_size*(j+1), feel_background_texture[1],1));

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
            object[i][j]=Circle_element(i*feel_seg_size,j*feel_seg_size);

    left_menu_background=Figure(0,left_menu_size,0,WinHei,empty_,1.0);

    for (int i=0;i<7;i++)
        left_menu_vertical[i]=Figure(0,left_menu_size/2.0,100+i*(WinHei-100)/7.0,100+(i+1)*(WinHei-100)/7.0,put,1.0);

    for (int i=0;i<7;i++)
        left_menu_horizontal[i]=Figure(left_menu_size/2.0,left_menu_size,100+i*(WinHei-100)/7.0,100+(i+1)*(WinHei-100)/7.0,put,1.0);
}

void Initialize(int w, int h)
{
    glViewport(0,0,w,h);
    WinWid=w;
    WinHei=h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, WinWid, WinHei, 0.0, 0.f, -1.f);

	glMatrixMode(GL_MODELVIEW);

	creat_feel();

}

void mouse_pressed(int button, int state, int x, int y)
{
    mousex=x;
    mousey=y;
    if (in_feel)
    {
        if (mousex<=left_menu_size)
            left_menu_mouse_pressed(button,state); else
            feel_mouse_pressed(button,state);
    }
}

void mouse_pressed_motion(int x, int y)
{
    mousex=x;
    mousey=y;
}

void mouse_motion(int x, int y)
{
    mousex=x;
    mousey=y;
}



void redraw(int)
{
    glutPostRedisplay();
    glutTimerFunc(30,redraw,0);
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);
    ilSetInteger(IL_KEEP_DXTC_DATA, IL_TRUE);
    ilutEnable(ILUT_GL_AUTODETECT_TEXTURE_TARGET);
    ilutEnable(ILUT_OPENGL_CONV);
    ilutEnable(ILUT_GL_USE_S3TC);


    glutCreateWindow("q");
    load_all();
    glutReshapeFunc(Initialize);
    glutDisplayFunc(Draw);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(skeyboard);
    glutTimerFunc(30, redraw, 0);
    glutMouseFunc(mouse_pressed);
    glutMotionFunc(mouse_pressed_motion);
    glutPassiveMotionFunc(mouse_motion);
    glutFullScreen();
    creat_feel();

	glutMainLoop();

	return 0;
}
