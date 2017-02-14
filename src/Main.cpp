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


int main()
{
	bool close = false;

	Window tela("Tela de Teste", 600, 400);
	tela.setDrawColor({150,150,255,255});

	tela.setResizable(true);

	Image image = Image();
	image.load(&tela);


	Text text = Text();
	text.setWindow(&tela);
	text.setFontSize(40);
	text.setColor({255, 255, 255});
	text.setText("Texto aqui");
	text.update();


	Button btSair = Button();
	btSair.setWindow(&tela);
	btSair.setText("Sair");
	btSair.setPosition(300, 300);
	btSair.setOutsideColor(52, 73, 94);
	btSair.setInsideColor(44, 62, 80);
	btSair.setClickColor(127, 140, 141);
	btSair.setTextColor(250,250,250);

	TextBox txBx = TextBox();
	txBx.setSize(300, 50);
	txBx.setPosition(200, 100);
	txBx.setColor(255, 255, 255);
	txBx.setTextColor(0,0,0);

	TextBox tbGeral = TextBox();
	tbGeral.setSize(400, 50);
	tbGeral.setPosition(100, 10);
	tbGeral.setColor(244, 244, 244);
	tbGeral.setTextColor(3, 3, 3);


	while(!close)
	{
		while(tela.getEvent())
		{
			close = tela.getClose();
		

			txBx.listener(&tela);
			tbGeral.listener(&tela);

			close = btSair.listener();
		}


		SDL_Delay(30);


		image.print(&tela);

		text.print();
		txBx.print(&tela);
		tbGeral.print(&tela);
		btSair.print();
		tela.update();
	}
	return 0;
}
