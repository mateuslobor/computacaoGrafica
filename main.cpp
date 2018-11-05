#include <GL/glut.h>  
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;
GLfloat win,r,g,b,angle,x1=0, x2=0,x3=0,x4=-10,posicao_huck_x = 0, posicao_huck_y = 0;
GLint view_w, view_h;
bool ida = true;

char conteudo_texto[20];

void texto(char *string){
        glPushMatrix();
        glRasterPos2f(-win, win-(win*0.08));
        while(*string)
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*string++);
        glPopMatrix();
}
void Desenha(void)
{
        glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
                   
    glClear(GL_COLOR_BUFFER_BIT);
    
       	glBegin(GL_QUADS);//Chegada
    		glColor3f(1.0f,0.0f,1.0f);
        	glVertex2f(-145, 120);
        	glVertex2f(-145, 145);  
			glVertex2f(-120, 145);  
			glVertex2f(-120, 120); 
        glEnd();
        
        glBegin(GL_QUADS);//Obstaculos
    		glColor3f(1.0f,0.0f,0.0f);
        	glVertex2f(-150, 70);
        	glVertex2f(50, 70);  
			glVertex2f(50, 25);  
			glVertex2f(-150, 25);
        glEnd();
        
       	glBegin(GL_QUADS);//Obstaculos
    		glColor3f(1.0f,0.0f,0.0f);
        	glVertex2f(-52, -90);
        	glVertex2f(-52, -45);
        	glVertex2f(150, -45);
        	glVertex2f(150, -90);    
        glEnd();
        
        glPushMatrix();//personagem
        	glTranslatef(posicao_huck_x, posicao_huck_y, 0);
        	//glRotated(angulo_pedra,0, 0 ,1);
       		glBegin(GL_QUADS);
                glColor3f(r,g,b);
        		glVertex2f(120, -145);
        		glVertex2f(120, -120);
        		glVertex2f(145, -120);
        		glVertex2f(145, -145);    
        	glEnd();
        glPopMatrix();
    
        glPushMatrix();
          	glTranslatef(x1, 0, 0);
 			glBegin(GL_QUADS);//Inimigo 1
        		glColor3f(1.0f,1.0f,1.0f);
        		glVertex2f(-145, -40);
        		glVertex2f(-145, -20);
       			glVertex2f(-125, -20);
        		glVertex2f(-125, -40);    
      	    glEnd();
        glPopMatrix();
        
        glPushMatrix();
          	glTranslatef(x2, 0, 0);
 			glBegin(GL_QUADS);//Inimigo 2
        		glColor3f(1.0f,1.0f,1.0f);
        		glVertex2f(120, -10);
        		glVertex2f(120, 10);
       			glVertex2f(140, 10);
        		glVertex2f(140, -10);    
      	    glEnd();
        glPopMatrix();
        
        glPushMatrix();
          	glTranslatef(x3, 0, 0);
 			glBegin(GL_QUADS);//Inimigo 3
        		glColor3f(1.0f,1.0f,1.0f);
        		glVertex2f(-100, 75);
        		glVertex2f(-100, 95);
       			glVertex2f(-80, 95);
        		glVertex2f(-80, 75);    
      	    glEnd();
        glPopMatrix();
        
        glPushMatrix();
          	glTranslatef(x4, 0, 0);
 			glBegin(GL_QUADS);//Inimigo 4
        		glColor3f(1.0f,1.0f,1.0f);
        		glVertex2f(120, 110);
        		glVertex2f(120, 130);
       			glVertex2f(140, 130);
        		glVertex2f(140, 110);    
      	    glEnd();
        glPopMatrix();
        
        glColor3f(1.0f,1.0f,1.0f);
        texto(conteudo_texto);
        
                //glFlush();  // Requisita que o buffer usado para as operações de renderização seja exibido na tela
        glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void inicializa() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Inicializar a cor de fundo da tela
        win=150.0f;
        
       // fprintf(conteudo_texto, "(0),%f", x1);
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{ 
    // Especifica as dimensões da Viewport
    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);
    view_w = w;
    view_h = h;                   

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-win, win, -win, win);
}
/*
bool colisao(float Ax, float Ay, float Acomp, float Aalt, float Bx, float By, float Bcomp, float Balt){
	if (Ax > Bx+Bcomp) return true;
}
*/

void movimenta(){

	if(ida){
		if(x1<250){
			x1+=0.02;
			x2-=0.02;
			x3+=0.02;
			x4-=0.018;
		}
		else ida = false;
	}
	else{
		if(x1>0){
			x1-=0.02;
			x2+=0.02;
			x3-=0.02;
			x4+=0.018;
		}
		else ida =true;
	}
}

bool colisao(float Ax1, float Ax2, float Ay1, float Ay2, float Bx1, float Bx2, float By1, float By2){
	return(!((Ax1>Bx2 || Ax2<Bx1)||(Ay1>By2 || Ay2 <By1)));
}

bool colisaoEmY(float Ay1, float Ax1){
	return (((Ay1>=55 && Ay1<= 102) && (Ax1>=-195))||((Ay1>=169 && Ay1<215) && Ax1 <= -72));
}

bool colisaoEmX(float Ay1, float Ax1){
	return((Ay1<100 && Ay1>30) && Ax1 >= -198||((Ay1>145&& Ay1<215)&& Ax1<=-69));
}



void atualizar(){
        //if(colisao(posicao_huck_x, posicao_huck_y, 25 ,25, posicao_pedra_x+40, posicao_pedra_y+40, 20,20)){
        if(colisao(posicao_huck_x+120, posicao_huck_x+145, posicao_huck_y-145, posicao_huck_y-120, x1-145,x1-125,-40,-20)){
        	posicao_huck_x = 0;
        	posicao_huck_y=0;
		}
		
		else if(colisao(posicao_huck_x+120, posicao_huck_x+145, posicao_huck_y-145, posicao_huck_y-120, x2+120,x2+140,-10,10)){
        	posicao_huck_x = 0;
        	posicao_huck_y=0;
        }
        else if(colisao(posicao_huck_x+120, posicao_huck_x+145, posicao_huck_y-145, posicao_huck_y-120, x3-100,x3-80,75,95)){
        	posicao_huck_x = 0;
        	posicao_huck_y=0;
        }
        else if(colisao(posicao_huck_x+120, posicao_huck_x+145, posicao_huck_y-145, posicao_huck_y-120, x4+120,x4+140,110,130)){
        	posicao_huck_x = 0;
        	posicao_huck_y=0;
        }
        else if(colisao(posicao_huck_x+120, posicao_huck_x+145, posicao_huck_y-145, posicao_huck_y-120, -145,-120,120,145)){
        	posicao_huck_x = 0;
        	posicao_huck_y=0;
        	r=0.0;
        	g=1.0;
        	b=1.0;
		}

	movimenta();

        glutPostRedisplay();
}
void teclado(unsigned char tecla, int x, int y){
        switch(tecla){
                case 'w':
                	if (!colisaoEmY(posicao_huck_y+25,posicao_huck_x)){posicao_huck_y += 3;}  
                        break;
                case 's':
                	if(!colisaoEmY(posicao_huck_y, posicao_huck_x)){posicao_huck_y -= 3;}
        		        break;
                case 'd':
                	if(!colisaoEmX(posicao_huck_y, posicao_huck_x+3)){posicao_huck_x += 3;}
                        break;
                case 'a':
					if(!colisaoEmX(posicao_huck_y, posicao_huck_x-3)){posicao_huck_x -= 3;}
          		        break;
        }
}
/*void TeclasEspeciais(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
                posicao_pedra_y += 1;
    }
    if(key == GLUT_KEY_DOWN) {
          posicao_pedra_y -= 1;
    }
    if(key == GLUT_KEY_LEFT) {
        posicao_pedra_x -= 1;
    }
    if(key == GLUT_KEY_RIGHT) {
        posicao_pedra_x += 1;
    }
    
    glutPostRedisplay();
}*/



int main(int argc, char** argv) {
        
        glutInit(&argc, argv); // Inicializa GLUT
        glutInitDisplayMode(GLUT_DOUBLE); // Habilita double buffer(geralmente utilizado com animação) mas pode ser SINGLE também
    glutInitWindowSize(400,300);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Exemplo Aula");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
        glutKeyboardFunc(teclado);
    //    glutSpecialFunc(TeclasEspeciais); 
        //glutPassiveMotionFunc(cursormouse);
        
        inicializa();
        glutIdleFunc(atualizar);
        
        // initGL(); // OpenGL initialization
           glutMainLoop(); // Chama a máquina de estados do OpenGL e processa todas as mensagens
        
           return 0;
}


