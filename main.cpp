#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<math.h>
using namespace std;
void myinit(){
    cout << "Tekan spasi untuk memulai permainan..." << endl;
//    glClearColor(0.0,0.0,0.0,0.0);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(6.5, 53.5, 6.5, 223.5, -250.0, 250.0);
//    glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, 1.0, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);

    GLfloat light_position_diff[] = { -1.0, 1.0, 1.0, 0.0 };
    GLfloat diffuse_light[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat light_position_spec[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat specular_light[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat ambient_light[] = { 0.9, 0.9, 0.9, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position_diff);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position_spec);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
    GLfloat mat_specular[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_shininess[] = { 10.0 };
    GLfloat mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
//    glShadeModel(GL_FLAT);
//    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    srand(time(NULL));
}

float jarak_X_Canvas_dengan_0 = 6.5 - 0.0 + (53.5-6.5)/2; // untuk Rotasi Canvas
float jarak_Y_Canvas_dengan_0 = 6.5 - 0.0 + (223.5-6.5)/2; //untuk Rotasi Canvas
float sudutXCanvas = 0.0, sudutYCanvas = 0.0, posisiYCanvas = 0.0; //untuk Rotasi Canvas

int xPlayer1=0, yPlayer1=0, xPlayer2 = 0, yPlayer2=0, xObserver = 0, yObserver = 0;
int giliran = 1;
float alpha = 1.0, sudutObserver = 0.0;
bool selesai = false, pertama_klik_V = true;
string mode = "orthogonal", rotasiObserver = "x";
boolean diff = true, spec = true, amb = true;


void balok(float x1, float x2, float y1, float y2, float z1, float z2){
    //depan
    glBegin(GL_POLYGON);

        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x1, y2, z1);
    glEnd();
    //belakang
    glBegin(GL_POLYGON);
        glVertex3f(x2, y1, z2);
        glVertex3f(x1, y1, z2);
        glVertex3f(x1, y2, z2);
        glVertex3f(x2, y2, z2);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1, y2, z1);
        glVertex3f(x1, y2, z2);
        glVertex3f(x1, y1, z2);
    glEnd();
    //kanan
    glBegin(GL_POLYGON);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y1, z2);
        glVertex3f(x2, y2, z2);
        glVertex3f(x2, y2, z1);
    glEnd();
    //atas
    glBegin(GL_POLYGON);
        glVertex3f(x1, y2, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);
    glEnd();
    //bawah
    glBegin(GL_POLYGON);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1, y1, z2);
        glVertex3f(x2, y1, z2);
        glVertex3f(x2, y1, z1);
    glEnd();
}
void prisma(float x1, float x2, float y1, float y2, float z1, float z2){
    //depan
    glBegin(GL_POLYGON);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y1, z1);
        glVertex3f(x1+(x2-x1)/2, y2, z1);
    glEnd();

    //belakang
    glBegin(GL_POLYGON);
        glVertex3f(x2, y1, z2);
        glVertex3f(x1, y1, z2);
        glVertex3f(x1+(x2-x1)/2, y2, z2);
    glEnd();

    //kanan
    glBegin(GL_POLYGON);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y1, z2);
        glVertex3f(x1+(x2-x1)/2, y2, z2);
        glVertex3f(x1+(x2-x1)/2, y2, z1);
    glEnd();

    //kiri
    glBegin(GL_POLYGON);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1+(x2-x1)/2, y2, z1);
        glVertex3f(x1+(x2-x1)/2, y2, z2);
        glVertex3f(x1, y1, z2);
    glEnd();

    //bawah
    glBegin(GL_POLYGON);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1, y1, z2);
        glVertex3f(x2, y1, z2);
        glVertex3f(x2, y1, z1);
    glEnd();
}
void prismaUlar(float xBawah, float xAtas, float yKiri, float yKanan, float z1, float z2){
    //depan
    glBegin(GL_POLYGON);
        glVertex3f(xBawah, yKiri, z1);
        glVertex3f(xBawah+2, yKiri, z1);
        glVertex3f(xAtas, yKanan, z1);
        glVertex3f(xAtas-2, yKanan, z1);
    glEnd();

    //belakang
    glBegin(GL_POLYGON);
        glVertex3f(xBawah, yKiri, z2);
        glVertex3f(xAtas-2, yKanan, z2);
        glVertex3f(xAtas, yKanan, z2);
        glVertex3f(xBawah+2, yKiri, z2);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
        glVertex3f(xBawah, yKiri, z1);
        glVertex3f(xAtas-2, yKanan, z1);
        glVertex3f(xAtas-2, yKanan, z2);
        glVertex3f(xBawah, yKiri, z2);
    glEnd();

    //kanan
    glBegin(GL_POLYGON);
        glVertex3f(xBawah+2, yKiri, z1);
        glVertex3f(xBawah+2, yKiri, z2);
        glVertex3f(xAtas, yKanan, z2);
        glVertex3f(xAtas, yKanan, z1);
    glEnd();

    //atas
    glBegin(GL_POLYGON);
        glVertex3f(xAtas, yKanan, z1);
        glVertex3f(xAtas, yKanan, z2);
        glVertex3f(xAtas-2, yKanan, z2);
        glVertex3f(xAtas-2, yKanan, z1);
    glEnd();

    //bawah
    glBegin(GL_POLYGON);
        glVertex3f(xBawah+2, yKiri, z1);
        glVertex3f(xBawah, yKiri, z1);
        glVertex3f(xBawah, yKiri, z2);
        glVertex3f(xBawah+2, yKiri, z2);
    glEnd();
}
void observer(){
    glColor3f(0.8, 0.8, 0.8);

    glPushMatrix();
    glTranslated(12.0+xObserver, 12.0+yObserver, 3.1);
     if (rotasiObserver == "z"){
        glRotatef(sudutObserver, 0.0, 0.0, 1.0);
    }else if (rotasiObserver == "y"){
        glRotatef(sudutObserver, 0.0, 1.0, 0.0);
    }else{
        glRotatef(sudutObserver, 1.0, 0.0, 0.0);
    }
    glTranslated(-(12.0+xObserver), -(12.0+yObserver), -3.1);
    glTranslated(12.0+xObserver, 12.0+yObserver, 3.1);
    glutSolidCone(2, 3, 10, 20);
    glPopMatrix();
}
void player(){
    glColor3f(1.0,1.0,0.0);
    //Prisma Player 1
    prisma(14+xPlayer1, 18+xPlayer1, 15+yPlayer1, 18+yPlayer1, 6.0, 3.1 );

    glColor3f(0.0,1.0,0.0);
    //Kubus Player 2
    balok(15+xPlayer2, 18+xPlayer2, 11.5+yPlayer2, 14.5+yPlayer2, 6.0, 3.1);
}
void tangga(float x1, float y1, float x2, float y2, float z1, float z2, float sudut){
//    glColor3f(0.1,0.2,0.1);
    glColor3f(0.8,0.1,0.9);
    float jarak_x_dengan_0 = x1 - 0.0 + (x2-x1)/2;
    float jarak_y_dengan_0 = y1 - 0.0 + 5;

    glPushMatrix();
    glTranslated(jarak_x_dengan_0, jarak_y_dengan_0, 0);
    glRotated(sudut, 0, 0, 1);
    glTranslated(-jarak_x_dengan_0, -jarak_y_dengan_0, 0);

    balok(x1+2, x1+3, y1+5.5, y2-5.5, z1, z2 );
    balok(x2-3 ,x2-2, y1+5.5,  y2-5.5, z1, z2);
    for (int i=4; i<=(y2-y1-15); i+=5){
        balok(x1+2, x2-2, y1+5.5+i,  y1+5.5+i+1, z1, z2);
    }

    glPopMatrix();
}
void posTangga(){
    tangga(20, 140, 30, 190,3.0, 2.1, 0);
    tangga(40, 70, 50, 125, 3.0, 2.1, 45);
    tangga(40, 30, 50, 70, 3.0, 2.1, 90);
}
void ular(){
    //ULAR 1
   //glColor3f(0.1,0.1, 0.1);
   glColor3f(0.8,0.1,0.9);
   prismaUlar(22.0, 14.0, 54.0, 64.0, 3.0, 2.1);
   balok(22.0, 24.0, 44.0, 54.0, 3.0, 2.1);
   balok(22.0, 34.0, 44.0, 46.0, 3.0, 2.1);

   //ULAR 2
   prismaUlar(32.0, 44.0, 134.0, 144.0, 3.0, 2.1);
   balok(32.0, 34.0, 124.0, 134.0, 3.0, 2.1);
   prismaUlar(22.0, 34.0, 114.0, 124.0, 3.0, 2.1);

   //ULAR 3
   balok(32.0, 34.0, 204.0, 214.0, 3.0, 2.1);
   balok(24.0, 34.0, 204.0, 206.0, 3.0, 2.1);
   prismaUlar(14.0, 26.0, 196.0, 206.0, 3.0, 2.1);
}
void angka1(int x1, int y1){
    glColor3f (1.0, 0.0, 0.0);
    balok( x1, (x1+1), y1, (y1+5), 2.0, 0.2);
}
void angka2(int x1, int y1){
    float y2=y1+1;
    glColor3f (1.0, 0.0, 0.0);
    for (int i=1; i <= 3; i++){
        balok(x1, (x1+3), y1, (y1+1), 2.0, 0.2);
        y1+=2;
    }
    for (int i=1; i<=2; i++){
        balok(x1, (x1+1), y2, (y2+1), 2.0, 0.2);
        x1+=2;y2+=2;
    }
}
void posAngka(){
    angka1(18.0,13.0);
    angka2(26.0,13.0);
    angka1(28.0,33.0);
    angka1(36.0,33.0);
    angka1(38.0,33.0);
    angka1(44.0,33.0);
    angka2(46.0,33.0);
    angka1(48.0,43.0);
    angka1(38.0,43.0);
    angka1(28.0,43.0);
    angka1(18.0,43.0);
    angka1(18.0,43.0);
    angka1(18.0,53.0);
    angka1(28.0,53.0);
    angka1(38.0,53.0);
    angka2(46.0,53.0);
    angka2(44.0,63.0);
    angka1(48.0,63.0);
    angka2(32.0,63.0);
    angka2(36.0,63.0);
    angka2(26.0,63.0);
    angka2(16.0,63.0);
    angka2(16.0,73.0);
    angka2(26.0,73.0);
    angka2(36.0,73.0);
    angka2(46.0,73.0);
    angka2(46.0,83.0);
    angka1(28.0,83.0);
    angka2(16.0,83.0);
    angka1(18.0,113.0);
    angka2(26.0,113.0);
    angka1(38.0,133.0);
    angka2(46.0,133.0);
    angka1(48.0,163.0);
    angka2(36.0,163.0);
    angka1(28.0,183.0);
    angka2(16.0,183.0);
    angka1(18.0,213.0);
    angka2(26.0,213.0);
}
void pagar(){
    glColor3f (0.0, 0.7, 0.0);
    //Pagar Luar
    balok(9.0, 10.0, 9.0, 221.0, 2.0, -3.0);//kiri
    balok(9.0, 51.0, 9.0, 10.0, 2.0, -3.0);//bawah
    balok(50.0, 51.0, 9.0, 221.0, 2.0, -3.0); //kanan
    balok(9.0, 51.0, 220.0, 221.0, 2.0, -3.0);//atas

    //Pagar Dalam
    float x1=9.0,x2=51.0,y1=19.5,y2=20.5;
    for (int i=0; i<20; i+=1){
        if (i%2==0){
            balok(x1, (x2-11.0), y1, y2, 2.0, 0.2 );
        }else{
            balok((x1+11.0), x2, y1, y2, 2.0, 0.2);
        }
        y1+=10;y2+=10;
    }
}
void petak(){
    for (int x=10 ; x <=40 ; x+=10){
        for(int y=10 ; y<=210 ; y+=10){
            if ( (x/10)%2 == (y/10)%2 ){
                glColor4f (1.0, 1.0, 1.0, alpha);
            }else{
                glColor4f (0.0, 0.0, 1.0, alpha);
            }
            balok(x,(x+10), y, (y+10), 0.0, -3.0);
        }
    }
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    if(mode == "orthogonal"){
        glLoadIdentity();
    }else if (mode == "isometric"){
        glTranslated(jarak_X_Canvas_dengan_0, jarak_Y_Canvas_dengan_0, 0.0);
        glRotated(sudutXCanvas, 1, 0, 0);
        glRotated(sudutYCanvas, 0, 1, 0);
        glTranslated(-jarak_X_Canvas_dengan_0, -jarak_Y_Canvas_dengan_0, 0.0);
        glTranslated(0.0, posisiYCanvas, 0.0);
    }
    posAngka();
    posTangga();
    ular();
    player();
    observer();
    pagar();
    petak();
    glPopMatrix();


    glutSwapBuffers();
}
void akibatUlar(){
    if ( (yPlayer1==200) && (xPlayer1==20) ){
        xPlayer1=0;yPlayer1=180;
        cout << "Player 1 mendapat ular 3 " << endl;
    }
    if ( (yPlayer1==130) && (xPlayer1==30) ){
        xPlayer1=10;yPlayer1=100;
        cout << "Player 1 mendapat ular 2 " << endl;
    }
    if ( (yPlayer1==50) && (xPlayer1==0) ){
        xPlayer1=20;yPlayer1=30;
        cout << "Player 1 mendapat ular 1 " << endl;
    }
    if ( (yPlayer2==200) && (xPlayer2==20) ){
        xPlayer2=0;yPlayer2=180;
        cout << "Player 2 mendapat ular 3 " << endl;
    }
    if ( (yPlayer2==130) && (xPlayer2==30) ){
        xPlayer2=10;yPlayer2=100;
        cout << "Player 2 mendapat ular 2 " << endl;
    }
    if ( (yPlayer2==50) && (xPlayer2==0) ){
        xPlayer2=20;yPlayer2=30;
        cout << "Player 2 mendapat ular 1 " << endl;
    }

}
void akibatTangga(){
    if ( (yPlayer1==20) && (xPlayer1==0) ){
        xPlayer1=30;yPlayer1=20;
        cout << "Player 1 mendapat tangga 1 " << endl;
    }
    if ( (yPlayer1==60) && (xPlayer1==30) ){
        xPlayer1=0;yPlayer1=90;
        cout << "Player 1 mendapat tangga 2 " << endl;
    }
    if ( (yPlayer1==130) && (xPlayer1==10) ){
        xPlayer1=10;yPlayer1=170;
        cout << "Player 1 mendapat tangga 3" << endl;
    }
    if ( (yPlayer2==20) && (xPlayer2==0) ){
        xPlayer2=30;yPlayer2=20;
        cout << "Player 2 mendapat tangga 1 " << endl;
    }
    if ( (yPlayer2==60) && (xPlayer2==30) ){
        xPlayer2=0;yPlayer2=90;
        cout << "Player 2 mendapat tangga 2 " << endl;
    }
    if ( (yPlayer2==130) && (xPlayer2==10) ){
        xPlayer2=10;yPlayer2=170;
        cout << "Player 2 mendapat tangga 3 " << endl;
    }
}
void aturanGerakPlayer(){
    int randAngka = rand() % 6 + 1;
    if(giliran == 1){
        giliran = 2;
        cout << "Player 1 mendapat angka : " << randAngka << endl;
        if((yPlayer1/10)%2==0){
            xPlayer1 = xPlayer1 + (randAngka*10);
            if (xPlayer1 > 30){
                yPlayer1 = yPlayer1 + 10;
                int pemindahX = 2*(xPlayer1 - 30) - 10;
                xPlayer1= xPlayer1 - pemindahX;
            }
            if (xPlayer1 < 0){
                yPlayer1 = yPlayer1 + 10;
                int pemindahX = 2*xPlayer1 * (-1) - 10;
                xPlayer1= xPlayer1 + pemindahX;
            }
        }else{
            xPlayer1 = xPlayer1 - (randAngka*10);
            if (xPlayer1 < 0){
                yPlayer1 = yPlayer1 + 10;
                int pemindahX = 2*xPlayer1 * (-1) - 10;
                xPlayer1= xPlayer1 + pemindahX;
            }
            if (xPlayer1 > 30){
                yPlayer1 = yPlayer1 + 10;
                int pemindahX = 2*(xPlayer1 - 30) - 10;
                xPlayer1= xPlayer1 - pemindahX;
            }
        }
        if (xPlayer1==30 && yPlayer1==200){
            selesai=true;
            cout << "Player 1 Menang!!" << endl;
        }
        if (yPlayer1>200){
            yPlayer1=200;
            xPlayer1=30;
            selesai=true;
            cout << "Player 1 Menang!!" << endl;

        }
        akibatUlar();
        akibatTangga();
    }else{
        giliran = 1;
        cout << "Player 2 mendapat angka : " << randAngka << endl;
        if((yPlayer2/10)%2==0){
            xPlayer2 = xPlayer2 + (randAngka*10);
            if (xPlayer2 > 30){
                yPlayer2 = yPlayer2 + 10;
                int pemindahX = 2*(xPlayer2 - 30) - 10;
                xPlayer2 = xPlayer2 - pemindahX;
            }
            if (xPlayer2 < 0){
                yPlayer2 = yPlayer2 + 10;
                int pemindahX = 2*xPlayer2 * (-1) - 10;
                xPlayer2 = xPlayer2 + pemindahX;
            }
        }else{
            xPlayer2 = xPlayer2 - (randAngka*10);
            if (xPlayer2 < 0){
                yPlayer2 = yPlayer2 + 10;
                int pemindahX = 2*xPlayer2 * (-1) - 10;
                xPlayer2 = xPlayer2 + pemindahX;
            }
            if (xPlayer2 > 30){
                yPlayer2 = yPlayer2 + 10;
                int pemindahX = 2*(xPlayer2 - 30) - 10;
                xPlayer2 = xPlayer2 - pemindahX;
            }
        }
        if (xPlayer2==30 && yPlayer2==200){
            selesai=true;
            cout << "Player 2 Menang!!" << endl;
        }
        if (yPlayer2>200){
            yPlayer2=200;
            xPlayer2=30;
            selesai=true;
            cout << "Player 2 Menang!!" << endl;
        }
        akibatUlar();
        akibatTangga();
    }
}
void myidle(void){
    sudutObserver +=0.05;
    if (sudutObserver > 360.0)
    sudutObserver = sudutObserver - 360.0;
    glutPostRedisplay();
}
void input(unsigned char key, int x, int y){
    if (key==' '){
        if (selesai==false){
            aturanGerakPlayer();
        }
    }
    if (key=='w' || key=='W'){
        if (yObserver<206){
            yObserver+=1;
        }
    }
    if (key=='s' || key=='S'){
        if (yObserver>0){
            yObserver-=1;
        }
    }
    if (key=='d' || key=='D'){
        if (xObserver<36){
            xObserver+=1;
        }
    }
    if (key=='a' || key=='A'){
        if (xObserver>0){
            xObserver-=1;
        }
    }
    if (key=='v' || key=='V'){
        if (mode == "orthogonal"){
            if (pertama_klik_V == true){
                pertama_klik_V = false;
                glPushMatrix();
                sudutXCanvas-=20;
                posisiYCanvas-=5.0;
                mode = "isometric";
                alpha = 0.3;
                glutIdleFunc(myidle);
            }else{
                glPopMatrix();
                mode = "isometric";
                alpha = 0.3;
                glutIdleFunc(myidle);
            }
        }else if (mode == "isometric"){
            glPushMatrix();
            mode = "orthogonal";
            alpha = 1.0;
            glutIdleFunc(NULL);
            glLoadIdentity();
        }
    }
    if( mode == "isometric"){
        if(key=='i' || key=='I'){
            sudutXCanvas-=2;
        }
        if(key=='k' || key=='K'){
           sudutXCanvas+=2;
        }
        if(key=='l' || key=='L'){
            sudutYCanvas+=2;
        }
        if(key=='j' || key=='J'){
            sudutYCanvas-=2;
        }
    }

    if (key=='1'){
        if (amb == true){
            GLfloat ambient_light[] = { 0.3, 0.3, 0.3, 1.0 };
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);
            amb = false;
        }
        else{
            GLfloat ambient_light[] = { 0.9, 0.9, 0.9, 1.0 };
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);
            amb = true;
        }
    }
    if (key=='2'){
        if (diff == true){
            glDisable(GL_LIGHT0);
            diff = false;
        }
        else{
            glEnable(GL_LIGHT0);
            diff = true;
        }
    }
        if (key=='3'){
        if (spec == true){
            glDisable(GL_LIGHT1);
            spec = false;
        }
        else{
            glEnable(GL_LIGHT1);
            spec = true;
        }
    }
    glutPostRedisplay();
}
void mymouse(int button, int state, int x, int y){
    switch (button){
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN){
            rotasiObserver = "x";
        }
        break;
    case GLUT_MIDDLE_BUTTON:
        if(state == GLUT_DOWN){
            rotasiObserver = "y";
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if(state == GLUT_DOWN){
            rotasiObserver = "z";
        }
        break;
    }
}
int main(int argc, char* argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(150,690);
    glutInitWindowPosition(600,0);
    glutCreateWindow("ULAR TANGGA");
    glutDisplayFunc(display);
    glutKeyboardFunc(input);
    glutMouseFunc(mymouse);
    myinit();
    glutMainLoop();
    return 0;
}
