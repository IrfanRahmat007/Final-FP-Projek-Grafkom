#include <Windows.h>
#include <stdio.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include "glm.h"
GLMmodel *sample;
GLMmodel *mobil;
float ratio;
float angka=15.0f;
float percepatanZ=0.00001f;
float percepatanY=0.00001f;
float percepatanX=0.00002f;
float bump=0.0001f;
int status=0;
float sudut=1.f;
float inc=0.05f;
float pusatx = 0.0, pusaty = 0.0, radius = 0.1;
float PosisiX = 0.02, PosisiY=0.01, PosisiZ=0.f;
float PercepatanSY=0.f, SudutY=0.f, SudutY2=0.1f;
float CameraX=0.f,CameraY=0.f,CameraZ=5.f;
float CameraRX=0.f,CameraRY=0.f,CameraRZ=0.f;
float CameraUX=0.f,CameraUY=1.f,CameraUZ=0.f;
int sequence;
void Init() {
//inisialisasi mode smoot dan texture dari gambar
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 100.0 };
GLfloat mat_emission[] = {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat ambient_color[] = {0.5f, 0.5f, 0.5f,0.f};
GLfloat diffuse_color[] = {1.f, 1.f, 1.f,0.f};
GLfloat specular_color[]= {0.01f, 0.01f, 0.01f, 0.f};
GLfloat light_position[] = { 1.0, 1.0, -1.0, 0.0 };
glClearColor (0.0, 0.0, 0.0, 0.0);
glShadeModel (GL_SMOOTH);

//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//glMaterialfv(GL_FRONT,GL_EMISSION, mat_emission);
//glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_color);
//glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color);
glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);
glLightfv(GL_LIGHT0, GL_SPECULAR, specular_color);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_DEPTH_TEST);
glEnable(GL_TEXTURE_2D);
glEnable(GL_POINT_SMOOTH);
glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
//Perspektif View
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
//blend warna untuk texture dan warna
glEnable(GL_COLOR_MATERIAL);
glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}
void display() {
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(80, ratio,1, 300);
gluLookAt(CameraX,CameraY,CameraZ,CameraRX,CameraRY,CameraRZ,CameraUX,CameraUY,CameraUZ);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
//mode buffer warna dan 3 dimensi
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//warna latar
glClearColor(1, 1, 1, 1);
//inisialisasi identity
glLoadIdentity();
//push matrix object
glPushMatrix();
//load object jika belum di load
if (!sample) {
sample = glmReadOBJ("kota.obj");
if (!sample) exit(0); //gagal = exit
glmUnitize(sample);
}
//jika ingin rotasi, translate, scale bisa di aplikasikan sebelum
//glmDraw(sample, GLM_SMOOTH | GLM_TEXTURE);
/*glTranslatef(angka-5, 0, -angka);
glTranslatef(0,0,-5);
*/

//glRotatef(180,0,0,1);
//glLoadIdentity();
glRotatef(sudut,1,0,0);
if(sequence==0)
{
//    glRotatef(180.f,1,0,0);
    sudut=-90.f;
}
else
{
    if(sudut<=0.f)
    {
        sudut+=0.9f;

    }

}
//glRotatef(90,1,0,0);
//glRotatef(90,0,0,1);
glScalef(3, 3, 3);
//glRotatef(YRot,0,1,0);
//glRotatef(ZRot,0,0,1);
//draw object
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
glColor3ub(255, 255, 255);
glmDraw(sample, GLM_SMOOTH | GLM_COLOR | GLM_TEXTURE);
//pop matrix object
glPopMatrix();
if(mobil)
{
    glLoadIdentity();
    //printf("Status : %d\n",status);
    glScalef(0.3f,0.3f,0.3f);
    glTranslatef(PosisiX,PosisiY, PosisiZ);
    PosisiZ+=percepatanZ;
    PosisiY-=percepatanY;
    PosisiX+=percepatanX;
    glRotatef(SudutY,0,1,0);
    if(PosisiY>-1.f)
    {
        if(status==0)
        {
            percepatanY=0.01f;
        }
    }
    else if(PosisiY<=-1.5f)
    {
        if(bump<=0 )
        {
            percepatanY=0;
            if(status==0)
            {
                status=1;
            }
        }
        else
        {
            percepatanY=-percepatanY+bump;
            bump=bump-0.00005;

        }
    }
    if(status==1)
    {
        if(PosisiZ>-3.f)
        {
            percepatanX=0.f;
            percepatanY=0.f;
            percepatanZ=-0.01f;
        }
        else if(PosisiZ<=-2.f && PosisiZ>-3.1f)
        {
            //printf("Wahaha\n");

            SudutY+=SudutY2;
            if(SudutY>90)
            {
                SudutY2=0;
            }
            else
            {
                SudutY2=3.f;
                percepatanZ=percepatanZ+0.008f;
            }
        }
        else
        {
            status=2;
            percepatanZ=0.f;
        }
    }
    if(status==2)
    {
        if(PosisiX<=-4.f)
        {
            status=3;
            percepatanX=0.f;
        }
        else if(PosisiX<=-3.9f)
        {
            //printf("Wahaha\n");

            SudutY+=SudutY2;
            if(SudutY>180)
            {
                SudutY2=0;
            }
            else
            {
                SudutY2=3.f;
                percepatanX=percepatanX+0.008f;
            }
        }
        else
        {
            percepatanX=-0.01f;
        }
    }
    if(status==3)
    {
        if(PosisiZ>=5.f)
        {
            status=4;
            percepatanZ=0.f;
        }
        else if(PosisiZ>=4.9f)
        {
            //printf("Wahaha\n");

            SudutY+=SudutY2;
            if(SudutY>270)
            {
                SudutY2=0;
            }
            else
            {
                SudutY2=3.f;
                percepatanZ=percepatanZ-0.008f;
            }
        }
        else
        {
            percepatanZ=0.01f;

        }
    }
    if(status==4)
    {
        if(PosisiX>=4.5f)
        {
            SudutY=0;
            status=1;
            percepatanZ=0.01f;
        }
        else if(PosisiX>=4.4f)
        {
            //printf("Wahaha\n");

            SudutY+=SudutY2;
            if(SudutY>360 && SudutY!=0)
            {
                SudutY2=0;
            }
            else
            {
                SudutY2=3.f;
                percepatanX=percepatanX-0.008f;
            }
        }
        else
        {
            percepatanX=0.01f;
        }
    }
    //Kurang Deteksi Lebih dari 18 PosisiZ, Harus belok(Percepetan sudut y ditambah). Percepatan x minus( kiri).
    glmDraw(mobil,  GLM_SMOOTH | GLM_COLOR | GLM_TEXTURE);
}
//kirim ke display dan swap buffer
glFlush();
glutSwapBuffers();
}
//yang ini biar object porposional walaupun window di lebarin atau dikecilin
void reshape(int w, int h){
if (h == 0) h = 1;
ratio = 1.0 * w / h;
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glViewport(0, 0, w, h);
gluPerspective(80, ratio,1, 300);
gluLookAt(CameraX,CameraY,CameraZ,CameraRX,CameraRY,CameraRZ,CameraUX,CameraUY,CameraUZ);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}

void keyboardfunc(unsigned char key, int x, int y)
{
switch(key) {
    case 32:
        // call a function
        inc=(inc==0.f?0.05f:0.f);
        break;
    case 27:
        exit(1);
        break;
    case 13:
        sequence=1;
        break;
    case 'r':
        CameraX=0.f;
        CameraY=0.f;
        CameraZ=5.f;
        break;
    case 'p':
        if (!mobil)
        {
            PosisiX=4.15f;
            PosisiY=1.f;
            PosisiZ=5.f;
            mobil = glmReadOBJ("mobil3.obj");
            glmUnitize(mobil);
            status=0;
        }
    case 'a':
        break;
    case 'd':
    default:
        break;
}
glutPostRedisplay(); /* this redraws the scene without
waiting for the display callback so that any changes appear
instantly */
}

void specialKey(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_DOWN:
            CameraZ+=0.1f;
            CameraRZ+=0.1f;
            break;
        case GLUT_KEY_UP:
            CameraZ-=0.1f;
            CameraRZ-=0.1f;
            break;
        case GLUT_KEY_RIGHT:
            CameraX+=0.1f;
            break;
        case GLUT_KEY_LEFT:
            CameraX-=0.1f;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv){
sudut=0;
sequence=0;
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); //inisialisasi mode detail, 3 dimensi dan RGB
glutInitWindowPosition(300, 1);
glutInitWindowSize(1000, 1000);
glutCreateWindow("TestObject");
glutDisplayFunc(display);
glutIdleFunc(display);
glutKeyboardFunc(keyboardfunc);
glutSpecialFunc(specialKey);
glutReshapeFunc(reshape);
Init(); //init
glutMainLoop();
}
