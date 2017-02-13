//This file is only to test this engine
#include <iostream>
#include "Window/Window.hpp"
#include "Rectangle/Rectangle.hpp"
#include "Image/Image.hpp"
#include "Text/Text.hpp"
#include "Button/Button.hpp"
#include "TextBox/TextBox.hpp"
#include <math.h>

using namespace std;

int aceleration;
int velX, velY;


void updateRectanglePosition(Rectangle* rectangle)
{
	int x = rectangle->getX();
	int y = rectangle->getY();

	velY = velY + aceleration;

	rectangle->setPosition(x+velX, velY+y);

	if(x+velX >= 600-100 || x + velX <= 0)
	{
		velX = velX * -1;
	}
	if((y+ velY >= 400-50  && velY>=0 ) || (y + velY <= 0    &&  velY <=0))
	{
		velY = velY * -1;
	}
	if((y+velY >= 400-50) && velY >=0)
	{
		velY +=25;
	}
}




int main()
{
	bool close = false;
	bool flag = false;
	Window tela("Tela de Teste", 600, 400);
	tela.setDrawColor({150,150,255,255});

	Rectangle rect(100,50);
	rect.setPosition((tela.getWidth()-rect.getWidth())/2, 50);
	rect.setColor(255,120,90);

	Image image = Image();
	image.load(&tela);

	int r=40, g=70, b=120;

	Text text = Text();
	text.setLogs(true);
	text.setWindow(&tela);
	text.setFontSize(40);
	text.setColor({255, 255, 255});
	text.setText("Texto aqui");
	text.update();


	Button btSair = Button();
	btSair.setWindow(&tela);
	btSair.setText("Sair");
	btSair.setPosition(300, 300);

	TextBox txBx = TextBox();
	txBx.setLogs(true);
	txBx.setSize(300, 50);
	txBx.setPosition(200, 100);
	txBx.setColor(255, 255, 255);
	txBx.setTextColor(0,0,0);


	velX = 4;
	velY = 2;

	aceleration = 1;
	flag = true;

	while(!close)
	{
		while(tela.getEvent())
		{
			close = tela.getClose();
			if(rect.getClicked(&tela) || !flag)
			{
				rect.setPosition(tela.getCursorXPosition(), tela.getCursorYPosition());
				flag = false;
			}
			if(rect.getReleased(&tela) && !flag)
			{
				flag = true;
			}

			txBx.listener(&tela);

			close = btSair.listener();
		}

		if(r >= 255)
			r = 0;
		if(g >= 255)
			g=0;
		if(b >=255)
			b=0;

		b++;
		g++;
		r++;
		tela.setDrawColor({(Uint8)r, (Uint8)g, (Uint8)b});

//		SDL_Delay(30);
		if(flag)
			updateRectanglePosition(&rect);


		image.print(&tela);

		rect.printFilled(&tela);
		text.print();
		txBx.print(&tela);
		btSair.print();
		tela.update();
	}
	return 0;
}
